/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:APP_COMPANY.c
�ļ�����:ҵ��λǩԼ
�� Ŀ ��:
�� �� Ա:YangDong
��������:2014��7��10��
�� �� Ա:YangDong
��������:2015��9��15��
*********************************************************************/
#include "gaps_head.h"
#include "../incl/app_head.h"

#define SOCOMPVERSION "V4.1.0.1"
#define SOCOMPBUILDNO BUILDDATETIME

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>APP_COMPANY.so</soname>\
        <sosrcname>APP_COMPAY.c</sosrcname>\
        <sonote>APP��λ��ƷǩԼ����</sonote>\
        <version>\
        <rec ver=\"2.1.0.3\" modify=\"2014-7-10 15:08\" programer=\"YangDong\" filesize=\"1591618\">��λ��ƷǩԼ����</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-9-15 15:08\" programer=\"YangDong\" filesize=\"1591618\">DCI����</rec>\
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

APP_DWCPXY sdb_app_dwcpxy;
APP_DWXX sdb_app_dwxx;
APP_DW_CPXY sdb_app_dw_cpxy;
char sSql[1024+1];  
char sSql2[1024+1];
    
/**********************************************************************
�������: SAPP_ADDDWXY
�������: ������λЭ��
���������
���������
���������
����˵��: 
*************************************************************************/
IRESULT SAPP_AddDwxy(HXMLTREE lXmlhandle)
{
    int  i,iParas;
    int  iDwbh;
    char sYwbh[16+1];
    char sDwbh[16+1];
    char sBuf[512+1];
    char sTmp[128+1];
    char sWhsj[14+1];
    fpub_InitSoComp(lXmlhandle);
    int iRet = -1;
    char sErrmsg[512];
                      
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")  
       
    /*����������*/
    COMP_PARACOUNTCHKMIN(2)

    memset( &sdb_app_dwcpxy, 0x00, sizeof( sdb_app_dwcpxy ) );
    memset( &sdb_app_dwxx, 0x00, sizeof( sdb_app_dwxx ) );
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��Ʒ����") 
    trim(sBuf);
    strncpy( sdb_app_dwcpxy.cpdm, sBuf, sizeof( sdb_app_dwcpxy.cpdm ) );
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"�ո���־")
    trim(sBuf);
    pstrcopy( sdb_app_dwcpxy.sfbz, sBuf, sizeof( sdb_app_dwcpxy.sfbz ) );

    LOG(LM_DEBUG,Fmtmsg("��Ʒ����[%s]",sdb_app_dwcpxy.cpdm ),"DEBUG")  

    /* ��λ��š�ҵ���� */
    COMP_SOFTGETXML(  XMLNM_APP_REQ_DWBH, sDwbh );
    COMP_SOFTGETXML(  XMLNM_APP_REQ_YWBH, sYwbh );
    trim( sDwbh );
    trim( sYwbh );
    
    /* ��ȡ���͵�λǩԼ�����Ϣ */
    /* ���׻�������Ա */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(  XMLNM_APP_REQ_JYJG, sBuf);
    pstrcopy( sdb_app_dwcpxy.bljg, sBuf, sizeof( sdb_app_dwcpxy.bljg ) );
    pstrcopy( sdb_app_dwcpxy.whjg, sBuf, sizeof( sdb_app_dwcpxy.bljg ) );

    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(  XMLNM_APP_REQ_JYGY, sBuf);
    pstrcopy( sdb_app_dwcpxy.blgy, sBuf, sizeof( sdb_app_dwcpxy.blgy ) );
    pstrcopy( sdb_app_dwcpxy.whgy, sBuf, sizeof( sdb_app_dwcpxy.blgy ) );

    /* �������� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_ZWRQ, sBuf);
    pstrcopy( sdb_app_dwcpxy.blrq, sBuf, sizeof( sdb_app_dwcpxy.blrq ) );

    /* ά��ʱ�� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_SYSTIME, sBuf);
    snprintf( sWhsj, sizeof( sWhsj ), "%s%s", sdb_app_dwcpxy.blrq, sBuf );
    pstrcopy( sdb_app_dwcpxy.whsj, sWhsj, sizeof( sWhsj ) );
    pstrcopy( sdb_app_dwxx.whsj, sWhsj, sizeof( sWhsj ) );
 
    /* ��ͬ��� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_XYBH, sBuf);
    pstrcopy( sdb_app_dwcpxy.xybh, sBuf, sizeof( sdb_app_dwcpxy.xybh ) );

    /* ҵ������Ϊ�� - ʹ�õ�λ����+��Ʒ���� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_YWMC, sBuf);
    strlen( sBuf );
    if( strlen( sBuf ) < 2 )
    {
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWMC, sBuf);
        memset(sTmp, 0, sizeof(sTmp));
        COMP_SOFTGETXML( XMLNM_APP_CPXX_CPMC, sTmp);
        snprintf( sdb_app_dwcpxy.ywmc, sizeof( sdb_app_dwcpxy.ywmc ) ,"%s%s",sBuf,sTmp );
    }
    else
        pstrcopy( sdb_app_dwcpxy.ywmc, sBuf, sizeof( sdb_app_dwcpxy.ywmc ) );

    /* ���д��� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_YHDM, sBuf);
    pstrcopy( sdb_app_dwcpxy.yhdm, sBuf, sizeof( sdb_app_dwcpxy.yhdm ) );

    /* �˻����� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_ZHLX, sBuf);
    pstrcopy( sdb_app_dwcpxy.zhlx, sBuf, sizeof( sdb_app_dwcpxy.zhlx ) );

    /* �����˺� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DSZH, sBuf);
    pstrcopy( sdb_app_dwcpxy.dszh, sBuf, sizeof( sdb_app_dwcpxy.dszh ) );

    /* ���ջ����� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DSZHMC, sBuf);
    pstrcopy( sdb_app_dwcpxy.dszhmc, sBuf, sizeof( sdb_app_dwcpxy.dszhmc ) );

    /* �����˺� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DFZH, sBuf);
    pstrcopy( sdb_app_dwcpxy.dfzh, sBuf, sizeof( sdb_app_dwcpxy.dfzh ) );

    /* ���������� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DFZHMC, sBuf);
    pstrcopy( sdb_app_dwcpxy.dfzhmc, sBuf, sizeof( sdb_app_dwcpxy.dfzhmc ) );

    /* �ͻ��������� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_KHJL, sBuf);
    pstrcopy( sdb_app_dwcpxy.khjl, sBuf, sizeof( sdb_app_dwcpxy.khjl ) );

    /* ��Լ��ʼ���� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_HYKSRQ, sBuf);
    /* Ϊ����Ĭ��Ϊ���� */
    if( strlen( sBuf ) < 1 )
        strcpy( sdb_app_dwcpxy.hyksrq, sdb_app_dwcpxy.blrq );
    else
        pstrcopy( sdb_app_dwcpxy.hyksrq, sBuf, sizeof( sdb_app_dwcpxy.hyksrq ) );

    /* ��Լ�������� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_HYJSRQ, sBuf);
    /* Ϊ����Ĭ��Ϊһ���ϴ����� 
    if( strlen( sBuf ) < 1 )
        strcpy( sdb_app_dwcpxy.hyjsrq, "20500101");
    else */
        pstrcopy( sdb_app_dwcpxy.hyjsrq, sBuf, sizeof( sdb_app_dwcpxy.hyjsrq ) );

    /* �˻���Ͷ�� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_ZDED, sBuf);
    sdb_app_dwcpxy.zhzded = atof(  sBuf );

    /* �ڲ����ɻ� ������չ�ֶ�1 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBZH, sBuf);
    pstrcopy( sdb_app_dwcpxy.extfld1, sBuf, sizeof( sdb_app_dwcpxy.extfld1 ) );

    /* �Ƿ���ҪУ��ǩԼ��ϵ��������չ�ֶ�2 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_JYQY, sBuf);
    pstrcopy( sdb_app_dwcpxy.extfld2, sBuf, sizeof( sdb_app_dwcpxy.extfld2 ) );

    /*  ��λ���� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWMC, sBuf);
    pstrcopy( sdb_app_dwxx.dwmc, sBuf, sizeof( sdb_app_dwxx.dwmc ) );

    /*  ��λ֤������ */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWZJLX, sBuf);
    pstrcopy( sdb_app_dwxx.dwzjlx, sBuf, sizeof( sdb_app_dwxx.dwzjlx ) );

    /*  ��λ֤������ */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWZJHM, sBuf);
    pstrcopy( sdb_app_dwxx.dwzjhm, sBuf, sizeof( sdb_app_dwxx.dwzjhm ) );

    /* ��λ��ϵ������ */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWLXR , sBuf);
    pstrcopy( sdb_app_dwxx.dwlxr, sBuf, sizeof( sdb_app_dwxx.dwlxr ) );
    pstrcopy( sdb_app_dwcpxy.lxr, sBuf, sizeof( sdb_app_dwcpxy.lxr ) );

    /* ��λ��ϵ�˵绰 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWLXRDH, sBuf);
    pstrcopy( sdb_app_dwxx.dwlxrdh, sBuf, sizeof( sdb_app_dwxx.dwlxrdh ) );
    pstrcopy( sdb_app_dwcpxy.lxdh, sBuf, sizeof( sdb_app_dwcpxy.lxdh ) );

    /* ��λ��ϵ��ַ */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWDZ, sBuf);
    pstrcopy( sdb_app_dwxx.dwdz, sBuf, sizeof( sdb_app_dwxx.dwdz ) );

    /* ��λ��ϵemail*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWEMAIL, sBuf);
    pstrcopy( sdb_app_dwxx.dwemail, sBuf, sizeof( sdb_app_dwxx.dwemail ) );

    /* ��չ�ֶ�1 ����ڲ��ͻ��� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBKHH, sBuf);
    pstrcopy( sdb_app_dwxx.extfld1, sBuf, sizeof( sdb_app_dwxx.extfld1 ) );

    /* ��չ�ֶ�2*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_EXTFLD2, sBuf);
    pstrcopy( sdb_app_dwxx.extfld2, sBuf, sizeof( sdb_app_dwxx.extfld2 ) );

    /* �������ҵ���ţ���ֱ��ʹ��(�涨���ҵ�����ⲿ���ɣ���λ���Ҳ�ⲿ����) */
    if( strlen( sYwbh ) > 0 )
    {
        strcpy( sdb_app_dwcpxy.ywbh, sYwbh ) ;
        strcpy( sdb_app_dwcpxy.dwbh, sDwbh ) ;
        strcpy( sdb_app_dwxx.dwbh, sDwbh ) ;
    }
    else
    {
        /* �����л�ȡ��λ���*/
        if( fprv_getSeqno( "K_DWBH", &iDwbh ) < 0 )
        {
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        } 

        /* ����ҵ���� :��Ʒ���룫��λ��� */
        snprintf( sdb_app_dwcpxy.ywbh, sizeof( sdb_app_dwcpxy.ywbh ) , "%s%06d", sdb_app_dwcpxy.cpdm, iDwbh ) ;
        strcpy( sdb_app_dwcpxy.dwbh, sdb_app_dwcpxy.ywbh ) ;
        /* ��λ���ͬҵ���� */
        strcpy( sdb_app_dwxx.dwbh, sdb_app_dwcpxy.ywbh ) ;
    }

    LOG(LM_DEBUG,Fmtmsg("ҵ����[%s]",sdb_app_dwcpxy.ywbh ),"DEBUG")  

	/* add by sunpj 2016-11-11 beg*/

    /* ��������*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_FWRX, sBuf);
    pstrcopy( sdb_app_dwcpxy.fwrx, sBuf, sizeof( sdb_app_dwcpxy.fwrx ) );

	/* �ɷѱ����ʾ����*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_JFBHXSMC, sBuf);
    pstrcopy( sdb_app_dwcpxy.jfbhxsmc, sBuf, sizeof( sdb_app_dwcpxy.jfbhxsmc ) );

	/* �ͻ���*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_KHH, sBuf);
    pstrcopy( sdb_app_dwcpxy.khh, sBuf, sizeof( sdb_app_dwcpxy.khh ) );

	/* �ڲ����˺�����*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBHZHMC, sBuf);
    pstrcopy( sdb_app_dwcpxy.nbhzhmc, sBuf, sizeof( sdb_app_dwcpxy.nbhzhmc ) );

	/* �ڲ����˺�*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBHZH, sBuf);
    pstrcopy( sdb_app_dwcpxy.nbhzh, sBuf, sizeof( sdb_app_dwcpxy.nbhzh ) );

	/* �������ڲ����˺�����*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_SXFNBHZHMC, sBuf);
    pstrcopy( sdb_app_dwcpxy.sxfnbhzhmc, sBuf, sizeof( sdb_app_dwcpxy.sxfnbhzhmc ) );

	/* �������ڲ����˺�*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_SXFNBHZH, sBuf);
    pstrcopy( sdb_app_dwcpxy.sxfnbhzh, sBuf, sizeof( sdb_app_dwcpxy.sxfnbhzh ) );

	/* �ϴ���ʽ*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_SCFS, sBuf);
    pstrcopy( sdb_app_dwcpxy.scfs, sBuf, sizeof( sdb_app_dwcpxy.scfs ) );

	/* ���״̬*/
    pstrcopy( sdb_app_dwcpxy.shzt, "9", sizeof( sdb_app_dwcpxy.shzt ) );

	/* add by sunpj 2016-11-11 end*/

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* �Ǽǵ�λ��Ϣ  ��λ��Ϣ���ж��ظ� */
    sdb_app_dwxx.zt[0] = '0';

    iRet = DBInsert("app_dwxx", SD_APP_DWXX, NUMELE(SD_APP_DWXX), &sdb_app_dwxx, sErrmsg);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* �Ǽǵ�λ��ƷЭ����Ϣ */
    sdb_app_dwcpxy.qyzt[0] = '0';

    iRet = DBInsert("app_dwcpxy", SD_APP_DWCPXY, NUMELE(SD_APP_DWCPXY), &sdb_app_dwcpxy, sErrmsg);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if( DCICommit() != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ҵ���� */
    COMP_HARDSETXML( XMLNM_APP_RESP_YWBH, sdb_app_dwcpxy.ywbh  );
    /* ��λ��� */
    COMP_HARDSETXML( XMLNM_APP_RESP_DWBH, sdb_app_dwcpxy.dwbh  );
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}


