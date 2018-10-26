/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.0)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:BAT_CHECK.c
�ļ�����:BATCHУ�麯���������
�� Ŀ ��:�м�ҵ��ƽ̨AGENT2.1��Ʒ��
�� �� Ա:chensy YangDong
��������:2011��8��1��

�� �� Ա:YangDong
�޸�����:20141018
�޸�˵��:DCI����
*********************************************************************/
#include "gaps_head.h"
/*#include "DCI.h"*/
#include "batch_head.h"
#include "app_macro.h"
#include "app_xmlmacro.h"

#define SOCOMPVERSION "V2.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_CHECK.so</soname>\
        <sosrcname>BAT_CHECK.c</sosrcname>\
        <sonote>BATCHУ�麯���������</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"Chensy YangDong\" filesize=\"1128297\">HS-AgentV2.1����</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1128297\">DCI����</rec>\
        </version>\
        </root>";
    printf("\n================��̬���������Ϣ================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if(strlen(sversion) >= isize)
    {
        printf(" ȡ��ϸ��Ϣʧ��...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" ��鿴��ϸ��Ϣ...\n");
    
    return 0;
}
int iLrzbs,iLpwjzbs,iHZbs;
int iAuditingSn;
double dLrzje=0.00,dLpwjzje=0.00,fHZje=0.00;
char sZbs[16];
char sPtpch[8+1],sPkrq[8+1],sYwbm[50+1];
char sDsql[512]; 
char sSql1[1024]; 
char sLname[64+1],sLen[6+1];
char sCpdm[16+1];
char sShbs[50+1]; 
char sErrmsg[512]; 

/************************************************************************
��̬�����������
�����������:BATCH_CHECKALLNUM
�������:BATCH_CHECKALLNUM
�������: ����ҵ��У���ܱ����ܽ��
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
  
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT BATCH_CHECKALLNUM(HXMLTREE lXmlhandle)
{
    char sBuf[128];
    char sMsg[60];
    /*int iResult = -1;*/
    char sFileFmt[2+1];

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", "BATCH_CHECKALLNUM"),"DEBUG");

    memset(sBuf,0,sizeof(sBuf));
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf)
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));
    if(strlen(sPtpch)<=0)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        LOG(LM_DEBUG,Fmtmsg("ƽ̨���κŲ���Ϊ��"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }    
    memset(sBuf,0,sizeof(sBuf));
    memset(sPkrq,0,sizeof(sPkrq));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf)
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sYwbm,0,sizeof(sYwbm));
    COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_YWBM,sBuf)
    pstrcopy(sYwbm,sBuf,sizeof(sYwbm));
    
    /* ȡ�ⲿ�ļ��Ǽ��ܱ��� �ܽ��*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZBS,sBuf)
    iLrzbs=atoi(sBuf);
    if( iLrzbs > 0 )
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZJE,sBuf)
        dLrzje=atof(sBuf);
    }
    
    /* ȡ�����ļ����ܼ�¼����ܱ��� �ܽ��*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_HZ_ZBS,sBuf)
    iLpwjzbs=atoi(sBuf);
    if( iLpwjzbs > 0 )
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_HZ_ZJE,sBuf)
        dLpwjzje=atof(sBuf);
    }
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_MX_ZBS,sBuf)
    iHZbs=atoi(sBuf);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_MX_ZJE,sBuf)
    fHZje=atof(sBuf);
                            
    if( iLrzbs > 0 )
    {
        /* �ܱ������� */
        if( abs(iHZbs - iLrzbs) > 0 )        
        {
            LOG(LM_STD,Fmtmsg("BATCH: ¼���ܱ���[%d]����ϸ[%d]����",\
                               iLrzbs,iHZbs),"INFO");
            fpub_SetMsg(lXmlhandle,MID_BATCH_LRZBS_MXZBS,\
                        Fmtmsg(MSG_BATCH_LRZBS_MXZBS,iLrzbs,iHZbs));        
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -3;
        }
        /* �ܽ��� */
        if( fabs(fHZje - dLrzje) > 0.001 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ¼���ܽ��[%f]����ϸ�ܽ��[%f]����",\
                               dLrzje,fHZje),"INFO");
            fpub_SetMsg(lXmlhandle,MID_BATCH_LRZJE_MXZJE,\
                             Fmtmsg(MSG_BATCH_LRZJE_MXZJE,dLrzje,fHZje));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -4;
        }
    }

    memset(sBuf,0,sizeof(sBuf));
    memset(sFileFmt,0,sizeof(sFileFmt));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_FILEFMT,sBuf)
    pstrcopy(sFileFmt,sBuf,sizeof(sFileFmt));
    /* �ļ����� 02 ���ܣ�����ϸ 03 ����ϸ������ 04 ���ܣ�����ϸ������ */
    if( memcmp( sFileFmt,"01", 2 ) != 0 )
    /* 20111108 ����ǵ���ϸ��ʽ�������ܽ���ܱ���У��ʱ,��������ж�
    if( iLpwjzbs > 0 )
    */
    {
        if( abs(iHZbs - iLpwjzbs) > 0 )        
        {
            LOG(LM_STD,Fmtmsg("BATCH: �����ļ�������Ϣ�ܱ���[%d]\
                ����ϸ�ܱ���[%d]����",iLpwjzbs,iHZbs),"INFO");
            /* modified by yangdong 20121122 �ܽ���ܱ���ʧ����Ϣ�ϲ�
            fpub_SetMsg(lXmlhandle,MID_BATCH_WJZBS_MXZBS,\
                         Fmtmsg(MSG_BATCH_WJZBS_MXZBS,iLpwjzbs,iHZbs));        
            */
            fpub_SetMsg(lXmlhandle,MID_BATCH_WJZBS_MXZBS, Fmtmsg(MSG_BATCH_WJZBS_MXZBS,iLpwjzbs,iHZbs) );        
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -3;
        }
        /* �ܽ��� */
        if( fabs(fHZje - dLpwjzje) > 0.001 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: �����ļ�������Ϣ�ܽ��[%.2f]����ϸ�ܽ��[%.2f]����",\
                dLpwjzje,fHZje),"INFO");
            fpub_SetMsg(lXmlhandle,MID_BATCH_WJZJE_MXZJE,Fmtmsg(MSG_BATCH_WJZJE_MXZJE,dLpwjzje,fHZje));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -4;
        }
    }
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", "BATCH_CHECKALLNUM"), "DEBUG");

    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: BATCH_CHECKLEN
