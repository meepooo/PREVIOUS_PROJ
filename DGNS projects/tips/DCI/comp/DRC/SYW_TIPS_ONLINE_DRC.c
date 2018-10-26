/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V3.0.00
����ϵͳ:AIX5.3
�ļ�����:SYW_TIPS_ONLINE_DRC.c
�ļ�����:TIPS����ʵʱ����
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:sunpj
��������:
��    ��:
�޸�����:
*********************************************************************/

#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include "gaps_head.h"

#include "../../eh/tips_drls.h"/* ������ˮ�� */
#include "../../eh/DRC/tips_wtgxdj_drc.h"/* ί�й�ϵ�Ǽ� */
#include "../../eh/DRC/tips_wtgxdjlsls_drc.h"/* ί�й�ϵ�Ǽ���ʷ��ˮ */
#include "../../eh/DRC/tips_taxtypemx_drc.h"/* ˰����ϸ�� */
#include "../../eh/DRC/tips_taxsubjectlist_drc.h"/* ˰Ŀ��ϸ�� */


/************************************************************************
��̬�����������
�����������: SYW_TIPS_AddSFXY_DRC
�������: ǩԼ����Э��
�������: 
  ǩԼ����Э��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

�������裺
   ǰ��������������ɾ��ǰ����ɶ��˺�����������У��
        1 ����
          ���ջ���У��
          ��ѯ���ջ��ء���˰���˺š�֧�����кż�¼�Ƿ���ڡ�
            ����->�ж�Э������Ƿ��ǰ̨���͵�һ�£�
                     һ�£��޸�ί�й�ϵ״̬->0�����سɹ�
                     ��һ��,����ʧ�ܣ����ջ��ء���˰���˺š�֧�����кŶ�Ӧ��ϵ�Ѵ��ڡ�                                                      
            �����ڣ�����
          ��ѯЭ����������ݿ����Ƿ��Ѵ��ڡ�
            ����->����ʧ��,Э�����Ӧ�����ջ��ء���˰���˺š�֧�����кż�¼������ 
            ������->��������Э�顣

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�    tips_wtgxdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: sunpj
��������: 2017��3��15��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_AddSFXY_DRC(HXMLTREE lXmlhandle)
{
    int iParas;
    char sProtocolNo[60+1];/* Э����� */
    char sTaxOrgCode[12+1];/* ���ջ��ش��� */
    char sPayAcct[32+1];/* �����˺� */
    char sPayBkCode[12+1];/* �������к� */
    char sPayOpBkCode[12+1];/* ������к� */
    char sYzbz_tmp[1+1];
    SDB_TIPS_WTGXDJ stWtgxdj;
    SDB_TIPS_WTGXDJ stWtgxdj1;
    int iCount;

    char sBuf[256];
    char sZwrq[8+1];
    char sBankProNo[30];
    
    char sSql1[512];  /*DCI ִ��sql���*/
    char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ*/ 
    int iRet=0;

    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(4);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "Э�����")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "���ջ��ش���")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "�����˺�")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(4, sBuf, "�������к�")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    LOG(LM_STD,Fmtmsg("ǩԼ����Э�鿪ʼ����..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("Э�����[%s],���ջ��ش���[%s],�����˺�[%s],�������к�[%s]", 
        sProtocolNo, sTaxOrgCode, sPayAcct, sPayBkCode),fpub_GetCompname(lXmlhandle))
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT count(*) FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);         
    iRet = DBSelectToVar( sErrmsg, &iCount, sSql1) ; 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
        fpub_GetCompname(lXmlhandle))
    }
    if ( iCount > 0 )
    {
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof(sSql1), "SELECT yzbz FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);         
        iRet = DBSelectToVar( sErrmsg, &sYzbz_tmp, sSql1) ;             
        trim(sYzbz_tmp); 
        if( strcmp(sYzbz_tmp,"2")==0 )
        {
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            snprintf( sSql1, sizeof(sSql1), "delete FROM tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);
            iRet = DCIExecuteDirect(sSql1);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
                fpub_SetMsg(lXmlhandle, 24319, "ɾ������Э��ʧ��");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ������Э��ʧ��"),
                fpub_GetCompname(lXmlhandle))
            }
        }
        else
        {
            fpub_SetMsg(lXmlhandle, 24325, "����Э���Ѵ���,ǩԼʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э���Ѵ���,ǩԼʧ��"),
            fpub_GetCompname(lXmlhandle))        
        }
    }
    
    /*Э�����δ��ʹ��,��ʼ��������Э��*/     
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));     
    COMP_SOFTGETXML("/tips/zwrq",sBuf);
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(&stWtgxdj,0,sizeof(stWtgxdj));

    /* ��������Э������� */
    iRet = 0;
    memset(sBankProNo,0x00,sizeof(sBankProNo));
    iRet = prv_tips_genxh2(1,sBuf,sBankProNo);
    if (iRet < 0)
    {
        fpub_SetMsg(lXmlhandle, 24326, "���������ڲ�Э���ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���������ڲ�Э���ʧ��"),
            fpub_GetCompname(lXmlhandle)) 
    }
    trim(sBankProNo);
    COMP_SOFTSETXML("/tips/BANKProtocolNo",sBankProNo)
    
    memset(&stWtgxdj,0,sizeof(stWtgxdj));

    /*����Э�����*/
    pstrcopy(stWtgxdj.bankprotocolno,sBankProNo,sizeof(stWtgxdj.bankprotocolno));

    /*ί�й�ϵ״̬*/ 
    stWtgxdj.wtgxzt[0]='0';

    /*Э�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/ProtocolNo",sBuf)
    pstrcopy(stWtgxdj.protocolno, sBuf, sizeof(stWtgxdj.protocolno));
    if(strlen(stWtgxdj.protocolno)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "Э����Ų���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("Э����Ų���Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }

    /*���ջ��ش���*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode",sBuf)
    pstrcopy(stWtgxdj.taxorgcode, sBuf, sizeof(stWtgxdj.taxorgcode));
    if(strlen(stWtgxdj.taxorgcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "���ջ��ش��벻��Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ջ��ش��벻��Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_taxcodeinfo WHERE taxorgcode='%s'",sTaxOrgCode);         
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24321, "��ѯ���ջ��ش���ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ���ջ��ش���ʧ��"),
            fpub_GetCompname(lXmlhandle))
        
    }
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24322, "���ջ��ش��벻����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ջ��ش��벻����"),
            fpub_GetCompname(lXmlhandle))        
    }
    
    /*��˰�˱���*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/TaxPayCode",sBuf)
    pstrcopy(stWtgxdj.taxpaycode, sBuf, sizeof(stWtgxdj.taxpaycode));
    if(strlen(stWtgxdj.taxpaycode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "��˰�˱��벻��Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��˰�˱��벻��Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*��˰������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName",sBuf)
    pstrcopy(stWtgxdj.taxpayname, sBuf, sizeof(stWtgxdj.taxpayname));
     if(strlen(stWtgxdj.taxpayname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "��˰�����Ʋ���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��˰�����Ʋ���Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
   /*�ɿλ����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jkdwmc",sBuf)
    pstrcopy(stWtgxdj.handorgname, sBuf, sizeof(stWtgxdj.handorgname));
     if(strlen(stWtgxdj.handorgname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�ɿλ���Ʋ���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�ɿλ���Ʋ���Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /* �������к�*/
    pstrcopy(stWtgxdj.paybkcode, sPayBkCode, sizeof(stWtgxdj.paybkcode));
    if(strlen(stWtgxdj.paybkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�������кŲ���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�������кŲ���Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /* �����ʻ�*/ 
    pstrcopy(stWtgxdj.payacct, sPayAcct, sizeof(stWtgxdj.payacct));
    if(strlen(stWtgxdj.payacct)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�����ʻ�����Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����ʻ�����Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*�ͻ�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/khh",sBuf)
    pstrcopy(stWtgxdj.khh, sBuf, sizeof(stWtgxdj.khh));

    /*��ϵ�Ǽ�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/gxdjrq",sBuf)
    pstrcopy(stWtgxdj.gxdjrq, sBuf, sizeof(stWtgxdj.gxdjrq));
    
    /*�Ǽ���ˮ��*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/zhqzlsh",sBuf)
    pstrcopy(stWtgxdj.djlsh, sBuf, sizeof(stWtgxdj.djlsh));

    /*��������*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/jgdh",sBuf)
    pstrcopy(stWtgxdj.djjgdh, sBuf, sizeof(stWtgxdj.djjgdh));

    /*��������*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh",sBuf)
    pstrcopy(stWtgxdj.djdqdh, sBuf, sizeof(stWtgxdj.djdqdh));

    /*���׹�Ա*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy",sBuf)
    pstrcopy(stWtgxdj.djjygy, sBuf, sizeof(stWtgxdj.djjygy));

    /*�ն˴���*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh",sBuf)
    pstrcopy(stWtgxdj.djzddh, sBuf, sizeof(stWtgxdj.djzddh));

    /*��չ��־*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/resp/zhlx", sBuf)/* �ʻ����� */  
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[0]=sBuf[0];
    }
    else
    {
        stWtgxdj.kzbz[0]='0'; 
    }
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/chbz", sBuf)/* �����־ */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[1]=sBuf[0];
    }else
    {
        stWtgxdj.kzbz[1]='0';
    }
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/kzbz", sBuf)/* ���۱�־ P���˻� C���� Ĭ�����˻�P*/
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[2]=sBuf[0];
    }
    else
    {
        stWtgxdj.kzbz[2]='P'; 
    }
    strcat(stWtgxdj.kzbz, "00000");
    LOG(LM_STD,Fmtmsg("Э�����[%s],���ջ��ش���[%s],�����˺�[%s],kzbz[%s]", 
    sProtocolNo, sTaxOrgCode, sPayAcct, stWtgxdj.kzbz),fpub_GetCompname(lXmlhandle))    

    /*��֤��־*/
    stWtgxdj.yzbz[0]='0';

    /*�ͻ���*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/khh",sBuf);
    pstrcopy(stWtgxdj.khh,sBuf,sizeof(stWtgxdj.khh)); 

    /*������л�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.opbankno,sBuf,sizeof(stWtgxdj.opbankno)); 

    /*��ע--�����л�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));
    
    /*��������к�*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode",sBuf);
    pstrcopy(stWtgxdj.payopbkcode,sBuf,sizeof(stWtgxdj.payopbkcode));
    if(strlen(stWtgxdj.payopbkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "��������кŲ���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������кŲ���Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }

    /*��ע*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bz",sBuf);
    pstrcopy(stWtgxdj.bz,sBuf,sizeof(stWtgxdj.bz));

    /*�˺�2*//*�޸�by liurj add 20180713*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct2",sBuf);
    pstrcopy(stWtgxdj.payacct2,sBuf,sizeof(stWtgxdj.payacct2));
    /*pstrcopy(stWtgxdj.payacct2, stWtgxdj.payacct, sizeof(stWtgxdj.payacct2));*/

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_wtgxdj", SD_TIPS_WTGXDJ, NUMELE(SD_TIPS_WTGXDJ), &stWtgxdj, sErrmsg);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        
        fpub_SetMsg(lXmlhandle, 24327, "��������Э��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������Э��ʧ��"),
        fpub_GetCompname(lXmlhandle))
    }
    
    fpub_SetMsg(lXmlhandle, 0, "ǩԼ����Э��ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("ǩԼ����Э��ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_UpdSFXY_DRC
�������: �޸�����Э��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

�������裺
   ǰ��������������ɾ��ǰ����ɶ��˺�����������У��        1 ����

          ��ѯЭ����������ݿ����Ƿ��Ѵ��ڡ�
            ����->��֤Э�����Ӧ�����ջ��ء���˰���˺š�֧�����кż�¼�Ƿ�����������Ľ���ʧ�ܣ����ϵĸ��¡� 
            ������->����ʧ��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�    tips_wtgxdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: sunpj
��������: 2017��3��15��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_UpdSFXY_DRC(HXMLTREE lXmlhandle)
{
    int iParas;
    char sProtocolNo[60+1];/* Э����� */
    char sProtocolno_tmp[60+1];/* Э����� */
    char sTaxOrgCode[12+1];/* ���ջ��ش��� */
    char sPayAcct[32+1];/* �����˺� */
    char sPayBkCode[12+1];/* �������к� */
    char sPayOpBkCode[12+1];/* �������к� */
    SDB_TIPS_WTGXDJ stWtgxdj;
    SDB_TIPS_WTGXDJ stWtgxdj1;
    int iCount;
    
    char sBuf[256];
    char sZwrq[8+1];
    char sBankProNo[30];
    int iret;
    
    char sSql1[1024];  /*DCI ִ��sql���*/
    char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ*/ 
    int iRet=0;
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
           
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(4);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "Э�����")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "���ջ��ش���")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "�����˺�")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(4, sBuf, "�������к�")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    LOG(LM_STD,Fmtmsg("ǩԼ����Э�鿪ʼ����..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("Э�����[%s],���ջ��ش���[%s],�����˺�[%s],�������к�[%s]", 
    sProtocolNo, sTaxOrgCode, sPayAcct, sPayBkCode),fpub_GetCompname(lXmlhandle))
    
    memset(&stWtgxdj1, 0x00, sizeof(stWtgxdj1));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select yzbz from tips_wtgxdj where protocolno='%s' ",sProtocolNo);         
    iRet = DBSelectToVar(sErrmsg, &stWtgxdj1.yzbz, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
        fpub_GetCompname(lXmlhandle))   
    }
    if( iRet == 0)
    {
        fpub_SetMsg(lXmlhandle, 24325, "����Э�鲻����,����ǩԼ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э�鲻����,����ǩԼ����"),
        fpub_GetCompname(lXmlhandle))        
    }

    LOG(LM_STD,Fmtmsg("��֤��־[%s]...",stWtgxdj1.yzbz),fpub_GetCompname(lXmlhandle))
    if( !(strcmp(stWtgxdj1.yzbz,"1")) )
    {
        fpub_SetMsg(lXmlhandle, 24327, "������Э������֤�������޸�");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("������Э������֤�������޸�"),
        fpub_GetCompname(lXmlhandle))
    }
    
    /*��ʼ�޸�����Э��*/     
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));     
    COMP_SOFTGETXML("/tips/zwrq",sBuf);
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    iret = 0;
    
    memset(&stWtgxdj,0,sizeof(stWtgxdj));
      

    /*ί�й�ϵ״̬*/ 
    stWtgxdj.wtgxzt[0]='0';
    
    /*Э�����*/
    pstrcopy(stWtgxdj.protocolno, sProtocolNo, sizeof(stWtgxdj.protocolno));
    if(strlen(stWtgxdj.protocolno)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "Э����Ų���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("Э����Ų���Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*���ջ��ش���*/
    pstrcopy(stWtgxdj.taxorgcode, sTaxOrgCode, sizeof(stWtgxdj.taxorgcode));
    if(strlen(stWtgxdj.taxorgcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "���ջ��ش��벻��Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ջ��ش��벻��Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_taxcodeinfo WHERE taxorgcode='%s'",sTaxOrgCode);         
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24321, "��ѯ���ջ��ش���ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ���ջ��ش���ʧ��"),
            fpub_GetCompname(lXmlhandle))
        
    }
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24322, "���ջ��ش��벻����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ջ��ش��벻����"),
            fpub_GetCompname(lXmlhandle))        
    }
    
   /*��˰�˱���*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/TaxPayCode",sBuf)
    pstrcopy(stWtgxdj.taxpaycode, sBuf, sizeof(stWtgxdj.taxpaycode));
    if(strlen(stWtgxdj.taxpaycode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "��˰�˱��벻��Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��˰�˱��벻��Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*��˰������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName",sBuf)
    pstrcopy(stWtgxdj.taxpayname, sBuf, sizeof(stWtgxdj.taxpayname));
    if(strlen(stWtgxdj.taxpayname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "��˰�����Ʋ���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��˰�����Ʋ���Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*�ɿλ����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jkdwmc",sBuf)
    pstrcopy(stWtgxdj.handorgname, sBuf, sizeof(stWtgxdj.handorgname));
    if(strlen(stWtgxdj.handorgname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�ɿλ���Ʋ���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�ɿλ���Ʋ���Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /* �������к�*/
    pstrcopy(stWtgxdj.paybkcode, sPayBkCode, sizeof(stWtgxdj.paybkcode));
    if(strlen(stWtgxdj.paybkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�������кŲ���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�������кŲ���Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /* �����ʻ�*/ 
    pstrcopy(stWtgxdj.payacct, sPayAcct, sizeof(stWtgxdj.payacct));
    if(strlen(stWtgxdj.payacct)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�����ʻ�����Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����ʻ�����Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*�ͻ�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/khh",sBuf)
    pstrcopy(stWtgxdj.khh, sBuf, sizeof(stWtgxdj.khh));
    
    /*��ϵ�޸�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/xgrq",sBuf)
    pstrcopy(stWtgxdj.xgrq, sBuf, sizeof(stWtgxdj.xgrq));
    
    /*�޸���ˮ��*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/zhqzlsh",sBuf)
    pstrcopy(stWtgxdj.xglsh, sBuf, sizeof(stWtgxdj.xglsh));
    
    /*�޸Ļ�������*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/jgdh",sBuf)
    pstrcopy(stWtgxdj.xgjgdh, sBuf, sizeof(stWtgxdj.xgjgdh));
    
    /*�޸ĵ�������*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh",sBuf)
    pstrcopy(stWtgxdj.xgdqdh, sBuf, sizeof(stWtgxdj.xgdqdh));
    
    /*�޸Ľ��׹�Ա*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy",sBuf)
    pstrcopy(stWtgxdj.xgjygy, sBuf, sizeof(stWtgxdj.xgjygy));
    
    /*�޸��ն˴���*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh",sBuf)
    pstrcopy(stWtgxdj.xgzddh, sBuf, sizeof(stWtgxdj.xgzddh));
    
    /*��չ��־*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/resp/zhlx", sBuf)/* �ʻ����� */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[0]=sBuf[0];
    }
    else
    {
        stWtgxdj.kzbz[0]='0'; 
    }
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/chbz", sBuf)/* �����־ */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[1]=sBuf[0];
    }
    else
    {
        stWtgxdj.kzbz[1]='0';
    }
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/kzbz", sBuf)/* ���۱�־ add 20140901 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[2]=sBuf[0];
    }
    else
    {
        stWtgxdj.kzbz[2]='C'; 
    }
    strcat(stWtgxdj.kzbz, "00000");   
    
    /*��������к�*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode",sBuf);
    pstrcopy(stWtgxdj.payopbkcode, sBuf, sizeof(stWtgxdj.payopbkcode));
    if(strlen(stWtgxdj.payopbkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "��������кŲ���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������кŲ���Ϊ��"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*������л�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.opbankno,sBuf,sizeof(stWtgxdj.opbankno)); 
    
    /*��ע--�����л����� */
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));
    
    /*��ע*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bz",sBuf);
    pstrcopy(stWtgxdj.bz,sBuf,sizeof(stWtgxdj.bz));

    /*�˺�2*//*�޸�by liurj add 20180713*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct2",sBuf);
    pstrcopy(stWtgxdj.payacct2,sBuf,sizeof(stWtgxdj.payacct2));
    /*pstrcopy(stWtgxdj.payacct2, stWtgxdj.payacct, sizeof(stWtgxdj.payacct2));*/
    
    /*��������Э��*/
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj  \
                set payacct='%s'    \
                    ,payopbkcode='%s'\
                    ,taxpayname='%s' \
                    ,handorgname='%s'\
                    ,byzd='%s'       \
                    ,khh='%s'        \
                    ,xgrq='%s'       \
                    ,xglsh='%s'      \
                    ,xgdqdh='%s'     \
                    ,xgjgdh='%s'     \
                    ,xgjygy='%s'     \
                    ,xgzddh='%s'     \
                    ,opbankno='%s'   \
                    ,bz='%s'         \
                    ,payacct2='%s'   \
                where protocolno='%s'" \
              ,stWtgxdj.payacct      \
              ,stWtgxdj.payopbkcode  \
              ,stWtgxdj.taxpayname   \
              ,stWtgxdj.handorgname  \
              ,stWtgxdj.byzd         \
              ,stWtgxdj.khh          \
              ,stWtgxdj.xgrq         \
              ,stWtgxdj.xglsh        \
              ,stWtgxdj.xgdqdh       \
              ,stWtgxdj.xgjgdh       \
              ,stWtgxdj.xgjygy       \
              ,stWtgxdj.xgzddh       \
              ,stWtgxdj.opbankno     \
              ,stWtgxdj.bz           \
              ,stWtgxdj.payacct2     \
              ,sProtocolNo);
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))                   
    iRet = DCIExecuteDirect(sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24327, "�޸�����Э��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�޸�����Э��ʧ��"),
        fpub_GetCompname(lXmlhandle))
    }
    iRet =DCICommit();
    
    fpub_SetMsg(lXmlhandle, 0, "�޸�����Э��ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�޸�����Э��ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_DelSFXY_DRC
�������: ��������Э��
�������: 
  ��������Э��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

�������裺
   ǰ��������������ɾ��ǰ����ɶ��˺�����������У��
        
        ɾ��
          ����Э����š���ѯ����Э������
             У������Э���ֶΣ����ջ��ش��š���˰���˺š�֧�����к��Ƿ��ǰ̨���͵�һ��
             ����Э�����ί�й�ϵ״̬-->1,���سɹ���

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�    tips_wtgxdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: sunpj
��������: 2017��03��25��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_DelSFXY_DRC(HXMLTREE lXmlhandle)
{
    int iParas;
    char sProtocolNo[60+1];/* Э����� */
    char sTaxOrgCode[12+1];/* ���ջ��ش��� */
    char sPayAcct[32+1];/* �����˺� */
    SDB_TIPS_WTGXDJ stWtgxdj;
    SDB_TIPS_WTGXDJ stWtgxdj1;

    char sBuf[256];
    
    char sSql1[512];  /*DCI ִ��sql���*/
    char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ*/ 
    int iRet=0;
    
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "Э�����")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "���ջ��ش���")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "�����˺�")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);

    LOG(LM_STD,Fmtmsg("��������Э�鿪ʼ����..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("Э�����[%s],���ջ��ش���[%s],�����˺�[%s]", 
    sProtocolNo, sTaxOrgCode, sPayAcct),fpub_GetCompname(lXmlhandle))
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    memset( &stWtgxdj, 0x00, sizeof( &stWtgxdj ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT PROTOCOLNO, TAXORGCODE, PAYBKCODE, PAYACCT, BANKPROTOCOLNO, TAXPAYCODE, \
            PAYOPBKCODE, TAXPAYNAME, HANDORGNAME, KHH, WTGXZT, GXDJRQ, DJLSH, DJDQDH, DJJGDH, DJJYGY, DJZDDH, XGRQ, \
            XGLSH, XGDQDH, XGJGDH, XGJYGY, XGZDDH, KZBZ, YZBZ, BYZD, OPBANKNO, BZ, PAYACCT2, YZXGRQ \
            FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))  
         
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stWtgxdj.protocolno,&stWtgxdj.taxorgcode,\
    &stWtgxdj.paybkcode,&stWtgxdj.payacct,&stWtgxdj.bankprotocolno,&stWtgxdj.taxpaycode,&stWtgxdj.payopbkcode,\
    &stWtgxdj.taxpayname,&stWtgxdj.handorgname,&stWtgxdj.khh,&stWtgxdj.wtgxzt,&stWtgxdj.gxdjrq,&stWtgxdj.djlsh,\
    &stWtgxdj.djdqdh,&stWtgxdj.djjgdh,&stWtgxdj.djjygy,&stWtgxdj.djzddh,&stWtgxdj.xgrq,&stWtgxdj.xglsh,\
    &stWtgxdj.xgdqdh,&stWtgxdj.xgjgdh,&stWtgxdj.xgjygy,&stWtgxdj.xgzddh,&stWtgxdj.kzbz,&stWtgxdj.yzbz,\
    &stWtgxdj.byzd,&stWtgxdj.opbankno,&stWtgxdj.bz,&stWtgxdj.payacct2,&stWtgxdj.yzxgrq);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
        fpub_GetCompname(lXmlhandle))
        
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24317, "ί�й�ϵδ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ί�й�ϵδ����"),
        fpub_GetCompname(lXmlhandle))    
    }
    
    /*�޸���ˮ�� */
    COMP_SOFTGETXML("/pub/zhqzlsh",stWtgxdj.xglsh);
    
    /*�޸����� */
    COMP_SOFTGETXML("/sys/sysdate",stWtgxdj.xgrq);
    
    /*�޸Ļ������� */
    COMP_SOFTGETXML("/pub/jgdh",stWtgxdj.xgjgdh);
    
    /*�޸ĵ������� */
    COMP_SOFTGETXML("/pub/dqdh",stWtgxdj.xgdqdh);
    
    /*�޸Ľ��׹�Ա */
    COMP_SOFTGETXML("/pub/jygy",stWtgxdj.xgjygy);
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_wtgxdjlsls", SD_TIPS_WTGXDJLSLS, NUMELE(SD_TIPS_WTGXDJLSLS), &stWtgxdj, sErrmsg);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, 24318, "������ʷί�м�¼ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("������ʷί�м�¼ʧ��"),
        fpub_GetCompname(lXmlhandle))
    }
    
    /* ADD DCI 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "delete FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);
    iRet = DCIExecuteDirect(sSql1);
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 24319, "ɾ������Э��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ������Э��ʧ��"),
        fpub_GetCompname(lXmlhandle))
    }
    
    fpub_SetMsg(lXmlhandle, 0, "ɾ������Э��ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("ɾ������Э��ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitPZSJ_DB_DRC
�������: �Ǽ�ƾ֤������Ϣ(����)
�������: 
  �Ǽ�ƾ֤������Ϣ(����)
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

�������裺


������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
������ˮ��    tips_drls
˰����ϸ��    tips_taxtypemx
˰Ŀ��ϸ��    tips_taxsubjectlist

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: sunpj
��������: 2017��3��29��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitPZSJ_DB_DRC(HXMLTREE lXmlhandle)
{
    int iParas;
    SDB_TIPS_DRLS stDrls;
    SDB_TIPS_TAXTYPEMX stTaxtypemx;
    SDB_TIPS_TAXSUBJECTLIST stTaxsubjectlist;
    char sZwrq[8+1];/* �������� */
    int iZhqzlsh;
    
    char sBuf[256];
    char sRoot[256];
    int  iCount=0,i,j;
    char sXmlNodePath[200];
    char sTaxInfoPath[200];
    char sPayment3102[10240];
    int iret;
    FILE *fp;
    
    char sSql1[512]; 
    char sErrmsg[256];
    int iRet=0;
    
    char sProtocolno[61];
    char sSpxx[41];
    
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    iZhqzlsh=0;
    COMP_GETPARSEPARAS(2, sBuf, "�ۺ�ǰ����ˮ��")
    iZhqzlsh = atoi(sBuf);

    LOG(LM_STD,Fmtmsg("�Ǽ�ƾ֤������Ϣ(����)��ʼ����..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("��������[%s],�ۺ�ǰ����ˮ��[%d]", 
        sZwrq, iZhqzlsh),fpub_GetCompname(lXmlhandle))
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    memset( &stDrls, 0x00, sizeof( &stDrls ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_drls where zwrq='%s' and zhqzlsh=%d",sZwrq,iZhqzlsh); 
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))    
       
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,
                               &stDrls.zwrq         ,
                               &stDrls.zhqzlsh      ,
                               &stDrls.jyqd         ,
                               &stDrls.workdate     ,
                               &stDrls.entrustdate  ,
                               &stDrls.taxorgcode   ,
                               &stDrls.trano        ,
                               &stDrls.msgno        ,
                               &stDrls.entrustdate2 ,
                               &stDrls.trano2       ,
                               &stDrls.zhqzlsh2     ,
                               &stDrls.chkdate      ,
                               &stDrls.chkacctord   ,
                               &stDrls.handletype   ,
                               &stDrls.trecode      ,
                               &stDrls.payeebankno  ,
                               &stDrls.payeeorgcode ,
                               &stDrls.payeeacct    ,
                               &stDrls.payeename    ,
                               &stDrls.paybkcode    ,
                               &stDrls.payopbkcode  ,
                               &stDrls.protocolno   ,
                               &stDrls.payacct      ,
                               &stDrls.handorgname  ,
                               &stDrls.dfzh         ,
                               &stDrls.jyje         ,
                               &stDrls.taxvouno     ,
                               &stDrls.dqdh         ,
                               &stDrls.jgdh         ,
                               &stDrls.jygy         ,
                               &stDrls.zddh         ,
                               &stDrls.jyrq         ,
                               &stDrls.jysj         ,
                               &stDrls.zjrq         ,
                               &stDrls.zjsj         ,
                               &stDrls.zjlsh        ,
                               &stDrls.zjxym        ,
                               &stDrls.zjxyxx       ,
                               &stDrls.sxf          ,
                               &stDrls.zhye         ,
                               &stDrls.xym          ,
                               &stDrls.xyxx         ,
                               &stDrls.jyzt         ,
                               &stDrls.dzbz         ,
                               &stDrls.qsbz         ,
                               &stDrls.kzbz         ,
                               &stDrls.taxpaycode   ,
                               &stDrls.taxpayname   ,
                               &stDrls.spxx         ,
                               &stDrls.byzd          );
        
    LOG(LM_STD,Fmtmsg("ZWRQ         [%s]",stDrls.zwrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHQZLSH      [%d]",stDrls.zhqzlsh     ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYQD         [%s]",stDrls.jyqd        ),"INFO") 
    LOG(LM_STD,Fmtmsg("WORKDATE     [%s]",stDrls.workdate    ),"INFO") 
    LOG(LM_STD,Fmtmsg("ENTRUSTDATE  [%s]",stDrls.entrustdate ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXORGCODE   [%s]",stDrls.taxorgcode  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TRANO        [%s]",stDrls.trano       ),"INFO") 
    LOG(LM_STD,Fmtmsg("MSGNO        [%s]",stDrls.msgno       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ENTRUSTDATE2 [%s]",stDrls.entrustdate2),"INFO") 
    LOG(LM_STD,Fmtmsg("TRANO2       [%s]",stDrls.trano2      ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHQZLSH2     [%d]",stDrls.zhqzlsh2    ),"INFO") 
    LOG(LM_STD,Fmtmsg("CHKDATE      [%s]",stDrls.chkdate     ),"INFO") 
    LOG(LM_STD,Fmtmsg("CHKACCTORD   [%s]",stDrls.chkacctord  ),"INFO") 
    LOG(LM_STD,Fmtmsg("HANDLETYPE   [%s]",stDrls.handletype  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TRECODE      [%s]",stDrls.trecode     ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEBANKNO  [%s]",stDrls.payeebankno ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEORGCODE [%s]",stDrls.payeeorgcode),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEACCT    [%s]",stDrls.payeeacct   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEENAME    [%s]",stDrls.payeename   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYBKCODE    [%s]",stDrls.paybkcode   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYOPBKCODE  [%s]",stDrls.payopbkcode ),"INFO") 
    LOG(LM_STD,Fmtmsg("PROTOCOLNO   [%s]",stDrls.protocolno  ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYACCT      [%s]",stDrls.payacct     ),"INFO") 
    LOG(LM_STD,Fmtmsg("HANDORGNAME  [%s]",stDrls.handorgname ),"INFO") 
    LOG(LM_STD,Fmtmsg("DFZH         [%s]",stDrls.dfzh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYJE         [%f]",stDrls.jyje        ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXVOUNO     [%s]",stDrls.taxvouno    ),"INFO") 
    LOG(LM_STD,Fmtmsg("DQDH         [%s]",stDrls.dqdh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JGDH         [%s]",stDrls.jgdh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYGY         [%s]",stDrls.jygy        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZDDH         [%s]",stDrls.zddh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYRQ         [%s]",stDrls.jyrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYSJ         [%s]",stDrls.jysj        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJRQ         [%s]",stDrls.zjrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJSJ         [%s]",stDrls.zjsj        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJLSH        [%s]",stDrls.zjlsh       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJXYM        [%s]",stDrls.zjxym       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJXYXX       [%s]",stDrls.zjxyxx      ),"INFO") 
    LOG(LM_STD,Fmtmsg("SXF          [%f]",stDrls.sxf         ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHYE         [%f]",stDrls.zhye        ),"INFO") 
    LOG(LM_STD,Fmtmsg("XYM          [%s]",stDrls.xym         ),"INFO") 
    LOG(LM_STD,Fmtmsg("XYXX         [%s]",stDrls.xyxx        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYZT         [%s]",stDrls.jyzt        ),"INFO") 
    LOG(LM_STD,Fmtmsg("DZBZ         [%s]",stDrls.dzbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("QSBZ         [%s]",stDrls.qsbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("KZBZ         [%s]",stDrls.kzbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXPAYCODE   [%s]",stDrls.taxpaycode  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXPAYNAME   [%s]",stDrls.taxpayname  ),"INFO") 
    LOG(LM_STD,Fmtmsg("SPXX         [%s]",stDrls.spxx        ),"INFO") 
    LOG(LM_STD,Fmtmsg("BYZD         [%s]",stDrls.byzd        ),"INFO") 
    
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24201, "��ѯ������ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ������ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))    
         return COMPRET_FAIL ;        
    }
    
    /* ˰Ʊ��Ϣ */
    memset(sPayment3102, 0x00, sizeof(sPayment3102));
    memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
    if (strcmp(stDrls.msgno, "3001") == 0)
    {
        strcpy(sXmlNodePath,"/tips/MSG/Payment3001");   
    
        if ( (iret=xml_ExportXMLString(lXmlhandle,sPayment3102,sizeof(sPayment3102),sXmlNodePath,1 )) == -1 )
        {
             fpub_SetMsg(lXmlhandle, 24211, "��ȡ˰Ʊ��Ϣʧ��");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("��ȡ˰Ʊ��Ϣʧ��[%s]", sXmlNodePath), fpub_GetCompname(lXmlhandle))    
             return COMPRET_FAIL ;        
        }
        /* ��˰Ʊ��Ϣ��ŵ��ļ���ȥ */
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));/* ��ŵ��ļ��� */
        snprintf(sXmlNodePath, sizeof(sXmlNodePath), "spxx_%s_%d",sZwrq, iZhqzlsh);
        trim(sXmlNodePath);
        snprintf(sTaxInfoPath, sizeof(sTaxInfoPath), "%s/file/tips/spxx/%s", getenv("HOME"), sXmlNodePath);
        fp = fopen(sTaxInfoPath, "w+");
        if ( fp==NULL )
        {
             fpub_SetMsg(lXmlhandle, 24212, "��˰Ʊ��Ϣ�ļ�ʧ��");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("��˰Ʊ��Ϣ�ļ�ʧ��"), fpub_GetCompname(lXmlhandle))    
             return COMPRET_FAIL ;        
        }
        fprintf(fp, "%s\n", sPayment3102); 
        if (NULL != fp)
        {
            fclose(fp);
            fp = NULL;
        }
        
        pstrcopy(stDrls.spxx, sXmlNodePath, sizeof(stDrls.spxx));        
        COMP_SOFTSETXML("/tips/spxx", sXmlNodePath)

        /*��ϸ����*/
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/MSG/Payment3001/TaxTypeNum",sBuf)
        iCount=atoi(sBuf);
       
        /*ѭ��ȡ˰����ϸ��Ϣ*/
        for(i=1; i<=iCount; i++)
        {
            
            memset(&stTaxtypemx, 0x00, sizeof(stTaxtypemx));
            pstrcopy(stTaxtypemx.jyrq, stDrls.zwrq, sizeof(stTaxtypemx.jyrq));
			sprintf(stTaxtypemx.jylsh, "%d", stDrls.zhqzlsh);
            pstrcopy(stTaxtypemx.spxx, stDrls.spxx, sizeof(stTaxtypemx.spxx));
            LOG(LM_STD,Fmtmsg("jyrq[%s]",stTaxtypemx.jyrq),fpub_GetCompname(lXmlhandle))
            LOG(LM_STD,Fmtmsg("jylsh[%s]",stTaxtypemx.jylsh),fpub_GetCompname(lXmlhandle))

            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment3001/TaxTypeList3001|%d/ProjectId",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.projectid, sBuf, sizeof(stTaxtypemx.projectid));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxTypeName",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxtypename, sBuf, sizeof(stTaxtypemx.taxtypename));

            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));         
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxStartDate",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxstartdate, sBuf, sizeof(stTaxtypemx.taxstartdate));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxEndDate",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxenddate, sBuf, sizeof(stTaxtypemx.taxenddate));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxTypeAmt",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            stTaxtypemx.taxtypeamt = atof(sBuf);
            
            LOG(LM_STD,Fmtmsg("i[%d],jyrq[%s],jylsh[%s],projectid[%s]",i,stTaxtypemx.jyrq,stTaxtypemx.jylsh,stTaxtypemx.projectid),"INFO") 
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            iRet = DBInsert("tips_taxtypemx", SD_TIPS_TAXTYPEMX, NUMELE(SD_TIPS_TAXTYPEMX), &stTaxtypemx, sErrmsg);
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                
                fpub_SetMsg(lXmlhandle, 24327, "����˰����ϸ��ʧ��");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����˰����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))
            }
        }
        
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof(sSql1), "update tips_drls set spxx ='%s' where zwrq='%s' and zhqzlsh=%d",stDrls.spxx,sZwrq,iZhqzlsh);         
        LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))       
        iRet = DCIExecuteDirect(sSql1);     
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
            
            fpub_SetMsg(lXmlhandle, 24201, "���µ�����ˮ��ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOG(LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))    
            return COMPRET_FAIL ;        
        }
        
    }
    else if (strcmp(stDrls.msgno, "1008") == 0)
    {
        strcpy(sXmlNodePath,"/tips/MSG/Payment1008");  
        
        /*��ϸ����*/
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/MSG/Payment1008/TaxTypeNum",sBuf)
        iCount=atoi(sBuf);
       
        /*ѭ��ȡ˰����ϸ��Ϣ*/
        for(i=1; i<=iCount; i++)
        {
            LOG(LM_STD,Fmtmsg("����˰����ϸ��ʼ..."),fpub_GetCompname(lXmlhandle))
            memset(&stTaxtypemx, 0x00, sizeof(stTaxtypemx));
            pstrcopy(stTaxtypemx.jyrq, stDrls.zwrq, sizeof(stTaxtypemx.jyrq));
			sprintf(stTaxtypemx.jylsh, "%d", stDrls.zhqzlsh);
            pstrcopy(stTaxtypemx.spxx, stDrls.spxx, sizeof(stTaxtypemx.spxx));

            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/ProjectId",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.projectid, sBuf, sizeof(stTaxtypemx.projectid));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/BudgetSubjectCode",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.budgetsubjectcode, sBuf, sizeof(stTaxtypemx.budgetsubjectcode));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/LimitDate",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.limitdate, sBuf, sizeof(stTaxtypemx.limitdate));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxTypeName",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxtypename, sBuf, sizeof(stTaxtypemx.taxtypename));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/BudgetLevelCode",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.budgetlevelcode, sBuf, sizeof(stTaxtypemx.budgetlevelcode));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/BudgetLevelName",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.budgetlevelname, sBuf, sizeof(stTaxtypemx.budgetlevelname));

            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxStartDate",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxstartdate, sBuf, sizeof(stTaxtypemx.taxstartdate));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxEndDate",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxenddate, sBuf, sizeof(stTaxtypemx.taxenddate));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/ViceSign",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.vicesign, sBuf, sizeof(stTaxtypemx.vicesign));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxType",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxtype, sBuf, sizeof(stTaxtypemx.taxtype));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxTypeAmt",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            stTaxtypemx.taxtypeamt = atof(sBuf);
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/DetailNum",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.detailnum, sBuf, sizeof(stTaxtypemx.detailnum));
            
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            iRet = DBInsert("tips_taxtypemx", SD_TIPS_TAXTYPEMX, NUMELE(SD_TIPS_TAXTYPEMX), &stTaxtypemx, sErrmsg);
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                
                fpub_SetMsg(lXmlhandle, 24327, "����˰����ϸ��ʧ��");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����˰����ϸ��ʧ��"),
                fpub_GetCompname(lXmlhandle))
            }
            
            LOG(LM_STD,Fmtmsg("����˰����ϸ�����..."),fpub_GetCompname(lXmlhandle))
            
            for (j = 0; j < atol(stTaxtypemx.detailnum); j++)
            {
                LOG(LM_STD,Fmtmsg("����˰Ŀ��ϸ��ʼ..."),fpub_GetCompname(lXmlhandle))
                memset(&stTaxsubjectlist, 0x00, sizeof(stTaxsubjectlist));
                pstrcopy(stTaxsubjectlist.jyrq, stDrls.zwrq, sizeof(stTaxsubjectlist.jyrq));
				sprintf(stTaxsubjectlist.jylsh, "%d", stDrls.zhqzlsh);
                pstrcopy(stTaxsubjectlist.projectid, stTaxtypemx.projectid, sizeof(stTaxsubjectlist.projectid));

                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/DetailNo",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                pstrcopy(stTaxsubjectlist.detailno, sBuf, sizeof(stTaxsubjectlist.detailno));
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/TaxSubjectCode",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                pstrcopy(stTaxsubjectlist.taxsubjectcode, sBuf, sizeof(stTaxsubjectlist.taxsubjectcode));
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/TaxSubjectName",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                pstrcopy(stTaxsubjectlist.taxsubjectname, sBuf, sizeof(stTaxsubjectlist.taxsubjectname));
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/TaxNumber",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                pstrcopy(stTaxsubjectlist.taxnumber, sBuf, sizeof(stTaxsubjectlist.taxnumber));
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/TaxAmt",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                stTaxsubjectlist.taxamt = atof(sBuf);
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/TaxRate",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                stTaxsubjectlist.taxrate = atof(sBuf);
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/ExpTaxAmt",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                stTaxsubjectlist.exptaxamt = atof(sBuf);
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/DiscountTaxAmt",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                stTaxsubjectlist.discounttaxamt = atof(sBuf);
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/FactTaxAmt",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                stTaxsubjectlist.facttaxamt = atof(sBuf);
                
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                iRet = DBInsert("tips_taxsubjectlist", SD_TIPS_TAXSUBJECTLIST, NUMELE(SD_TIPS_TAXSUBJECTLIST), &stTaxsubjectlist, sErrmsg);
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                    
                    fpub_SetMsg(lXmlhandle, 24327, "����˰Ŀ��ϸ��ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����˰Ŀ��ϸ��ʧ��"),
                    fpub_GetCompname(lXmlhandle))
                }
                
                LOG(LM_STD,Fmtmsg("����˰Ŀ��ϸ�����..."),fpub_GetCompname(lXmlhandle))
            }
        }
        
    }
    else
    {
        fpub_SetMsg(lXmlhandle, 24211, Fmtmsg("��֧�ִ˱��ı��[%s]��ʵʱƾ֤", stDrls.msgno));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("��֧�ִ˱��ı��[%s]��ʵʱƾ֤", stDrls.msgno), fpub_GetCompname(lXmlhandle))    
        return COMPRET_FAIL ;        
    }            
    
    /* ���뵥��ƾ֤���� */
    LOG(LM_STD,Fmtmsg("����ƾ֤���ݿ�ʼ"),fpub_GetCompname(lXmlhandle))       
    iret = prv_tips_InitPZSJ_db(lXmlhandle, stDrls);
    if ( iret < 0 )
    {
         fpub_SetMsg(lXmlhandle, 24213, "����ƾ֤��Ϣʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("����ƾ֤��Ϣʧ��[%d]", iret), fpub_GetCompname(lXmlhandle))    
         return COMPRET_FAIL ;        
    }
    LOG(LM_STD,Fmtmsg("����ƾ֤���ݽ���"),fpub_GetCompname(lXmlhandle))  
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_drls \
        set spxx ='%s' where zwrq='%s' and zhqzlsh=%d",stDrls.spxx,sZwrq,iZhqzlsh);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")                
    iRet = DCIExecuteDirect(sSql1);     
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24201, "���µ�����ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))    
         return COMPRET_FAIL ;        
    }
    
    iRet =DCICommit();
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),"ERROR");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))    
    }
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�Ǽ�ƾ֤������Ϣ(����)�������"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;       
}