/**********************************************************************
�������: SAPP_MODDWXY
�������: �޸ĵ�λЭ��
���������
���������
���������
����˵��: 
*************************************************************************/
IRESULT SAPP_ModDwxy(HXMLTREE lXmlhandle)
{
    int  i,iParas;
    int  iDwbh;
    char sYwbh[16+1];
    char sJybz[1+1];
    char sBuf[512+1];
    char sTmp[128+1];
    char sWhsj[14+1];
    int  iFlag = 0;     /* ��λ��ƷЭ���޸ı�־ */
    int  iFlag2 = 0;    /* ��λ��Ϣ�޸ı�־ */
    int iRet = -1;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);
                      
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")   
       
    /*����������*/
    COMP_PARACOUNTCHKMIN(3)

    memset( &sdb_app_dwcpxy, 0x00, sizeof( sdb_app_dwcpxy ) ) ;

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"ҵ����") 
    trim(sBuf);
    strncpy( sdb_app_dwcpxy.ywbh, sBuf, sizeof( sdb_app_dwcpxy.ywbh ) );
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"��λ���") 
    trim(sBuf);
    strncpy( sdb_app_dwcpxy.dwbh, sBuf, sizeof( sdb_app_dwcpxy.dwbh ) );
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"���ױ�־")   /* 1-ά��  2-��Լ */
    trim(sBuf);
    strncpy( sJybz, sBuf, sizeof( sJybz ) );

    /* ���׻�������Ա */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_JYJG  , sBuf);
    pstrcopy( sdb_app_dwcpxy.bljg, sBuf, sizeof( sdb_app_dwcpxy.bljg ) );

    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(  XMLNM_APP_REQ_JYGY, sBuf);
    pstrcopy( sdb_app_dwcpxy.blgy, sBuf, sizeof( sdb_app_dwcpxy.blgy ) );

    /* �������� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_ZWRQ, sBuf);
    pstrcopy( sdb_app_dwcpxy.blrq, sBuf, sizeof( sdb_app_dwcpxy.blrq ) );

    /* ά��ʱ�� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_SYSTIME, sBuf);
    snprintf( sWhsj, sizeof( sWhsj ), "%s%s", sdb_app_dwcpxy.blrq, sBuf );

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* ���°����Ա��Ϣ */
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( sSql2, 0x00, sizeof( sSql2 ) );
	/*modify by llh 20180704 ����ά����������Ա��ʱ��,���ǰ����������Ա��ʱ��*/