�������: BATCH_CHECKLEN
�������: ����ҵ��У�������ݳ���
�������:
��� ��������    ��������     ��Դ���         ȱʡֵ    �ɿ�    ����˵��        
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT BATCH_CHECKLEN(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    int iResult = -1;
    int iRet=-1;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");
        
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_AUDITING_AUDISN,sBuf)/*ȡ�������*/
    iAuditingSn=atoi(sBuf);
    
    memset(sShbs,0,sizeof(sShbs));
    COMP_SOFTGETXML(XMLNM_BATCH_AUDITING_AUDIID,sBuf)/*ȡ��˱�ʶ*/
    trim(sBuf);
    pstrcopy(sShbs,sBuf,sizeof(sShbs));

    memset(sPtpch,0,sizeof(sPtpch));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf)/*ȡ���κ�*/
    trim(sBuf);
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));
    
    memset(sPkrq,0,sizeof(sPkrq));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ ,sBuf)/*ȡ��������*/
    trim(sBuf);
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    /* ����һ ȡ�б�ʶ */
    memset( sLname, 0x00, sizeof( sLname ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT funcpara FROM BATCH_AUDITINGCFG\
        WHERE auditingid='%s' AND auditingsn='%d' AND funcparasn=1 ", sShbs, iAuditingSn );
    iRet = DBSelectToVarChar(sErrmsg, sLname, sSql1);
    if( iRet < 1 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_SHGZPZ,MSG_BATCH_SEL_SHGZPZ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;

    }
    trim(sLname);

    /* ������ ��˳��� */
    memset( sLen, 0x00,sizeof( sLen ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT funcpara FROM BATCH_AUDITINGCFG\
        WHERE auditingid='%s' AND auditingsn='%d' AND funcparasn=2 ", sShbs, iAuditingSn );
    iRet = DBSelectToVarChar(sErrmsg, sLen, sSql1);
    if( iRet < 1 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_SHGZPZ,MSG_BATCH_SEL_SHGZPZ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    trim(sLen);

    DCIBegin();
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_YWBM,sBuf);
    pstrcopy(sYwbm,sBuf,sizeof(sYwbm));
    memset(sDsql,0,sizeof(sDsql));
    snprintf(sDsql, sizeof( sDsql ), "UPDATE %s \
        SET shzt='1', clzt='1', cgbz='2', xym='3', xyxx='���Ȳ���'\
        WHERE pkrq='%s' AND ptpch='%s' AND LENGTH( trim( %s ) ) NOT IN ( %s )",\
        sYwbm,sPkrq,sPtpch,sLname,sLen);

    iRet = DCIExecuteDirect( sDsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("SQLEERR,sql[%s]sqlerr[%s]ret[%d]",sDsql, DCILastError(), iRet ),"ERROR");
        /*sql_RollbackTrans();*/
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_SHZT,MSG_BATCH_UPD_SHZT);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    LOG(LM_STD, Fmtmsg("���Ȳ�����¼[%d]��,sDsql[%s] iRet[%d]\n", iResult,sDsql, iRet), "DEBUG")
    
    memset(sDsql,0,sizeof(sDsql));
    snprintf(sDsql, sizeof( sDsql ), "UPDATE %s SET shzt='0' \
        WHERE pkrq='%s' AND ptpch='%s' AND LENGTH( trim( %s) ) in (%s)",\
        sYwbm,sPkrq,sPtpch,sLname,sLen);
    iRet = DCIExecuteDirect( sDsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("SQLEERR,sql[%s]sqlerr[%s]ret[%d]",sDsql, DCILastError(), iRet ),"ERROR");
        /*sql_RollbackTrans();*/
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_SHZT,MSG_BATCH_UPD_SHZT);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    LOG(LM_DEBUG, Fmtmsg("���������¼[%d]��[%s] iRet [%d]\n", iResult, sDsql, iRet ), "DEBUG")
    
    /* add by yr 20120919 */
    /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");

    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: BATCH_CHECKSIGN
�������: BATCH_CHECKSIGN
�������: ����ҵ��У����ǩԼ��ϵ
�������:
��� ��������    ��������    ��Դ���         ȱʡֵ    �ɿ�    ����˵��        
    
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT BATCH_CHECKSIGN(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    /*int iResult = -1;*/
    int  iRet = -1;
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");
        
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_AUDITING_AUDISN,sBuf)/*ȡ�������*/
    iAuditingSn=atoi(sBuf);
    
    memset(sShbs,0,sizeof(sShbs));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_AUDITING_AUDIID,sBuf)/*ȡ��˱�ʶ*/
    trim(sBuf);
    pstrcopy(sShbs,sBuf,sizeof(sShbs));
    
    memset(sPtpch,0,sizeof(sPtpch));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf)/*ȡ���κ�*/
    trim(sBuf);
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));
    
    memset(sPkrq,0,sizeof(sPkrq));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ ,sBuf)/*ȡ��������*/
    trim(sBuf);
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* ����һ �û����ֶ��� */
    memset( sLname, 0x00, sizeof( sLname ) );

    snprintf( sSql1, sizeof( sSql1 ), "SELECT funcpara FROM BATCH_AUDITINGCFG\
         WHERE auditingid='%s' AND auditingsn='%d' AND funcparasn=1 ", sShbs, iAuditingSn );
    iRet = DBSelectToVarChar(sErrmsg, sLname, sSql1);
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_SHGZPZ,MSG_BATCH_SEL_SHGZPZ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    trim(sLname);
    if( iRet == 0 || ( strlen( sLname ) < 1 ) )
        strcpy( sLname,"yhh1" );  /*  Ĭ���û��Ŵ����yhh1�ֶ��� */
   
    /*  ȡҵ����� */
    memset(sBuf,0,sizeof(sBuf));
    memset( sYwbm, 0x00, sizeof( sYwbm ) );
    COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_YWBM,sBuf);
    pstrcopy(sYwbm,sBuf,sizeof(sYwbm));
    /*  ȡ��Ʒ���� */
    memset(sBuf,0,sizeof(sBuf));
    memset(sCpdm,0,sizeof(sCpdm));
    COMP_SOFTGETXML(XMLNM_APP_DWCPXY_CPDM,sBuf);
    pstrcopy(sCpdm,sBuf,sizeof(sCpdm));

    DCIBegin();
    memset(sDsql,0,sizeof(sDsql));
    /* modified by yangdong 20120827 ����trim  */
    snprintf(sDsql, sizeof( sDsql ), "UPDATE %s SET shzt='1', clzt='1',\
        cgbz='2', xym='NOSIGN', xyxx='ǩԼ��ϵ�����ڻ���ʧЧ' \
        WHERE pkrq='%s' AND ptpch='%s' AND trim(%s) NOT IN \
        ( SELECT yhh1 FROM app_khcpqy WHERE cpdm='%s' AND qyzt='0' )",\
        sYwbm, sPkrq, sPtpch, sLname, sCpdm );
    LOG(LM_STD,Fmtmsg("ִ��SQL[%s]", sDsql ),"INFO")             
