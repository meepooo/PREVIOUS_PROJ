/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.0)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:AGT_PUB.c
�ļ�����:����ҵ��ƽ̨�����ദ���������
�� Ŀ ��:
�� �� Ա:nierui
��������:2009��7��24��
�޸�����: 20110711
�޶�����: ������־�����ʽ
�� �� Ա:YangDong
�޸�����: 20140918
�޶�����: DCI����
*********************************************************************/

#include "gaps_head.h"
#include "../incl/agent_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
          <root>\
          <soname>AGT_PTGL.so</soname>\
          <sosrcname>AGT_PTGL.c</sosrcname>\
          <sonote>AGENTƽ̨�����������</sonote>\
          <version>\
          <rec ver=\"2.0.1.1\" modify=\"2010-4-1 15:08\" programer=\"NieRui\" filesize=\"1104980\">HS-AgentV2.0����</rec>\
          <rec ver=\"2.1.0.1\" modify=\"2011-11-1 13:08\" programer=\"S..C\" filesize=\"1129574\">HS-AgentV2.1����</rec>\
          <rec ver=\"4.1.0.1\" modify=\"2014-09-18 13:08\" programer=\"YangDong\" filesize=\"1129574\">DCI����</rec>\
          </version>\
          </root>";
    printf("\n================��̬���������Ϣ================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if (strlen(sversion) >= isize)
    {
        printf(" -->ȡ��ϸ��Ϣʧ��...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" -->��鿴��ϸ��Ϣ...\n");
    return 0;
    
}

char sSql1[512];
/******************************************************************************
�������: SAGENT_CHECK_DETAIL
�������:���ո�Ӧ����������ϸ����
����˵���������ԭ��,��������ϸΪ׼,�в�ƽʱ�ǼǶ��˲�ƽ��ͬʱ�޸ĵ�����
          ˮ����˱�־��
   
�������:
��� ��������         ��Դ���   ȱʡֵ         �Ƿ�ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
 
�� Ŀ ��: �м�ҵ���Ʒ�з���
�� �� Ա:nierui
��������:2009��2��
�޸�����:2009��7��
******************************************************************************/
IRESULT SAGENT_CHECK_DETAIL(HXMLTREE lXmlhandle)
{
    AGENT_DZLSB sdb_agent_dzlsb;
    AGENT_DRLS sdb_agent_drls;
    AGENT_DZBPB sdb_agent_dzbpb;
        
    char sRunCpdmSql[512];
    char sDelSsql[512];
    char sDzrq[8+1];
    char sYwbh[16+1];
    char sJyzt[1+1];  /* ����״̬ */
    char  sBuf[256];
    char  sSqlCond[256];
    char  sAdjust[2];     /* ������־ */
    int   iParas,i;
    int   iCount = 0;
    int   iFlag = 0;      /* 0 ����ƽ 1 ���˲�ƽ */
    int iRet =-1;
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);
 
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*����������*/
    COMP_PARACOUNTCHK(3)
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    trim(sBuf);
    memset(sDzrq,0,sizeof(sDzrq));
    memcpy(sDzrq,sBuf,sizeof(sDzrq)-1);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"ҵ����")
    trim(sBuf);
    memset(sYwbh,0,sizeof(sYwbh));
    strncpy(sYwbh, sBuf, sizeof(sYwbh)-1);

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"������־" );
    trim(sBuf);
    memset( sAdjust, 0, sizeof( sAdjust ) );
    strncpy(sAdjust, sBuf, sizeof(sAdjust)-1);
    
    memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
    memset( sSqlCond, 0, sizeof( sSqlCond ) );
    trim( sYwbh );
    if( strlen(sYwbh) > 0 )
    {
        sprintf( sSqlCond," AND trim( ywbh )='%s'",sYwbh);
    }

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    memset( sDelSsql, 0, sizeof( sDelSsql ) );
    /* 20130111  ֻɾ���������˲�ƽ������δ�����¼
    sprintf(sDelSsql, "delete from AGENT_DZBPB where dzrq='%s' %s", sDzrq,sSqlCond);
    */
    sprintf(sDelSsql, "delete from AGENT_DZBPB where dzrq='%s' AND lslx='1' AND clzt='0' %s", sDzrq,sSqlCond);
    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* ��ʼ������״̬Ϊ0 δ���� added by yangdong 20090807 */
    memset( sDelSsql, 0x00, sizeof( sDelSsql ) );
    sprintf( sDelSsql,  "UPDATE agent_drls SET zjdzbz='0' WHERE ptrq='%s'  %s ", sDzrq, sSqlCond );
    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    /* end of add */
            
    /*������,ƽ̨�޵ļ�¼--B*/
    memset( sRunCpdmSql, 0x00, sizeof( sRunCpdmSql ) );
    sprintf(sRunCpdmSql, "SELECT * FROM agent_dzlsb WHERE ptrq='%s' AND jyzt='0'  %s AND \
        ptls NOT IN (SELECT DISTINCT ptls FROM agent_drls WHERE ptrq='%s' %s AND jyzt='0')", \
        sDzrq,sSqlCond,sDzrq,sSqlCond);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"INFO");
    /*ȡ������,ƽ̨�޵���ˮ*/
    if ((cur = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    memset(&sdb_agent_dzlsb, 0, sizeof(sdb_agent_dzlsb));
    while( ( iRet = DBFetch(cur, SD_AGENT_DZLSB, NUMELE(SD_AGENT_DZLSB), &sdb_agent_dzlsb, sErrmsg ) ) > 0 )
    {
        iFlag ++;
        /*�Ǽǲ�ƽ��ˮ��*/
        memset(&sdb_agent_dzbpb, 0, sizeof(sdb_agent_dzbpb));
        memcpy(sdb_agent_dzbpb.dzrq,sDzrq,sizeof(sdb_agent_dzbpb.dzrq)-1);
        memcpy(sdb_agent_dzbpb.ptrq,sdb_agent_dzlsb.ptrq,sizeof(sdb_agent_dzbpb.ptrq)-1);
        sdb_agent_dzbpb.ptls = sdb_agent_dzlsb.ptls;
        trim( sdb_agent_dzlsb.zjrq);
        memcpy(sdb_agent_dzbpb.zjrq,sdb_agent_dzlsb.zjrq,sizeof(sdb_agent_dzbpb.zjrq)-1);
        trim( sdb_agent_dzlsb.zjls);
        memcpy(sdb_agent_dzbpb.zjls,sdb_agent_dzlsb.zjls,sizeof(sdb_agent_dzbpb.zjls)-1);
        trim( sdb_agent_dzlsb.jyjg);
        memcpy(sdb_agent_dzbpb.jyjg,sdb_agent_dzlsb.jyjg,sizeof(sdb_agent_dzbpb.jyjg)-1);
        trim( sdb_agent_dzlsb.jygy);
        memcpy(sdb_agent_dzbpb.jygy,sdb_agent_dzlsb.jygy,sizeof(sdb_agent_dzbpb.jygy)-1);
        trim( sdb_agent_dzlsb.jybz);
        memcpy(sdb_agent_dzbpb.jybz,sdb_agent_dzlsb.jybz,sizeof(sdb_agent_dzbpb.jybz)-1);
        trim( sdb_agent_dzlsb.ywbh);
        memcpy(sdb_agent_dzbpb.ywbh,sdb_agent_dzlsb.ywbh,sizeof(sdb_agent_dzbpb.ywbh)-1);
        trim( sdb_agent_dzlsb.xzbz);
        memcpy(sdb_agent_dzbpb.xzbz,sdb_agent_dzlsb.xzbz,sizeof(sdb_agent_dzbpb.xzbz)-1);
        trim( sdb_agent_dzlsb.jdbz);
        memcpy(sdb_agent_dzbpb.jdbz,sdb_agent_dzlsb.jdbz,sizeof(sdb_agent_dzbpb.jdbz)-1);
        sdb_agent_dzbpb.jyje=sdb_agent_dzlsb.jyje;
        sdb_agent_dzbpb.ptjyje=0.00;
        trim( sdb_agent_dzlsb.jfzh);
        memcpy(sdb_agent_dzbpb.jfzh,sdb_agent_dzlsb.jfzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
        trim( sdb_agent_dzlsb.jffzh);
        memcpy(sdb_agent_dzbpb.jffzh,sdb_agent_dzlsb.jffzh,sizeof(sdb_agent_dzbpb.jffzh)-1);
        trim( sdb_agent_dzlsb.dfzh);
        memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_dzlsb.dfzh,sizeof(sdb_agent_dzbpb.dfzh)-1);
        trim( sdb_agent_dzlsb.dffzh);
        memcpy(sdb_agent_dzbpb.dffzh,sdb_agent_dzlsb.dffzh,sizeof(sdb_agent_dzbpb.dffzh)-1);
        memcpy(sdb_agent_dzbpb.lslx, "1", 1); /* ��ˮ���� 1�������� */
        memcpy(sdb_agent_dzbpb.clzt, "0", 1); /* ����״̬ 0δ���� */
        memcpy(sdb_agent_dzbpb.extfld1,sdb_agent_dzlsb.extfld1,sizeof(sdb_agent_dzbpb.extfld1)-1);
        memcpy(sdb_agent_dzbpb.extfld2,sdb_agent_dzlsb.extfld2,sizeof(sdb_agent_dzbpb.extfld2)-1);
        memcpy(sdb_agent_dzbpb.extfld3,sdb_agent_dzlsb.extfld3,sizeof(sdb_agent_dzbpb.extfld3)-1);
        memcpy(sdb_agent_dzbpb.dzbz,"3",sizeof(sdb_agent_dzbpb.dzbz)-1);
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
           Fmtmsg("���˲�ƽ,�����ࣺ��������[%s] ������ˮ[%s] ƽ̨����[%s] ƽ̨��ˮ[%d]",\
           sDzrq, sdb_agent_dzbpb.zjls, sDzrq, sdb_agent_dzbpb.ptls),"INFO");
        /*�ǼǶ��˲�ƽ��*/
        iRet = DBInsert("agent_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        /*  added by yangdong 20090807 */
        memset( sJyzt, 0x00, sizeof( sJyzt ) );
        if( sAdjust[0] == '0' )  /* ����������ˮ����ƽ̨��ˮ״̬ */
        {
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            snprintf( sSql1, sizeof( sSql1 ), "SELECT jyzt FROM AGENT_DRLS WHERE ptrq='%s' AND ptls = %d", sDzrq,sdb_agent_dzlsb.ptls );
            iRet = DBSelectToVarChar(sErrmsg, sJyzt, sSql1);
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if( iRet == 0 )  /* ƽ̨�޼�¼  ��Ԥ����ˮ������£���Ӧ�ó��֣������������ض�����ˮ���� */
            {
                 LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("������ƽ̨�޼�¼ zjrq[%s] zjls[%s]", \
                         sDzrq, sdb_agent_dzlsb.zjls ),"INFO");
            }
            /* �����ɹ�ƽ̨ʧ�ܣ������ƽ̨״̬Ϊ�ɹ� */
            else 
            {
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls set jyzt='0',zjdzbz='3' \
                       WHERE ptrq ='%s' AND ptls =%d ",sDzrq, sdb_agent_dzlsb.ptls);
                iRet = DCIExecuteDirect( sSql1 ); 
                if(iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                    DCIRollback();
                    DCIFreeCursor(cur);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
               LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg(\
                       "������, ƽ̨����[%s] ƽ̨��ˮ[%d] ԭ״̬[%s] ����Ϊ�ɹ�", \
                       sDzrq, sdb_agent_dzlsb.ptls, sJyzt),"INFO");
            }
        }
        /*  end of add  */

        iCount ++;
    }
    DCIFreeCursor(cur);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("������ƽ̨�ޱ���[%d]", iCount ),"INFO");
    iCount = 0;
    /* ������,ƽ̨�޼�¼ --E*/
    
    /* ������,ƽ̨�м�¼ --B*/
    memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
    sprintf(sRunCpdmSql, " SELECT * \
                           FROM agent_drls WHERE ptrq='%s' %s AND jyzt='0' \
                           AND jydm in ('920301','920302','920303','920304')\
                           AND ptls NOT IN (SELECT DISTINCT ptls  \
                           FROM agent_dzlsb WHERE ptrq='%s' AND jyzt='0' )",sDzrq, sSqlCond, sDzrq);
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG, Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"DEBUG");
    if ((cur = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    memset(&sdb_agent_dzlsb, 0, sizeof(sdb_agent_dzlsb));
    while( ( iRet = DBFetch(cur, SD_AGENT_DRLS, NUMELE(SD_AGENT_DRLS), &sdb_agent_drls, sErrmsg ) ) > 0 )
    {
        iFlag ++;
        /*�Ǽǲ�ƽ��ˮ��*/
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
            Fmtmsg("���˲�ƽ��ƽ̨�ࣺƽ̨����=[%s],ƽ̨��ˮ=[%d]",\
            sdb_agent_drls.ptrq,sdb_agent_drls.ptls),"INFO");
        memset(&sdb_agent_dzbpb, 0, sizeof(sdb_agent_dzbpb));

        memcpy(sdb_agent_dzbpb.dzrq,sDzrq,sizeof(sdb_agent_dzbpb.dzrq)-1);
        memcpy(sdb_agent_dzbpb.ptrq,sdb_agent_drls.ptrq,sizeof(sdb_agent_dzbpb.ptrq)-1);
        sdb_agent_dzbpb.ptls = sdb_agent_drls.ptls;
        memcpy(sdb_agent_dzbpb.zjrq,sdb_agent_drls.zjrq,sizeof(sdb_agent_dzbpb.zjrq)-1);
        memcpy(sdb_agent_dzbpb.zjls,sdb_agent_drls.zjlsh,sizeof(sdb_agent_dzbpb.zjls)-1);
        memcpy(sdb_agent_dzbpb.jyjg,sdb_agent_drls.jyjg,sizeof(sdb_agent_dzbpb.jyjg)-1);
        memcpy(sdb_agent_dzbpb.jygy,sdb_agent_drls.jygy,sizeof(sdb_agent_dzbpb.jygy)-1);
        memcpy(sdb_agent_dzbpb.jybz,sdb_agent_drls.jybz,sizeof(sdb_agent_dzbpb.jybz)-1);
        memcpy(sdb_agent_dzbpb.ywbh,sdb_agent_drls.ywbh,sizeof(sdb_agent_dzbpb.ywbh)-1);
        memcpy(sdb_agent_dzbpb.xzbz,sdb_agent_drls.xzbz,sizeof(sdb_agent_dzbpb.xzbz)-1);
        memcpy(sdb_agent_dzbpb.jdbz,sdb_agent_drls.jdbz,sizeof(sdb_agent_dzbpb.jdbz)-1);
        sdb_agent_dzbpb.ptjyje=sdb_agent_drls.jyje;
        sdb_agent_dzbpb.jyje=0.00;
        if( sdb_agent_drls.jdbz[0]='D' )
        {
            memcpy(sdb_agent_dzbpb.jfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
        }
        else
        {
            memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
        }
        memcpy(sdb_agent_dzbpb.lslx, "1", 1); /* ��ˮ���� 1�������� */
        memcpy(sdb_agent_dzbpb.clzt, "0", 1); /* ����״̬ 0δ���� */
        memcpy(sdb_agent_dzbpb.extfld1,sdb_agent_drls.extfld1,sizeof(sdb_agent_dzbpb.extfld1)-1);
        memcpy(sdb_agent_dzbpb.extfld2,sdb_agent_drls.extfld2,sizeof(sdb_agent_dzbpb.extfld2)-1);
        memcpy(sdb_agent_dzbpb.extfld3,sdb_agent_drls.extfld3,sizeof(sdb_agent_dzbpb.extfld3)-1);
        memcpy(sdb_agent_dzbpb.dzbz,"2",sizeof(sdb_agent_dzbpb.dzbz)-1);
        
        /*�ǼǶ��˲�ƽ��*/
        iRet = DBInsert("agent_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        /*  added by yangdong 20090807 */
        if( sAdjust[0] == '0' )  /* ������ ��ƽ̨�� ������ƽ̨״̬Ϊ ʧ�� */
        {
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls SET jyzt='1', zjdzbz='2' \
                WHERE ptrq ='%s' AND ptls =%d ",sDzrq, sdb_agent_drls.ptls);
            iRet = DCIExecuteDirect( sSql1 ); 
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("������ƽ̨�� ptrq[%s] ptls[%d] ����Ϊʧ�� ", \
                                     sDzrq, sdb_agent_drls.ptls ),"INFO");
        }
        /*  end of add  */

        iCount ++;
    }
    DCIFreeCursor(cur);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("������ƽ̨�б���[%d]", iCount ),"INFO");
    /*������,ƽ̨�м�¼ --E*/

    /* ���¶���״̬ added by yangdong 20090807 */
    memset( sDelSsql, 0x00, sizeof( sDelSsql ) );
    sprintf( sDelSsql,  "UPDATE agent_drls SET zjdzbz='1' \
        WHERE ( ptrq='%s' ) %s AND zjdzbz = '0' ", sDzrq, sSqlCond );
    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    /* end */
   
    if( iFlag == 0 )
    {
        COMP_HARDSETXML( XMLNM_AGENT_RESP_ZJDZZT, "0" );  /* ��������״̬ 0 ƽ */
    }
    else
    {
        COMP_HARDSETXML( XMLNM_AGENT_RESP_ZJDZZT, "1" );  /* ��������״̬ 1 ��ƽ */
    }
    
    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC; 
}


