/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�����м�ҵ��ƽ̨��ĿV2.0)
��    ��:V4.1.0.1
ϵͳ����:
�ļ�����:APP_SXF.c
�ļ�����:������ģ��
�� Ŀ ��:
�� �� Ա:YangDong
��������:
��    ��:
�޸�����: 20110711
          �޸������Ѽ��㣬���ݿۼ���ʽ�������ѽ��еĴ���
          �޸���־��ӡģʽ
�޸�����: 20140918
          DCI����
*********************************************************************/
#include "gaps_head.h"
#include "../incl/app_head.h"

double min(double a,double b)
{
    return a <= b?a:b;
}

double max(double a,double b)
{
    return a >= b?a:b;
}

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
      <root>\
      <soname>APP_SXF.so</soname>\
      <sosrcname>APP_SXF.c</sosrcname>\
      <sonote>�����ѹ����������</sonote>\
      <version>\
      <rec ver=\"2.0.1.1\" modify=\"2010-4-1  15:08\" programer=\"YangDong\" filesize=\"1120946\">HS-AgentV2.0����</rec>\
      <rec ver=\"2.1.0.1\" modify=\"2011-11-01  9:28\" programer=\"S..C..\" filesize=\"1120946\">AgentV2.1����</rec>\
      <rec ver=\"4.1.0.1\" modify=\"2014-09-18  9:28\" programer=\"YangDong\" filesize=\"1120946\">DCI����</rec>\
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
/************************************************************************
��̬�����������
�����������:SApp_ChargeJrnl
�������:SApp_ChargeJrnl
�������:�����Ѽ�����ˮ
�������:
 ��� ��������  ��������       ��Դ���       ȱʡֵ            �ɿ�  ����˵��


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
�� �� Ա: YangDong
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_ChargeJrnl(HXMLTREE lXmlhandle)
{
    APP_SXFLS sdb_app_sxfls;   
    char sSql[255];
    int iRet = -1;
    char sErrmsg[512];

    int  iParas;
    char sBuf[255];

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    memset(&sdb_app_sxfls,0,sizeof(sdb_app_sxfls));

    /*ȡƽ̨����*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_PTRQ,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.ptrq,sBuf,sizeof(sdb_app_sxfls.ptrq));
    
    /*ȡƽ̨��ˮ��*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_PTLS,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.ptls,sBuf,sizeof(sdb_app_sxfls.ptls));
    
    /*ȡ���ʱ�ʶ*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_FLBS,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.flbs,sBuf,sizeof(sdb_app_sxfls.flbs ));
    
    /*ȡӦ�ñ�ʶ*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_YYBS,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.yybs,sBuf,sizeof(sdb_app_sxfls.yybs ));
    
    /*ȡ������ʶ*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_QDBS,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.qdbs,sBuf,sizeof(sdb_app_sxfls.qdbs ));
    
    /*ȡ��Ʒ����*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_CPDM,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.cpdm,sBuf,sizeof(sdb_app_sxfls.cpdm));
    
    /*ȡҵ����*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_YWBH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.ywbh,sBuf,sizeof(sdb_app_sxfls.ywbh));
    
    /*ȡ������ʶ*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JGBS,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jgbs,sBuf,sizeof(sdb_app_sxfls.jgbs));
    
    /*ȡ�ͻ�����*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_KHLX,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.khlx,sBuf,sizeof(sdb_app_sxfls.khlx));
    
    /*ȡ�ͻ����*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_KHBH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.khbh,sBuf,sizeof(sdb_app_sxfls.khbh));
    
    /*ȡ�ͻ���*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_YHH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.yhh,sBuf,sizeof(sdb_app_sxfls.yhh ));
    
    /*ȡ��λ���*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_DWBH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.dwbh,sBuf,sizeof(sdb_app_sxfls.dwbh));
    
    /*ȡԭ������ˮ��*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYLSH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jylsh,sBuf,sizeof(sdb_app_sxfls.jylsh));
    
    /*ȡ��������*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYRQ,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jyrq,sBuf,sizeof(sdb_app_sxfls.jyrq));
    
    /*ȡ���׻���*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYJG,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jyjg,sBuf,sizeof(sdb_app_sxfls.jyjg));
    
    /*ȡ���׹�Ա*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYGY,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jygy,sBuf,sizeof(sdb_app_sxfls.jygy));
    
    /*ȡ��������*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYLX,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jylx,sBuf,sizeof(sdb_app_sxfls.jylx));
    
    /*ȡ���׽��*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYJE,sBuf);
    trim(sBuf);
    sdb_app_sxfls.jyje = atof(sBuf);
    
    /*ȡ���ױ���*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYBS,sBuf);
    trim(sBuf);
    /* modified by yangdong 20090328
    ���ױ���Ĭ��Ϊһ��
    sdb_app_sxfls.jybs = atof(sBuf);
    */
    if( atoi( sBuf ) > 0 )
        sdb_app_sxfls.jybs = atoi(sBuf);
    else
        sdb_app_sxfls.jybs = 1;
    /* end */

    /*ȡ������*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SXF,sBuf);
    trim(sBuf);
    sdb_app_sxfls.sxfje = atof(sBuf);
    
    /*ȡ�շ���ˮ��*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SFLSH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.sfls,sBuf,sizeof(sdb_app_sxfls.sfls));
    
    /*ȡ�跽�ʺ�*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JFZH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jfzh,sBuf,sizeof(sdb_app_sxfls.jfzh));
    
    /*ȡ�����ʺ�*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_DFZH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.dfzh,sBuf,sizeof(sdb_app_sxfls.dfzh));
    
    /*ȡϵͳ�����־*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_XTNWBZ,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.xtnbz,sBuf,sizeof(sdb_app_sxfls.xtnbz));
    
    /* �շѹ�Ա*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SFJYGY,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.sfjygy,sBuf,sizeof( sdb_app_sxfls.sfjygy ) );
    
    /* �շѻ���*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SFJYJG,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.sfjyjg,sBuf,sizeof( sdb_app_sxfls.sfjyjg ) );
    
    /* �շ����� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SFRQ,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.sfrq,sBuf,sizeof( sdb_app_sxfls.sfrq ) );
    
    /* �շ�״̬*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SFZT,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.sfzt,sBuf,sizeof( sdb_app_sxfls.sfzt ) );

    /* �����ֶ�1*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_EXTFLD1,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.extfld1,sBuf,sizeof( sdb_app_sxfls.extfld1 ) );
    
    /* �����ֶ�2*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_EXTFLD2,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.extfld2,sBuf,sizeof( sdb_app_sxfls.extfld2 ) );

    /* ��ˮ״̬��ʼֵ 0 ���� */
    sdb_app_sxfls.lszt[0] = '0' ;

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
  
    iRet = DBInsert("app_sxfls", SD_APP_SXFLS, NUMELE(SD_APP_SXFLS), &sdb_app_sxfls, sErrmsg);
    if( iRet < 0)
    {   /*������ˮʧ��*/
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        LOGRET(-1, LM_STD, Fmtmsg("�����쳣���������ݿ����ʧ��[%s]", sErrmsg ),
        fpub_GetCompname(lXmlhandle))
    }

    if (DCICommit() != 0)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        LOGRET(-1, LM_STD, Fmtmsg("�����쳣���ύ����ʧ��[%s]", DCILastError()),
        fpub_GetCompname(lXmlhandle))
    }
  
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;  
}
/************************************************************************
��̬�����������
�����������:SApp_ChargeCal
�������:SApp_ChargeCal
�������:�����Ѽ���
�������:��(���������Ѽ��㽻�׽ӿ��ĵ���ֵ)

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

ʹ������:�����������������ѿ��Ʊ�Ŀ�����������/app/sxf/�ڵ��»�ȡ��
         ��������� jffs�����/app/sxf/jffs��ȡֵ��
�� Ŀ ��: 
�� �� Ա: YangDong
��������: 2009��6��21��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_ChargeCal(HXMLTREE lXmlhandle)
{
    /* ������Ϣ */
    char sCpdm[16+1];                           /*��Ʒ����*/
    char sQdbs[8+1];                            /*������ʶ*/
    char sJyje[17+1];                           /*���׽��*/
    double dJyje = 0.00;                        /*���׽��*/
    char sJybs[10+1];                           /*���ױ���*/
    int iJybs = 0;                              /*���ױ���*/
    char sJyrq[8+1];                            /*��������*/
    char sJsfs[1+1];                            /*���㷽ʽ*/                                      
    char sFlbs[32+1];                           /*���ʱ�ʶ*/
    char sKzsx[64];                             /*��������*/
    char sQss[16];                              /*��ʼ����*/
    char sJss[16];                              /*��������*/
    /* �����ѷ�����Ϣ */
    APP_SXFFL  sdb_app_sxffl;
    APP_CPSXFKZ  sdb_app_cpsxfkz;
    char sJslx[1+1];
    double dJscs = 0.00;                          /* ������� */
    double dKjcs = 0.00;                          /* �ۼ����� */
    /* ͨ�ÿ������� */
    char sCommon[16+1];
    int  iCommon = 0;

    char sErrmsg[512];
    char sSql[1024];
    char sBuf[255];
    char sCond[512];
    char sTmpCond[64];
    char sTmp[256];
	char sDftFlg[2];                             /* add by sunpj 2016-11-14 */
    int  iCount = 0;
    CURSOR cur;
    CURSOR cur2;
    int iRet = -1;

    double charge_amt = 0.00;                     /* ������   */
    double tmp_amt = 0.00;
    int    count = 0;
    
    fpub_InitSoComp(lXmlhandle);
  
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    /*ȡ��Ʒ����*/
    memset(sCpdm,0,sizeof(sCpdm));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_CPDM,sBuf);
    trim(sBuf);
    memcpy(sCpdm,sBuf,sizeof(sCpdm));

    /*ȡ���׽��*/
    memset(sJyje,0,sizeof(sJyje));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYJE,sBuf);
    trim(sBuf);
    memcpy(sJyje,sBuf,sizeof(sJyje) );
    dJyje=atof(sJyje);
    
    /*ȡ���ױ���*/
    memset(sJybs,0,sizeof(sJybs));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYBS,sBuf);
    trim(sBuf);
    memcpy(sJybs,sBuf,sizeof(sJybs) );
    iJybs = atoi( sJybs );

    /*ȡ��������*/
    memset(sJyrq,0,sizeof(sJyrq));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYRQ,sBuf);
    trim(sBuf);
    memcpy(sJyrq,sBuf,sizeof(sJyrq));

    /* ȡ���㷽ʽ */
    memset(sJsfs,0,sizeof(sJsfs));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JSFS,sBuf);
    trim(sBuf);
    memcpy(sJsfs,sBuf,sizeof(sJsfs) );

    /*ȡ���ʱ�ʶ*/
    memset(sFlbs,0,sizeof(sFlbs));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_FLBS,sBuf);
    trim(sBuf);
    memcpy(sFlbs,sBuf,sizeof(sFlbs));

    /* add by sunpj 2016-11-14 beg*/

	/*ȡĬ�ϱ�־*/
    memset(sDftFlg,0,sizeof(sDftFlg));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_MRBZ,sBuf);
    trim(sBuf);
    memcpy(sDftFlg,sBuf,sizeof(sDftFlg));

	/* add by sunpj 2016-11-14 end*/

    /* ����㷽ʽΪ1��ʾֱ�Ӱ�������ʱ�ʶ���� */
    if( sJsfs[0] == '1' && strlen( sFlbs ) > 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("������ʱ�ʶ=[%s]",sFlbs ),"INFO");
    }
    /* Ĭ�ϼ��㷽ʽΪ0���ѯ���ʿ��Ʊ�ȷ�����ʱ�ʶ */
    else
    {
        memset( sFlbs, 0x00, sizeof( sFlbs ) );
        memset( sSql, 0x00, sizeof( sSql ) );
        memset( sCond, 0x00, sizeof( sCond ) );
        /* ȡ��Ʒ�������� */
         
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_cpsxfkz \
            WHERE cpdm ='%s' ORDER BY xh ASC",sCpdm );
        if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        count = 0;

        while( 1 )
        {
            memset( sBuf, 0x00, sizeof( sBuf ) ) ;
            /* ��ȡ���������� */
            iRet = DBFetch(cur, SD_APP_CPSXFKZ, NUMELE(SD_APP_CPSXFKZ), &sdb_app_cpsxfkz, sErrmsg );
            if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIFreeCursor(cur);
                fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if( iRet == 0 )
                break;
            count ++;
            if( count > 10 ) /* ���10���������� */
            {
                DCIFreeCursor(cur);
                fpub_SetMsg( lXmlhandle, MID_CHARGE_CAL_KZSX_ERR, MSG_CHARGE_CAL_KZSX_ERR );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            /* ��ȡ��������ֵ */
			memcpy(sBuf, sdb_app_cpsxfkz.kzsx, sizeof(sdb_app_cpsxfkz.kzsx));/* add by sunpj 2016-11-14 */
            trim( sBuf );
            memset( sTmp, 0x00, sizeof( sTmp ) );
            /* 20110929 modiefied by yangdong */
            if( sBuf[0] != '/' )
                sprintf( sTmp, "/app/sxf/%s",sBuf ); 
            else
                sprintf( sTmp, "%s",sBuf ); 
            /* end of mod */
            trim( sTmp );
            COMP_SOFTGETXML( sTmp, sKzsx);   /* �����������δ�ӽ��״��룬Ϊ��ֵ */
            trim( sKzsx );

            /* �ж��Ƿ���ͨ������ALL */
            /* modified by yang dong 20111009 */
            if( iCommon == 0 )  /* ����ͨ�����������жϣ�����̨����ֻ��һ��ALL����  */
            {
                memset( sSql, 0x00, sizeof( sSql ) );
                memset( sTmp , 0x00, sizeof( sTmp ) );
                sprintf( sSql, "SELECT count(*) FROM app_cpsxfgx WHERE cpdm='%s'\
                    AND kztj%d='ALL' AND qyrq<='%s' AND sxrq >'%s'", \
                    sCpdm, count, sJyrq, sJyrq );
                iRet = DBSelectToVar(sErrmsg, &iCount, sSql);  
                if( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("sqlerr=[%s]", DCILastError() ),"ERROR");
                    DCIFreeCursor(cur);
                    fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            
                /*  �Ҳ��������ض����������ģ�ʹ��ͨ�ÿ������� ALL
                    ά�����ʿ��ƹ�ϵʱ��Ӧ�ÿ������ά��һ��ALL����
                    �����޷�׼ȷ��λ���� */
                 
                if( iCount >= 1)  /* ������������ALLͨ�����ԣ������������ֵ������ */
                {
                    if( iCommon > 0 )/* �Ѿ���һ��ͨ�ÿ������ԣ����� */
                    {
                        DCIFreeCursor(cur);
                        fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FLBS_COMMON,MSG_CHARGE_CAL_FLBS_COMMON );
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    memset( sCommon, 0x00, sizeof( sCommon ) );
                    strcpy( sCommon, sKzsx );  
                    iCommon = count;
                    /* 20111009 modified by yangdong 
                    break;
                    */
                    continue;
                }
            }
            if( count == 1 )
                sprintf( sCond, " AND kztj1='%s' ", sKzsx );
            else
            {
                memset( sTmpCond , 0x00, sizeof( sTmpCond ) );
                sprintf( sTmpCond, " AND kztj%d='%s' ", count, sKzsx);
                strcat( sCond, sTmpCond );
            }
            /* DCIFreeCursor(cur); */ /* delete by sunpj 2016-11-14 */
        }

        DCIFreeCursor(cur);

        if( iCommon > 0 ) /* ͨ�����Կ��ƴ���ֻ�������һ��ͨ������ */
        {
            memset( sSql, 0x00, sizeof( sSql ) );
            sprintf( sSql," SELECT count(*) FROM APP_CPSXFGX \
                WHERE cpdm='%s' %s AND kztj%d='%s'  AND qyrq <='%s' AND sxrq >'%s' ",\
                sCpdm, sCond, iCommon, sCommon, sJyrq, sJyrq );
            iRet = DBSelectToVar(sErrmsg, &iCount, sSql); 
            if( iRet <= 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                         Fmtmsg("sqlerr=[%s]", DCILastError()),"ERROR");
                fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            memset( sTmp, 0x00, sizeof( sTmp ) );
            if( iCount == 0 ) /* δ�ҵ���ȷƥ��ֵ����Ϊͨ������ALL */
            {
                 sprintf( sTmp, " AND kztj%d='ALL' ", iCommon );
                 strcat( sCond, sTmp );
            }
            else   /* ����ȷƥ��������� */
            {
                 sprintf( sTmp, " AND kztj%d='%s' ", iCommon,  sCommon );
                 strcat( sCond, sTmp );
            }
        }
        /* �����������Ʋ�ѯ���� */
        memset( sSql, 0x00, sizeof( sSql ) );
        sprintf( sSql," SELECT flbs FROM APP_CPSXFGX \
                           WHERE cpdm='%s' %s AND qyrq <='%s' AND sxrq >'%s' ", sCpdm, sCond,sJyrq, sJyrq );
		/* modify by sunpj 2016-11-14 */
        /* iRet = DBSelectToVarChar(sErrmsg, sFlbs, sSql1); */
		iRet = DBSelectToVarChar(sErrmsg, sFlbs, sSql);
        /*û�м�¼�������*/
        if( iRet == 0 )
        {
		    if (0 == strcmp(sDftFlg, "Y")) /* add by sunpj 2016-11-14 */
		    {
				/*ȡĬ�Ϸ���*/
				memset(sFlbs,0,sizeof(sFlbs));
				COMP_SOFTGETXML(XMLNM_APP_SXF_MRFL,sFlbs);
		    }
		    else
		    {
                fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FLBS_NOTFOUND ,MSG_CHARGE_CAL_FLBS_NOTFOUND );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
		    }
        }
        else if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("sqlerr=[%s]", DCILastError() ),"ERROR");
            fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    trim( sFlbs );
    /* ���ݷ��ʱ�ʶ����ѯ������Ϣ ,ֻȡ��һ����¼ */
    memset( sSql, 0x00, sizeof( sSql ) );
	/* modify by sunpj 2016-11-14 */
    /* snprintf( sSql, sizeof( sSql ), "SELECT * FROM APP_SXFFL WHERE flbs='%s' AND ROWNUM <= 1 ", sFlbs ); */
    snprintf( sSql, sizeof( sSql ), "SELECT * FROM APP_SXFFL WHERE flbs='%s' FETCH FIRST 1 ROWS ONLY ", sFlbs );   
    iRet = fprv_SelToStruct( sSql, SD_APP_SXFFL, NUMELE(SD_APP_SXFFL), &sdb_app_sxffl); 
    if( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FL_NOTFOUND ,MSG_CHARGE_CAL_FL_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    else if( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                      Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
        fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    dKjcs = sdb_app_sxffl.kjcs;
    if( sdb_app_sxffl.fdbz[0] == '0')  /* �̶����� */
    {
        dJscs = sdb_app_sxffl.jscs;
        
        if( sdb_app_sxffl.jslx[0] == '1') /*�����������Ϊ���*/
        {
            charge_amt = iJybs * dJscs;
        }
        else if( sdb_app_sxffl.jslx[0] == '2' )/*�����������Ϊ�ٷֱ�*/
        {
            if( sdb_app_sxffl.nwkbz[0] == '1')   /*�ۿʽΪ�ڿ�*/
            {
                tmp_amt = 0.00;
                tmp_amt = dJyje/( 1 + ( dJscs/100 ) );
                charge_amt = dJyje - tmp_amt;
            }
            else                  /* Ĭ����� */
            {
                charge_amt = dJyje * dJscs/100 ;
            }
        }
        else      /* ����������ʹ� */
        {
            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* delete by sc �ۼ�����ͳһ���洦����Ҫ����kjbz�������ж� */
        /*charge_amt =  charge_amt - dKjcs ;*/  /* ��ȥ�ۼ����� */
        /* delete end */
    }
    else if( sdb_app_sxffl.fdbz[0] == '1')    /* �������� */
    {
        if( sdb_app_sxffl.nwkbz[0] == '1' )  /* ��������ʱ�������ڿ� */
        {
            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FD1_ERR ,MSG_CHARGE_CAL_FD1_ERR  );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        dJscs = 0.00;
        /*dKjcs = 0.00;*/
      
        if(sdb_app_sxffl.ljbz[0] == '0')   /*���ۼ� */
        {
            if( sdb_app_sxffl.fdlx[0] == '2')   /* �����׽��� */
            {
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                if( sdb_app_sxffl.bhbz[0] == '1')   /*��������*/
                {
                    snprintf( sSql1, sizeof( sSql ), "SELECT jslx, jscs FROM app_sxffl \
                             WHERE flbs='%s' AND  %d >= qss AND %d < jss )",sFlbs, dJyje, dJyje );
                }
                else if(sdb_app_sxffl.bhbz[0] == '0')/*��������*/
                {
                    snprintf( sSql1, sizeof( sSql ), "SELECT jslx, jscs FROM app_sxffl \
                             WHERE flbs='%s' AND ( %f > qss AND %f <= jss )",sFlbs, dJyje, dJyje );
                }
                else   /* ������־�� */
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FDBH_ERR , MSG_CHARGE_CAL_FDBH_ERR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                iRet = DBSelectToMultiVar( sErrmsg, sSql1, sJslx, &dJscs ) ; 
                if( iRet == 0 )  /* δ�ҵ�������Ϣ */
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FL_NOTFOUND , MSG_CHARGE_CAL_FL_NOTFOUND  );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                else if( iRet == 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                 Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
                    fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }

                if( sJslx[0] == '1')  /* ��������Ϊ��� */
                    charge_amt = dJscs * iJybs;
                else if( sJslx[0] == '2')  /* ����Ϊ�ٷֱ� */            
                    charge_amt = dJscs * dJyje/100 ;
                else
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }

            else if( sdb_app_sxffl.fdlx[0] == '1')   /*�����ױ����� */
            {
                if( sdb_app_sxffl.bhbz[0] == '1')   /*��������*/
                {
                    snprintf( sSql1, sizeof( sSql1 ), "SELECT jslx, jscs FROM app_sxffl \
                             WHERE flbs='%s' AND ( %d >= qss AND %d < jss ) ", sFlbs, iJybs, iJybs );
                }
                else if(sdb_app_sxffl.bhbz[0] == '0')/*��������*/
                {
                    snprintf( sSql1, sizeof( sSql1 ), "SELECT jslx, jscs FROM app_sxffl \
                             WHERE flbs='%s' AND ( %d > qss AND %d <= jss ) ", sFlbs, iJybs, iJybs );
                }
                else /* ����������־�� */
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FDBH_ERR , MSG_CHARGE_CAL_FDBH_ERR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
         
                iRet = DBSelectToMultiVar( sErrmsg, sSql1, sJslx, &dJscs ) ; 
                if( iRet == 0 ) /* δ�ҵ�������Ϣ */
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FL_NOTFOUND , MSG_CHARGE_CAL_FL_NOTFOUND  );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                else if(iRet < 0)
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                 Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
                    fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }

                if( sJslx[0] == '1')  /*  �������Ϊ��� */
                    charge_amt = dJscs * iJybs;
                else if( sJslx[0] == '2')  /*  �������Ϊ�ٷֱ� */
                    charge_amt = dJscs * dJyje / 100 ;
                else /* ����������ʹ� */
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }
            else /* ֻ֧�ְ��������߱������� */
            {
                fpub_SetMsg(lXmlhandle, MID_CHARGE_CAL_FDTJ_ERR, MSG_CHARGE_CAL_FDTJ_ERR );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            /* �ۼ��ۼ����� */
            /* delete by sc �ۼ�����ͳһ���洦����Ҫ����kjbz�������ж� */
            /*charge_amt -= dKjcs ;*/
        }
        else if( sdb_app_sxffl.ljbz[0] == '1' )   /* �ۼ� */
        {
            /* ��ѯ���з��ʶ� ����ʼ������������ */
            snprintf( sSql1, sizeof( sSql1 ), " SELECT  * FROM app_sxffl\
                       WHERE flbs = '%s' ORDER by qss ASC ",sFlbs );
            if ((cur2 = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }
            if (DCIExecute(cur2) == -1)
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }

            if( sdb_app_sxffl.fdlx[0] == '2')   /* �����׽��� */
            {
                while( 1 )
                {
                    memset( sQss , 0x00, sizeof( sQss ) );
                    memset( sJss , 0x00, sizeof( sJss ) );
                    dJscs = 0.00;
                    /*dKjcs = 0.00;*/

                    iRet = DBFetch(cur2, SD_APP_SXFFL, NUMELE(SD_APP_SXFFL), &sdb_app_sxffl, sErrmsg );
                    if( iRet == 0 )
                    {
                        /* ��ʱӦ���н��ﵽ���õĽ����������ޣ��в��ֽ��׽��δ���������� */
                        break;
                    }
                    else if(iRet < 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                            Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
                        DCIFreeCursor(cur2);
                        fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    strcpy( sJslx, sdb_app_sxffl.jslx );
                    strcpy( sQss, sdb_app_sxffl.qss );
                    strcpy( sJss, sdb_app_sxffl.jss );
                    dJscs = sdb_app_sxffl.jscs ;

                    if( dJyje > atof( sJss ) )
                    { 
                        if( sJslx[0] == '2')  /* ����Ϊ�ٷֱ� */            
                        {
                            charge_amt += ( atof( sJss ) - atof( sQss ) ) *  dJscs / 100 ;
                        }
                        else    /* �������۽��ģ����������ױ������㣬����������Ϊ��� */
                        {
                            DCIFreeCursor(cur2);
                            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                            return COMPRET_FAIL;
                        }
                        /* delete by sc �ۼ�����ͳһ���洦����Ҫ����kjbz�������ж� */
                        /*charge_amt -= dKjcs;*/
                    }
                    else /*  ���׽��С�ڵ��ڽ����������˳�ѭ��,���һ�μ��� */
                    {
                        if( sJslx[0] == '2')  /* ����Ϊ�ٷֱ� */            
                        {
                            charge_amt += ( dJyje - atof( sQss ) ) *  dJscs / 100 ;
                        }
                        else    /* �������۽��ģ����������ױ������㣬����������Ϊ��� */
                        {
                            DCIFreeCursor(cur2);
                            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                            return COMPRET_FAIL;
                        }
                        /* delete by sc �ۼ�����ͳһ���洦����Ҫ����kjbz�������ж� */
                        /*charge_amt -= dKjcs;*/
                        break;  /* �������������ѭ�� */
                    }

                }
            }
            else if( sdb_app_sxffl.fdlx[0] == '1')   /*�����ױ������� */
            {
                while( 1 )
                {
                    memset( sQss , 0x00, sizeof( sQss ) );
                    memset( sJss , 0x00, sizeof( sJss ) );
                    dJscs = 0.00;
                    /*dKjcs = 0.00;*/
                    iRet = DBFetch(cur2, SD_APP_SXFFL, NUMELE(SD_APP_SXFFL), &sdb_app_sxffl, sErrmsg );
                    if( iRet == 0 )
                    {
                        /* ��ʱӦ���н��ﵽ���õĽ����������ޣ��в��ֽ��׽��δ���������� */
                        break;
                    }
                    else if(iRet < 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                               Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
                        DCIFreeCursor(cur2);
                        fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    strcpy( sJslx, sdb_app_sxffl.jslx );
                    strcpy( sQss, sdb_app_sxffl.qss );
                    strcpy( sJss, sdb_app_sxffl.jss );
                    dJscs = sdb_app_sxffl.jscs ;

                    if( iJybs > atoi( sJss ) )
                    { 
                        if( sJslx[0] == '1')       /* ��������Ϊ��� */
                        {
                            charge_amt += ( atoi( sJss ) - atoi( sQss ) ) * dJscs ;
                        }
                        else    /* �����ױ��������۽��ģ����������׽����㣬����������Ϊ�ٷֱ� */
                        {
                            DCIFreeCursor(cur2);
                            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                            return COMPRET_FAIL;
                        }
                        /* delete by sc �ۼ�����ͳһ���洦����Ҫ����kjbz�������ж� */
                        /*charge_amt -= dKjcs;*/
                    }
                    else
                    {
                        if( sJslx[0] == '1')       /* ��������Ϊ��� */
                        {
                            charge_amt += ( iJybs - atoi( sQss ) ) * dJscs ;
                        }
                        else    /* �����ױ��������۽��ģ����������׽����㣬����������Ϊ�ٷֱ� */
                        {
                            DCIFreeCursor(cur2);
                            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                            return COMPRET_FAIL;
                        }
                        /* delete by sc �ۼ�����ͳһ���洦����Ҫ����kjbz�������ж� */
                        /*charge_amt -= dKjcs;*/
                        break;  /* �������������ѭ�� */
                    }
                }
            }
           else
           {
               DCIFreeCursor(cur2);
               fpub_SetMsg(lXmlhandle, MID_CHARGE_CAL_LJBZ_ERR, MSG_CHARGE_CAL_LJBZ_ERR );
               fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
               return COMPRET_FAIL;
           }
           DCIFreeCursor(cur2);
       }
       else
       {
           fpub_SetMsg(lXmlhandle, MID_CHARGE_CAL_FDLX_ERR, MSG_CHARGE_CAL_FDLX_ERR );
           fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
           return COMPRET_FAIL;
       }
    }
      /* add by SC 20110607 �����ѿۼ����� */
      if( sdb_app_sxffl.kjbz[0] == '2' )/* �����ѿۼ�,2:�ٷֱ�,1:���,0:�� */
    {
        charge_amt = charge_amt * ( 1 -  dKjcs / 100 );
    }
    else if( sdb_app_sxffl.kjbz[0] == '1' )
    {
        charge_amt = charge_amt - dKjcs;
    }
      /* add by SC ---end */

    if(sdb_app_sxffl.sxxkz[0] == '0') /* �����޿��� */
    {
        /*  20090716 modified by yangdong �����޽���жϴ���
        charge_amt = max( sdb_app_sxffl.sxje, min( charge_amt, sdb_app_sxffl.xxje ) );
        */
        charge_amt = max( sdb_app_sxffl.xxje, min( charge_amt, sdb_app_sxffl.sxje ) );
    }
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("������=[%.2f]",charge_amt),"DEBUG");

    /* ��������д����ӦXML�ڵ� */
    memset(sTmp,0,sizeof(sTmp));
    sprintf(sTmp,"%.2f",charge_amt);
    COMP_HARDSETXML(XMLNM_APP_SXF_SXF,sTmp );

    /* �����ʱ�ʶд����ӦXML�ڵ� */
    COMP_HARDSETXML(XMLNM_APP_SXF_FLBS,sFlbs);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:SApp_ChargeReport
�������:SApp_ChargeReport
�������:�����ѻ������� 
�������:
 ��� ��������  ��������       ��Դ���       ȱʡֵ            �ɿ�  ����˵��
   1    int     pg_num                                           yes  ÿҳ���� 
   2    char    report_type                                      no   ��������


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
�� �� Ա: YangDong
��������:
�޸�����:2009��2��5��
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_ChargeReport(HXMLTREE lXmlhandle)
{
    APP_SXFLS sSxfls;
    char sQdbs[8+1];                            /*������ʶ*/
    char sCpdm[16+1];                            /*��Ʒ����*/
    char sJyjg[16+1];                           /*���׻���*/ 
    char sYybs[32+1];                           /*Ӧ�ñ�ʶ*/
    char sQsrq[8+1];                            /*��ʼ����*/
    char sJsrq[8+1];                            /*��������*/
    char sSql[1024];                            /**/
    int  iParas;
    char sFile[128];
    char sBuf[256];
    char sTmpBuf[256];
    int  iPage_num;
    int  iReport_type;
    int  iCount = 0;
    FILE * fp;
    char sErrmsg[512];
    int iRet = -1;
    CURSOR cur;
  
    fpub_InitSoComp(lXmlhandle);
  
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
    COMP_PARACOUNTCHKMIN(2)
    memset( sBuf,0,sizeof(sBuf) );
    COMP_GETPARSEPARAS(1,sBuf,"ÿҳ����")
    iPage_num = atoi( sBuf );
    if( iPage_num == 0 )
        iPage_num = 35;  /* Ĭ��35��ÿҳ */
    COMP_GETPARSEPARAS(2,sBuf, "��������");
    iReport_type = atoi( sBuf );

    memset( sFile, 0, sizeof( sFile ) );
    memset( sCpdm, 0, sizeof( sCpdm ) );
    memset( sJyjg, 0, sizeof( sJyjg ) );
    memset( sQdbs, 0, sizeof( sQdbs ) );
    memset( sYybs, 0, sizeof( sYybs ) );
    memset( sQsrq, 0, sizeof( sQsrq ) );
    memset( sJsrq, 0, sizeof( sJsrq ) );
    memset( sBuf, 0, sizeof( sBuf ) );
    memset( sTmpBuf, 0, sizeof( sTmpBuf ) );

    /* ��Ʒ���� */
    COMP_SOFTGETXML(XMLNM_APP_SXF_CPDM, sBuf);
    trim( sBuf );
    memcpy( sCpdm,  sBuf,  sizeof( sCpdm ) );
  
    /* ������ʶ */
    COMP_SOFTGETXML(XMLNM_APP_SXF_QDBS, sBuf);
    trim( sBuf );
    memcpy( sQdbs,  sBuf,  sizeof( sQdbs ) );
  
    /* ���׻��� */
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYJG, sBuf);
    trim( sBuf );
    memcpy( sJyjg,  sBuf,  sizeof( sJyjg ) );

    /* ��ʼ���� */
    COMP_SOFTGETXML(XMLNM_APP_SXF_QSRQ, sBuf);
    trim( sBuf );
    memcpy( sQsrq,  sBuf,  sizeof( sQsrq ) );
  
    /* �������� */
    COMP_SOFTGETXML(XMLNM_APP_SXF_JSRQ, sBuf);
    trim( sBuf );
    memcpy( sJsrq,  sBuf,  sizeof( sJsrq ) );

    memset( sSql, 0, sizeof(sSql) );
    if( iReport_type == 0 )  /* ��ϸ���� */
    {
        sprintf(sSql, " SELECT * FROM app_sxfls WHERE 1=1 " );
    }
    else{
        sprintf(sSql, " SELECT  cpdm, qdbs,jyjg, NVL(sum(jyje),0.00),NVL(sum(jybs),0),NVL(sum(sxfje),0.00 )  FROM app_sxfls WHERE 1=1 " );
    }
    if( strlen( sCpdm ) > 0 )
    {
         sprintf( sTmpBuf, "and cpdm='%s' ", sCpdm );
         strcat( sSql, sTmpBuf );
    }
    if( strlen( sQdbs ) > 0 )
    {
         sprintf( sTmpBuf, "and qdbs='%s' ", sQdbs );
         strcat( sSql, sTmpBuf );
    }
    if( strlen( sJyjg ) > 0 ) 
    {
        sprintf( sTmpBuf, "and jyjg='%s' ", sJyjg );
        strcat( sSql, sTmpBuf );
    }
    if( strlen( sQsrq ) > 0 )
    {
         sprintf( sTmpBuf, "and jyrq>='%s' ", sQsrq );
         strcat( sSql, sTmpBuf );
    }
    if( strlen( sJsrq ) > 0 )
    {
         sprintf( sTmpBuf, "and jyrq<='%s' ", sJsrq );
         strcat( sSql, sTmpBuf );
    }
   
    if( iReport_type == 0 )  /* ��ϸ���� */
    {
        strcat( sSql ," ORDER BY ptrq,cpdm,qdbs,jyjg " );
    }
    else if( iReport_type == 1 )  /* ͳ�Ʊ��� */
    {
         strcat(sSql, "  GROUP BY cpdm,qdbs,jyjg " );
    }
    else
    {
        fpub_SetMsg(lXmlhandle,MID_CHARGE_RPTTYPE_ERR,MSG_CHARGE_RPTTYPE_ERR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("sql str[%s]",sSql ),"DEBUG");
  
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    memset( sBuf, 0, sizeof( sBuf ) );
    COMP_SOFTGETXML("/pub/zhqzlsh",sBuf);
    snprintf( sFile,sizeof( sFile ),"%s/file/charge_report%s%s%s",getenv( "HOME" ), sCpdm,sJyjg,sBuf );
    if( ( fp = ( fopen( sFile,"w+" ) ) ) == NULL )
    {
        DCIFreeCursor(cur);
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg(" ���ļ�ʧ��,file[%s],error[%s]",sFile,strerror(errno)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("���ļ�ʧ��"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    fprintf( fp, "\n\n" );
    if( iReport_type == 0 )
    {
        fprintf( fp,"                                    ��������ϸ����   \n\n" );
        fprintf( fp," ��ֹ���� %8s - %8s                  \n", sQsrq, sJsrq ); 
        fprintf( fp,"��--------��--------��----------------��--------��----------------��--------��----------------��\n");
        fprintf( fp,"|��Ʒ����|������ʶ|    ���׻���    |��������|    ���׽��    |���ױ���|    ������      | \n");
    }
    else
    {
        fprintf( fp,"                                  ������ͳ�Ʊ���   \n" );
        fprintf( fp," ��ֹ���� %8s - %8s                  \n", sQsrq, sJsrq ); 
        fprintf( fp,"��--------��--------��----------------��----------------��--------��----------------��\n");
        fprintf( fp,"|��Ʒ����|������ʶ|   ���׻���     |   ���׽��     |���ױ���|   �����Ѻϼ�   |\n" );
    }
    

    while( 1 ) 
    {
        memset( &sSxfls, 0 , sizeof( sSxfls ) ); 
        if( iReport_type == 0 ){
            iRet = DBFetch(cur, SD_APP_SXFLS, NUMELE(SD_APP_SXFLS), &sSxfls, sErrmsg ); 
        }
        else{
            iRet = DBSelectToMultiVar( sErrmsg, sSql, sSxfls.cpdm, sSxfls.qdbs, sSxfls.jyjg, sSxfls.jyje, sSxfls.jybs, sSxfls.sxfje );
        }
        if( iRet < 0 )      
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
            fclose( fp );
            DCIFreeCursor(cur);
            fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if( iRet == 0 )
            break;
        if(  iCount != 0 &&( iCount % iPage_num ) == 0 ) /* ��ҳ���� */
        {
            if( iReport_type == 0 )
            {
                fprintf( fp,"��--------��--------��----------------��--------��----------------��--------��----------------�� \n " );
                fprintf( fp,"                                                                                                         �� %3d ҳ " , iCount/iPage_num );
                fprintf( fp,"\f" );
                fprintf( fp,"��--------��--------��----------------��--------��----------------��--------��----------------��\n");
                fprintf( fp,"|��Ʒ����|������ʶ|      ������ʶ  |��������|    ���׽��    |���ױ���|    ������      | \n");
            }
            else
            {
                fprintf( fp,"��--------��--------��----------------��----------------��--------��----------------�� \n  " );
                fprintf( fp,"                                                                                                         �� %3d ҳ " , iCount/iPage_num );
                fprintf( fp,"\f" );
                fprintf( fp,"��--------��--------��----------------��----------------��--------��----------------��\n");
                fprintf( fp,"|��Ʒ����|������ʶ|    ������ʶ    |   ���׽��     |���ױ���|   �����Ѻϼ�   |\n" );
            }
        }

        if( iReport_type == 0 )
        {
            fprintf( fp, "��--------��--------��----------------��--------��----------------��--------��----------------��\n");

            fprintf( fp, "|%8s|%8s|%16s|%8s|%16.2f|%8d|%16.2f|  \n",\
                 trim( sSxfls.cpdm ), trim( sSxfls.qdbs ), trim( sSxfls.jyjg ), \
                     trim( sSxfls.jyrq ), sSxfls.jyje, sSxfls.jybs, sSxfls.sxfje );
        }
        else
        {
            fprintf( fp, "��--------��--------��----------------��----------------��--------��----------------��\n");
            fprintf( fp, "|%8s|%8s|%16s|%16.2f|%8d|%16.2f|  \n",\
                 trim( sSxfls.cpdm ), trim( sSxfls.qdbs ), trim( sSxfls.jyjg ), \
                                        sSxfls.jyje,sSxfls.jybs, sSxfls.sxfje );
        }
        iCount ++;
    }
    if( iReport_type == 0 )
        fprintf( fp,"��--------��--------��----------------��--------��----------------��--------��----------------�� \n " );
    else
        fprintf( fp,"��--------��--------��----------------��----------------��--------��----------------�� \n  " );
    fprintf( fp,"                                                                  �� %3d ҳ  \n  " , iCount/iPage_num + 1 );
    fclose( fp );
    DCIFreeCursor(cur);

    /* ��������ļ��� */
    COMP_HARDSETXML(XMLNM_APP_SXF_BBWJMC, sFile );

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");
  
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return 0;
}