/*    sprintf( sSql, "UPDATE app_dwcpxy SET bljg='%s',blgy='%s',blrq='%s' ",\
        sdb_app_dwcpxy.bljg, sdb_app_dwcpxy.blgy,sdb_app_dwcpxy.blrq  );
*/
    sprintf( sSql, "UPDATE app_dwcpxy SET whjg='%s',whgy='%s',whsj='%s' ",\
        sdb_app_dwcpxy.bljg, sdb_app_dwcpxy.blgy,sWhsj );
	/*modify by llh 20180704 ����ά����������Ա��ʱ��,���ǰ����������Ա��ʱ��*/

    sprintf( sSql2, "UPDATE app_dwxx SET whjg='%s',whgy='%s',whsj='%s' ",\
        sdb_app_dwcpxy.bljg, sdb_app_dwcpxy.blgy,sWhsj );

    /* �޸ĵ�λ��ƷЭ����Ϣ */
    if( sJybz[0] == '2' ) /* ��Լ */
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, ", qyzt='1', shzt='9'" );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }
    else
    {
        /* �����˺� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DSZH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dszh='%s' " , sBuf );
            strcat( sSql, sTmp ) ;
            iFlag = 1;
        }
        
        /* �����˺����� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DSZHMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dszhmc='%s' " , sBuf );
            strcat( sSql, sTmp ) ;
            iFlag = 1;
        }
   
        /* �����˺� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DFZH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dfzh='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
        
        /* �����˺����� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DFZHMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dfzhmc='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
        
        /* ҵ������ */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_YWMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", ywmc='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
        
        /* ��Լ�������� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_HYJSRQ, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", hyjsrq='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
   
        /* �ڲ����ɻ� ������չ�ֶ�1 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_NBZH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", extfld1='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
        
        /* �Ƿ���ҪУ��ǩԼ��ϵ��������չ�ֶ�2 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_QYJY, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", extfld2='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

		/* add by sunpj 2016-11-11 beg*/
		        
	    /* �������� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_FWRX, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", fwrx='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* ��Ʒ���� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_CPDM, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", cpdm='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* �ɷѱ����ʾ���� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_JFBHXSMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", jfbhxsmc='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* �ڲ����˺����� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_NBHZHMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", nbhzhmc='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* �ڲ����˺� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_NBHZH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", nbhzh='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* �������ڲ����˺����� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_SXFNBHZHMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", sxfnbhzhmc='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* �������ڲ����˺� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_SXFNBHZH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", sxfnbhzh='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

		/* �ͻ��� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_KHH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", khh='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

		/* �ϴ���ʽ */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_SCFS, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", scfs='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

		if (1 == iFlag)
		{
			memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", shzt='%s' " , "9" );
            strcat( sSql, sTmp ); 
		}

		/* add by sunpj 2016-11-11 end*/
		
		/* add by llh 20181022 beg*/
		/* ��Լ��ʼ���� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_HYKSRQ, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", hyksrq='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
        /* Э���� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_XYBH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", xybh='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
		/* add by llh 20181022 end*/
        
        /*  �޸ĵ�λ��Ϣ */
        /*  ��λ���� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dwmc='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        /* ��λ��ϵ������ */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWLXR, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dwlxr='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        /* ��λ��ϵ�˵绰 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWLXRDH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dwlxrdh='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        /* ��λ��ϵ��ַ */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWDZ, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dwdz='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        /* ��λ��ϵemail*/
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWEMAIL, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dwemail='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        /* ��չ�ֶ�1 ����ڲ��ͻ��� */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_NBKHH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", extfld1='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        if( iFlag == 0 && iFlag2 == 0 )
        {
            LOG(LM_STD,Fmtmsg("û����Ϣ��Ҫ�޸�"),"INFO")  
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
            return COMPRET_SUCC;
        }
    }
   
    if( iFlag == 1 )  /* ���µ�λ��ƷЭ�� */
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, " WHERE ywbh='%s'", sdb_app_dwcpxy.ywbh );
        strcat( sSql, sTmp ) ;
        /* �ж��Ƿ񳬳�*/
        if( strlen( sSql ) > sizeof( sSql ) )
        {
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->sSql[%s]",sSql),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }

        iRet = DCIExecuteDirect( sSql );
        if ( iRet < 1 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s][%d][%s]",DCILastError(),iRet,sSql),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_UPD_KHQY,MSG_CUSTOM_UPD_KHQY);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
    }
    if( iFlag2 == 1 )  /* ���µ�λ��Ϣ */
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, " WHERE dwbh='%s'", sdb_app_dwcpxy.dwbh );
        strcat( sSql2, sTmp ) ;
        /* �ж��Ƿ񳬳�*/
        if( strlen( sSql2 ) > sizeof( sSql2 ) )
        {
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->sSql[%s]",sSql2),"ERROR");
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }

        iRet = DCIExecuteDirect( sSql2 );
        if ( iRet < 1 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s][%d][%s]",DCILastError(),iRet,sSql),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_UPD_KHQY,MSG_CUSTOM_UPD_KHQY);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
    } 

    if( DCICommit() != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError()),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}

