/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.0)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:
�ļ�����:ͨ��Ӧ��ƽ̨�������
�� Ŀ ��:
�� �� Ա: CHENSY 
��������:
��    ��: �
�޸�����: 20090708

�޸�����: 20111222
��    ��: �
�޶�����: ǩԼ�޸��ж�

�޸�����: 20130220
��    ��: �
�޶�����: ǩԼģʽ���� 4-ҵ����+�û��� 
          �޸�ǩԼģʽ 2-��Ʒ����+�û��� ΪĬ��
          ���Ӳ�ѯ����

�޸�����: 20140910
��    ��: �
�޶�����: DCI����
*********************************************************************/
#include "gaps_head.h"
#include "../incl/app_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
       <root>\
       <soname>APP_CUSTOM.so</soname>\
       <sosrcname>APP_CUSTOM.c</sosrcname>\
       <sonote>�ͻ�ǩԼͨ���������</sonote>\
       <version>\
       <rec ver=\"2.0.1.1\" modify=\"2010-4-1 10:08\" programer=\"YangDong\" filesize=\"1244135\">HS-AgentV2.0����</rec>\
       <rec ver=\"2.1.0.1\" modify=\"2011-11-01  10:50\" programer=\"S..C\" filesize=\"1462110\">HS-AgentV2.1����</rec>\
       <rec ver=\"2.1.0.2\" modify=\"2011-12-22  10:50\" programer=\"S..C\" filesize=\"1462110\">HS-AgentV2.1����</rec>\
       <rec ver=\"2.1.0.3\" modify=\"2013-02-20  10:50\" programer=\"YangDong\" filesize=\"1462110\">����ǩԼģʽ,�����ѯ����</rec>\
       <rec ver=\"4.1.0.1\" modify=\"2014-09-10  10:50\" programer=\"YangDong\" filesize=\"1462110\">DCI����</rec>\
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
char sSql1[512+1];