/******************************************************************************
�������: SAgent_PreBptz
�������:���ո�Ӧ��������ƽ����Ԥ����
����˵��:��֯��ѯ���˲�ƽ��SQL ��where����
   
�������:
��� ��������         ��Դ���   ȱʡֵ         �Ƿ�ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
 
�� Ŀ ��: �м�ҵ���Ʒ�з���
�� �� Ա:nierui
��������:2009��7��
�޸�����:
******************************************************************************/
IRESULT SAgent_PreBptz(HXMLTREE lXmlhandle)
{
    int   iYptlsh;
    char  sPtrq[8+1],sYzjlsh[16+1];
    char  sZjrq[10+1];
    char  sSqlCond[256],sYptlsh[8+1];
    char  sBuf[256],sXmlNode[128];
    int   iParas,i;

    fpub_InitSoComp(lXmlhandle);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
      
    /*����������*/
    COMP_PARACOUNTCHK(5)
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"ƽ̨����")
    trim(sBuf);
    memset(sPtrq,0,sizeof(sPtrq));
    memcpy(sPtrq,sBuf,sizeof(sPtrq)-1);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"ԭƽ̨��ˮ��")
    trim(sBuf);
    memset(sYptlsh,0,sizeof(sYptlsh));
    strncpy(sYptlsh, sBuf, sizeof(sYptlsh)-1);
    iYptlsh = atoi(sYptlsh);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"ԭ������ˮ��")
    trim(sBuf);
    memset(sYzjlsh,0,sizeof(sYzjlsh));
    strncpy(sYzjlsh, sBuf, sizeof(sYzjlsh)-1);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"��������")
    trim(sBuf);
    memset(sZjrq,0,sizeof(sZjrq));
    strncpy(sZjrq, sBuf, sizeof(sZjrq)-1);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARAS(5,sBuf,"���SQL")
    trim(sBuf);
    memset(sXmlNode,0,sizeof(sXmlNode));
    memcpy(sXmlNode,sBuf,sizeof(sXmlNode)-1);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("zjrq=[%s] zjls=[%s] ptrq=[%s] ptls=[%d]",sZjrq, sYzjlsh, sPtrq, iYptlsh ),"DEBUG");
    
    memset(sSqlCond,0,sizeof(sSqlCond));
    /* �����������ں�������ˮ�ţ���������ˮ������ */
    if( ( strlen(sZjrq) == 8 ) && ( strlen( sYzjlsh ) > 0 ) )
    {
        sprintf(sSqlCond, " WHERE  zjrq='%s' AND zjls='%s'", sZjrq, sYzjlsh );
    }
    else
    {
        if( strlen( sPtrq ) != 8 || iYptlsh <= 0 )
        {
            fpub_SetMsg(lXmlhandle,MID_AGENT_SERIAL_NOTFOUND ,MSG_AGENT_SERIAL_NOTFOUND );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        sprintf(sSqlCond, " WHERE  ptrq='%s' AND ptls=%d", sPtrq, iYptlsh );
      
    }
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("sSqlCond=[%s]",sSqlCond),"DEBUG");
      
    COMP_HARDSETXML(sXmlNode,sSqlCond);
      
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC; 
}