/**********************************************************************
�������: SAPP_QryDWXY
�������: ��ѯ��λЭ��
���������
���������
���������
����˵��: 
*************************************************************************/
IRESULT SAPP_QryDwxy(HXMLTREE lXmlhandle)
{
    int  i,iParas;
    char sYwbh[16+1];
    char sBuf[512+1];
    char sTmp[128+1];
    int  iFlag = 0; 
    int  returnFlag = 0; 
    int  iCount =0;
    char sXmlNode[64+1];
    char sBaseNode[64+1];
    char sInnerOrg[27+1];
    char sJgbh1[16+1]={0};  /* �ϼ����� */
    char sJgbh2[16+1]={0};  /* ���ϼ����� */
    char sJgbh3[16+1]={0};  /* �����ϼ����� */ 
    char sJgbh4[16+1]={0};  /* �������ϼ����� */ 
    char sQryType[1+1];
    /* ��ѯ���� 1����Ȩ�� ��ѯ�������������ҵ��(Ĭ��) 2��ѯ���������������������ҵ�� 3 ��ѯ�ϼ�����ǩԼҵ�� */

    int iRet = -1;
    char sErrmsg[512];
    CURSOR cur;

    fpub_InitSoComp(lXmlhandle);
                      
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")   
       
    /*����������*/
    COMP_PARACOUNTCHKMIN(2)

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��ѯ��־")   /* 0-�б��ѯ 1-��ϸ��Ϣ��ѯ */
    trim(sBuf);
    returnFlag = atoi( sBuf ) ;

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"���ؽڵ���")   
    trim(sBuf);
    strncpy( sBaseNode, sBuf, sizeof( sBaseNode ) );

    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, "select a.*,b.*  from app_dwcpxy a, app_dwxx b  where a.dwbh=b.dwbh  " );

    memset( &sdb_app_dwcpxy, 0x00, sizeof( sdb_app_dwcpxy ) ) ;
    memset( &sdb_app_dwxx, 0x00, sizeof( sdb_app_dwxx ) ) ;

    iFlag = 0;
    memset(sBuf, 0, sizeof(sBuf));
    /* ҵ���� */
    COMP_SOFTGETXML( XMLNM_APP_REQ_YWBH, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.ywbh='%s' " , sBuf );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }

    /* ��Ʒ���� */
    COMP_SOFTGETXML( XMLNM_APP_REQ_CPDM, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.cpdm='%s' " , sBuf );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }

    /* ��ѯ��������Ա */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_QXJG  , sBuf);
    if( strlen( sBuf ) > 1 )
    {
        /* added by yangdong 20141103 ��ѯ�¼����� */
        memset( sQryType, 0x00, sizeof( sQryType) );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        COMP_SOFTGETXML( XMLNM_APP_REQ_QXLX, sTmp );
        pstrcopy( sQryType, sTmp, sizeof( sQryType ) );
        if( sQryType[0] == '2' ) /* �����ѯ�¼�����ǩԼ��ҵ�� */
        {
            /* ��ȡ�ڲ������� ���ݽ��׻�����ȡ */
            memset( sInnerOrg, 0x00, sizeof( sInnerOrg ) );
            COMP_SOFTGETXML( XMLNM_APP_JGXX_INNER_ORG_ID, sInnerOrg );

            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, "and a.bljg in ( select trim(org_id) from t_org where inner_org_id like '%s%%' )",  sInnerOrg );
            strcat( sSql, sTmp );
        }
        else if( sQryType[0] == '3' ) /* �����ѯ�ϼ�����ǩԼ��ҵ�� */
        {
            /* ��ȡ�ϼ����� ���ݽ��׻�����ȡ */
            memset( sJgbh1, 0x00, sizeof( sJgbh1 ) );
            memset( sJgbh2, 0x00, sizeof( sJgbh2 ) );
            memset( sJgbh3, 0x00, sizeof( sJgbh3 ) );
            memset( sJgbh4, 0x00, sizeof( sJgbh4 ) );
            COMP_SOFTGETXML( XMLNM_APP_JGXX_ORG_ID1, sJgbh1 );
            COMP_SOFTGETXML( XMLNM_APP_JGXX_ORG_ID2, sJgbh2 );
            COMP_SOFTGETXML( XMLNM_APP_JGXX_ORG_ID3, sJgbh3 );
            COMP_SOFTGETXML( XMLNM_APP_JGXX_ORG_ID4, sJgbh4 );

            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, "and a.bljg in ( '%s','%s','%s','%s','%s' )", sBuf, sJgbh1, sJgbh2, sJgbh3, sJgbh4 );
            strcat( sSql, sTmp );
        }
        else
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, "and a.bljg='%s'", sBuf );
            strcat( sSql, sTmp );
        }
        iFlag = 1;
    }

    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(  XMLNM_APP_REQ_QXGY, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.blgy='%s' " , sBuf );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }

    /* �����˺� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DSZH, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, " and a.dszh='%s' " , sBuf );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }

    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DSZHMC, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.dszhmc='%%%s%%' " , sBuf );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }

    /* �����˺� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DFZH, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.dfzh='%s' " , sBuf );
        strcat( sSql, sTmp ); 
        iFlag = 1;
    }

    /* �����˺����� */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DFZHMC, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.dfzhmc like '%%%s%%' " , sBuf );
        strcat( sSql, sTmp ); 
        iFlag = 1;
    }

    /* �ڲ����ɻ� ������չ�ֶ�1 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBZH, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.extfld1='%s' " , sBuf );
        strcat( sSql, sTmp ); 
        iFlag = 1;
    }

    /* �ڲ��ͻ��� ������չ�ֶ�1 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBKHH, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and b.extfld1='%s' " , sBuf );
        strcat( sSql, sTmp ); 
        iFlag = 1;
    }

    if( iFlag == 0 )
    {
        LOG(LM_STD,Fmtmsg("û�в�ѯ����"),"INFO")  
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }

    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError()),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sql[%s] err[%s]", sSql, DCILastError()),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
 
    memset( &sdb_app_dwcpxy, 0x00, sizeof( sdb_app_dwcpxy ) );
    memset( &sdb_app_dwxx, 0x00, sizeof( sdb_app_dwxx ) );
    iCount=0;
    while( ( iRet = DBFetch(cur, SD_APP_DW_CPXY, NUMELE(SD_APP_DW_CPXY), &sdb_app_dw_cpxy, sErrmsg ) ) > 0 )
    {
        iCount++;
        /*��ȡ�������ݽ��д���*/
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "%s/ywbh|%d/ywbh", sBaseNode, iCount );
        COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.ywbh );

        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "%s/ywbh|%d/ywmc", sBaseNode, iCount );
        COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.ywmc );
       
        if( returnFlag == 1 )  /* ������ϸ��Ϣ */
        {
            if( iCount > 100 ) /* ���ؼ�¼������100��ֱ������ѭ�� */
                continue;

            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwbh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwbh);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/xybh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.xybh);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dszh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dszh);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dszhmc", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dszhmc);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dfzh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dfzh);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dfzhmc", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dfzhmc);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/lxr", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.lxr);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/lxdh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.lxdh );
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/email", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.email );
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/hyksrq", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.hyksrq);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/hyjsrq", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.hyjsrq);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/bljg", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.bljg);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/blgy", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.blgy);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/sfbz", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.sfbz );
              
            /* �ڲ��˺� */ 
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/nbzh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.extfld1 );

            /* У���־ */ 
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/jybz", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.extfld2 );

            /* ��λ��Ϣ */
            /* ��λ���� */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwmc", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwmc);
    
            /* ��λ֤������ */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwzjlx", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwzjlx);
    
            /* ��λ֤������ */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwzjhm", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwzjhm);

            /* ��λ��ϵ�� */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwlxr", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwlxr);

            /* ��λ��ϵ�˵绰 */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwlxrdh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwlxrdh);

            /* ��λ��ַ */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwdz", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwdz);
        }
        memset( &sdb_app_dw_cpxy, 0x00, sizeof( sdb_app_dw_cpxy ) );
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError()),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);

    memset(sXmlNode,0,sizeof(sXmlNode));
    COMP_SOFTSETXML( XMLNM_APP_RESP_COUNT,itoa(iCount));

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}