/************************************************************************
��̬�����������
�����������: SYW_TIPS_YzcxSFXY_DRC
�������: ��֤�볷������Э��
�������: 
  ��֤�볷������Э��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�    tips_wtgxdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: sunpj
��������: 2017��04��11��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_YzcxSFXY_DRC(HXMLTREE lXmlhandle)
{
    int iParas;
    char sTaxOrgCode[12+1];/* ���ջ��ش��� */
    char sPayBkCode[12+1];/* �������к� */
    char sPayAcct[32+1];/* �����˺� */
	char sPayAcct2[32+1];/* Э���˺� */
    char sProtocolNo[60+1];/* Э����� */
    char sProtocolNo_t[60+1];/* Э����� */
    char sHandOrgName_t[200+1];/* �ɿλ���� */
    char sTaxPayCode_t[20+1];/* ��˰�˱��� */
    char sWtgxzt[1+1];/* ί�й�ϵ״̬ */
    char sBankProtocolNo[30+1];/* �����ڲ�Э��� */

    char sBuf[256];
    char sHandOrgName[200+1];/* �ɿλ���� */
    char sTaxPayCode[20+1];/* ��˰�˱��� */
    char sVCSign[1+1];/* ��֤��־ */
	char sYzxgrq[8+1];/* ��֤�޸����� */
	char sPayOpBkCode[12+1];/* �������� */
    
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
    char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
    int iRet=0;
    
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(7);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(1, sBuf, "���ջ��ش���")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(2, sBuf, "�������к�")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "�����˺�")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(4, sBuf, "Э�����")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sHandOrgName, 0x00, sizeof(sHandOrgName));
    COMP_GETPARSEPARAS(5, sBuf, "�ɿλ����")
    pstrcopy(sHandOrgName, sBuf, sizeof(sHandOrgName));
    trim(sHandOrgName);
    LOG(LM_STD,Fmtmsg("�ɿλ����_t[%s]", sHandOrgName), fpub_GetCompname(lXmlhandle))    
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
    COMP_GETPARSEPARAS(6, sBuf, "��˰�˱���")
    pstrcopy(sTaxPayCode, sBuf, sizeof(sTaxPayCode));
    trim(sTaxPayCode);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sVCSign, 0x00, sizeof(sVCSign));
    COMP_GETPARSEPARAS(7, sBuf, "��֤��־")
    pstrcopy(sVCSign, sBuf, sizeof(sVCSign));
    trim(sVCSign);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sYzxgrq, 0x00, sizeof(sYzxgrq));
    COMP_SOFTGETXML("/tips/zwrq", sBuf);
    trim(sBuf);
    pstrcopy(sYzxgrq, sBuf, sizeof(sYzxgrq));
       
    LOG(LM_STD,Fmtmsg("��֤��������Э�鿪ʼ����... ���ջ��ش���[%s],�������к�[%s],�����˺�[%s]", 
        sTaxOrgCode, sPayBkCode, sPayAcct), fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("Э�����[%s],�ɿλ����[%s],��˰�˱���[%s],��֤��־[%s]", 
        sProtocolNo, sHandOrgName, sTaxPayCode, sVCSign), fpub_GetCompname(lXmlhandle))        

    /* ��ѯ�ͻ�ί�й�ϵ */
    memset(sWtgxzt, 0x00, sizeof(sWtgxzt));
    memset(sProtocolNo_t, 0x00, sizeof(sProtocolNo_t));
    memset(sHandOrgName_t, 0x00, sizeof(sHandOrgName_t));
    memset(sTaxPayCode_t, 0x00, sizeof(sTaxPayCode_t));
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT wtgxzt, protocolno, handorgname, taxpaycode, bankprotocolno, payacct2, payopbkcode FROM tips_wtgxdj\
        WHERE taxorgcode='%s' AND paybkcode ='%s' AND payacct ='%s' AND protocolno ='%s'",sTaxOrgCode, sPayBkCode, sPayAcct, sProtocolNo);         
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
    iRet = DBSelectToMultiVar(sErrmsg, sSql1, &sWtgxzt, &sProtocolNo_t, &sHandOrgName_t, &sTaxPayCode_t, &sBankProtocolNo, &sPayAcct2, &sPayOpBkCode);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24346, Fmtmsg("��ѯί�й�ϵ�ǼǱ�ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�ǼǱ�ʧ��"), 
            fpub_GetCompname(lXmlhandle));    
        
    }
    if ( iRet == 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24347, Fmtmsg("����Э��δǩԼ�����ջ��ش��š������˺Ų���."));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э��δǩԼ�����ջ��ش��š������˺Ų���."), 
            fpub_GetCompname(lXmlhandle));     
    }
    
    trim(sWtgxzt);
	trim(sProtocolNo_t);
    trim(sHandOrgName_t);
    trim(sTaxPayCode_t);
    LOG(LM_STD,Fmtmsg("Э�����_t[%s],�ɿλ����_t[%s],��˰�˱���_t[%s]", 
        sProtocolNo_t, sHandOrgName_t, sTaxPayCode_t), fpub_GetCompname(lXmlhandle))    

    LOG(LM_STD,Fmtmsg("�ɿλ����_t[%s]", sHandOrgName_t), fpub_GetCompname(lXmlhandle))    

    /* �ж�ί�й�ϵ״̬ */
    if ( sWtgxzt[0]=='1' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24348, Fmtmsg("����Э�鱻����"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э�鱻����"), 
            fpub_GetCompname(lXmlhandle));         
    }        
    if ( sWtgxzt[0]=='2' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24349, Fmtmsg("����Э�鱻����"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э�鱻����"), 
            fpub_GetCompname(lXmlhandle));         
    }
    if ( sWtgxzt[0]!='0' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24350, Fmtmsg("����Э��״̬�쳣"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э��״̬�쳣"), 
            fpub_GetCompname(lXmlhandle));         
    }
    /* �ж�Э������Ƿ�һ�� */
    if ( strcmp(sProtocolNo, sProtocolNo_t) != 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24351, Fmtmsg("Э����Ų�һ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("Э����Ų�һ��"), 
            fpub_GetCompname(lXmlhandle));         
    }    
    /* �жϽɿλ�����Ƿ�һ�� */
    if ( strcmp(sHandOrgName, sHandOrgName_t) != 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24352, Fmtmsg("�ɿλ���Ʋ�һ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�ɿλ���Ʋ�һ��"), 
            fpub_GetCompname(lXmlhandle));
    }
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    
    if (sVCSign[0]=='0')/* ��֤ */
    {
        snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj set yzbz='1',yzxgrq='%s' WHERE taxorgcode='%s' AND paybkcode ='%s' AND payacct ='%s' AND protocolno ='%s'",\
                         sYzxgrq, sTaxOrgCode, sPayBkCode, sPayAcct, sProtocolNo);        
        LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
        iRet = DCIExecuteDirect(sSql1);     
        if ( iRet < 0 || iRet == 0)/* add 20141215 iRet=0Ҳ��Ϊ���²��ɹ� */
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
            fpub_SetMsg(lXmlhandle, 24354, "����ί�й�ϵ�ǼǱ�ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����ί�й�ϵ�ǼǱ�ʧ��"),fpub_GetCompname(lXmlhandle))
        }
        LOG(LM_STD,Fmtmsg("����Э����֤ͨ��"), fpub_GetCompname(lXmlhandle))
		COMP_SOFTSETXML("/tips/opeflag","1");
    }
    else
    {
        snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj set yzbz='2',yzxgrq='%s' WHERE taxorgcode='%s' AND paybkcode ='%s' AND payacct ='%s' AND protocolno ='%s'",\
                       sYzxgrq, sTaxOrgCode, sPayBkCode, sPayAcct, sProtocolNo);         
        LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
        iRet = DCIExecuteDirect(sSql1);                 
        if ( iRet < 0 || iRet == 0)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
            fpub_SetMsg(lXmlhandle, 24354, "����ί�й�ϵ�ǼǱ�ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����ί�й�ϵ�ǼǱ�ʧ��"),fpub_GetCompname(lXmlhandle))
        }
        LOG(LM_STD,Fmtmsg("����Э�鳷��ͨ��"), fpub_GetCompname(lXmlhandle))
        COMP_SOFTSETXML("/tips/opeflag","3");
    }

	COMP_SOFTSETXML("/tips/inprotocol", sBankProtocolNo);
	COMP_SOFTSETXML("/tips/PayAcct2", sPayAcct2);
	COMP_SOFTSETXML("/tips/PayOpBkCode", sPayOpBkCode);
    
    fpub_SetMsg(lXmlhandle, 0, "����Э����֤�볷������ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("����Э����֤�볷������ɹ�"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}