/************************************************************************
��̬�����������
�����������:SApp_InsCUSTOM
�������:SApp_InsCUSTOM
�������:�Ǽǹ���ǩԼ��ϵ�����
�������:
 ��� ��������  ��������         ��Դ���         ȱʡֵ  �ɿ�  ����˵��

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

�� Ŀ ��: 
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
int SApp_InsCUSTOM(HXMLTREE lXmlhandle)
{
    APP_KHXX sdb_app_khxx;
    APP_KHCPQY sdb_app_khcpqy;
    char sPkey[20+1];
    char sSignStat[1+1];  /* ǩԼ״̬ */
    char sXybh[16+1];     /* Э���� */
    char sRunKhxxSql[512];
    char sSetKhxxSql[2048];
    char sRunQyxxSql[512];
    char sWhere[512];
    char sErrmsg[512];
    int iCount;
    
    int  i,iResult=0;
    long iseqno=0;
    char sbuf[255];
    char sSignType[2];
    int  iSqlKhxxlen=0;
    int  iSqlQyxxlen=0;
    int  iRet = -1;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    memset(&sdb_app_khcpqy,0,sizeof(sdb_app_khcpqy));
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJLX, sbuf );
    pstrcopy( sdb_app_khcpqy.zjlx, sbuf,sizeof( sdb_app_khcpqy.zjlx ) );
    if ( 0 == sdb_app_khcpqy.zjlx[0] ) 
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->�����ܾ�:֤�����Ͳ�����Ϊ��!"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_ZJLX_ISNULL,MSG_CUSTOM_ZJLX_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJHM, sbuf);
    pstrcopy( sdb_app_khcpqy.zjhm, sbuf,sizeof( sdb_app_khcpqy.zjhm ) );
    if ( 0 ==  sdb_app_khcpqy.zjhm[0] ) 
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->�����ܾ�:֤�����벻����Ϊ��!"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_ZJHM_ISNULL,MSG_CUSTOM_ZJHM_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    /* ---------- �жϿͻ��Ƿ���ǩԼ begin ---------- */
    /* ��Ʒ���� */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_CPDM , sbuf );
    pstrcopy( sdb_app_khcpqy.cpdm, sbuf,sizeof( sdb_app_khcpqy.cpdm ) );
    if ( 0 == sdb_app_khcpqy.cpdm[0])
    {
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_CPDM_ISNULL,MSG_CUSTOM_CPDM_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;    
    }
    trim(sdb_app_khcpqy.cpdm);
      
    /* �û��� */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1 , sbuf );
    pstrcopy( sdb_app_khcpqy.yhh1, sbuf,sizeof( sdb_app_khcpqy.yhh1 ) );
    trim(sdb_app_khcpqy.yhh1);
    
    /* �����ʺ� */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH , sbuf );
    pstrcopy( sdb_app_khcpqy.qyzh, sbuf,sizeof( sdb_app_khcpqy.qyzh ) );
    trim(sdb_app_khcpqy.qyzh);

    /*�������˺�*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD1,sbuf );
    pstrcopy( sdb_app_khcpqy.extfld1,sbuf,sizeof( sdb_app_khcpqy.extfld1));
    trim(sdb_app_khcpqy.extfld1);

    /*�ն˺���Ϣ*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD2,sbuf );
    pstrcopy( sdb_app_khcpqy.extfld2,sbuf,sizeof( sdb_app_khcpqy.extfld2));
    trim(sdb_app_khcpqy.extfld2);
    
    /* �����ͻ���� */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJKHBH  , sbuf );
    pstrcopy( sdb_app_khxx.zjkhbh, sbuf,sizeof( sdb_app_khxx.zjkhbh ) );
    trim(sdb_app_khxx.zjkhbh);
    
    /* ϵͳ֧��ǩԼģʽ */
    memset(sSignType, 0, sizeof(sSignType));
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML( XMLNM_APP_CPXX_QYMS, sbuf );
    pstrcopy( sSignType, sbuf,sizeof( sSignType ) );
    trim(sSignType);
    
    iCount=0;
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("ǩԼ������Ʒ����[%s], �ʺ�[%s], �û���[%s]",\
        sdb_app_khcpqy.cpdm, sdb_app_khcpqy.qyzh, sdb_app_khcpqy.yhh1),"DEBUG");
    
    memset( sSignStat, 0x00, sizeof( sSignStat ) );
    memset( sXybh, 0x00, sizeof( sXybh ) );
    memset( sWhere, 0x00, sizeof( sWhere ) );
    memset( sRunQyxxSql, 0x00, sizeof( sRunQyxxSql ) );
    memset( sSql1, 0x00, sizeof( sSql1 ) );

    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("ǩԼ״̬[%s],ǩԼģʽ[%s]",sSignStat,sSignType),"DEBUG");
    /* ��Ʒ����+�����ʺ�Ψһ */
    if ( sSignType[0] == '1' )
    {
        /* �����ʺŲ���Ϊ�� */
        if ( 0 == sdb_app_khcpqy.qyzh[0] )
        {
             fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return -1;    
        }
        snprintf( sWhere, sizeof( sWhere ), "WHERE qyzh = '%s' AND  cpdm = '%s' ", \
                       sdb_app_khcpqy.qyzh, sdb_app_khcpqy.cpdm );
            
        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy \
                    WHERE qyzh = '%s' AND cpdm ='%s'",\
                    sdb_app_khcpqy.qyzh , sdb_app_khcpqy.cpdm);
    }
    else /* ��Ʒ����+�����ʺ�+�û����Ψһ ǩԼ����3 */
    if ( sSignType[0] == '3' )
    {
        /* �����ʺŲ���Ϊ�� */
        if ( 0 == sdb_app_khcpqy.qyzh[0] )
        {
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;    
        }

        /* �û���Ų���Ϊ�� */
        if ( 0 == sdb_app_khcpqy.yhh1[0] )
        {
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;    
        }
        snprintf( sWhere, sizeof( sWhere ), "WHERE yhh1= '%s' AND qyzh = '%s'  AND cpdm = '%s' ",\
                      sdb_app_khcpqy.yhh1,sdb_app_khcpqy.qyzh, sdb_app_khcpqy.cpdm );

        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy \
                    WHERE qyzh = '%s' AND yhh1 = '%s' AND cpdm ='%s'",\
                    sdb_app_khcpqy.qyzh ,sdb_app_khcpqy.yhh1 ,sdb_app_khcpqy.cpdm);
    }
    /* added by yangdong 20130220 ���󵥱��201302200005  ����ǩԼ����ģʽ  */
    else /* ҵ����+�û����Ψһ */
    if ( sSignType[0] == '4' )
    {
        /* �û���Ų���Ϊ�� */
        if ( 0 == sdb_app_khcpqy.yhh1[0] )
        {
             DCIRollback();
             fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return -1;    
        }
        snprintf( sWhere, sizeof( sWhere ), "WHERE yhh1= '%s'  AND ywbh = '%s' ",\
                                   sdb_app_khcpqy.yhh1, sdb_app_khcpqy.ywbh );

        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy \
                    WHERE yhh1 = '%s' AND ywbh='%s'",sdb_app_khcpqy.yhh1 ,sdb_app_khcpqy.ywbh );
    }
    else
    /* ��Ʒ����+�û����Ψһ  Ĭ��ֵ*/
    {
        /* �û���Ų���Ϊ�� */
        if ( 0 == sdb_app_khcpqy.yhh1[0] )
        {
             fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return -1;    
        }
        snprintf( sWhere,sizeof( sWhere ), "WHERE yhh1= '%s'  AND cpdm = '%s' ",\
                                   sdb_app_khcpqy.yhh1, sdb_app_khcpqy.cpdm );

        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy \
                    WHERE yhh1 = '%s' AND cpdm='%s'",sdb_app_khcpqy.yhh1 ,sdb_app_khcpqy.cpdm);
    }

    iRet = DBSelectToMultiVar( sErrmsg, sSql1, sSignStat, sXybh ) ;
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* δǩԼ����ǩԼ״̬������(�ͻ���Ϣ����,ǩԼ����) */
    if (  iRet < 1 || sSignStat[0] != '0'  )        
    {
        DCIBegin();
        if( sSignStat[0] != '0' )  /* ǩԼ״̬����������ɾ����¼�����²���ǩԼ�� */
        {
            memset( sRunQyxxSql, 0x00, sizeof( sRunQyxxSql ) );
            sprintf( sRunQyxxSql, " DELETE app_khcpqy %s", sWhere );
            iRet = DCIExecuteDirect( sRunQyxxSql );
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }

        /* ---------- �жϿͻ�������Ϣ�����Ƿ������Ӧ��¼ begin ---------- */
        memset(&sdb_app_khxx,0,sizeof(sdb_app_khxx));
        /* ��ȡ�ͻ���� */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT khbh FROM app_khxx \
            WHERE zjlx ='%s' and zjhm ='%s'", sdb_app_khcpqy.zjlx ,sdb_app_khcpqy.zjhm );
        iRet = DBSelectToMultiVar( sErrmsg, sSql1,sdb_app_khcpqy.khbh) ;
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* ��������Ǽǿͻ���Ϣ�� */    
        if ( iRet == 0 )
        {
            /* ���ɿͻ���� */
            if ( fprv_getSeqno("K_KHBH", &iseqno) < 0)
            {
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("-->���ɿͻ���ű��ʧ��,pkey=[%s],xybh=[%d]",\
                    "K_KHBH",iseqno),"ERROR");
                DCIRollback();
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_XYBH,Fmtmsg(MSG_CUSTOM_XYBH));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;
            }
            memset(sdb_app_khxx.khbh, 0, sizeof(sdb_app_khxx.khbh));
            sprintf(sdb_app_khxx.khbh, "%d",iseqno);
            sprintf(sdb_app_khcpqy.khbh, "%d",iseqno);
            trim(sdb_app_khxx.khbh);
            trim(sdb_app_khcpqy.khbh);
            if ( 0 == sdb_app_khxx.khbh[0] ) 
            {
                DCIRollback();
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->�����ܾ�:�ͻ���Ų�����Ϊ��!"),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_KHBH_ISNULL,MSG_CUSTOM_KHBH_ISNULL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;
            }
            /* �ͻ����� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_KHXM   ,sbuf  );
            pstrcopy( sdb_app_khxx.khxm, sbuf,sizeof( sdb_app_khxx.khxm ) );
            /* Ӣ������ */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_YWXM   ,sbuf );
            pstrcopy( sdb_app_khxx.ywxm, sbuf,sizeof( sdb_app_khxx.ywxm ) );
            /* ���� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_BM , sbuf );
            pstrcopy( sdb_app_khxx.bm, sbuf,sizeof( sdb_app_khxx.bm ) );
            /* �ͻ����� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_KHLX   ,sbuf  );
            pstrcopy( sdb_app_khxx.khlx, sbuf,sizeof( sdb_app_khxx.khlx ) );
            /* �����ͻ���� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZJKHBH ,sbuf );
            pstrcopy( sdb_app_khxx.zjkhbh, sbuf,sizeof( sdb_app_khxx.zjkhbh ) );
            /* ֤������ */
            memcpy( sdb_app_khxx.zjlx,sdb_app_khcpqy.zjlx ,sizeof(sdb_app_khxx.zjlx)   );
            /* ֤������ */
            memcpy( sdb_app_khxx.zjhm,sdb_app_khcpqy.zjhm ,sizeof(sdb_app_khxx.zjhm)   );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_CSNY   ,sbuf  );
            pstrcopy( sdb_app_khxx.csny, sbuf,sizeof( sdb_app_khxx.csny ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SEX  ,sbuf  );
            pstrcopy( sdb_app_khxx.sex, sbuf,sizeof( sdb_app_khxx.sex ) );
            /* Ĭ�Ϲ��� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GJ  ,sbuf   );
            pstrcopy( sdb_app_khxx.gj, sbuf,sizeof( sdb_app_khxx.gj ) );
            trim(sdb_app_khxx.gj);
            if ( strlen(sdb_app_khxx.gj) <=0 )
            {
                strcpy(sdb_app_khxx.gj, "CHN");
            }
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_HK     ,sbuf  );
            pstrcopy( sdb_app_khxx.hk, sbuf,sizeof( sdb_app_khxx.hk ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_HYZK   ,sbuf  );
            pstrcopy( sdb_app_khxx.hyzk, sbuf,sizeof( sdb_app_khxx.hyzk ) );
            /* Ĭ�ϻ���״�� */
            trim(sdb_app_khxx.hyzk);
            if ( strlen(sdb_app_khxx.hyzk) <=0 )
            {
                strcpy(sdb_app_khxx.hyzk, "9");
            }
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_JYCD   ,sbuf  );
            pstrcopy( sdb_app_khxx.jycd, sbuf,sizeof( sdb_app_khxx.jycd ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZY     ,sbuf  );
            pstrcopy( sdb_app_khxx.zy, sbuf,sizeof( sdb_app_khxx.zy ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZW     ,sbuf   );
            pstrcopy( sdb_app_khxx.zw, sbuf,sizeof( sdb_app_khxx.zw ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SRQK   ,sbuf   );
            sdb_app_khxx.srqk=atof(sbuf);
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSDZ   ,sbuf  );
            pstrcopy( sdb_app_khxx.gsdz, sbuf,sizeof( sdb_app_khxx.gsdz ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSYB   ,sbuf  );
            pstrcopy( sdb_app_khxx.gsyb, sbuf,sizeof( sdb_app_khxx.gsyb ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSDH   ,sbuf  );
            pstrcopy( sdb_app_khxx.gsdh, sbuf,sizeof( sdb_app_khxx.gsdh ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZDZ   ,sbuf );
            pstrcopy( sdb_app_khxx.zzdz, sbuf,sizeof( sdb_app_khxx.zzdz ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZYB   ,sbuf  );
            pstrcopy( sdb_app_khxx.zzyb, sbuf,sizeof( sdb_app_khxx.zzyb ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZDH   ,sbuf  );
            pstrcopy( sdb_app_khxx.zzdh, sbuf,sizeof( sdb_app_khxx.zzdh ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_YJDZLX ,sbuf );
            pstrcopy( sdb_app_khxx.yjdzlx, sbuf,sizeof( sdb_app_khxx.yjdzlx ) );
            /* Ĭ���ʼĵ�ַ���� */
            trim(sdb_app_khxx.yjdzlx);
            if ( strlen(sdb_app_khxx.yjdzlx) <=0 )
            {
                strcpy(sdb_app_khxx.yjdzlx, "0");
            }
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SJHM   ,sbuf  );
            pstrcopy( sdb_app_khxx.sjhm, sbuf,sizeof( sdb_app_khxx.sjhm ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_Email  ,sbuf );
            pstrcopy( sdb_app_khxx.memail, sbuf,sizeof( sdb_app_khxx.memail ) );
            strcpy(sdb_app_khxx.bz,"0");
            
            iRet = DBInsert("app_khxx", SD_APP_KHXX, NUMELE(SD_APP_KHXX), &sdb_app_khxx, sErrmsg);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg(" khbh[%s] zjlx[%s] zjhm[%s]",\
                    sdb_app_khcpqy.khbh, sdb_app_khcpqy.zjlx, sdb_app_khcpqy.zjhm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_INS_KHXX,Fmtmsg(MSG_CUSTOM_INS_KHXX));
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPSTATUS_FAIL;
            }
        }
        /* ��������¿ͻ���Ϣ�� */
        else
        {          
            /* by yr 20120830 */
            trim(sdb_app_khcpqy.khbh);
              
            iSqlKhxxlen=0;
            memset(sSetKhxxSql,0,sizeof(sSetKhxxSql));
            /* �ͻ���־ */
            sprintf(sSetKhxxSql+iSqlKhxxlen, "  bz='%s'","0");
            iSqlKhxxlen=strlen(sSetKhxxSql);
                  
            memset(&sdb_app_khxx, 0, sizeof(sdb_app_khxx));
            /* �ͻ����� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_KHXM  ,sbuf  );
            pstrcopy( sdb_app_khxx.khxm, sbuf,sizeof( sdb_app_khxx.khxm ) );
            trim(sdb_app_khxx.khxm);
            if ( strlen(sdb_app_khxx.khxm) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,khxm='%s'",sdb_app_khxx.khxm);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* Ӣ������ */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_YWXM   ,sbuf   );
            pstrcopy( sdb_app_khxx.ywxm, sbuf, sizeof( sdb_app_khxx.ywxm ) );
            trim(sdb_app_khxx.ywxm);
            if ( strlen(sdb_app_khxx.ywxm) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,ywxm='%s'",sdb_app_khxx.ywxm);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ���� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_BM ,sbuf  );
            pstrcopy( sdb_app_khxx.bm, sbuf, sizeof( sdb_app_khxx.bm ) );
            trim(sdb_app_khxx.bm);
            if ( strlen(sdb_app_khxx.bm) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,bm='%s'",sdb_app_khxx.bm);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* �����ͻ���� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZJKHBH ,sbuf );
            pstrcopy( sdb_app_khxx.zjkhbh, sbuf, sizeof( sdb_app_khxx.zjkhbh ) );
            trim(sdb_app_khxx.zjkhbh);
            if ( strlen(sdb_app_khxx.zjkhbh) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zjkhbh='%s'",sdb_app_khxx.zjkhbh);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* �������� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_CSNY ,sbuf  );
            pstrcopy( sdb_app_khxx.csny, sbuf, sizeof( sdb_app_khxx.csny ) );
            trim(sdb_app_khxx.csny);
            if ( strlen(sdb_app_khxx.csny) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,csny='%s'",sdb_app_khxx.csny);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* �Ա� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SEX , sbuf );
            pstrcopy( sdb_app_khxx.sex, sbuf, sizeof( sdb_app_khxx.sex ) );
            trim(sdb_app_khxx.sex);
            if ( strlen(sdb_app_khxx.sex) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,sex='%s'",sdb_app_khxx.sex);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ���� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GJ , sbuf  );
            pstrcopy( sdb_app_khxx.gj, sbuf, sizeof( sdb_app_khxx.gj ) );
            trim(sdb_app_khxx.gj);
            if ( strlen(sdb_app_khxx.gj) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,gj='%s'",sdb_app_khxx.gj);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ���� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_HK  , sbuf );
            pstrcopy( sdb_app_khxx.hk, sbuf, sizeof( sdb_app_khxx.hk ) );
            trim(sdb_app_khxx.hk);
            if ( strlen(sdb_app_khxx.hk) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,hk='%s'",sdb_app_khxx.hk);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ����״�� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_HYZK   ,sbuf  );
            pstrcopy( sdb_app_khxx.hyzk, sbuf, sizeof( sdb_app_khxx.hyzk ) );
            trim(sdb_app_khxx.hyzk);
            if ( strlen(sdb_app_khxx.hyzk) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,hyzk='%s'",sdb_app_khxx.hyzk);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* �����̶� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_JYCD   ,sbuf  );
            pstrcopy( sdb_app_khxx.jycd, sbuf, sizeof( sdb_app_khxx.jycd ) );
            trim(sdb_app_khxx.jycd);
            if ( strlen(sdb_app_khxx.jycd) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,jycd='%s'",sdb_app_khxx.jycd);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ְҵ */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZY , sbuf );
            pstrcopy( sdb_app_khxx.zy, sbuf, sizeof( sdb_app_khxx.zy ) );
            trim(sdb_app_khxx.zy);
            if ( strlen(sdb_app_khxx.zy) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zy='%s'",sdb_app_khxx.zy);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ְ�� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZW  ,sbuf );
            pstrcopy( sdb_app_khxx.zw, sbuf, sizeof( sdb_app_khxx.zw ) );
            trim(sdb_app_khxx.zw);
            if ( strlen(sdb_app_khxx.zw) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zw='%s'",sdb_app_khxx.zw);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ��������� */
            memset(sbuf, 0, sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SRQK   ,sbuf   );
            trim(sbuf);
            if ( strlen(sbuf) >0 )
            {
                sdb_app_khxx.srqk=atof(sbuf);
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,srqk=%15.2f",sdb_app_khxx.srqk);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ��˾��ַ */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSDZ   ,sbuf );
            pstrcopy( sdb_app_khxx.gsdz, sbuf, sizeof( sdb_app_khxx.gsdz ) );
            trim(sdb_app_khxx.gsdz);
            if ( strlen(sdb_app_khxx.gsdz) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,gsdz='%s'",sdb_app_khxx.gsdz);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ��˾�ʱ� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSYB , sbuf  );
            pstrcopy( sdb_app_khxx.gsyb, sbuf, sizeof( sdb_app_khxx.gsyb ) );
            trim(sdb_app_khxx.gsyb);
            if ( strlen(sdb_app_khxx.gsyb) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,gsyb='%s'",sdb_app_khxx.gsyb);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ��˾�绰 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSDH   , sbuf );
            pstrcopy( sdb_app_khxx.gsdh, sbuf, sizeof( sdb_app_khxx.gsdh ) );
            trim(sdb_app_khxx.gsdh);
            if ( strlen(sdb_app_khxx.gsdh) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,gsdh='%s'",sdb_app_khxx.gsdh);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* סլ��ַ */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZDZ  ,sbuf );
            pstrcopy( sdb_app_khxx.zzdz, sbuf, sizeof( sdb_app_khxx.zzdz ) );
            trim(sdb_app_khxx.zzdz);
            if ( strlen(sdb_app_khxx.zzdz) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zzdz='%s'",sdb_app_khxx.zzdz);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* סլ�ʱ� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZYB   ,sbuf  );
            pstrcopy( sdb_app_khxx.zzyb, sbuf, sizeof( sdb_app_khxx.zzyb ) );
            trim(sdb_app_khxx.zzyb);
            if ( strlen(sdb_app_khxx.zzyb) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zzyb='%s'",sdb_app_khxx.zzyb);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* סլ�绰 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZDH  , sbuf );
            pstrcopy( sdb_app_khxx.zzdh, sbuf, sizeof( sdb_app_khxx.zzdh ) );
            trim(sdb_app_khxx.zzdh);
            if ( strlen(sdb_app_khxx.zzdh) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zzdh='%s'",sdb_app_khxx.zzdh);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* �ʼ����� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_YJDZLX ,sbuf );
            pstrcopy( sdb_app_khxx.yjdzlx, sbuf, sizeof( sdb_app_khxx.yjdzlx ) );
            trim(sdb_app_khxx.yjdzlx);
            if ( strlen(sdb_app_khxx.yjdzlx) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,yjdzlx='%s'",sdb_app_khxx.yjdzlx);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* �ֻ����� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SJHM   , sbuf  );
            pstrcopy( sdb_app_khxx.sjhm, sbuf, sizeof( sdb_app_khxx.sjhm ) );
            trim(sdb_app_khxx.sjhm);
            if ( strlen(sdb_app_khxx.sjhm) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,sjhm='%s'",sdb_app_khxx.sjhm);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* �����ʼ� */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_Email  , sbuf  );
            pstrcopy( sdb_app_khxx.memail, sbuf, sizeof( sdb_app_khxx.memail ) );
            trim(sdb_app_khxx.memail);
            if ( strlen(sdb_app_khxx.memail) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,memail='%s'",sdb_app_khxx.memail);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* ���¼�¼ --B*/
            memset(sRunKhxxSql, 0, sizeof(sRunKhxxSql));
            snprintf(sRunKhxxSql,sizeof(sRunKhxxSql),"update app_khxx set %s where zjlx ='%s' and zjhm ='%s'",\
                                     sSetKhxxSql, sdb_app_khcpqy.zjlx, sdb_app_khcpqy.zjhm );
            iRet = DCIExecuteDirect( sRunKhxxSql );
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->�����ܾ�:���¿ͻ���Ϣʧ�� ֤������[%s],\
                    ֤������[%s]\n[%s],[%s]",sdb_app_khcpqy.zjlx,sdb_app_khcpqy.zjhm, sRunKhxxSql, DCILastError() ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_KHBH_EQUAL,MSG_CUSTOM_KHBH_EQUAL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;
            }
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("ǩԼ�������¿ͻ���Ϣ[%s]",sRunKhxxSql),"DEBUG");
            /* ���¼�¼ --E*/
         }
        /* ---------- �жϿͻ�������Ϣ�����Ƿ������Ӧ��¼ end   ---------- */
        
        /* ����Э������ֵ --B*/
        memset(sPkey, 0, sizeof(sPkey));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_PKEY, sPkey);
        trim(sPkey);
        if ( fprv_getSeqno(sPkey, &iseqno) < 0)
        {
            DCIRollback();
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->����Э����ʧ��,pkey=[%s],xybh=[%d]",sPkey,iseqno),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_XYBH,Fmtmsg(MSG_CUSTOM_XYBH));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        COMP_HARDSETXML(XMLNM_APP_CUSTOM_XYXH, itoa(iseqno));
        /* ����Э������ֵ --E*/
        
        COMP_SOFTGETXML( XMLNM_APP_CUSTOM_XYXH   ,sdb_app_khcpqy.xybh   );
        trim(sdb_app_khcpqy.xybh);
        
        /* ҵ���� */    
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YWBH     , sdb_app_khcpqy.ywbh     );
        trim(sdb_app_khcpqy.ywbh);
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHLX     , sdb_app_khcpqy.zhlx     );
        /*
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH     , sdb_app_khcpqy.qyzh     );
        */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHHM     , sdb_app_khcpqy.zhhm     );
        trim(sdb_app_khcpqy.zhhm);
        if ( strlen(sdb_app_khcpqy.zhhm) <=0 )
        {
            trim(sdb_app_khxx.khxm);
            strcpy(sdb_app_khcpqy.zhhm, sdb_app_khxx.khxm);
        }
        /* Ĭ��ǩԼ���� */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYLX     , sdb_app_khcpqy.qylx     );
        trim( sdb_app_khcpqy.qylx );
        if ( strlen(sdb_app_khcpqy.qylx) <= 0)
            strcpy(sdb_app_khcpqy.qylx, "0");
                
        /* Ĭ�Ͽͻ����� */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHJL     , sdb_app_khcpqy.khjl     );
        trim(sdb_app_khcpqy.khjl);
        if ( strlen(sdb_app_khcpqy.khjl) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_KHJL     , sdb_app_khcpqy.khjl     );
        }
        /* ��Լ��ʼ���� */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HYKSRQ   , sdb_app_khcpqy.hyksrq   );
        trim(sdb_app_khcpqy.hyksrq);
        if ( strlen(sdb_app_khcpqy.hyksrq) <= 0)
        {
            sprintf(sdb_app_khcpqy.hyksrq, "%s", GetSysDate());
        }
        /* ��Լ�������� */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HYJSRQ   , sdb_app_khcpqy.hyjsrq   );
        /* Ĭ�Ͽ�ͨ���� */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KTQD     , sdb_app_khcpqy.ktqd     );
        if ( strlen(sdb_app_khcpqy.ktqd) <=0 )
        {
            /* Ĭ�Ͽ�ͨ���� ALL */
            sprintf(sdb_app_khcpqy.ktqd,"ALL");
        }
        
        /* Ĭ��������� */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLJG     , sdb_app_khcpqy.bljg     );
        trim(sdb_app_khcpqy.bljg);
        if ( strlen(sdb_app_khcpqy.bljg) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG     , sdb_app_khcpqy.bljg     );
        }
        
        /* Ĭ�������Ա */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLGY     , sdb_app_khcpqy.blgy     );
        trim(sdb_app_khcpqy.blgy);
        if ( strlen(sdb_app_khcpqy.blgy) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBGY     , sdb_app_khcpqy.blgy     );
        }
        
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLRQ     , sdb_app_khcpqy.blrq     );
        /* Ĭ�ϰ������� */
        trim(sdb_app_khcpqy.blrq);
        if ( strlen(sdb_app_khcpqy.blrq) <=0 )
        {
              COMP_SOFTGETXML(XMLNM_APP_CPXX_YWRQ     , sdb_app_khcpqy.blrq     );
        }
        /*
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1     , sdb_app_khcpqy.yhh1     );
        */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH2     , sdb_app_khcpqy.yhh2     );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH3     , sdb_app_khcpqy.yhh3     );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DXTZBZ   , sdb_app_khcpqy.dxtzbz   );
        /* Ĭ�϶��ű�־ */
        trim(sdb_app_khcpqy.dxtzbz);
        if ( strlen(sdb_app_khcpqy.dxtzbz) <=0 )
        {
                strcpy(sdb_app_khcpqy.dxtzbz, "0");
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHZDED   , sbuf   );
        sdb_app_khcpqy.zhzded=atof(sbuf);

        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHJG, sdb_app_khcpqy.khjg );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHMC, sdb_app_khcpqy.yhmc );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHLX, sdb_app_khcpqy.yhlx );
    
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DLZJLX, sdb_app_khcpqy.dlzjlx );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DLZJHM, sdb_app_khcpqy.dlzjhm );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHYB, sdb_app_khcpqy.yhyb );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHDH, sdb_app_khcpqy.yhdh );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHDZ, sdb_app_khcpqy.yhdz );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_JYBZ, sdb_app_khcpqy.jybz );
		memset( sbuf, 0x00, sizeof( sbuf ) );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKZDXE, sbuf );
		sdb_app_khcpqy.kkzdxe = atof( sbuf );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKZQ, sdb_app_khcpqy.kkzq );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YDKKRQ, sdb_app_khcpqy.ydkkrq );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKZT, sdb_app_khcpqy.kkzt );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKRQ, sdb_app_khcpqy.kkrq );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD4  , sdb_app_khcpqy.extfld4  );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD5  , sdb_app_khcpqy.extfld5  );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD6  , sdb_app_khcpqy.extfld6  );
		memset( sbuf, 0x00, sizeof( sbuf ) );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD1  ,sbuf );
		pstrcopy( sdb_app_khcpqy.extfld1, sbuf,sizeof( sdb_app_khcpqy.extfld1 ) );	
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s][%s]",sbuf,sdb_app_khcpqy.extfld1),"ERROR")
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD2  , sdb_app_khcpqy.extfld2  );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD3  , sdb_app_khcpqy.extfld3  );
        strcpy(sdb_app_khcpqy.qyzt,"0");

        iRet = DBInsert("app_khcpqy", SD_APP_KHCPQY, NUMELE(SD_APP_KHCPQY), &sdb_app_khcpqy, sErrmsg);
        if ( iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_INS_KHQY,Fmtmsg(MSG_CUSTOM_INS_KHQY));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("('%s','%s')",sdb_app_khcpqy.xybh,sdb_app_khcpqy.cpdm),"ERROR");
            return COMPRET_FAIL;
        }
        /* �ύ���� */
        if ( DCICommit() !=MID_SYS_SUCC )
        {
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    /* ��ǩԼ��״̬���������� */
    else if( sSignStat[0] == '0' )
    {    
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_QY,MSG_CUSTOM_QY);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    COMP_SOFTSETXML(XMLNM_APP_CUSTOM_XYBH  , sdb_app_khcpqy.xybh );

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0; 
}