/******************************************************************************
�������: SAgent_InsDzbpb
�������:�����������˲�ƽ������ˮ
����˵��:
   
�������:
��� ��������         ��Դ���   ȱʡֵ         �Ƿ�ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
 
�� Ŀ ��: �м�ҵ���Ʒ�з���
�� �� Ա:nierui
��������:2009��7��
�޸�����:
******************************************************************************/
IRESULT SAgent_InsDzbpb(HXMLTREE lXmlhandle)
{
    AGENT_DZBPB    sdb_agent_dzbpb;
    
    char sErrmsg[256];
    char  sbuf[256];
    int   iParas;
    int iRet =-1;

    fpub_InitSoComp(lXmlhandle);
  
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    memset(&sdb_agent_dzbpb,0,sizeof(sdb_agent_dzbpb));
    
    /*��������*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_DZRQ,sbuf);
    memcpy(sdb_agent_dzbpb.dzrq,sbuf,sizeof(sdb_agent_dzbpb.dzrq)-1);

    /*ƽ̨����*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_ZWRQ,sbuf);
    memcpy(sdb_agent_dzbpb.ptrq,sbuf,sizeof(sdb_agent_dzbpb.ptrq)-1);
    
    /*ƽ̨��ˮ��*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_ZHQZLSH,sbuf);
    sdb_agent_dzbpb.ptls = atoi(sbuf);
    
    /*��������*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_ZJRQ,sbuf);
    memcpy(sdb_agent_dzbpb.zjrq,sbuf,sizeof(sdb_agent_dzbpb.zjrq)-1);
    
    /*������ˮ��*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_ZJLS,sbuf);
    trim( sbuf );
    memcpy(sdb_agent_dzbpb.zjls,sbuf,sizeof(sdb_agent_dzbpb.zjls)-1);
    
    /*���׻���*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JYJG,sbuf);
    trim( sbuf );
    memcpy(sdb_agent_dzbpb.jyjg,sbuf,sizeof(sdb_agent_dzbpb.jyjg)-1);
    
    /*���׹�Ա*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JYGY,sbuf);
    memcpy(sdb_agent_dzbpb.jygy,sbuf,sizeof(sdb_agent_dzbpb.jygy)-1);
    trim( sdb_agent_dzbpb.jygy);
    
    /*���ױ���*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JYBZ,sbuf);
    memcpy(sdb_agent_dzbpb.jybz,sbuf,sizeof(sdb_agent_dzbpb.jybz)-1);
    trim( sdb_agent_dzbpb.jybz);
    
    /*ҵ����*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_YWBH,sbuf);
    memcpy(sdb_agent_dzbpb.ywbh,sbuf,sizeof(sdb_agent_dzbpb.ywbh)-1);
    trim( sdb_agent_dzbpb.ywbh);
    
    /*��ת��־*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_XZBZ,sbuf);
    memcpy(sdb_agent_dzbpb.xzbz,sbuf,sizeof(sdb_agent_dzbpb.xzbz)-1);
    trim( sdb_agent_dzbpb.xzbz);
    
    /*�����ʶ*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JDBZ,sbuf);
    memcpy(sdb_agent_dzbpb.jdbz,sbuf,sizeof(sdb_agent_dzbpb.jdbz)-1);
    trim( sdb_agent_dzbpb.jdbz);
    
    /*���׽��*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JYJE,sbuf);
    sdb_agent_dzbpb.jyje = atof(sbuf);
    
    /*ƽ̨���׽��*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_PTJYJE,sbuf);
    sdb_agent_dzbpb.ptjyje = atof(sbuf);
    
    /*�跽�ʺ�*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JFZH,sbuf);
    memcpy(sdb_agent_dzbpb.jfzh,sbuf,sizeof(sdb_agent_dzbpb.jfzh)-1);
    trim( sdb_agent_dzbpb.jfzh);
    
    /*�跽���ʺ�*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JFFZH,sbuf);
    memcpy(sdb_agent_dzbpb.jffzh,sbuf,sizeof(sdb_agent_dzbpb.jffzh)-1);
    trim( sdb_agent_dzbpb.jffzh);
    
    /*�����ʺ�*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_DFZH,sbuf);
    memcpy(sdb_agent_dzbpb.dfzh,sbuf,sizeof(sdb_agent_dzbpb.dfzh)-1);
    trim( sdb_agent_dzbpb.dfzh);
    
    /*�������ʺ�*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_DFFZH,sbuf);
    memcpy(sdb_agent_dzbpb.dffzh,sbuf,sizeof(sdb_agent_dzbpb.dffzh)-1);
    trim( sdb_agent_dzbpb.dffzh);
    
    /*ҵ����ˮ��*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_YWLSH,sbuf);
    memcpy(sdb_agent_dzbpb.ywlsh,sbuf,sizeof(sdb_agent_dzbpb.ywlsh)-1);
    trim( sdb_agent_dzbpb.ywlsh);
    
    /*ҵ������*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_YWRQ,sbuf);
    memcpy(sdb_agent_dzbpb.ywrq,sbuf,sizeof(sdb_agent_dzbpb.ywrq)-1);
    
    /*��չ�ֶ�1*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_EXTFLD1,sbuf);
    memcpy(sdb_agent_dzbpb.extfld1,sbuf,sizeof(sdb_agent_dzbpb.extfld1)-1);
    
    /*��չ�ֶ�2*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_EXTFLD2,sbuf);
    memcpy(sdb_agent_dzbpb.extfld2,sbuf,sizeof(sdb_agent_dzbpb.extfld2)-1);
    
    /*��չ�ֶ�3*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_EXTFLD3,sbuf);
    memcpy(sdb_agent_dzbpb.extfld3,sbuf,sizeof(sdb_agent_dzbpb.extfld3)-1);

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    /*�ǼǶ��˲�ƽ��*/
    iRet = DBInsert("app_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    DCICommit();

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC; 
}


/******************************************************************************
�������: SAGENT_CHECK
�������:�ɷ�ƽ̨���������ϵͳ����
����˵���������ԭ��,��������ϸΪ׼,�в�ƽʱ�ǼǶ��˲�ƽ��ͬʱ�޸ĵ�����
          ˮ����˱�־��
   
�������:
��� ��������         ��Դ���   ȱʡֵ         �Ƿ�ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
 
�� Ŀ ��:
�� �� Ա:fuyw13006
��������:2016��11��
�޸�����:2016��11��
******************************************************************************/
IRESULT SAGENT_CHECK(HXMLTREE lXmlhandle)
{
    AGENT_DZLSB sdb_agent_dzlsb;
    AGENT_DRLS sdb_agent_drls;
    AGENT_DZBPB sdb_agent_dzbpb;
    APP_DWCPXY  sdb_app_dwcpxy;
        
    char sRunCpdmSql[512];
    char sDelSsql[512];
    char sDzrq[8+1];
    char sYwbh[16+1];
    char sJyzt[1+1];  /* ����״̬ */
    char sJzxt[2+1];  /* ����ϵͳ */
    char sBuf[256];
    char  sSqlCond[100];
    char  sSqlDzrq[100];
    char  sAdjust[2];  /* ������־ */
    int   iParas,i;
    int   iCount = 0;
    int   iFlag = 0;  /* 0 ����ƽ 1 ���˲�ƽ */
    int   iRet =-1;
    int   iFlag_msg=0; /*�Ƿ�������(����е�����Ҫ���Ͷ���֪ͨ),0-û�� 1-��*/
    CURSOR cur;
    CURSOR cur1;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);
 
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*����������*/
    COMP_PARACOUNTCHK(4)
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    trim(sBuf);
    memset(sDzrq,0,sizeof(sDzrq));
    memcpy(sDzrq,sBuf,sizeof(sDzrq)-1);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"ҵ����")
    trim(sBuf);
    memset(sYwbh,0,sizeof(sYwbh));
    strncpy(sYwbh, sBuf, sizeof(sYwbh)-1);

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"������־" );
    trim(sBuf);
    memset( sAdjust, 0, sizeof( sAdjust ) );
    strncpy(sAdjust, sBuf, sizeof(sAdjust)-1);

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"����ϵͳ" );
    trim(sBuf);
    memset( sJzxt, 0, sizeof( sJzxt ) );
    strncpy(sJzxt, sBuf, sizeof(sJzxt)-1);
    
    memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
    memset( sSqlCond, 0, sizeof( sSqlCond ) );
    trim( sYwbh );
    if( strlen(sYwbh) > 0 )
    {
        sprintf( sSqlCond," AND trim( ywbh )='%s'",sYwbh);
    }
    
    /*��ͬϵͳ�Բ�ͬ����Ϊ׼*/
    memset( sSqlDzrq, 0, sizeof( sSqlDzrq ) );
    switch(atoi(sJzxt))
    {
    case 1:/*����*/
        sprintf( sSqlDzrq," ptrq='%s'",sDzrq);
        break;
    case 3:/*֧������*/
        sprintf( sSqlDzrq," zjrq='%s'",sDzrq);
        break;
    case 5: /*�����˻�*/
    sprintf( sSqlDzrq," ptrq='%s'",sDzrq);
    break;
    case 2:/*�Ŵ�����*/
    case 4:/*������*/
    default:
        LOG(LM_STD,Fmtmsg("����ʧ��:����ϵͳ����[%s]",sJzxt ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    memset( sDelSsql, 0, sizeof( sDelSsql ) );
    sprintf(sDelSsql, "delete from AGENT_DZBPB where dzrq='%s' and EXTFLD2='%s' %s",sDzrq,sJzxt,sSqlCond);
    LOG(LM_STD,Fmtmsg("ɾ�����˲�ƽ��[%s]",sDelSsql ),"INFO")

    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��[%s]",sDelSsql ),"ERROR")
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* ��ʼ������״̬Ϊ0 δ���� added by yangdong 20090807 */
    memset( sDelSsql, 0x00, sizeof( sDelSsql ) );
    sprintf( sDelSsql,  "UPDATE agent_drls SET zjdzbz='0' WHERE %s %s AND EXTFLD2='%s'AND ZJDZBZ<>9", sSqlDzrq, sSqlCond ,sJzxt);
    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��[%s]",sDelSsql ),"ERROR")
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    /* end of add */

    /*add by zhandongdong 20171012 ���µ�����ˮ��,��״̬Ϊ'2'�İ��յ����˻������ļ�Ϊ׼���и���*/
    if(atoi(sJzxt)==5)
    {
        /*�����ʻ��͹����Ķ����ļ�����ֻ�����д���ɹ��ļ�¼*/
        /*��������ļ����������еļ�¼��,����Ϊ�ɹ�  AND jyzt='0'*/   
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls SET jyzt='0' , zjdzbz='1'\
        WHERE %s %s  AND ZJDZBZ<>9 AND jyzt='2' AND extfld2='05' AND trim(zjlsh) IN\
        (SELECT DISTINCT trim(zjls) FROM agent_dzlsb WHERE %s AND extfld2='05' )",sSqlDzrq, sSqlCond, sSqlDzrq);
    
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sSql1),"INFO");
        iRet = DCIExecuteDirect( sSql1 ); 
        if( iRet < 0 )
        { 
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /*��������ļ������������еļ�¼��,����Ϊʧ��*/ 
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls SET jyzt='1' , zjdzbz='1'\
        WHERE %s %s  AND ZJDZBZ<>9 AND jyzt='2' AND extfld2='05' AND trim(zjlsh) NOT IN\
        (SELECT DISTINCT trim(zjls) FROM agent_dzlsb WHERE %s AND extfld2='05')",sSqlDzrq, sSqlCond, sSqlDzrq);
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sSql1),"INFO");
        iRet = DCIExecuteDirect( sSql1 ); 
        if( iRet < 0 )
        { 
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        /*���½ɷ������,20-�����еĸ���Ϊ(��ˮ��-0 21-�ѽ�) (��ˮ��-1 90-��ʼ)*/
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_jfxq set zt='90' where jfrq='%s' and jfls in\
        (select char(ptls) from agent_drls where ptrq='%s' and jyzt='1' and extfld2='05' )",sDzrq,sDzrq);
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sSql1),"INFO");
        iRet = DCIExecuteDirect( sSql1 ); 
        if( iRet < 0 )
        { 
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_jfxq set zt='21' where jfrq='%s' and jfls in\
        (select char(ptls) from agent_drls where ptrq='%s' and jyzt='0' and extfld2='05' )",sDzrq,sDzrq);
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sSql1),"INFO");
        iRet = DCIExecuteDirect( sSql1 ); 
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    /*end by zhandongdong */
        
    /*������,ƽ̨�޵ļ�¼--B*/
    memset( sRunCpdmSql, 0x00, sizeof( sRunCpdmSql ) );
    sprintf(sRunCpdmSql, "SELECT * FROM agent_dzlsb WHERE %s AND jyzt='0'  %s AND \
        trim(zjls) NOT IN (SELECT DISTINCT trim(zjlsh) FROM agent_drls WHERE %s %s AND jyzt='0')\
        AND EXTFLD2='%s'AND ZJDZBZ<>9",sSqlDzrq,sSqlCond,sSqlDzrq,sSqlCond,sJzxt);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"INFO");
    /*ȡ������,ƽ̨�޵���ˮ*/
    if ((cur = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    memset(&sdb_agent_dzlsb, 0, sizeof(sdb_agent_dzlsb));
    while( ( iRet = DBFetch(cur, SD_AGENT_DZLSB, NUMELE(SD_AGENT_DZLSB), &sdb_agent_dzlsb, sErrmsg ) ) > 0 )
    {
        iFlag ++;
        /*�Ǽǲ�ƽ��ˮ��*/
        memset(&sdb_agent_dzbpb, 0, sizeof(sdb_agent_dzbpb));
        memcpy(sdb_agent_dzbpb.dzrq,sDzrq,sizeof(sdb_agent_dzbpb.dzrq)-1);
        memcpy(sdb_agent_dzbpb.ptrq,sdb_agent_dzlsb.ptrq,sizeof(sdb_agent_dzbpb.ptrq)-1);
        sdb_agent_dzbpb.ptls = sdb_agent_dzlsb.ptls;
        trim( sdb_agent_dzlsb.zjrq);
        memcpy(sdb_agent_dzbpb.zjrq,sdb_agent_dzlsb.zjrq,sizeof(sdb_agent_dzbpb.zjrq)-1);
        trim( sdb_agent_dzlsb.zjls);
        memcpy(sdb_agent_dzbpb.zjls,sdb_agent_dzlsb.zjls,sizeof(sdb_agent_dzbpb.zjls)-1);
        trim( sdb_agent_dzlsb.jyjg);
        memcpy(sdb_agent_dzbpb.jyjg,sdb_agent_dzlsb.jyjg,sizeof(sdb_agent_dzbpb.jyjg)-1);
        trim( sdb_agent_dzlsb.jygy);
        memcpy(sdb_agent_dzbpb.jygy,sdb_agent_dzlsb.jygy,sizeof(sdb_agent_dzbpb.jygy)-1);
        trim( sdb_agent_dzlsb.jybz);
        memcpy(sdb_agent_dzbpb.jybz,sdb_agent_dzlsb.jybz,sizeof(sdb_agent_dzbpb.jybz)-1);
        trim( sdb_agent_dzlsb.ywbh);
        memcpy(sdb_agent_dzbpb.ywbh,sdb_agent_dzlsb.ywbh,sizeof(sdb_agent_dzbpb.ywbh)-1);
        trim( sdb_agent_dzlsb.xzbz);
        memcpy(sdb_agent_dzbpb.xzbz,sdb_agent_dzlsb.xzbz,sizeof(sdb_agent_dzbpb.xzbz)-1);
        trim( sdb_agent_dzlsb.jdbz);
        memcpy(sdb_agent_dzbpb.jdbz,sdb_agent_dzlsb.jdbz,sizeof(sdb_agent_dzbpb.jdbz)-1);
        sdb_agent_dzbpb.jyje=sdb_agent_dzlsb.jyje;
        sdb_agent_dzbpb.ptjyje=0.00;
        trim( sdb_agent_dzlsb.jfzh);
        memcpy(sdb_agent_dzbpb.jfzh,sdb_agent_dzlsb.jfzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
        trim( sdb_agent_dzlsb.jffzh);
        memcpy(sdb_agent_dzbpb.jffzh,sdb_agent_dzlsb.jffzh,sizeof(sdb_agent_dzbpb.jffzh)-1);
        trim( sdb_agent_dzlsb.dfzh);
        memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_dzlsb.dfzh,sizeof(sdb_agent_dzbpb.dfzh)-1);
        trim( sdb_agent_dzlsb.dffzh);
        memcpy(sdb_agent_dzbpb.dffzh,sdb_agent_dzlsb.dffzh,sizeof(sdb_agent_dzbpb.dffzh)-1);
        memcpy(sdb_agent_dzbpb.lslx, "1", 1); /* ��ˮ���� 1�������� */
        memcpy(sdb_agent_dzbpb.clzt, "0", 1); /* ����״̬ 0δ���� */
        memcpy(sdb_agent_dzbpb.extfld1,sdb_agent_dzlsb.extfld1,sizeof(sdb_agent_dzbpb.extfld1)-1);
        memcpy(sdb_agent_dzbpb.extfld2,sdb_agent_dzlsb.extfld2,sizeof(sdb_agent_dzbpb.extfld2)-1);
        memcpy(sdb_agent_dzbpb.extfld3,"1",1);
        memcpy(sdb_agent_dzbpb.dzbz,"3",1);
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
           Fmtmsg("���˲�ƽ,�����ࣺ��������[%s] ������ˮ[%s] ҵ������[%s] ƽ̨��ˮ[%d]",\
           sDzrq, sdb_agent_dzbpb.zjls, sDzrq, sdb_agent_dzbpb.ptls),"INFO");
        /*�ǼǶ��˲�ƽ��*/
        iRet = DBInsert("agent_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }

        iCount ++;
    }
    DCIFreeCursor(cur);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("������ƽ̨�ޱ���[%d]", iCount ),"INFO");
    iCount = 0;
    /* ������,ƽ̨�޼�¼ --E*/
    
    /**mod by zhandongdong  �����˻��������м�ҵ��Ϊ׼**/
    if(atoi(sJzxt)==5)
    {
        /* �����˻���,ƽ̨�м�¼ --B*/
        memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
        sprintf(sRunCpdmSql, "SELECT * FROM agent_drls WHERE %s %s AND jyzt='0'\
             AND ZJDZBZ<>9 AND trim(zjlsh) NOT IN\
            (SELECT DISTINCT trim(zjls) FROM agent_dzlsb WHERE %s %s AND jyzt='0' )\
            AND extfld2='%s'",
            sSqlDzrq, sSqlCond, sSqlDzrq,sSqlCond, sJzxt);
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG, Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"DEBUG");
        if ((cur = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        memset(&sdb_agent_dzlsb, 0, sizeof(sdb_agent_dzlsb));
        while( ( iRet = DBFetch(cur, SD_AGENT_DRLS, NUMELE(SD_AGENT_DRLS), &sdb_agent_drls, sErrmsg ) ) > 0 )
        {
            /*add by ���ݵ�λ��Ż�ȡ��λ�տ��ڲ��˺�*/
            memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
            memset(&sdb_app_dwcpxy, 0, sizeof(sdb_app_dwcpxy));
            sprintf(sRunCpdmSql, "SELECT * FROM app_dwcpxy WHERE ywbh='%s'",sYwbh);
            
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG, Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"DEBUG");
            if ((cur1 = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }
            if (DCIExecute(cur1) == -1)
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIFreeCursor(cur1);
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }
            if(DBFetch(cur1, SD_APP_DWCPXY, NUMELE(SD_APP_DWCPXY), &sdb_app_dwcpxy, sErrmsg ) ==0)
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                DCIRollback();
                DCIFreeCursor(cur1);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG, Fmtmsg("sRunCpdmSql=[%s]",sdb_app_dwcpxy.nbhzh),"DEBUG");
            
            iFlag ++;
            /*�Ǽǲ�ƽ��ˮ��*/
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
                Fmtmsg("���˲�ƽ��ƽ̨�ࣺҵ������=[%s],ƽ̨��ˮ=[%d]",\
                sdb_agent_drls.ywrq,sdb_agent_drls.ptls),"INFO");
            memset(&sdb_agent_dzbpb, 0, sizeof(sdb_agent_dzbpb));
    
            memcpy(sdb_agent_dzbpb.dzrq,sDzrq,sizeof(sdb_agent_dzbpb.dzrq)-1);
            memcpy(sdb_agent_dzbpb.ptrq,sdb_agent_drls.ptrq,sizeof(sdb_agent_dzbpb.ptrq)-1);
            sdb_agent_dzbpb.ptls = sdb_agent_drls.ptls;
            memcpy(sdb_agent_dzbpb.zjrq,sdb_agent_drls.zjrq,sizeof(sdb_agent_dzbpb.zjrq)-1);
            memcpy(sdb_agent_dzbpb.zjls,sdb_agent_drls.zjlsh,sizeof(sdb_agent_dzbpb.zjls)-1);
            memcpy(sdb_agent_dzbpb.jyjg,sdb_agent_drls.jyjg,sizeof(sdb_agent_dzbpb.jyjg)-1);
            memcpy(sdb_agent_dzbpb.jygy,sdb_agent_drls.jygy,sizeof(sdb_agent_dzbpb.jygy)-1);
            memcpy(sdb_agent_dzbpb.jybz,sdb_agent_drls.jybz,sizeof(sdb_agent_dzbpb.jybz)-1);
            memcpy(sdb_agent_dzbpb.ywbh,sdb_agent_drls.ywbh,sizeof(sdb_agent_dzbpb.ywbh)-1);
            memcpy(sdb_agent_dzbpb.xzbz,sdb_agent_drls.xzbz,sizeof(sdb_agent_dzbpb.xzbz)-1);
            memcpy(sdb_agent_dzbpb.jdbz,sdb_agent_drls.jdbz,sizeof(sdb_agent_dzbpb.jdbz)-1);
            sdb_agent_dzbpb.ptjyje=sdb_agent_drls.jyje;
            sdb_agent_dzbpb.jyje=0.00;
            if( sdb_agent_drls.jdbz[0]='D' )
            {
                memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.dfzh)-1);
                memcpy(sdb_agent_dzbpb.jfzh,sdb_app_dwcpxy.nbhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
            }
            else
            {
                memcpy(sdb_agent_dzbpb.jfzh,sdb_app_dwcpxy.nbhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
                memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.dfzh)-1);
            }
            memcpy(sdb_agent_dzbpb.lslx, "1", 1); /* ��ˮ���� 1�������� */
            memcpy(sdb_agent_dzbpb.clzt, "0", 1); /* ����״̬ 0δ���� */
            memcpy(sdb_agent_dzbpb.extfld1,sdb_agent_drls.extfld1,sizeof(sdb_agent_dzbpb.extfld1)-1);
            memcpy(sdb_agent_dzbpb.extfld2,sdb_agent_drls.extfld2,sizeof(sdb_agent_dzbpb.extfld2)-1);
            memcpy(sdb_agent_dzbpb.extfld3,"1",1);
            memcpy(sdb_agent_dzbpb.dzbz,"2",1);
            
            /*���Զ����˵ǲżǶ��˲�ƽ��*/ 
            if( sAdjust[0] == '1' ) 
            {
                iRet = DBInsert("agent_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    DCIRollback();
                    DCIFreeCursor(cur);
                    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                    return COMPRET_FAIL;
                }
            }
            else if( sAdjust[0] == '0' )  /* ������ ��ƽ̨�� ������ƽ̨״̬Ϊ ʧ�� */
            {
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls SET jyzt='1', zjdzbz='1' \
                    WHERE %s AND ptls =%d  AND ZJDZBZ<>9",sSqlDzrq, sdb_agent_drls.ptls);
                iRet = DCIExecuteDirect( sSql1 ); 
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                    DCIRollback();
                    DCIFreeCursor(cur);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
    
                iFlag--;//�����󣬶��˽������޹�
    
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("������ƽ̨�� ptrq[%s] ptls[%d] ����Ϊʧ�� ", \
                                         sDzrq, sdb_agent_drls.ptls ),"INFO");
            }
            iCount ++;
        }
        DCIFreeCursor(cur);
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("������ƽ̨�б���[%d]", iCount ),"INFO");
        /*�����˻���,ƽ̨�м�¼ --E*/     
    }
    else
    {
        /* ������,ƽ̨�м�¼ --B*/
        memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
        sprintf(sRunCpdmSql, "SELECT * FROM agent_drls WHERE %s %s AND jyzt='0'\
             AND ZJDZBZ<>9 AND trim(zjlsh) NOT IN\
            (SELECT DISTINCT trim(zjls) FROM agent_dzlsb WHERE %s AND jyzt='0' )\
            AND extfld2='%s'",
            sSqlDzrq, sSqlCond, sSqlDzrq,sJzxt);
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG, Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"DEBUG");
        if ((cur = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        memset(&sdb_agent_dzlsb, 0, sizeof(sdb_agent_dzlsb));
        while( ( iRet = DBFetch(cur, SD_AGENT_DRLS, NUMELE(SD_AGENT_DRLS), &sdb_agent_drls, sErrmsg ) ) > 0 )
        {
            iFlag ++;
            /*�Ǽǲ�ƽ��ˮ��*/
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
                Fmtmsg("���˲�ƽ��ƽ̨�ࣺҵ������=[%s],ƽ̨��ˮ=[%d]",\
                sdb_agent_drls.ywrq,sdb_agent_drls.ptls),"INFO");
            memset(&sdb_agent_dzbpb, 0, sizeof(sdb_agent_dzbpb));
    
            memcpy(sdb_agent_dzbpb.dzrq,sDzrq,sizeof(sdb_agent_dzbpb.dzrq)-1);
            memcpy(sdb_agent_dzbpb.ptrq,sdb_agent_drls.ptrq,sizeof(sdb_agent_dzbpb.ptrq)-1);
            sdb_agent_dzbpb.ptls = sdb_agent_drls.ptls;
            memcpy(sdb_agent_dzbpb.zjrq,sdb_agent_drls.zjrq,sizeof(sdb_agent_dzbpb.zjrq)-1);
            memcpy(sdb_agent_dzbpb.zjls,sdb_agent_drls.zjlsh,sizeof(sdb_agent_dzbpb.zjls)-1);
            memcpy(sdb_agent_dzbpb.jyjg,sdb_agent_drls.jyjg,sizeof(sdb_agent_dzbpb.jyjg)-1);
            memcpy(sdb_agent_dzbpb.jygy,sdb_agent_drls.jygy,sizeof(sdb_agent_dzbpb.jygy)-1);
            memcpy(sdb_agent_dzbpb.jybz,sdb_agent_drls.jybz,sizeof(sdb_agent_dzbpb.jybz)-1);
            memcpy(sdb_agent_dzbpb.ywbh,sdb_agent_drls.ywbh,sizeof(sdb_agent_dzbpb.ywbh)-1);
            memcpy(sdb_agent_dzbpb.xzbz,sdb_agent_drls.xzbz,sizeof(sdb_agent_dzbpb.xzbz)-1);
            memcpy(sdb_agent_dzbpb.jdbz,sdb_agent_drls.jdbz,sizeof(sdb_agent_dzbpb.jdbz)-1);
            sdb_agent_dzbpb.ptjyje=sdb_agent_drls.jyje;
            sdb_agent_dzbpb.jyje=0.00;
            if( sdb_agent_drls.jdbz[0]='D' )
            {
                memcpy(sdb_agent_dzbpb.jfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
            }
            else
            {
                memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
            }
            memcpy(sdb_agent_dzbpb.lslx, "1", 1); /* ��ˮ���� 1�������� */
            memcpy(sdb_agent_dzbpb.clzt, "0", 1); /* ����״̬ 0δ���� */
            memcpy(sdb_agent_dzbpb.extfld1,sdb_agent_drls.extfld1,sizeof(sdb_agent_dzbpb.extfld1)-1);
            memcpy(sdb_agent_dzbpb.extfld2,sdb_agent_drls.extfld2,sizeof(sdb_agent_dzbpb.extfld2)-1);
            memcpy(sdb_agent_dzbpb.extfld3,"1",1);
            memcpy(sdb_agent_dzbpb.dzbz,"2",1);
            
            /*���Զ����˵ǲżǶ��˲�ƽ��*/ 
            if( sAdjust[0] == '1' ) 
            {
                iRet = DBInsert("agent_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    DCIRollback();
                    DCIFreeCursor(cur);
                    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                    return COMPRET_FAIL;
                }
            }
            else if( sAdjust[0] == '0' )  /* ������ ��ƽ̨�� ������ƽ̨��ˮ״̬Ϊ ʧ�� */
            {
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls SET jyzt='1', zjdzbz='1' \
                    WHERE %s AND ptls =%d  AND ZJDZBZ<>9",sSqlDzrq, sdb_agent_drls.ptls);
                iRet = DCIExecuteDirect( sSql1 ); 
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                    DCIRollback();
                    DCIFreeCursor(cur);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
    
                iFlag--;//�����󣬶��˽������޹�
                iFlag_msg=1; /*��������*/
    
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("������ƽ̨�� ptrq[%s] ptls[%d] ����Ϊʧ�� ", \
                                         sDzrq, sdb_agent_drls.ptls ),"INFO");
            }
            iCount ++;
        }
        DCIFreeCursor(cur);
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("������ƽ̨�б���[%d]", iCount ),"INFO");
        /*������,ƽ̨�м�¼ --E*/      
    }
    
    memset( sDelSsql, 0x00, sizeof( sDelSsql ) );
    sprintf( sDelSsql,  "UPDATE agent_drls SET zjdzbz='1' \
        WHERE %s %s AND zjdzbz = '0' AND extfld2='%s' AND ZJDZBZ<>9", sSqlDzrq, sSqlCond, sJzxt );
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sDelSsql),"INFO");
    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    /* end */
    
    /*���͵���֪ͨ����*/
    /*if(1) ������һ��*/
    if(iFlag_msg==1) 
    {
        memset(sBuf,0x00,sizeof(sBuf));
        COMP_SOFTSETXML("/agent/dz_msg/dwbh", sYwbh)
        strncpy(sBuf,sYwbh,3);
        COMP_SOFTSETXML("/agent/dz_msg/cpdm", sBuf)
        COMP_SOFTSETXML("/agent/dz_msg/jzxt",sJzxt)
        if(fpub_CallFlow(lXmlhandle,"subflow_jfpt_700675_message")!=MID_SYS_SUCC )
        {
            LOG(LM_STD, Fmtmsg("���ö�������������ʧ��"), fpub_GetCompname(lXmlhandle))
        }
    }
    
    if( iFlag == 0 )
    {
        COMP_HARDSETXML( XMLNM_AGENT_RESP_ZJDZZT, "0" )  /* ��������״̬ 0 ƽ */
    }
    else
    {
        COMP_HARDSETXML( XMLNM_AGENT_RESP_ZJDZZT, "1" )  /* ��������״̬ 1 ��ƽ */
    }
    
    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC; 
}
