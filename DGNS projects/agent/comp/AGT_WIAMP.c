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
/******************************************************************************
�������: SAGENT_WIAMP_CHECK
�������: �м�ҵ���뿨ȯƽ̨����
����˵����
�������:
��� ��������         ��Դ���   ȱʡֵ         �Ƿ�ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
 
�� Ŀ ��:
�� �� Ա: zhandongdong
��������:2018��08��
�޸�����:
******************************************************************************/
IRESULT SAGENT_WIAMP_CHECK(HXMLTREE lXmlhandle)
{
    COUPON_WIAMP_DZLSB sdb_coupon_wiamp_dzlsb;
    COUPON_ZJYW_DZLSB  sdb_coupon_zjyw_dzlsb;
    COUPON_DZBPB       sdb_coupon_dzbpb;
    COUPON_ZJYW_RZZT   sdb_coupon_zjyw_rzzt;
        
    char sRunCpdmSql[512];
    char sDzrq[8+1];
    char sPtrq[8+1];
    char sBuf[256];
    int   iParas,i;
    int   iCount = 0;
    int   iFlag = 0;  /* 0 ����ƽ !0 ���˲�ƽ */
    int   iRet =-1;
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);
 
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*����������*/
    COMP_PARACOUNTCHK(2)
    
    /*��������*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    trim(sBuf);
    memset(sDzrq,0,sizeof(sDzrq));
    memcpy(sDzrq,sBuf,sizeof(sDzrq)-1);
    /*ƽ̨����*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"ƽ̨����")
    trim(sBuf);
    memset(sPtrq,0,sizeof(sPtrq));
    memcpy(sPtrq,sBuf,sizeof(sPtrq)-1);

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
        
    /*��ȯƽ̨��,�м�ҵ���޵ļ�¼--BEG*/
    iCount = 0;
    memset( sRunCpdmSql, 0x00, sizeof( sRunCpdmSql ) );
    sprintf(sRunCpdmSql, "SELECT * FROM coupon_wiamp_dzlsb WHERE dzrq='%s' AND orderstatus='1'AND trim(changeorderno) NOT IN \
    (SELECT DISTINCT trim(changeorderno) FROM coupon_zjyw_dzlsb WHERE dzrq='%s' AND ORDERSTATUS='1')", sDzrq,sDzrq);
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
    memset(&sdb_coupon_wiamp_dzlsb, 0, sizeof(sdb_coupon_wiamp_dzlsb));
    while( ( iRet = DBFetch(cur, SD_COUPON_WIAMP_DZLSB, NUMELE(SD_COUPON_WIAMP_DZLSB), &sdb_coupon_wiamp_dzlsb, sErrmsg ) ) > 0 )
    {
        iFlag ++; /*�����в�ƽ�ļ�¼*/
        /*�Ǽǲ�ƽ��ˮ��*/
        memset(&sdb_coupon_dzbpb, 0, sizeof(sdb_coupon_dzbpb));
        memcpy(sdb_coupon_dzbpb.dzrq,sDzrq,sizeof(sdb_coupon_dzbpb.dzrq)-1);
        trim( sdb_coupon_dzbpb.dzrq);
        memcpy(sdb_coupon_dzbpb.ptrq,sPtrq,sizeof(sdb_coupon_dzbpb.ptrq)-1);
        trim( sdb_coupon_dzbpb.ptrq);
        memcpy(sdb_coupon_dzbpb.changeorderno,sdb_coupon_wiamp_dzlsb.changeorderno,sizeof(sdb_coupon_dzbpb.changeorderno)-1);
        trim( sdb_coupon_dzbpb.changeorderno);
        memcpy(sdb_coupon_dzbpb.weiorderno,sdb_coupon_wiamp_dzlsb.weiorderno,sizeof(sdb_coupon_dzbpb.weiorderno)-1);
        trim( sdb_coupon_dzbpb.weiorderno);
        memcpy(sdb_coupon_dzbpb.couponno,sdb_coupon_wiamp_dzlsb.couponno,sizeof(sdb_coupon_dzbpb.couponno)-1);
        trim( sdb_coupon_dzbpb.couponno);
        memcpy(sdb_coupon_dzbpb.status,"1",1); /*��ȯƽ̨��*/
        sdb_coupon_dzbpb.wiamp_ordernum=sdb_coupon_wiamp_dzlsb.couponnum;
        sdb_coupon_dzbpb.zjyw_ordernum=0;
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
        Fmtmsg("���˲�ƽ,��ȯƽ̨�ࣺ��������[%s] ����������[%s] ",sDzrq, sdb_coupon_dzbpb.changeorderno),"INFO");
        /*�ǼǶ��˲�ƽ��*/
        iRet = DBInsert("coupon_dzbpb", SD_COUPON_DZBPB, NUMELE(SD_COUPON_DZBPB), &sdb_coupon_dzbpb, sErrmsg);
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
        iFlag++;
    }
    DCIFreeCursor(cur);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("��ȯƽ̨��,�м�ҵ����-����[%d]", iCount ),"INFO");
    /*��ȯƽ̨��,�м�ҵ���޵ļ�¼--END*/


    /* ��ȯƽ̨��,�м�ҵ���еļ�¼ --BEG*/
    iCount = 0;
    memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
    sprintf(sRunCpdmSql, "SELECT * FROM coupon_zjyw_dzlsb WHERE dzrq='%s' AND orderstatus='1' AND trim(changeorderno) NOT IN\
        (SELECT DISTINCT trim(changeorderno) FROM coupon_wiamp_dzlsb WHERE dzrq='%s' AND orderstatus='1' )",sDzrq, sDzrq);
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
    
    memset(&sdb_coupon_zjyw_dzlsb, 0, sizeof(sdb_coupon_zjyw_dzlsb));
    while( ( iRet = DBFetch(cur, SD_COUPON_ZJYW_DZLSB, NUMELE(SD_COUPON_ZJYW_DZLSB), &sdb_coupon_zjyw_dzlsb, sErrmsg ) ) > 0 )
    {
        /*�Ǽǲ�ƽ��ˮ��*/
        memset(&sdb_coupon_dzbpb, 0, sizeof(sdb_coupon_dzbpb));
        memset(&sdb_coupon_dzbpb, 0, sizeof(sdb_coupon_dzbpb));
        memcpy(sdb_coupon_dzbpb.dzrq,sDzrq,sizeof(sdb_coupon_dzbpb.dzrq)-1);
        trim( sdb_coupon_dzbpb.dzrq);
        memcpy(sdb_coupon_dzbpb.ptrq,sPtrq,sizeof(sdb_coupon_dzbpb.ptrq)-1);
        trim( sdb_coupon_dzbpb.ptrq);
        memcpy(sdb_coupon_dzbpb.changeorderno,sdb_coupon_zjyw_dzlsb.changeorderno,sizeof(sdb_coupon_dzbpb.changeorderno)-1);
        trim( sdb_coupon_dzbpb.changeorderno);
        memcpy(sdb_coupon_dzbpb.weiorderno,sdb_coupon_zjyw_dzlsb.weiorderno,sizeof(sdb_coupon_dzbpb.weiorderno)-1);
        trim( sdb_coupon_dzbpb.weiorderno);
        memcpy(sdb_coupon_dzbpb.couponno,sdb_coupon_zjyw_dzlsb.couponno,sizeof(sdb_coupon_dzbpb.couponno)-1);
        trim( sdb_coupon_dzbpb.couponno);
        memcpy(sdb_coupon_dzbpb.status,"2",1); /*�м�ҵ���*/
        sdb_coupon_dzbpb.wiamp_ordernum=0;
        sdb_coupon_dzbpb.zjyw_ordernum=sdb_coupon_zjyw_dzlsb.couponnum;

        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
        Fmtmsg("���˲�ƽ,�м�ҵ��ࣺ��������[%s] ����������[%s] ",sDzrq, sdb_coupon_dzbpb.changeorderno),"INFO");   
        iRet = DBInsert("coupon_dzbpb", SD_COUPON_DZBPB, NUMELE(SD_COUPON_DZBPB), &sdb_coupon_dzbpb, sErrmsg);
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
        iFlag++;

    }
    DCIFreeCursor(cur);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("��ȯƽ̨���м�ҵ���б���[%d]", iCount ),"INFO");
    /*������,ƽ̨�м�¼ --END*/      
    
    /*������һ�µ�����������*/
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("������һ�µ�����������"),"INFO");
    
    /**��������״̬��**/
    memset( sRunCpdmSql, 0x00, sizeof( sRunCpdmSql ) );
    if( iFlag == 0 )
    {
          /* ����״̬ 0 ƽ*/
        sprintf(sRunCpdmSql, "UPDATE coupon_zjyw_rzzt SET  status='0' WHERE dzrq='%s' AND ptrq='%s'", sDzrq,sPtrq);
    }
    else
    {
          /* ����״̬ 1 ��ƽ*/
        sprintf(sRunCpdmSql, "UPDATE coupon_zjyw_rzzt SET  status='1' WHERE dzrq='%s' AND ptrq='%s'", sDzrq,sPtrq);
    }
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"INFO");
    iRet = DCIExecuteDirect( sRunCpdmSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC; 
}