/************************************************************************
��̬�����������
�����������:SApp_UpdCUSTOM
�������:SApp_UpdCUSTOM
�������:���¹���ǩԼ��ϵ�����
         �޸Ŀͻ���Ϣ ��֤�����ͺ�֤������Ϊ��
         �޸�ǩԼ��ϵ���Բ�Ʒ���룫Э����Ϊ��
�������:
 ��� ��������  ��������         ��Դ���         ȱʡֵ  �ɿ�  ����˵��

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

�� Ŀ ��: 
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_UpdCUSTOM(HXMLTREE lXmlhandle)
{
    char sModType[1+1];          /* �޸�����  0 ȫ��[Ĭ��] 1 �ͻ���Ϣ 2 ǩԼ��Ϣ */
    char sStrSet[512],sStrSetSql[2048],sSql[2048];
    APP_KHCPQY sdb_app_khcpqy;
    int iResult;
    char sbuf[255];
	char sbuf1[255];
    char sStrSetKhxxSql[2048];
    int  iRet = -1;
    
    int iSetFlag=0;
    int iSetKhxxFlag=0;
    int iSqlLen=0;
    fpub_InitSoComp(lXmlhandle);
    memset(sbuf,0,sizeof(sbuf));
    
    COMP_SOFTGETXML( XMLNM_APP_CUSTOM_XGLX,sbuf ); /* �޸����� */
    pstrcopy( sModType, sbuf,sizeof( sModType ) );
    memset(&sdb_app_khcpqy, 0x00, sizeof(sdb_app_khcpqy));

    if( sModType[0] != '1' )  /* ����ֻ�޸Ŀͻ���Ϣ������ ��ȡǩԼ��Ϣ */
    {
        /* �ۿ�����,�ۿ�״̬,֤������,֤������,�ʻ�����, �û���,
           ��Ʒ����,ҵ����,Э����,�ͻ���Ų������޸� */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLJG, sdb_app_khcpqy.bljg     );
        trim(sdb_app_khcpqy.bljg);
        if ( strlen(sdb_app_khcpqy.bljg) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG, sdb_app_khcpqy.bljg     );
        }
        
        /* Ĭ�������Ա:��Ʒ�����Ա */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLGY, sdb_app_khcpqy.blgy     );
        trim(sdb_app_khcpqy.blgy);
        if ( strlen(sdb_app_khcpqy.blgy) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBGY, sdb_app_khcpqy.blgy     );
        }
        
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLRQ     , sdb_app_khcpqy.blrq     );
        /* Ĭ�ϰ������� */
        trim(sdb_app_khcpqy.blrq);
        if ( strlen(sdb_app_khcpqy.blrq) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_YWRQ     , sdb_app_khcpqy.blrq     );
        }
    
        memset(sbuf,0,sizeof(sbuf));
        memset(sStrSetSql,0,sizeof(sStrSetSql));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHLX,sbuf);
        if (strlen(sbuf) > 0)
        {
             memset(sStrSet, 0, sizeof(sStrSet));
             sprintf(sStrSet, "zhlx ='%s',", sbuf);
             strcat(sStrSetSql,sStrSet);
             iSetFlag=1;
        }

        /* added by yangdong 20140915 �����ϲ������޸� */
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH,sbuf);
        if( strlen(sbuf) > 0 )
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "qyzh ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1,sbuf);
        if( strlen(sbuf) > 0 )
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhh1 ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        /* end of add */
      
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHHM,sbuf);
        if( strlen(sbuf) > 0 )
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zhhm ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
      
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYLX,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "qylx ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHJL,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "khjl ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HYKSRQ,sbuf);
        if( strlen( sbuf ) > 0 )
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "hyksrq ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HYJSRQ,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "hyjsrq ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KTQD,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "ktqd ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH2,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhh2 ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH3,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhh3 ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHJG, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "khjg='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHMC, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhmc='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHLX, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhlx='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DLZJLX, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "dlzjlx='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DLZJHM, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "dlzjhm='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHYB, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhyb='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHDH, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhdh='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHDZ, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhdz='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_JYBZ, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "jybz='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKZDXE, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "kkzdxe=%.2f,", atof( sbuf ) );
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKZQ, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "kkzq='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YDKKRQ, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "ydkkrq='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
		memset(sbuf1,0,sizeof(sbuf1));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD1  , sbuf );
	    pstrcopy(sbuf1, sbuf,sizeof( sdb_app_khcpqy.extfld1 ) );
        if (strlen(sbuf1) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld1='%s',", sbuf1);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD2  , sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld2='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD3  , sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld3='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD4  , sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld4='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD5  , sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld5='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD6  , sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld6='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
      
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DXTZBZ,sbuf);
        if (strlen(sbuf) > 0)
        {
          memset(sStrSet, 0, sizeof(sStrSet));
          sprintf(sStrSet, "dxtzbz ='%s',", sbuf);
          strcat(sStrSetSql,sStrSet);
          iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHZDED,sbuf);
        if (strlen(sbuf) > 0)
        {
          memset(sStrSet, 0, sizeof(sStrSet));
          sprintf(sStrSet, "zhzded =%.2f,", atof(sbuf) );
          strcat(sStrSetSql,sStrSet);
          iSetFlag=1;
        }
    }
    if( sModType[0] != '2' )  /* ��ȡ�ͻ���Ϣ */
    {
        /*  �ͻ���ţ�֤�����ͣ�֤������,�������� �����޸� */
        memset( sStrSetKhxxSql,0,sizeof( sStrSetKhxxSql ));
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHXM,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "khxm='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YWXM,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "ywxm='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BM,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "bm='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHLX,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "khlx='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJKHBH,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zjkhbh='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_CSNY,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "csny='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_SEX,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "sex='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_GJ,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "gj='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HK,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "hk='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HYZK,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "hyzk='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_JYCD,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "jycd='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZY,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zy='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZW,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zw='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_SRQK,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "srqk=%15.2f,", atof(sbuf) );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_GSDZ,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "gsdz='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_GSYB,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "gsyb='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_GSDH,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "gsdh='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZZDZ,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zzdz='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZZYB,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zzyb='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZZDH,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zzdh='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YJDZLX,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yjdzlx='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_SJHM,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "sjhm='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_Email,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "memail='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    }

    /* modified by � 20111222 �жϷ���ǰ���� */
    if ( 0 == iSetKhxxFlag &&  0 == iSetFlag  )
    {
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_SET_ISNULL,MSG_CUSTOM_SET_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;    
    }

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* �޸�ģʽΪ �޸Ŀͻ���Ϣ������ͬʱ�޸Ŀͻ���Ϣ��ǩԼ��Ϣʱ */
    if( sModType[0] != '2' && iSetKhxxFlag == 1 )  /* ����ֻ�޸�ǩԼ��Ϣ�������޸Ŀͻ���Ϣ */
    {
        /* ��֤�����ͺ�֤������ �޸Ŀͻ���Ϣ */
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJLX,sbuf);
        if ( 0 == sbuf[0] ) 
        {
             DCIRollback();
             fpub_SetMsg(lXmlhandle,MID_CUSTOM_ZJLX_ISNULL,MSG_CUSTOM_ZJLX_ISNULL);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return -1;    
        }
        memcpy(sdb_app_khcpqy.zjlx,sbuf,sizeof(sdb_app_khcpqy.zjlx ));    
      
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJHM,sbuf);
        if ( 0 == sbuf[0] ) 
        {
             DCIRollback();
             fpub_SetMsg(lXmlhandle,MID_CUSTOM_ZJHM_ISNULL,MSG_CUSTOM_ZJHM_ISNULL);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return -1;    
        }
        memcpy(sdb_app_khcpqy.zjhm, sbuf,sizeof(sdb_app_khcpqy.zjhm ));    

        /* ȥ�����һ��, */
        iSqlLen = strlen( sStrSetKhxxSql );
        sStrSetKhxxSql[ iSqlLen - 1 ] = '\0';

        memset( sSql, 0x00, sizeof( sSql ) );
        snprintf(sSql,sizeof(sSql),"update app_khxx set %s where zjlx= '%s' AND zjhm='%s' "\
                               ,sStrSetKhxxSql, sdb_app_khcpqy.zjlx, sdb_app_khcpqy.zjhm );
        iRet = DCIExecuteDirect(  sSql );
        if ( iRet < 0 )
        {
            DCIRollback();
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->sSql[%s]",sSql),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_UPD_KHQY,MSG_CUSTOM_UPD_KHQY);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
            return -1;
        }
    } 
    if( sModType[0] != '1' && iSetFlag == 1 )  
    /* ����ֻ�޸Ŀͻ���Ϣ�����򰴲�Ʒ�����Э���Ÿ���ǩԼ��  */
    {
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_CPDM,sbuf);
        if ( 0 == sbuf[0] ) 
        {
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_CPDM_ISNULL,MSG_CUSTOM_CPDM_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;    
        }
        memcpy(sdb_app_khcpqy.cpdm,sbuf,sizeof(sdb_app_khcpqy.cpdm));    
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_XYBH,sbuf);
        if ( 0 == sbuf[0] ) 
        {
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_XYBH_ISNULL,MSG_CUSTOM_XYBH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;    
        }
        memcpy(sdb_app_khcpqy.xybh,sbuf,sizeof(sdb_app_khcpqy.xybh ));    

        memset( sSql, 0x00, sizeof( sSql ) );
        snprintf(sSql,sizeof(sSql),"UPDATE app_khcpqy SET %s bljg='%s',blgy='%s',blrq='%s'\
            WHERE cpdm= '%s' AND xybh='%s' " ,sStrSetSql, sdb_app_khcpqy.bljg,\
            sdb_app_khcpqy.blgy, sdb_app_khcpqy.blrq,sdb_app_khcpqy.cpdm, sdb_app_khcpqy.xybh );

        iRet = DCIExecuteDirect( sSql );
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->sSql[%s]",sSql),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_UPD_KHQY,MSG_CUSTOM_UPD_KHQY);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
            return -1;
        }
    }

    DCICommit();

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);   
    return 0; 
}