/* modified by yangdong 20130809 sql_DynExec ������sqlcode
    if( sql_DynExec(sDsql,&iResult) !=0 && !SQLNOTFOUND  )
*/
    iRet = DCIExecuteDirect( sDsql );
    if( iRet < 0  )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        /*sql_RollbackTrans();*/
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_SHZT,MSG_BATCH_UPD_SHZT);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    memset(sDsql,0,sizeof(sDsql));

    /* modified by yangdong 20120827 ����trim  */
    snprintf( sDsql, sizeof( sDsql ), "UPDATE %s SET shzt='0' \
        WHERE pkrq='%s' AND ptpch='%s' AND trim(%s) IN \
        ( SELECT yhh1 FROM app_khcpqy WHERE cpdm='%s' AND qyzt='0' )",\
        sYwbm, sPkrq, sPtpch, sLname, sCpdm );
    LOG(LM_STD,Fmtmsg("ִ��SQL[%s]", sDsql ),"INFO")       
/* modified by yangdong 20130809 sql_DynExec ������sqlcode
    if( sql_DynExec(sDsql,&iResult) !=0  && !SQLNOTFOUND )
*/
    iRet = DCIExecuteDirect( sDsql );
    if( iRet < 0  )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        /*sql_RollbackTrans();*/
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_SHZT,MSG_BATCH_UPD_SHZT);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    
    /* add by yr 20120919 */
    /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