/************************************************************************
��̬�����������
�����������:SApp_QuyCUSTOM
�������:SApp_QuyCUSTOM
�������:��ѯ����ǩԼ��ϵ�����
�������:
 ��� ��������  ��������         ��Դ���         ȱʡֵ  �ɿ�  ����˵��

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

�� Ŀ ��: 
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_QuyCUSTOM(HXMLTREE lXmlhandle)
{
    APP_KHCPQY sdb_app_khcpqy;
    APP_KHXX sdb_app_khxx;
    char ssql[1024];
    int  iMaxRecord = 0;
    char sStrWhere[1024],sStrWhereSql[1024],sTmp[1024];
    int iParas;
    char sbuf[255];
    int i, iflag;
    char sXmlnode[512];
    int  iSqllen=0;
    int  iRet = -1;
    char sErrmsg[512];
    CURSOR cur;
    
    char sRespNode[32];

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /* 20090717 modified by yangdong �޸Ĳ�ѯ���ؽڵ��� */
    memset( sRespNode, 0x00, sizeof( sRespNode ) );
    sprintf( sRespNode,"/app/custom/info" );
    
    memset(&sdb_app_khcpqy,0,sizeof(sdb_app_khcpqy));
    
    iSqllen=0;
    memset(sStrWhereSql,0,sizeof(sStrWhereSql));

    /* ǩԼ��ѯ����¼������ */
    memset( sbuf, 0x00, sizeof( sbuf ) );
    COMP_SOFTGETXML( XMLNM_APP_CUSTOM_QYCXXZ, sbuf );
    iMaxRecord = atoi( sbuf );
    
    /* ֻ������ЧǩԼ��¼ */
    /* modifie by yangdong 20130220 ���а�״̬��ѯ
    sprintf(sStrWhereSql, "  qyzt='0' AND rownum <= %s ", sbuf );
    */
    /*sprintf(sStrWhereSql, " rownum <= %s ", sbuf );
    iSqllen=strlen(sStrWhereSql);*/
    
    sprintf(sStrWhereSql, " 1=1 ");
    iSqllen=strlen(sStrWhereSql);

    /* ��Ʒ���� */
    COMP_SOFTGETXML( XMLNM_APP_CUSTOM_CPDM, sdb_app_khcpqy.cpdm     );
    if ( strlen( sdb_app_khcpqy.cpdm ) > 0)
    {
        sprintf(sStrWhereSql+iSqllen, " and cpdm='%s'",sdb_app_khcpqy.cpdm);
        iSqllen=strlen(sStrWhereSql);
    }
    
    /* �û��� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1     , sdb_app_khcpqy.yhh1     );
    trim(sdb_app_khcpqy.yhh1);
    if ( strlen(sdb_app_khcpqy.yhh1) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and yhh1='%s'",sdb_app_khcpqy.yhh1);
        iSqllen=strlen(sStrWhereSql);
    }
    
    /* �����ʺ� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH     , sdb_app_khcpqy.qyzh     );
    trim(sdb_app_khcpqy.qyzh);
    if ( strlen(sdb_app_khcpqy.qyzh) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and qyzh='%s'",sdb_app_khcpqy.qyzh);
        iSqllen=strlen(sStrWhereSql);
    }

    /* ֤������ */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJLX, sdb_app_khcpqy.zjlx );
    trim(sdb_app_khcpqy.zjlx );
    if ( strlen(sdb_app_khcpqy.zjlx) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and zjlx='%s'",sdb_app_khcpqy.zjlx);
        iSqllen=strlen(sStrWhereSql);
    }
    /* ֤������ */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJHM, sdb_app_khcpqy.zjhm );
    trim(sdb_app_khcpqy.zjhm );
    if ( strlen(sdb_app_khcpqy.zjhm) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and zjhm='%s'",sdb_app_khcpqy.zjhm );
        iSqllen=strlen(sStrWhereSql);
    }

    /* added by yangdong 20130220 ���󵥱�� 201302200006 ������ģ����ѯ���� ��������������Ա��ҵ����  */
    /* ������� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLJG, sdb_app_khcpqy.bljg);
    trim(sdb_app_khcpqy.bljg);
    if ( strlen(sdb_app_khcpqy.bljg) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and bljg='%s'",sdb_app_khcpqy.bljg );
        iSqllen=strlen(sStrWhereSql);
    }
    
    /* �����Ա */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLGY, sdb_app_khcpqy.blgy);
    trim(sdb_app_khcpqy.blgy);
    if ( strlen(sdb_app_khcpqy.blgy) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and blgy='%s'",sdb_app_khcpqy.blgy );
        iSqllen=strlen(sStrWhereSql);
    }
    
    /* �޸�[zff]20130507 start ���Ӳ�ѯ����:�������� */
    /* �������� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLRQ, sdb_app_khcpqy.blrq);
    trim(sdb_app_khcpqy.blrq);
    if ( strlen(sdb_app_khcpqy.blrq) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and blrq='%s'",sdb_app_khcpqy.blrq );
        iSqllen=strlen(sStrWhereSql);
    }
    /* �޸�[zff]20130507 end */
    
    /* ҵ���� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YWBH, sdb_app_khcpqy.ywbh);
    trim(sdb_app_khcpqy.ywbh);
    if ( strlen(sdb_app_khcpqy.ywbh) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and ywbh='%s'",sdb_app_khcpqy.ywbh);
        iSqllen=strlen(sStrWhereSql);
    }
    /* ǩԼ״̬ */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZT, sdb_app_khcpqy.qyzt);
    trim(sdb_app_khcpqy.qyzt);
    if( sdb_app_khcpqy.qyzt[0] == '2' )
         /* ��ѯȫ���û� */
        ;
    else if( sdb_app_khcpqy.qyzt[0] == '1' || sdb_app_khcpqy.qyzt[0] == '0' )
        sprintf(sStrWhereSql+iSqllen, " and qyzt='%s'",sdb_app_khcpqy.qyzt);
    else /* Ĭ�ϲ�ѯ��������ǩԼ�û� */
        sprintf(sStrWhereSql+iSqllen, " and qyzt='0'" );

    iSqllen=strlen(sStrWhereSql);
    /* end of add */
    
    memset(ssql,0,sizeof(ssql));
    /*sprintf(ssql,"SELECT * FROM app_khcpqy WHERE %s ORDER BY cpdm,xybh",sStrWhereSql);*/
    sprintf(ssql,"SELECT * FROM  app_khcpqy WHERE %s ORDER BY cpdm,xybh fetch first %s rows only",sStrWhereSql,sbuf);
    if ((cur = DCIDeclareCursor(ssql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
  
    for (i=0,iflag=0;;i++)
    {
        memset(&sdb_app_khcpqy,0,sizeof(sdb_app_khcpqy));    
        iRet = DBFetch(cur, SD_APP_KHCPQY, NUMELE(SD_APP_KHCPQY), &sdb_app_khcpqy, sErrmsg ) ;
        if( iRet < 0 )
        { 
            iflag = -1 ; 
            break;
        }
        if ( iRet == 0 )
            break;

        /*��ȡ�������ݽ��д���*/
        /* Э���� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/xybh", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.xybh    );
        
        /* ��Ʒ���� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/cpdm", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.cpdm    );
        
        /* ҵ���� */
        trim(sdb_app_khcpqy.ywbh);
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/ywbh", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.ywbh    );
        
        /* �ʺ����� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/zhlx", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.zhlx    );
        
        /* ǩԼ�ʺ� */
        trim(sdb_app_khcpqy.qyzh);
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/qyzh", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.qyzh    );
        
        /* ���� */
        trim(sdb_app_khcpqy.zhhm);
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/zhhm", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.zhhm    );
        
        /* ֤������ */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/zjlx", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.zjlx    );
        
        /* ֤������ */
        trim(sdb_app_khcpqy.zjhm);
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/zjhm", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.zjhm    );
        
        /* ǩԼ���� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/qylx", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.qylx    );
        
        /* �ͻ����� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/khjl", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.khjl    );
        
        /* ��Լ��ʼ���� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/hyksrq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.hyksrq    );
        
        /* ��Լ�������� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/hyjsrq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.hyjsrq    );
        
        /* ��ͨ���� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/ktqd", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.ktqd    );
        
        /* ������� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/bljg", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.bljg    );
        
        /* �����Ա */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/blgy", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.blgy    );
        
        /* �������� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/blrq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.blrq    );
        
        /* �û����1 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhh1", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhh1    );
        
        /* �û����2 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhh2", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhh2    );
        
        /* �û����3 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhh3", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhh3    );
        
        memset(&sdb_app_khxx, 0, sizeof(sdb_app_khxx));
        /* ��ȡ�ͻ���Ϣ --B*/
        snprintf( sSql1, sizeof( sSql1 ),  "SELECT * FROM app_khxx \
            WHERE zjlx = '%s' AND zjhm ='%s'",sdb_app_khcpqy.zjlx,sdb_app_khcpqy.zjhm );
        if( iRet < 0 )
        {
            DCIFreeCursor(cur);
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* ��ȡ�ͻ���Ϣ --B*/
        
        /* �����ʼ� */
        trim(sdb_app_khxx.memail);
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/email", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khxx.memail    );
        
        /* ���ű�־ */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/dxtzbz", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.dxtzbz    );
        
        /* �޶� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/zhzded", sRespNode, i+1 );
        memset(sbuf,0,sizeof(sbuf));
        sprintf( sbuf,"%f",sdb_app_khcpqy.zhzded);
        COMP_SOFTSETXML(sXmlnode     , sbuf    );
        
        /* ��չ�ֶ�1 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld1", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld1    );
        
        /* ��չ�ֶ�2 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld2", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld2    );
        
        /* ��չ�ֶ�3 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld3", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld3    );
  
        /* added by yangdong 20090708  */
        /* �������� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/khjg", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.khjg );
        
        /* �û�����  */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhmc", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhmc);
        
        /* �û�����  */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhlx", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhlx);
  
        /* ����֤������ */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/dlzjlx", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.dlzjlx);
        
        /* ����֤������ */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/dlzjhm", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.dlzjhm );
        
        /* �û��ʱ� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhyb", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhyb );
        
        /* �û��绰 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhdh", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhdh );
        
        /* �û���ַ */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhdz", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhdz );
        
        /* ���ױ��� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/jybz", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.jybz );
        
        /* �ۿ�����޶� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/kkzdxe", sRespNode, i+1 );
        memset( sbuf, 0x00, sizeof( sbuf ) );
        sprintf( sbuf, "%.2f", sdb_app_khcpqy.kkzdxe );
        COMP_SOFTSETXML(sXmlnode     , sbuf );
        
        /* Լ���ۿ����� */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/ydkkrq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.ydkkrq );
        
        /* �ۿ�����*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/kkzq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.kkzq);
        
        /* �ۿ�״̬*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/kkzt", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.kkzt);
        
        /* �ۿ�����*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/kkrq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.kkrq );
  
        /* ��չ�ֶ�4 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld4", sRespNode, i+1 );
         COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld4 );
        
        /* ��չ�ֶ�5 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld5", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld5 );
        
        /* ��չ�ֶ�6 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld6", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld6 );
        /* end of add */
      
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/qyzt", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.qyzt    );
    }
    DCIFreeCursor(cur);
    if (iflag < 0)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->���׾ܾ�:XX����ʧ��,iret[%d]",iflag),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,MSG_YW_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    if ( 0 == i )  /*��¼û�ҵ�*/
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->��¼û�ҵ�[%d]",i),"INFO");
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("ssql[%s]",ssql),"INFO");
        /* by yr 20120913 */
        fpub_SetMsg(lXmlhandle,MID_APP_QY_NOTFOUND ,MSG_APP_QY_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML( XMLNM_APP_CUSTOM_COUNT, itoa( i ) );

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    return COMPSTATUS_SUCC;
}

/************************************************************************
��̬�����������
�����������:SApp_DelCUSTOM
�������:SApp_DelCUSTOM
�������:ɾ������ǩԼ��ϵ�����
�������:
 ��� ��������  ��������         ��Դ���         ȱʡֵ  �ɿ�  ����˵��

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

�� Ŀ ��: 
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_DelCUSTOM(HXMLTREE lXmlhandle)
{
    char sQyzh[32+1];
    char sCpdm[16+1];
    char sYhh[32+1];
    char sYwbh[16+1];
    char sBljg[16+1];
    char sBlgy[16+1];
    char sBlrq[8+1];
    char sSignType[2];   /* ǩԼģʽ */
    char sSignStat[2];   /* ǩԼ״̬ */
    char sbuf[255];
    char sSql[1024],sStrWhere[1024];
    char sErrmsg[512];
    int iResult;
    int  iRet = -1;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"");
  
    memset(sSignType, 0, sizeof(sSignType));
    COMP_SOFTGETXML( XMLNM_APP_CPXX_QYMS, sSignType);
    trim(sSignType);
    
    /* ��Ʒ���� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_CPDM     , sCpdm);
    if ( 0 == sCpdm[0])
    {
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_CPDM_ISNULL,MSG_CUSTOM_CPDM_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;    
    }
    trim(sCpdm);

    /* ҵ���� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YWBH     , sYwbh );
    trim(sYwbh);
    
    /* �û��� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1     , sYhh     );
    trim(sYhh);
    
    /* �����ʺ� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH     , sQyzh     );
    trim(sQyzh);
    
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLJG     , sBljg     );
    trim(sBljg);
    if ( strlen(sBljg) <=0 )
    {
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG     , sBlrq     );
    }

    /* Ĭ�������Ա */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLGY     , sBlgy     );
    trim(sBlgy);
    if ( strlen(sBlgy) <=0 )
    {
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBGY     , sBlgy     );
    }

    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLRQ     , sBlrq     );
    /* Ĭ�ϰ������� */
    trim(sBlrq);
    if ( strlen(sBlrq) <=0 )
    {
        COMP_SOFTGETXML(XMLNM_APP_CPXX_YWRQ     , sBlrq     );
    }
    
    memset(sStrWhere, 0, sizeof(sStrWhere));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    switch (atoi(sSignType))
    {
        case 1: /* ��Ʒ����+�����ʺ�Ψһ */
            if ( 0 == sQyzh[0] ) 
            {
                 fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
                 fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                 return -1;    
            }
            
            snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt FROM app_khcpqy \
                WHERE qyzh = '%s'and cpdm = '%s'", sQyzh, sCpdm );
            snprintf(sStrWhere, sizeof( sStrWhere ), "  cpdm = '%s' and qyzh = '%s' ", sCpdm,sQyzh);
            break;
            
        case 3 : /* ��Ʒ����+�����ʺ�+�û����Ψһ*/
            if ( 0 == sQyzh[0] ) 
            {
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            
            if ( 0 == sYhh[0] ) 
            {
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            
            snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt FROM app_khcpqy WHERE \
                 yhh1 = '%s' AND qyzh = '%s'AND cpdm ='%s'",sYhh, sQyzh, sCpdm );
            
            snprintf(sStrWhere, sizeof( sStrWhere ), "  cpdm = '%s' and qyzh='%s' and yhh1 = '%s' ", sCpdm,sQyzh,sYhh);
            
            break;

        case 4 : /* ҵ���� +�û����Ψһ */
            if ( 0 == sYhh[0] ) 
            {
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt FROM app_khcpqy \
                         WHERE yhh1 = '%s' and ywbh = '%s' ",sYhh, sYwbh );
            memset(sStrWhere, 0, sizeof(sStrWhere));
            snprintf(sStrWhere, sizeof( sStrWhere ), "  ywbh = '%s' and yhh1 = '%s' ", sYwbh, sYhh);
            break;

        default : /* ��Ʒ����+�û����Ψһ */
            if ( 0 == sYhh[0] ) 
            {
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt FROM app_khcpqy \
                         WHERE yhh1 = '%s' and cpdm = '%s' ",sYhh, sCpdm );
            snprintf(sStrWhere, sizeof( sStrWhere ), "  cpdm = '%s' and yhh1 = '%s' ", sCpdm,sYhh);
    }
    iRet = DBSelectToMultiVar( sErrmsg, sSql1, sSignStat ) ;
    if( iRet < 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if ( iRet == 0 || sSignStat[0] == '1' )  /* ��¼�����ڻ����ѽ�Լ */
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,\
            Fmtmsg("��Ʒ����[%s],�û���[%s],�����ʺ�[%s],ǩԼ״̬[%s]",sCpdm,sYhh, sQyzh,sSignStat),"INFO");
                  
        if( iRet == 0 )
            fpub_SetMsg(lXmlhandle,MID_APP_QY_NOTFOUND,MSG_APP_QY_NOTFOUND );
        else
            fpub_SetMsg(lXmlhandle,MID_APP_KHCPQY,MSG_APP_KHCPQY);

        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);   
        return 0; 
    }
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* ��Լ���� */
    memset(sSql,0,sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"update app_khcpqy set \
            qyzt = '1', bljg='%s',blgy='%s',blrq='%s'  where %s ",\
            sBljg, sBlgy, sBlrq , sStrWhere);
    iRet = DCIExecuteDirect( sSql );
    if(iRet<0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("  -->sSql[%s]",sSql),"debug2");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg(MSG_SYS_DBEXEC,sSql),"SDB_DynExecSql");
    }

    DCICommit();

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);   
    return 0; 
}


/************************************************************************
��̬�����������
�����������:SApp_SerchCUS
�������:SApp_SerchCUS
�������:��ѯ����ǩԼ��ϵ����Ϣ�Ƿ����
�������:
 ��� ��������  ��������         ��Դ���         ȱʡֵ  �ɿ�  ����˵��

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

�� Ŀ ��: 
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
int SApp_SerchCUS(HXMLTREE lXmlhandle)
{
    char   sCpdm[16+1]={0};    /*��Ʒ����*/
    char   sQyzh[32+1]={0};   /*ǩԼ�˻�*/
    char   sYhh[32+1]={0};    /*�û���*/
    char   sYwbh[16+1]={0};    /*ҵ����*/
    char   sSignType[2]={0};  /*ǩԼ����*/
    char   sXybh[20+1]={0};   /*Э����*/
    char   sQyzt[1+1]={0};    /*ǩԼ״̬*/
    char sErrmsg[512];
    int iRet = -1;

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"");
    /* ---------- �жϿͻ��Ƿ���ǩԼ begin ---------- */
    
    /* ��Ʒ���� */
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPDM , sCpdm );
    trim(sCpdm);
    if ( 0 == sCpdm[0])
    {
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_CPDM_ISNULL,MSG_CUSTOM_CPDM_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    /* ҵ���� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YWBH , sYwbh );
    trim(sYwbh);

    /* �û��� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1 , sYhh );
    trim(sYhh);
    
    /* �����ʺ� */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH , sQyzh );
    trim(sQyzh);
    
    /* ϵͳ֧��ǩԼģʽ */
    memset(sSignType, 0, sizeof(sSignType));
    COMP_SOFTGETXML( XMLNM_APP_CPXX_QYMS, sSignType );
    trim(sSignType);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("ǩԼ��ϵ����Ʒ����[%s], �ʺ�[%s], �û���[%s], ҵ���� [%s], ǩԼ��ʽ [%s]", \
        sCpdm, sQyzh, sYhh, sYwbh, sSignType),"INFO");
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    /* ��Ʒ����+�����ʺ�Ψһ */
    if ( sSignType[0] == '1' )
    {
        /* �����ʺŲ���Ϊ�� */
        if ( 0 == sQyzh[0] )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy WHERE\
            qyzh='%s' AND cpdm='%s'",sQyzh, sCpdm );
    }
    else
    /* ��Ʒ����+�����ʺ�+�û����Ψһ ǩԼ����3 ΪĬ��ֵ */
    if ( sSignType[0] == '3' )
    {
        /* �����ʺŲ���Ϊ�� */
        if ( 0 == sQyzh[0] )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;    
        }
        /* �û���Ų���Ϊ�� */
        if ( 0 == sYhh[0] )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy WHERE\
            qyzh='%s' AND yhh1='%s'  AND cpdm='%s'",sQyzh, sYhh, sCpdm );
    }

    else
    /* ҵ����+�û����Ψһ */
    if ( sSignType[0] == '4' )
    {
        /* �û���Ų���Ϊ�� */
        if ( 0 == sYhh[0] )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
		/*modefied by llh 20181012 begin*/
        /*snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy WHERE\
            yhh1='%s'  AND ywbh='%s'",sQyzh, sYhh);*/
        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy WHERE\
            yhh1='%s'  AND ywbh='%s'", sYhh, sYwbh);
		/*modefied by llh 20181012 end */
    }

    else
    /* ��Ʒ����+�û����Ψһ */
    {
        /* �û���Ų���Ϊ�� */
        if ( 0 == sYhh[0] )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy WHERE\
            yhh1='%s'  AND cpdm='%s'", sQyzh, sCpdm );
    }

    iRet = DBSelectToMultiVar( sErrmsg, sSql1, sQyzt, sXybh ) ;
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )  /* ��¼������ */
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("��Ʒ����[%s],�ͻ���[%s],ǩԼ״̬[%s]",sCpdm,sYhh,sQyzt),"INFO");
        fpub_SetMsg(lXmlhandle,MID_APP_QY_NOTFOUND,MSG_APP_QY_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }
    if( sQyzt[0] == '0' )
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("��Ʒ����[%s],�ͻ���[%s],ǩԼ״̬[%s]",sCpdm,sYhh,sQyzt),"INFO");
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_QY,MSG_CUSTOM_QY);
        fpub_SetCompStatus(lXmlhandle, 1);/* �ͻ���ǩԼ */
        return COMPRET_FAIL;
    }
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"");
    fpub_SetMsg(lXmlhandle,MID_CUSTOM_QY,"�ͻ�ǩԼ��ϵ������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
