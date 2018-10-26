/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.1)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:BAT_PUB.c
�ļ�����: �����������������
�� �� Ա:chensy YangDong
��������:2001-08-01

�� �� Ա:YangDong
�޸�����:20141018
�޸�˵��:DCI����
*********************************************************************/
#include "gaps_head.h"
#include "app_macro.h"
#include "app_xmlmacro.h"
#include "batch_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_PUB.so</soname>\
        <sosrcname>BAT_PUB.c</sosrcname>\
        <sonote>BATCHͨ���������</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"Chensy YangDong\" filesize=\"1438053\">HS-AgentV2.1����</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2012-7-1 15:08\" programer=\"YangDong\" filesize=\"1438053\">����</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1438053\">DCI����</rec>\
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
batchlong  lvr;

/************************************************************************
��̬�����������
�����������:SBATCH_REGFILE
�������:BATCH_REGFILE
�������: ����ҵ���ⲿ�ļ��Ǽ�
�������:
 ��� ��������  ��������   ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
 1   1-����   ¼�뷽ʽ     416-�����ַ���       Y   1������¼�룬2������¼�� 
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_REGFILE(HXMLTREE lXmlhandle)
{
    int  iParas;
    int  iRet=-1;
    char sErrmsg[512];
    char sSql1[1024];
    char sFlowId[51];
    char sBuf[255];
    char sJyfs[1+1];
    char sTjsj[8+1];
    char sTjrq[8+1];
    int  i = 0;
    int iPcCount=0;
    CURSOR cur;
    /*int  j = 0;*/
    BATCH_WBWJDJ sdb_batch_wbwjdj;

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    /*ָ�������ύʱ��ֻ����ҹ������*/
    memset(sTjrq, 0x00, sizeof(sTjrq));
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_DATE, sTjrq)
    memset(sTjsj, 0x00, sizeof(sTjsj));
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_TIME, sTjsj)
    if (sTjrq[0] != '\0' || sTjsj[0] != '\0')
    {
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sJyfs, 0x00, sizeof(sJyfs));
        COMP_SOFTGETXML("/app/cpxx/jyfs", sBuf)
        if ( sBuf[0] == '\0')
        {
            sBuf[0] = '2';/*2-����*/
        }
        sJyfs[0] = sBuf[0];
        LOG(LM_STD,Fmtmsg("�ύ����ʱ��[%s,%s],���׷�ʽ[%s]",
            sTjrq, sTjsj, sJyfs),fpub_GetCompname(lXmlhandle))
        if ( sJyfs[0] != '4'  && sJyfs[0] != '7')
        {/*ҹ������*/
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,MSG_BATCH_SJTJ_NIGHT,"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_SJTJ_NIGHT,MSG_BATCH_SJTJ_NIGHT );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    

    memset(&sdb_batch_wbwjdj,0,sizeof(sdb_batch_wbwjdj));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "%s", "INSERT INTO batch_wbwjdj (\
        djrq, djlsh, djsj, ywbh, djjg, djgy, shpch, pkrq, ptpch, lpwjlj, lpwjm, zbs,\
        zje, threadno, taskmode, pczt, shzt, note, extfld1, extfld2, extfld3)\
        VALUES( :v1, :v2, :v3, :v4, :v5, :v6, :v7, :V8, :v9, :v10, :v11, \
        :v12, :v13, :v14, :v15, :v16, :v17, :V18, :v19, :v20, :v21 ) ");

    if ( (cur = DCIDeclareCursor( sSql1, 0)) == -1)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("���ݿ����ʧ��[%s]",DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    i = 0;
    if (DCIBindPara(cur, 0, sdb_batch_wbwjdj.djrq,  sizeof( sdb_batch_wbwjdj.djrq ), DCIT_VARCHAR) != 0)
        i++;
    if (DCIBindPara(cur, 1, &sdb_batch_wbwjdj.djlsh,  sizeof( sdb_batch_wbwjdj.djlsh), DCIT_INTEGER ) != 0)
        i++;
    if (DCIBindPara(cur, 2, sdb_batch_wbwjdj.djsj,  sizeof( sdb_batch_wbwjdj.djsj), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 3, sdb_batch_wbwjdj.ywbh,  sizeof( sdb_batch_wbwjdj.ywbh), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 4, sdb_batch_wbwjdj.djjg,  sizeof( sdb_batch_wbwjdj.djjg), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 5, sdb_batch_wbwjdj.djgy,  sizeof( sdb_batch_wbwjdj.djgy), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 6, sdb_batch_wbwjdj.shpch,  sizeof( sdb_batch_wbwjdj.shpch), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 7, sdb_batch_wbwjdj.pkrq,  sizeof( sdb_batch_wbwjdj.pkrq), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 8, sdb_batch_wbwjdj.ptpch,  sizeof( sdb_batch_wbwjdj.ptpch), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 9, sdb_batch_wbwjdj.lpwjlj,  sizeof( sdb_batch_wbwjdj.lpwjlj), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 10, sdb_batch_wbwjdj.lpwjm,  sizeof( sdb_batch_wbwjdj.lpwjm), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 11, sdb_batch_wbwjdj.zbs,  sizeof( sdb_batch_wbwjdj.zbs), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 12, &sdb_batch_wbwjdj.zje,  sizeof( sdb_batch_wbwjdj.zje), DCIT_DOUBLE ) != 0)
        i++;
    if (DCIBindPara(cur, 13, &sdb_batch_wbwjdj.threadno,  sizeof( sdb_batch_wbwjdj.threadno), DCIT_INTEGER ) != 0)
        i++;
    if (DCIBindPara(cur, 14, sdb_batch_wbwjdj.taskmode,  sizeof( sdb_batch_wbwjdj.taskmode), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 15, sdb_batch_wbwjdj.pczt,  sizeof( sdb_batch_wbwjdj.pczt), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 16, sdb_batch_wbwjdj.shzt,  sizeof( sdb_batch_wbwjdj.shzt), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 17, sdb_batch_wbwjdj.note,  sizeof( sdb_batch_wbwjdj.note), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 18, sdb_batch_wbwjdj.extfld1,  sizeof( sdb_batch_wbwjdj.extfld1), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 19, sdb_batch_wbwjdj.extfld2,  sizeof( sdb_batch_wbwjdj.extfld2), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 20, sdb_batch_wbwjdj.extfld3,  sizeof( sdb_batch_wbwjdj.extfld3), DCIT_VARCHAR ) != 0)
        i++;

    if( i > 0 )
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("���ݿ����ʧ��[%s]",DCILastError()),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*��������(��Ʒ����)*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_ZWRQ,sBuf);
    if( 0 == sBuf[0] ) 
    {
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_DJRQ_NULL,MSG_BATCH_DJRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_batch_wbwjdj.djrq,sBuf,sizeof(sdb_batch_wbwjdj.djrq));
    COMP_SOFTSETXML( XMLNM_BATCH_WBWJDJ_DJRQ, sdb_batch_wbwjdj.djrq );

    /* �����ļ�·�� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_LOCALPATH,sBuf);
    pstrcopy(sdb_batch_wbwjdj.lpwjlj,sBuf,sizeof(sdb_batch_wbwjdj.lpwjlj));
    
    /* �����ļ��� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_LPWJM,sBuf);
    if( 0 == sBuf[0] )
    {
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_LPWJM_NULL,MSG_BATCH_LPWJM_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    } 
    pstrcopy(sdb_batch_wbwjdj.lpwjm,sBuf,sizeof(sdb_batch_wbwjdj.lpwjm));

    LOG(LM_STD,Fmtmsg("BATCH: �����ļ���[%s]",sdb_batch_wbwjdj.lpwjm),"INFO")

    /*����ģʽ*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_TASKMODE,sBuf);
    pstrcopy(sdb_batch_wbwjdj.shpch,sBuf,sizeof(sdb_batch_wbwjdj.shpch));
    /* ҵ���� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YWBH,sBuf);
    if( 0 == sBuf[0] ) 
    {
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBH_NULL,MSG_BATCH_YWBH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_batch_wbwjdj.ywbh,sBuf,sizeof(sdb_batch_wbwjdj.ywbh));
    /* added by yangdong 20120422 �����̻����κż�¼ */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_SHPCH,sBuf);
    pstrcopy(sdb_batch_wbwjdj.shpch,sBuf,sizeof(sdb_batch_wbwjdj.shpch));
    if (sdb_batch_wbwjdj.shpch[0] != '\0')
    {/*�̻����κŲ�Ϊ��ʱ�����*/
        memset(sSql1, 0x00, sizeof(sSql1));
        snprintf( sSql1, sizeof( sSql1 ), "SELECT count(*) FROM batch_wbwjdj \
            WHERE ywbh ='%s' AND shpch='%s' AND pczt <> 'X' AND pczt <> 'C'",\
            sdb_batch_wbwjdj.ywbh, sdb_batch_wbwjdj.shpch );
        memset(sBuf,0,sizeof(sBuf));
        iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
        if( iRet < 0 )
        {
            DCIFreeCursor(cur);
            LOG(LM_STD,Fmtmsg("BATCH: sqlerr[%s] shpch[%s]",\
                        DCILastError(), sdb_batch_wbwjdj.shpch ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        iPcCount=atoi( sBuf );
        if( iPcCount > 0 )
        {
            DCIFreeCursor(cur);
            LOG(LM_STD,Fmtmsg("BATCH: count[%d] lpwjm[%s]",\
                        iPcCount, sdb_batch_wbwjdj.lpwjm ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_SHPCH,MSG_BATCH_SHPCH);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    
    /* ������ͬ���ļ����֣�ʧ�ܱ����tamc�������� */
    /* �����ѳ�������ͬ�� 20120517 mod by yangdong */
    memset(sBuf,0,sizeof(sBuf));
    snprintf( sSql1, sizeof( sSql1 ), "SELECT count(*) FROM batch_wbwjdj \
        WHERE ywbh ='%s' AND lpwjm='%s' AND pczt <> 'X' AND pczt <> 'C'",\
        sdb_batch_wbwjdj.ywbh, sdb_batch_wbwjdj.lpwjm );

    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
    if( iRet < 0 )
    {
        DCIFreeCursor(cur);
        LOG(LM_STD,Fmtmsg("BATCH: sqlerr[%s] lpwjm[%s]",\
                    DCILastError(), sdb_batch_wbwjdj.lpwjm ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    iPcCount=atoi( sBuf );

    if( iPcCount > 0 )
    {
        DCIFreeCursor(cur);
        LOG(LM_STD,Fmtmsg("BATCH: count[%d] lpwjm[%s]",\
                    iPcCount, sdb_batch_wbwjdj.lpwjm ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SHPCH,MSG_BATCH_WJDJ_EXIST);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }             
    
    /* ��˱�־ 0����Ҫ����ⲿ�ļ���1������Ҫ����ⲿ�ļ� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_RUNCTRL_SHBZ,sBuf);
    if( '0' == sBuf[0] ) 
    {
        sdb_batch_wbwjdj.shzt[0] = WBWJDJ_SHZT_NO;
        sdb_batch_wbwjdj.shzt[1] = 0;
    }
    else   /* Ĭ�� 1 ������Ҫ����ⲿ�ļ� */
    {
        sdb_batch_wbwjdj.shzt[0] = WBWJDJ_SHZT_YES;
        sdb_batch_wbwjdj.shzt[1] = 0;
    }
    
    /* �Ǽǻ���(Ĭ���������) */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DJJG,sBuf);
    if( 0 == sBuf[0] ) 
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG,sBuf);
        if( 0 == sBuf[0] ) 
        {/*cpxx����������ҲΪ��*/
            fpub_SetMsg(lXmlhandle,MID_BATCH_JYJGNULL,MSG_BATCH_JYJGNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    pstrcopy(sdb_batch_wbwjdj.djjg,sBuf,sizeof(sdb_batch_wbwjdj.djjg));
    
    /* �Ǽǹ�Ա(Ĭ�������Ա) */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DJGY,sBuf);
    if( 0 == sBuf[0] ) 
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBGY,sBuf);
    }
    pstrcopy(sdb_batch_wbwjdj.djgy,sBuf,sizeof(sdb_batch_wbwjdj.djgy));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZBS,sBuf);
    if (sBuf[0] == '\0')
        sBuf[0] = '0';
    pstrcopy(sdb_batch_wbwjdj.zbs,sBuf,sizeof(sdb_batch_wbwjdj.zbs));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZJE,sBuf);
    sdb_batch_wbwjdj.zje=atof(sBuf);

    /*�ۺ�ǰ����ˮ��(��Ʒ��ˮ��)*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_ZHQZLSH,sBuf);
    if( 0 == sBuf[0] ) 
    {
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_DJLSH_NULL,MSG_BATCH_DJLSH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    COMP_SOFTSETXML( XMLNM_BATCH_WBWJDJ_DJLSH, sBuf);
    sdb_batch_wbwjdj.djlsh=atol(sBuf);
    
    /*ϵͳʱ��*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_SYSTIME,sBuf);
    pstrcopy(sdb_batch_wbwjdj.djsj,sBuf,sizeof(sdb_batch_wbwjdj.djsj));
    
    /*ƽ̨���κ� - �Ǽ�ʱΪ��*/
    pstrcopy(sdb_batch_wbwjdj.ptpch," ",sizeof(sdb_batch_wbwjdj.ptpch));
    
    /*�����ļ��� - �Ǽ�ʱΪ��*/

    /*����״̬ - �Ǽ�ʱΪ����*/
    sdb_batch_wbwjdj.pczt[0] = WBWJDJ_ZT_READY;
    sdb_batch_wbwjdj.pczt[1] = 0;
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_TASKMODE,sBuf);
    if( '\0' == sBuf[0] )
    {
        /* ����ʼģʽĬ��Ϊ�Զ� */
        sdb_batch_wbwjdj.taskmode[0] = '1';
    }
    else
    {
        sdb_batch_wbwjdj.taskmode[0] = sBuf[0];
    }
    
    sdb_batch_wbwjdj.threadno=1; /* Ĭ���߳���Ϊһ */
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_NOTE,sBuf);
    pstrcopy(sdb_batch_wbwjdj.note,sBuf,sizeof(sdb_batch_wbwjdj.note));
    
    /*��չ�ֶ�һ - */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD1,sBuf);
    pstrcopy(sdb_batch_wbwjdj.extfld1,sBuf,sizeof(sdb_batch_wbwjdj.extfld1));
    
    /*��չ�ֶζ� - */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD2,sBuf);
    pstrcopy(sdb_batch_wbwjdj.extfld2,sBuf,sizeof(sdb_batch_wbwjdj.extfld2));

    /*��չ�ֶ��� - */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD3,sBuf);
    pstrcopy(sdb_batch_wbwjdj.extfld3,sBuf,sizeof(sdb_batch_wbwjdj.extfld3));

    /*sql_BeginTrans(); ��DCIBegin���� 2015-1-7 by chenxm*/
    DCIBegin();

    iRet = DCIExecute(cur);
    if ( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("�Ǽ�ʧ��,sqlerr=[%s]",DCILastError()),"ERROR");
        DCIRollback();
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_INS_WBWJDJ,MSG_BATCH_INS_WBWJDJ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*if( sql_CommitTrans() !=MID_SYS_SUCC )*/
    if( DCICommit() != 0)
    {
        DCIFreeCursor(cur);
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:SBATCH_PRETRTMNTFILE
�������:BATCH_PRETRTMNTFILE
�������: ����ҵ���ⲿ�ļ���ϢԤ����
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_PRETRTMNTFILE(HXMLTREE lXmlhandle)
{
    int    iParas;
    int    iFlag=0;
    int i,iCount;
    char sBuf[255];
    char itemBuf[128];
    char calcBuf[20+1];
    char sFixBuf[54+1];
    char sLpwjm[128+1];
    char sPkey[40+1];
/* modified by yangdong 20150918 dci���죬����64λ
    long iSeqno=0;
*/
    int  iSeqno=0;

    char sEname[512+1];
    char sPczt[1+1];
    char sDjrq[8+1];
    int /*iCheckFlag=0,*/ret;
    char *pstr1,*pstr2;
    char sSql1[1024];
    char sErrmsg[512];
    int  iRet=-1;
    int iLen=0;
    int iDjlsh=0;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
      
    COMP_PARACOUNTCHKMIN(2)
  
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"�Ǽ�����")
    trim(sBuf);
    pstrcopy(sDjrq,sBuf,sizeof(sDjrq));
  
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"�Ǽ���ˮ")
    iDjlsh=atol(sBuf);
    
    /* modified by yangdong 20111202 */
    if( strlen( sDjrq ) == 8 )
    {
        /* ��ȡ�ⲿ�ļ���Ϣ --B*/
        snprintf( sSql1, sizeof( sSql1 ), "SELECT LPWJM, PCZT FROM BATCH_WBWJDJ\
            WHERE  djrq='%s' AND djlsh=%d",sDjrq, iDjlsh );
        iRet = DBSelectToMultiVar( sErrmsg, sSql1, sLpwjm, sPczt ) ;
        if ( iRet < 0 )  
        {
            LOG(LM_STD,Fmtmsg("BATCH: ��ȡ�ⲿ�ļ���Ϣ����,[%s],[%d],sqlerr[%s]",sDjrq,iDjlsh,DCILastError()),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WBWJDJ,MSG_BATCH_SEL_WBWJDJ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }  
    
        /* У��״̬ */
        switch(sPczt[0])
        {
            case WBWJDJ_ZT_PRE: /* �����ϴ� */
                 iFlag=-1;
                 fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_PRE,MSG_BATCH_WBWJDJ_PRE);
                 break;
            case WBWJDJ_ZT_READY: /* ���� */
                 iFlag=0;
                 break;
            case WBWJDJ_ZT_RUNNING: /* ���ڴ��� */
                 iFlag=1;
                 fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_RUNNING,MSG_BATCH_WBWJDJ_RUNNING);
                 break;
            case WBWJDJ_ZT_SUCC: /* �ѷ��� */
                 iFlag=1;
                 fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_SUCC,MSG_BATCH_WBWJDJ_SUCC);
                 break;
            case WBWJDJ_ZT_CX:  /* �ѳ��� */
                 iFlag=1;
                 fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_CX,MSG_BATCH_WBWJDJ_CX);
                 break;
            default:  /* ���� */
                 iFlag=-1;
                 fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_UNKNOWN,\
                             Fmtmsg(MSG_BATCH_WBWJDJ_UNKNOWN, sPczt ));
                 break;
        }
        /* �ļ�״̬���� */
        if ( iFlag )
        {
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    else
    {
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_LPWJM,sBuf);
        pstrcopy( sLpwjm,sBuf,sizeof( sLpwjm));
    }

    LOG(LM_DEBUG,Fmtmsg("BATCH: �����ļ����ƽ���,[%s]=>",sLpwjm),"DEBUG")

    /* �Ƚ���XML���� */
    if(xml_ParseXMLString(lXmlhandle,sLpwjm,sizeof(sLpwjm))==FAIL)
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,\
            Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* �������� */
    iCount=fprv_getDelimitCount(sLpwjm, "{SN(");
    for(i=0; i<iCount; i++)
    {
        /* ��ȡKEY
        strncpy(sEname,sLpwjm,sizeof(sEname)-1);
        memset(itemBuf, 0, sizeof(itemBuf));
        fprv_getSubStr(sEname,    1, "{SN(", itemBuf);
        memset(sPkey, 0, sizeof(sPkey));
        fprv_getSubStr(itemBuf, 0, ")}", sPkey);
        memset(sFixBuf, 0, sizeof(sFixBuf));
        snprintf(sFixBuf, sizeof( sFixBuf ),"{SN(%s)}",sPkey );
        */
        strncpy(sEname,sLpwjm,sizeof(sEname)-1);
        pstr1 = strstr(sEname,"{SN(");
        if ( !pstr1 )
            continue;
        pstr2 = strstr( pstr1,")}");
        if ( !pstr2 )
            continue;
        iLen = strlen(pstr1) - strlen(pstr2) -4 ;
        memset(sPkey, 0x00, sizeof(sPkey));
        memcpy(sPkey,pstr1+4,iLen);
        memset(sFixBuf, 0, sizeof(sFixBuf));
        snprintf(sFixBuf, sizeof( sFixBuf ),"{SN(%s)}",sPkey );
        LOG(LM_DEBUG,Fmtmsg("BATCH: �����ļ����ƽ���,[%d][%s]=>[%s]",
            i, sLpwjm, sPkey),"DEBUG")
        /* �������� */
        fprv_getSeqno(sPkey, &iSeqno);
        memset(calcBuf, 0, sizeof(calcBuf));
        snprintf(calcBuf, sizeof( calcBuf ), "%d", iSeqno);
        StrReplace(sLpwjm, sFixBuf, calcBuf);
    }
    LOG(LM_DEBUG,Fmtmsg("BATCH: ���������ļ������[%s]",sLpwjm),"DEBUG")
    COMP_SOFTSETXML( XMLNM_BATCH_REQ_LPWJM,sLpwjm );             

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_BREAK_RECOVER
�������:    BATCH_BREAK_RECOVER
�������: �ϵ����ݻָ�
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
  1   1-����    ��������      416XML�����ַ���  *      N    
  2   2-����    ƽ̨���κ�    416XML�����ַ���  *      N   
ʹ������:
       ���ñ����֮ǰ����Ҫ����/batch�ڵ�����Ҫ�������Ϣ��ԭ����/batch
�ṹ�ᱻ��������ݸ���
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_BREAK_RECOVER(HXMLTREE lXmlhandle)
{
    char sBuf[128];
    int  iParas;
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sSql1[1024];
    int  iRet=-1;
    CURSOR cur;
    BATCH_WBWJDJ sdb_batch_wbwjdj;
    BATCH_PLRW   sdb_batch_plrw;

    COMP_PARACOUNTCHKMIN(2)
    memset(sBuf,0,sizeof(sBuf));
    memset(sPkrq,0,sizeof(sPkrq));
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    trim(sBuf);
    /* added by yangdong 20151125 ���ӷǿ��ж� */
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_GETPARSEPARAS(2,sBuf,"ƽ̨���κ�")
    trim(sBuf);
    /* added by yangdong 20151125 ���ӷǿ��ж� */
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEUBG")

    /* ��ȡ�ⲿ�ļ���Ϣ --B*/
    memset(&sdb_batch_wbwjdj,0,sizeof(BATCH_WBWJDJ));
    memset(&lvr,0,sizeof(lvr));

    /*
    snprintf( sSql1, sizeof( sSql1 ), "SELECT PCZT, breakdata, SHZT FROM BATCH_WBWJDJ\
    */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT breakdata FROM BATCH_WBWJDJ\
        WHERE pkrq = '%s' AND ptpch = '%s'", sPkrq, sPtpch );
    if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("���ݿ����ʧ��[%s]",DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("���ݿ����ʧ��[%s]",DCILastError()),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    iRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0);
    /* modified by yangdong 20151125 �����ж��Ƿ񷵻����ݣ�����Ϊ�յ�ʱ����һ�δ����coredump 
    if( iRet == -1 )
    */
    if( iRet == -1 || iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: ��ȡ�ⲿ�ļ���Ϣʧ��,pkrq[%s]ptpch[%s],sql[%s],\
                           SQLERR=[%s] [%d]", sPkrq, sPtpch, sSql1, DCILastError(), iRet ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WBWJDJ,MSG_BATCH_SEL_WBWJDJ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

/*
    strncpy( sdb_batch_wbwjdj.pczt, DCIFieldAsString(cur, 0 ), sizeof( sdb_batch_wbwjdj.pczt ) );
    lvr.length = DCIFieldAsBlob(cur, 1, lvr.data, BATCH_MAX_XML );
    strncpy( sdb_batch_wbwjdj.shzt, DCIFieldAsString(cur, 2 ), sizeof( sdb_batch_wbwjdj.shzt ) );
*/

    lvr.length = DCIFieldAsBlob(cur, 0, lvr.data, BATCH_MAX_XML );

    DCIFreeCursor(cur);

    LOG(LM_DEBUG,Fmtmsg("BATCH: ��ȡ�ⲿ�ļ���Ϣ[%d][%s]",lvr.length, lvr.data ),"INFO");

    if( lvr.length <= 0  )        
    {
        LOG(LM_STD,Fmtmsg("BATCH: ��ȡ�ⲿ�ļ���Ϣʧ��,plrwkdy=[%s%s]bufsize[%d][%s]pczt[%s]shzt[%s]",\
               sPkrq,sPtpch, lvr.length, lvr.data ,sdb_batch_wbwjdj.pczt, sdb_batch_wbwjdj.shzt),"ERROR");
        /* 20110710 ��������Ӧ�룬����δ�Ǽ�buf
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WBWJDJ,MSG_BATCH_SEL_WBWJDJ);
        */
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }                

    /* �ϵ����ݻָ� */

    /* ֱ��ɾ��/batch�ڵ�������ֵ */
    if( xml_DelElement ( lXmlhandle, XMLNM_BATCH ) == -1 )
    {
        LOG(LM_STD,Fmtmsg("ɾ��batch�ڵ�ʧ��"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_XMLIMPORT,\
                   Fmtmsg(MSG_BATCH_XMLIMPORT,GETXMLERR));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* �ָ�����Ľڵ���Ϣ */
    lvr.data[lvr.length] = '\0';
    if (xml_ImportXMLString(lXmlhandle, lvr.data, "/", 0 ) == -1)
    {
        LOG(LM_STD,Fmtmsg("�ָ����뱣��ڵ���Ϣʧ��"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_XMLIMPORT,\
                    Fmtmsg(MSG_BATCH_XMLIMPORT,GETXMLERR));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    DCIFreeCursor(cur);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_GETINFO
�������:BATCH_GETINFO
�������: ����ҵ���ȡҵ����Ϣ
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
  1   1-����    ҵ����      416XML�����ַ���  *      N    
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_GETINFO(HXMLTREE lXmlhandle)
{
    int    iParas;
    char sBuf[255];
    char sCpdm[16+1];
    char sSql1[1024];
    char sErrmsg[512];
    int iRet=-1;
    BATCH_RUNCTRL sdb_batch_runctrl;
    BATCH_MAPINFO sdb_batch_mapinfo_zj;
    BATCH_MAPINFO sdb_batch_mapinfo_ww;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1)
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sCpdm,0,sizeof(sCpdm));
    COMP_GETPARSEPARAS(1,sBuf,"������Ʒ����")
    trim(sBuf);
    if( 0 == sBuf[0] )
    { 
            /* by yr 20121023 ���ش��� */
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBH_NULL,MSG_BATCH_YWBH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;      
    }
    pstrcopy(sCpdm,sBuf,sizeof(sCpdm));
    trim(sCpdm);

    LOG(LM_DEBUG,Fmtmsg("��Ʒ����[%s]",sCpdm),"DEBUG")
    
    /* ��ȡ���п��Ʋ��� */
    memset(&sdb_batch_runctrl, 0, sizeof(BATCH_RUNCTRL));
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM batch_runctrl WHERE cpdm='%s'", sCpdm );
    iRet = fprv_SelToStruct( sSql1, SD_BATCH_RUNCTRL, NUMELE(SD_BATCH_RUNCTRL), &sdb_batch_runctrl);
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_RUNCTR,MSG_BATCH_SEL_RUNCTR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    trim(sdb_batch_runctrl.cpdm);
    trim(sdb_batch_runctrl.flowid);
    trim(sdb_batch_runctrl.maxtask);
    trim(sdb_batch_runctrl.maxthread);
    trim(sdb_batch_runctrl.zjysbs);
    trim(sdb_batch_runctrl.wwysbs);
    trim(sdb_batch_runctrl.shbz);
    trim(sdb_batch_runctrl.taskmode);
    trim(sdb_batch_runctrl.taskpri);
    trim(sdb_batch_runctrl.extfld1);
    
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_CPDM,     sdb_batch_runctrl.cpdm)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_FLOWID, sdb_batch_runctrl.flowid)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_MAXTASK,    sdb_batch_runctrl.maxtask)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_MAXTHREAD,sdb_batch_runctrl.maxthread)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_ZJYSBS,     sdb_batch_runctrl.zjysbs)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_WWYSBS,     sdb_batch_runctrl.wwysbs)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_SHBZ ,sdb_batch_runctrl.shbz)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_TASKMODE, sdb_batch_runctrl.taskmode)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_TASKPRI, sdb_batch_runctrl.taskpri)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_EXTFLD1,sdb_batch_runctrl.extfld1)
    
    /* ��ȡ����ҵ������ӳ����Ϣ */
    if( strlen( sdb_batch_runctrl.zjysbs ) > 1 )
    {
        memset(&sdb_batch_mapinfo_zj, 0, sizeof(sdb_batch_mapinfo_zj));

        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM BATCH_MAPINFO WHERE mapid='%s' AND maptype = '1'", sdb_batch_runctrl.zjysbs );
        iRet = fprv_SelToStruct( sSql1, SD_BATCH_MAPINFO, NUMELE(SD_BATCH_MAPINFO), &sdb_batch_mapinfo_zj );
        if( iRet <= 0 )
        {
            LOG(LM_STD,Fmtmsg("�����ļ�ӳ���ʶ[%s]δ�ҵ�", sdb_batch_runctrl.zjysbs ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_MAPINFO,MSG_BATCH_SEL_MAPINFO);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        trim(sdb_batch_mapinfo_zj.mapid);
        trim(sdb_batch_mapinfo_zj.ywbm);
        trim(sdb_batch_mapinfo_zj.tjwjbs);
        trim(sdb_batch_mapinfo_zj.thwjbs);
        trim(sdb_batch_mapinfo_zj.zhbz);
        trim(sdb_batch_mapinfo_zj.zhbs);
        
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_MAPID     ,sdb_batch_mapinfo_zj.mapid)
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_YWBM      ,sdb_batch_mapinfo_zj.ywbm)
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_TJWJBS    ,sdb_batch_mapinfo_zj.tjwjbs)
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_THWJBS    ,sdb_batch_mapinfo_zj.thwjbs)
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_JLSXZ     ,itoa( sdb_batch_mapinfo_zj.jlsxz) );
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_ZHBZ      ,sdb_batch_mapinfo_zj.zhbz)
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_ZHBS      ,sdb_batch_mapinfo_zj.zhbs)
    }

    /* ��ȡ����ҵ����Χӳ����Ϣ */
    if( strlen( sdb_batch_runctrl.wwysbs ) > 1 )
    {
        memset(&sdb_batch_mapinfo_ww, 0, sizeof(sdb_batch_mapinfo_ww));
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM BATCH_MAPINFO WHERE mapid='%s' AND maptype = '0'", sdb_batch_runctrl.wwysbs );
        iRet = fprv_SelToStruct( sSql1, SD_BATCH_MAPINFO, NUMELE(SD_BATCH_MAPINFO), &sdb_batch_mapinfo_ww );
        if( iRet <= 0 )
        {
            LOG(LM_STD,Fmtmsg("��Χ�ļ�ӳ���ʶ[%s]δ�ҵ�", sdb_batch_runctrl.wwysbs ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_MAPINFO,MSG_BATCH_SEL_MAPINFO);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        trim(sdb_batch_mapinfo_ww.mapid);
        trim(sdb_batch_mapinfo_ww.ywbm);
        trim(sdb_batch_mapinfo_ww.lpwjbs);
        trim(sdb_batch_mapinfo_ww.hpwjbs);
        trim(sdb_batch_mapinfo_ww.zhbz);
        trim(sdb_batch_mapinfo_ww.zhbs);
        
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_MAPID     ,sdb_batch_mapinfo_ww.mapid)
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_YWBM      ,sdb_batch_mapinfo_ww.ywbm);
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_LPWJBS    ,sdb_batch_mapinfo_ww.lpwjbs)
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_HPWJBS    ,sdb_batch_mapinfo_ww.hpwjbs)
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_ZHBZ      ,sdb_batch_mapinfo_ww.zhbz)
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_ZHBS      ,sdb_batch_mapinfo_ww.zhbs)
    }

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_INS_PLRW
�������:BATCH_INS_PLRW
�������: ����ҵ��������Ϣ�Ǽ�
�������:
 ��� ��������    ��������                 ��Դ���         ȱʡֵ    �ɿ�    ����˵��        
    
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_INS_PLRW(HXMLTREE lXmlhandle)
{
    char sBuf[255];
    char sClrq[8+1];
    char sBusiMon[32+1];
    char sPlrwKey[24+1];
    char sErrmsg[512];
    int iRet=-1;
    int    iParas;
/* modified by yangdong 20150918 dci���죬����64λ
    long iseqno=0;
*/
    int iseqno=0;

    BATCH_PLRW sdb_batch_plrw;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")

    memset(&sdb_batch_plrw,0,sizeof(sdb_batch_plrw));
    
    /* ҵ���� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YWBH,sBuf);
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBH_NULL,MSG_BATCH_YWBH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_batch_plrw.ywbh,sBuf,sizeof(sdb_batch_plrw.ywbh));
    
    /*��������(��Ʒ����)*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf);
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_batch_plrw.pkrq,sBuf,sizeof(sdb_batch_plrw.pkrq));
    /*ȡƽ̨���κ�*/
    if( fprv_getSeqno2(BATCH_PTPCH_XLJZ, &iseqno) < 0)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    sprintf(sdb_batch_plrw.ptpch,"%ld",iseqno);
    trim(sdb_batch_plrw.ptpch);
    COMP_SOFTSETXML(XMLNM_BATCH_PTPCH,sdb_batch_plrw.ptpch);

    memset(sPlrwKey, 0x00, sizeof(sPlrwKey));
    snprintf(sPlrwKey, sizeof(sPlrwKey), "%s%s", sdb_batch_plrw.pkrq,sdb_batch_plrw.ptpch);
    COMP_SOFTSETXML(XMLNM_BATCH_PLRWKEY, sPlrwKey);
    /* �������ȼ� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_TASKPRI,sBuf);
    if (sBuf[0] == '\0')
    {/*�ӿ������ȼ�Ϊ�գ���ȡ���п��Ʊ��е����ȼ�*/
        COMP_SOFTGETXML(XMLNM_BATCH_RUNCTRL_TASKPRI,sBuf);
        if (sBuf[0] == '\0')
        {
            sBuf[0] = '0';/*�ͼ�*/
        }
    }
    pstrcopy(sdb_batch_plrw.taskpri,sBuf,sizeof(sdb_batch_plrw.taskpri));
    COMP_SOFTSETXML(XMLNM_BATCH_TASKPRI, sdb_batch_plrw.taskpri)
        
    /*�̻����κ�(�ⲿ�ļ��Ǽǻ�ȡ)*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_SHPCH,sBuf);
    pstrcopy(sdb_batch_plrw.shpch,sBuf,sizeof(sdb_batch_plrw.shpch));

    /*��λ���*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_DWCPXY_DWBH,sBuf);
    pstrcopy(sdb_batch_plrw.dwbh,sBuf,sizeof(sdb_batch_plrw.dwbh));

    /*�ύ����*/
    sprintf(sdb_batch_plrw.tjrq,"%s",GetSysDate());
    /*�ύʱ��*/
    sprintf(sdb_batch_plrw.tjsj,"%s",GetSysTime()); 
    /*��������*/
    pstrcopy(sdb_batch_plrw.clrq," ",sizeof(sdb_batch_plrw.clrq));
    memset( sClrq, 0x00, sizeof( sClrq ) );
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_DATE,sBuf);
    pstrcopy(sClrq,sBuf,sizeof(sClrq));
    if( strlen( sClrq ) < 4 )  /* ���δ����Ϸ��������ڣ�Ĭ��ȡ��ǰ���� */
    {
        pstrcopy(sdb_batch_plrw.clrq,sdb_batch_plrw.pkrq, sizeof(sdb_batch_plrw.clrq));
    }
    else
    {
        pstrcopy(sdb_batch_plrw.clrq, sClrq, sizeof(sdb_batch_plrw.clrq));
    }
    /*����ʱ��*/
    pstrcopy(sdb_batch_plrw.clsj," ",sizeof(sdb_batch_plrw.clsj));
    /*�ܽ��*/
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZJE,sBuf);
    sdb_batch_plrw.zje = atof(sBuf);
    /*�ܱ���*/
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZBS,sBuf);
    sdb_batch_plrw.zbs = atoi (sBuf);
    /*ʵ���ܽ��*/
    sdb_batch_plrw.sjzje = 0.00;
    /*ʵ���ܱ���*/
    sdb_batch_plrw.sjzbs = 0;
    /*�ɹ��ܽ��*/
    sdb_batch_plrw.cgzje = 0.00;
    /*�ɹ��ܱ���*/
    sdb_batch_plrw.cgzbs = 0;
    /*ʧ���ܽ��*/
    sdb_batch_plrw.sbzje = 0.00;
    /*ʧ���ܱ���*/
    sdb_batch_plrw.sbzbs = 0;
    /*�����ѽ��*/
    sdb_batch_plrw.sxfje = 0.00;
    /*�¿�������*/
    sdb_batch_plrw.xkhbs = 0;
    /*�¿������*/
    sdb_batch_plrw.xkhje = 0.00;
    /*�̻������ļ���*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_LPWJM,sBuf);
    pstrcopy(sdb_batch_plrw.lpwjm,sBuf,sizeof(sdb_batch_plrw.lpwjm));
    /*�ϴ������ļ���*/
    pstrcopy(sdb_batch_plrw.sczjwjm," ",sizeof(sdb_batch_plrw.sczjwjm));
    /*�����ظ��ļ���*/
    pstrcopy(sdb_batch_plrw.zjhfwjm," ",sizeof(sdb_batch_plrw.zjhfwjm));

    /*�ظ��̻��ɹ��ļ���*/
    pstrcopy(sdb_batch_plrw.shcgwjm," ",sizeof(sdb_batch_plrw.shsbwjm));
    /*�ظ��̻�ʧ���ļ���*/
    pstrcopy(sdb_batch_plrw.shsbwjm," ",sizeof(sdb_batch_plrw.shsbwjm));
    /*��������*/
    pstrcopy(sdb_batch_plrw.dqbd,"0",sizeof(sdb_batch_plrw.dqbd));
    /*��������*/
    pstrcopy(sdb_batch_plrw.fzbd,"00",sizeof(sdb_batch_plrw.fzbd));
    /*����״̬ - */
    pstrcopy(sdb_batch_plrw.bdzt,"9",sizeof(sdb_batch_plrw.bdzt));
    /*����״̬ - �ڴ���*/
    pstrcopy(sdb_batch_plrw.rwzt,"9",sizeof(sdb_batch_plrw.rwzt));
    /*��Ӧ����*/
    pstrcopy(sdb_batch_plrw.xydm," ",sizeof(sdb_batch_plrw.xydm));
    /*��Ӧ��Ϣ*/
    pstrcopy(sdb_batch_plrw.xyxx," ",sizeof(sdb_batch_plrw.xyxx));
    /*Ƕ����������*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_QTPKRQ,sBuf);
    pstrcopy(sdb_batch_plrw.qtpkrq,sBuf,sizeof(sdb_batch_plrw.qtpkrq));
    /*Ƕ��ƽ̨���κ�*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_QTPTPCH,sBuf);
    pstrcopy(sdb_batch_plrw.qtptpch,sBuf,sizeof(sdb_batch_plrw.qtptpch));
    if (sdb_batch_plrw.qtptpch[0] != '\0')
    {/*��Ƕ��*/
        sdb_batch_plrw.qtbz[0] = '2';
    }else
    {
        sdb_batch_plrw.qtbz[0] = '0';
    }
    COMP_SOFTSETXML(XMLNM_BATCH_REQ_QTBZ, sdb_batch_plrw.qtbz)
    /*sql_BeginTrans(); ��DCIBegin���� 2015-1-7 by chenxm*/
    DCIBegin();

    iRet = DBInsert("batch_plrw", SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), &sdb_batch_plrw, sErrmsg);
    if( iRet < 0 )
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle,MID_BATCH_INS_PLRW,MSG_BATCH_INS_PLRW);
        return COMPRET_FAIL;
    }

    /*if( sql_CommitTrans() !=MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_DQBD, sdb_batch_plrw.dqbd)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_FZBD, sdb_batch_plrw.fzbd)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_BDZT, sdb_batch_plrw.bdzt)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_RWZT, sdb_batch_plrw.rwzt)

    /*д��������ҵ����*/
    memset(sBusiMon, 0x00, sizeof(sBusiMon));
    COMP_SOFTGETXML(XMLNM_BATCH_MON_NORM, sBusiMon)
    if ( sBusiMon[0] == '\0')
    {
        pstrcopy(sBusiMon, BATCH_MON_NORM, sizeof(sBusiMon));
    }
    prv_batch_busimon(lXmlhandle, sBusiMon);

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_UPD_FILE
�������:BATCH_UPD_FILE
�������: ����ҵ���ⲿ�ļ���Ϣ����
�������:
 ��� ��������  ��������  ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
1   1-����   ���±�־   �����ַ���  *      N   1 ����ƽ̨���κ� 2 ��������״
2   2-����   ��������   �����ַ���  *      N   
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_UPD_FILE(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    char sUpdContent[16+1];
    int iParas,iUpdFlag;
    int iResult,ret;
    char sSql1[1024];
    char sErrmsg[512];
    int iRet=-1;
    BATCH_WBWJDJ sdb_batch_wbwjdj;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");
    
    COMP_PARACOUNTCHK(2)        /* �������������� */
    memset(sBuf,0,sizeof(sBuf));
    memset(&sdb_batch_wbwjdj,0,sizeof(sdb_batch_wbwjdj));
    COMP_GETPARSEPARAS(1, sBuf, "���±�־"); /*1 ����ƽ̨���κ� 2 ��������״̬ */
    iUpdFlag=atoi(sBuf);
        
    memset(sBuf,0,sizeof(sBuf));
    memset(sUpdContent,0,sizeof(sUpdContent));
    COMP_GETPARSEPARAS(2, sBuf, "��������");
    pstrcopy(sUpdContent, sBuf, sizeof(sUpdContent));
    trim(sUpdContent);

    memset(sBuf,0,sizeof(sBuf));    
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ, sBuf);  /*��������*/ 
    pstrcopy(sdb_batch_wbwjdj.pkrq,sBuf,sizeof(sdb_batch_wbwjdj.pkrq));
    if(strlen(sdb_batch_wbwjdj.pkrq)<=0)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }    

    /*sql_BeginTrans(); ��DCIBegin���� 2015-1-7 by chenxm*/
    DCIBegin();
        
    if( iUpdFlag ==1 )  /*  ����ƽ̨���κ� */
    {
        memset(sBuf,0,sizeof(sBuf));    
        COMP_SOFTGETXML(XMLNM_BATCH_WBWJDJ_DJRQ, sBuf);  /*�Ǽ�����*/ 
        pstrcopy(sdb_batch_wbwjdj.djrq,sBuf,sizeof(sdb_batch_wbwjdj.djrq));
        if(strlen(sdb_batch_wbwjdj.djrq)<=0)
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_DJRQ_NULL,MSG_BATCH_DJRQ_NULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }    
        memset(sBuf,0,sizeof(sBuf));                 
        COMP_SOFTGETXML(XMLNM_BATCH_WBWJDJ_DJLSH , sBuf); /*�Ǽ���ˮ��*/    
        if(strlen(sBuf)<=0)
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_DJLSH_NULL,MSG_BATCH_DJLSH_NULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        sdb_batch_wbwjdj.djlsh=atol(sBuf); 

        snprintf( sSql1, sizeof( sSql1 ), "UPDATE BATCH_WBWJDJ SET pkrq='%s', ptpch='%s', pczt = '3'\
            WHERE djrq='%s' AND djlsh=%d", sdb_batch_wbwjdj.pkrq, sUpdContent, sdb_batch_wbwjdj.djrq, sdb_batch_wbwjdj.djlsh);

        iRet = DCIExecuteDirect( sSql1 );
        if( iRet <= 0 )
        {
             LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sql[%s]err[%s]",sSql1, DCILastError() ),"ERROR")
             /*sql_RollbackTrans();*/
             DCIRollback();
             fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_WBWJDJ,MSG_BATCH_UPD_WBWJDJ );
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
        }
    }
    else if( iUpdFlag == 2 ) /* ��������״̬ */
    {
        memset(sBuf,0,sizeof(sBuf));    
        COMP_SOFTGETXML(XMLNM_BATCH_PTPCH, sBuf); /*ƽ̨���κ�*/ 
        pstrcopy(sdb_batch_wbwjdj.ptpch,sBuf,sizeof(sdb_batch_wbwjdj.ptpch));
        if(strlen(sdb_batch_wbwjdj.ptpch)<=0)
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }    
        snprintf( sSql1, sizeof( sSql1 ), "UPDATE BATCH_WBWJDJ SET pczt='%s' WHERE pkrq='%s' AND ptpch='%s'",\
            sUpdContent, sdb_batch_wbwjdj.pkrq, sdb_batch_wbwjdj.ptpch);\
        iRet = DCIExecuteDirect( sSql1 );
        if( iRet <= 0 )
        {
             LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s][%s]",DCILastError(),sSql1 ),"ERROR")
             /*sql_RollbackTrans();*/
             DCIRollback();
             fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_PLRWBD, MSG_BATCH_UPD_PLRWBD );
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
        }
    }
    else
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPDFLAG_FF,MSG_BATCH_UPDFLAG_FF);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;            
    }    

    /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
        
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");

    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_UPD_PLRW
�������:BATCH_UPD_PLRW
�������: 
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
  1   1-����   ��ǰ����      416XML�����ַ���     *         Y      
  1   1-����   ��������      416XML�����ַ���     *         N  
  1   1-����   ����״̬      416XML�����ַ���     *         Y      
  1   1-����   ����״̬      416XML�����ַ���     *         N      
  
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_UPD_PLRW(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    int iParas;
    int iResult;
    char sStep[8+1];
    char sStepNew[8+1];
    char sStepStatus[8+1];
    char sTaskStatus[8+1];
    char sAstStep[2+1];
    char sTestFlag[2+1];
    char sBreak[1+1];
    char sClsj[6+1];

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");
    
    COMP_PARACOUNTCHK(4)        /* �������������� */
            
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��ǰ����");
    trim(sBuf);
    pstrcopy( sStep, sBuf, sizeof( sStep ) );/*��ǰ����*/     
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sAstStep, 0x00, sizeof(sAstStep));
    COMP_GETPARSEPARAS(2, sBuf, "��������");
    trim(sBuf);
    pstrcopy( sAstStep, sBuf, sizeof( sAstStep  ) );/*��������*/  
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "����״̬");
    trim(sBuf);
    pstrcopy( sStepStatus, sBuf, sizeof( sStepStatus ) );/*����״̬*/    
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(4, sBuf, "����״̬");
    trim(sBuf);
    pstrcopy( sTaskStatus, sBuf, sizeof( sTaskStatus  ) );/*����״̬*/    
    
    memset(sBreak, 0x00, sizeof(sBreak));
    memset(sClsj, 0x00, sizeof(sClsj));
    if ( sStep[0] == BATCH_STEPSN_SJTJ)
    {
        COMP_SOFTGETXML("/batch/sjtj/ddbz", sBreak)
        if (sBreak[0] == BATCH_ATTRIBUTE_DDBZ_BREAK)
        {
            COMP_SOFTGETXML("/batch/sjtj/clsj", sClsj)
        }
    }
    LOG(LM_DEBUG, Fmtmsg("upd plrw sBreak=[%s],sClsj=[%s]", sBreak, sClsj), "DEBUG");
    /* modified by yangdong 20130219 ���ӿ�ʼ����ʱ�� 
    iResult = fprv_batch_upd_plrw( lXmlhandle,sStep,sStepStatus,sTaskStatus );
    */
    
    /*mod by tuql 20160606 begin
     * ����:201606060219
     */
    DCIBegin();
    iResult = fprv_batch_upd_plrw( lXmlhandle,sStep,sAstStep,sStepStatus,sTaskStatus,sBreak,sClsj );
    DCICommit();/*add by tuql 20160606 ����:201606060219 */
    return iResult;
}

/************************************************************************
��̬�����������
�����������:SBATCH_INS_PLRWBD
�������:BATCH_INS_PLRWBD
�������: ����ҵ�����񲽵���Ϣ�Ǽ�
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
  1   1-����   �ظ�������־   416XML�����ַ���     *   N   0���� 1������
  2   2-����   ��������       416XML�����ַ���     *   N   
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_INS_PLRWBD(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    int iParas;
    char xmlNode[512];
    char sCfczbz[1+1];
    char DB_sBdzt[1+1];
    /*int iUpdFlag=0;*/
    /* modified by yangdong 201201101 ����Ĭ���ظ�����
    char    sCfcs[3];
    */
    int   iClcs=0;
    char  sSjcfczcs[3];
    char  sStepID[100];
    char sSql1[1024];
    char sErrmsg[512];
    int iRet=-1;
    BATCH_PLRWBD sdb_batch_plrwbd;
    
    fpub_InitSoComp(lXmlhandle);
 
    COMP_PARACOUNTCHKMIN(2)
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"�ظ�������־") /* 0���� 1������*/
    trim( sBuf );
    pstrcopy( sCfczbz, sBuf, sizeof( sCfczbz ) );
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"��������") 
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_CZBD_NULL,MSG_BATCH_CZBD_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;        
    }
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ,�ظ�������־[%s],��������[%s]", 
        fpub_GetCompname(lXmlhandle), sCfczbz, sBuf), "DEBUG");
    memset(&sdb_batch_plrwbd,0,sizeof(sdb_batch_plrwbd));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_BDZT, sBuf)
    pstrcopy(sdb_batch_plrwbd.bdzt, sBuf, sizeof(sdb_batch_plrwbd.bdzt)); 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_DQBD, sBuf)
    pstrcopy(sdb_batch_plrwbd.czbd, sBuf, sizeof(sdb_batch_plrwbd.czbd)); 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_FZBD, sBuf)
    pstrcopy(sdb_batch_plrwbd.fzbd, sBuf, sizeof(sdb_batch_plrwbd.fzbd));
    
    /*��������*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_HARDGETXML(XMLNM_BATCH_PKRQ, sBuf);                        
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }    
    pstrcopy(sdb_batch_plrwbd.pkrq,sBuf,sizeof(sdb_batch_plrwbd.pkrq));
    trim(sdb_batch_plrwbd.pkrq);
    
    /*���κ�*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_HARDGETXML(XMLNM_BATCH_PTPCH , sBuf);                 
    pstrcopy(sdb_batch_plrwbd.ptpch,sBuf,sizeof(sdb_batch_plrwbd.ptpch));
    if(strlen(sdb_batch_plrwbd.ptpch)<=0)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*strcpy( sdb_batch_plrwbd.bdzt, BATCH_STEP_STATUS_S_RUNNING );*/

    /*����ִ�����*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_HARDGETXML(XMLNM_BATCH_FLOWCFG_FLOWSN , sBuf);                 
    sdb_batch_plrwbd.flowsn = atoi(sBuf);
    /*�������*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DJJG ,sBuf); 
    if( 0 == sBuf[0] ) 
    {/*���׻���Ϊ��*/
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG,sBuf);
        if( 0 == sBuf[0] ) 
        {/*cpxx����������ҲΪ��*/
            fpub_SetMsg(lXmlhandle,MID_BATCH_JYJGNULL,MSG_BATCH_JYJGNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    trim(sBuf);
    pstrcopy(sdb_batch_plrwbd.cljg,sBuf,sizeof(sdb_batch_plrwbd.cljg));
    
    /*�����Ա*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DJGY ,sBuf);
    if( 0 == sBuf[0] ) 
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG,sBuf);
    }
    trim(sBuf);
    pstrcopy(sdb_batch_plrwbd.clgy,sBuf,sizeof(sdb_batch_plrwbd.clgy));
    /*����ʼ����*/ 
    sprintf(sdb_batch_plrwbd.clksrq,"%s",GetSysDate());                
    
    /*����ʼʱ��*/                
    sprintf(sdb_batch_plrwbd.clkssj,"%s",GetSysTime());        

    /* ��鲽��״̬�� */        
    memset(DB_sBdzt,0,sizeof(DB_sBdzt));
    memset(sBuf,0,sizeof(sBuf));
    iClcs=0;

    snprintf( sSql1, sizeof( sSql1 ),"SELECT bdzt,clcs FROM batch_plrwbd\
        WHERE  pkrq='%s' AND ptpch='%s' AND flowsn = %d AND czbd='%s' ",\
        sdb_batch_plrwbd.pkrq, sdb_batch_plrwbd.ptpch, 
        sdb_batch_plrwbd.flowsn,sdb_batch_plrwbd.czbd );
    iRet = DBSelectToMultiVar( sErrmsg, sSql1, DB_sBdzt, sBuf );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    DCIBegin(); /*add by chenxm 2015-1-7*/
    iClcs = atoi( sBuf );

    /* �Ѿ����ڲ����¼ */
    if( iRet > 0 )
    {
        /* ��������ͬʱ���� 
        if( DB_sBdzt[0] == '9' )
        {
            LOG(LM_STD,Fmtmsg("����״̬[%s],�������ظ�����", DB_sBdzt ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_CFCZ,MSG_BATCH_CFCZ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        else */
        if( DB_sBdzt[0] == 'C' || DB_sBdzt[0] == 'X' || 
            DB_sBdzt[0] == 'c' || DB_sBdzt[0] == 'x' )
        {
            LOG(LM_STD,Fmtmsg("����״̬[%s],���������", DB_sBdzt ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_CANCELED,MSG_BATCH_CANCELED );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /*  �������ظ�������������״̬��Ϊ����ʧ�ܣ������� */
        /* add by yr 20120927  */    
        /* modified by yangdong 20121101 
        if( sCfczbz[0] != '0' )
        */
        if( ( sCfczbz[0] != '0' ) && ( DB_sBdzt[0] != '0' ) )
        {
            LOG(LM_STD,Fmtmsg("����״̬[%s],�������ظ�����", DB_sBdzt ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_CFCZ,MSG_BATCH_CFCZ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* del by yangdong 20121101
        if( DB_sBdzt[0] != '0'  )
        {
            LOG(LM_STD,Fmtmsg("����״̬[%s],�������ظ�����", DB_sBdzt ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_CFCZ,MSG_BATCH_CFCZ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        */
        LOG(LM_STD,Fmtmsg("insert/update plrwbd [%s%s%s]",  
            sdb_batch_plrwbd.pkrq, sdb_batch_plrwbd.ptpch, sdb_batch_plrwbd.czbd),"INFO")
        /* �ظ�����ʱ���ȸ��²���״̬Ϊ9  */
        snprintf( sSql1, sizeof( sSql1 ), "UPDATE batch_plrwbd SET bdzt = '9'\
            WHERE pkrq='%s' AND ptpch='%s' AND flowsn='%d' AND czbd='%s'",\
            sdb_batch_plrwbd.pkrq, sdb_batch_plrwbd.ptpch, 
            sdb_batch_plrwbd.flowsn, sdb_batch_plrwbd.czbd );
        iRet = DCIExecuteDirect( sSql1 );
        if( iRet < 1 )
        {
            /*sql_RollbackTrans();*/
            DCIRollback();
            LOG(LM_STD,Fmtmsg("����[%s]����״̬ʧ��", sdb_batch_plrwbd.czbd ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_PLRWBD,MSG_BATCH_UPD_PLRWBD);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
        if(DCICommit() != 0)
        {
            DCIRollback();
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
    }
    /* ��������Ǽ� */
    else
    {
        iRet = DBInsert("batch_plrwbd", SD_BATCH_PLRWBD, NUMELE(SD_BATCH_PLRWBD), &sdb_batch_plrwbd, sErrmsg);
        if( iRet < 0 )
        {
            /*sql_RollbackTrans();*/
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_BATCH_INS_PLRWBD,MSG_BATCH_INS_PLRWBD);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
        if(DCICommit() != 0)
        {
            DCIRollback();
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
    }
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");

    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_UPD_PLRWBD
�������:BATCH_UPD_PLRWBD
�������: ����ҵ�����񲽵���Ϣ����
�������:
 ��� ��������  �������� ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
1   1-����   ����״̬   �����ַ���     *   N   9�ڴ�����  0��ֹ 1����2�ϵ�3����4�ȴ�
2   2-����   ��������   �����ַ���     *   N   0 ��ȡ���� 1 ������� 2 ������� 3 �����ύ 4�������  5��ҵ����
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_UPD_PLRWBD(HXMLTREE lXmlhandle)
{
   char sBuf[128+1];
   char sStep[8+1];
   char sStepStatus[8+1];
   int iParas;
   int iRet = -1;
    
   fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");

    COMP_PARACOUNTCHK(2)        
    
    memset( sStep, 0x00, sizeof( sStep ) );
    memset( sStepStatus, 0x00, sizeof( sStepStatus ) );
    /*����״̬*/ 
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "����״̬");
    trim(sBuf);
    pstrcopy(sStepStatus, sBuf, sizeof(sStepStatus));    
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "��������");
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_CZBD_NULL,MSG_BATCH_CZBD_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;            
    }
    pstrcopy(sStep, sBuf, sizeof(sStep));    
    /*mod by tuql 20160606 begin
     * ����:201606060219
     */
    DCIBegin();
    iRet = fprv_batch_upd_plrwbd( lXmlhandle, sStepStatus, sStep );
    DCICommit();/*add by tuql 20160606 ����:201606060219 */
    return iRet;
}

/************************************************************************
��̬�����������
�����������:SBATCH_GETFILETYPE
�������:BATCH_GETFILETYPE
�������: ����ҵ���ȡ�ļ�������Ϣ
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
  1   1-����   �ļ���ʶ       416-�����ַ���            N    �ļ���ʶ              
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_GETFILETYPE(HXMLTREE lXmlhandle)
{
    int    iParas;
    char sBuf[255];
    char sFileId[50+1];
    char sSql1[1024];
    char sErrmsg[512];
    int iRet=-1;
    BATCH_FILETYPE sdb_batch_filetype;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")

    COMP_PARACOUNTCHKMIN(1)
    memset(sBuf,0,sizeof(sBuf));
    memset(sFileId,0,sizeof(sFileId));
    COMP_GETPARSEPARAS(1,sBuf,"�ļ���ʶ")
    pstrcopy(sFileId,sBuf,sizeof(sFileId));
    
    if( sFileId[0] == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJBS_NULL,MSG_BATCH_WJBS_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    } 
    
    memset(&sdb_batch_filetype,0,sizeof(sdb_batch_filetype));
    
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM BATCH_FILETYPE WHERE fileid='%s'", sFileId );
    iRet = fprv_SelToStruct( sSql1, SD_BATCH_FILETYPE, NUMELE(SD_BATCH_FILETYPE), &sdb_batch_filetype); 
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("��ѯ�ļ�����ʧ��[%s]",sFileId),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WJLX,MSG_BATCH_SEL_WJLX);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }                

    trim(sdb_batch_filetype.fileid);        
    trim(sdb_batch_filetype.filetype);    
    trim(sdb_batch_filetype.filefmt);  
    trim(sdb_batch_filetype.codefmt);    
    trim(sdb_batch_filetype.extfld1);    
    COMP_SOFTSETXML(XMLNM_BATCH_WJLX_FILEID    , sdb_batch_filetype.fileid)
    COMP_SOFTSETXML(XMLNM_BATCH_WJLX_FILETYPE  , sdb_batch_filetype.filetype)
    COMP_SOFTSETXML(XMLNM_BATCH_WJLX_FILEFMT   , sdb_batch_filetype.filefmt)
    COMP_SOFTSETXML(XMLNM_BATCH_WJLX_CODEFMT   , sdb_batch_filetype.codefmt)
    COMP_SOFTSETXML(XMLNM_BATCH_WJLX_EXTFLD1   , sdb_batch_filetype.extfld1)
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_RESP
�������:BATCH_RESP
�������: ����ҵ����Ӧ��ת�� ֻת�����ʧ����ϸ
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
 1   1-����   ��Ӧ����Դ��   416-�����ַ���            Y    ��Ӧ����Դ��   
 2   1-����   ��������       416-�����ַ���            Y    ��������   
 3   1-����   ƽ̨���κ�     416-�����ַ���            Y    ƽ̨���κ�   
 4   1-����   ҵ�����       416-�����ַ���            Y    ҵ�����   
 5   1-����   Դ��Ӧ��       416-�����ַ���            Y    Դ��Ӧ��
 6   1-����   Ŀ����Ӧ��     416-�����ַ���            Y    Ŀ����Ӧ��
 7   1-����   Ŀ����Ӧ��Ϣ   416-�����ַ���            Y    Ŀ����Ӧ��Ϣ
 8   1-����   ת����Χ       416-�����ַ���            Y    ת����Χ
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_RESP(HXMLTREE lXmlhandle)
{
    char sBuf[255];
    char sDft[1+1];
    char sMsgD[20+1];
    char sDest[20+1];
    char sDestMsg[40+1];
    char sSource[10+1];
    char sResName[50+1];
    char sColumnS[20+1];
    char sColumnD[20+1];
    char sErrmsg[512];
    char sSql1[1024];
    char sPkrq[8+1];
    char sPtpch[8+1];
    char DB_sTableName[50+1];
    char sFlag[1+1];
    int  iParas;
    int  i, iResult;
    int  iRet=-1;
    CURSOR cur;
    BATCH_MAPRESP sdb_batch_mapresp;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")

    COMP_PARACOUNTCHKMIN(7)
    memset(sBuf,0,sizeof(sBuf));
    memset(sResName,0,sizeof(sResName));
    COMP_GETPARSEPARAS(1,sBuf,"��Ӧ����Դ��")
    pstrcopy(sResName,sBuf,sizeof(sResName));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sPkrq,0,sizeof(sPkrq));
    COMP_GETPARSEPARAS(2,sBuf,"��������")
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_GETPARSEPARAS(3,sBuf,"ƽ̨���κ�")
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(DB_sTableName,0,sizeof(DB_sTableName));
    COMP_GETPARSEPARAS(4,sBuf,"ҵ�����")
    pstrcopy(DB_sTableName,sBuf,sizeof(DB_sTableName));
  
    memset(sBuf,0,sizeof(sBuf));
    memset(sColumnS,0,sizeof(sColumnS));
    COMP_GETPARSEPARAS(5,sBuf,"��Դ�ֶ���")
    pstrcopy(sColumnS,sBuf,sizeof(sColumnS));

    memset(sBuf,0,sizeof(sBuf));
    memset(sColumnD,0,sizeof(sColumnD));
    COMP_GETPARSEPARAS(6,sBuf,"Ŀ����Ӧ��")
    pstrcopy(sColumnD,sBuf,sizeof(sColumnD));

    memset(sBuf,0,sizeof(sBuf));
    memset(sMsgD,0,sizeof(sMsgD));
    COMP_GETPARSEPARAS(7,sBuf,"Ŀ����Ӧ��Ϣ")
    pstrcopy(sMsgD,sBuf,sizeof(sMsgD));

    memset(sBuf,0,sizeof(sBuf));
    memset(sFlag,0,sizeof(sFlag));
    COMP_GETPARSEPARAS(8,sBuf,"ת����Χ")
    pstrcopy(sFlag,sBuf,sizeof(sFlag));

    if( sColumnS[0] == '\0' )
       strcpy( sColumnS,"xym" );  /* Ĭ���ֶ�Ϊxym */
    if( sColumnS[0] == '\0' )
       strcpy( sColumnD,"xym" );  /* Ĭ���ֶ�Ϊxym */

    LOG(LM_DEBUG,Fmtmsg("BATCH:��Ӧ��ת����Դ��[%s] Դ�ֶ�[%s]  Ŀ���ֶ�[%s]", sResName, sColumnS, sColumnD),"DEBUG")
  
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM batch_mapresp WHERE mapid='%s'", sResName );
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
    
    DCIBegin();
    
    while( ( iRet = DBFetch(cur, SD_BATCH_MAPRESP, NUMELE(SD_BATCH_MAPRESP), &sdb_batch_mapresp, sErrmsg ) ) > 0 )
    {
        /*��ȡ�������ݽ��д���*/
        strcpy( sSource, sdb_batch_mapresp.resp_s ); 
        trim(sSource);

        strcpy( sDest, sdb_batch_mapresp.resp_d ); 
        trim(sDest);

        strcpy( sDestMsg, sdb_batch_mapresp.msg_d ); 
        trim(sDestMsg);

        sDft[0] = sdb_batch_mapresp.bz[0];

        memset(sSql1, 0, sizeof(sSql1));

        LOG(LM_DEBUG,Fmtmsg("BATCH:��Ӧ��ת�� Դֵ[%s] Ŀ��ֵ[%s] [%s]", sSource, sDest, sDestMsg ),"DEBUG")

        trim( sDestMsg ); 
        /* �ж��Ƿ���Ҫת����Ӧ��Ϣ  */
        if( strlen( sDestMsg ) > 0 )
        {
            /* Ĭ��ֵ���� */
            if( sDft[0] == '0' )  /* Ĭ��ֵ */
            {
                /* added by yangdong 20120508 ���Ӷ�NULL���ж� */
                /* added by yangdong 20130609 ֻ�������ʧ����ϸ������ж� */
                snprintf(sSql1,sizeof(sSql1),"UPDATE %s SET %s='%s', %s='%s' \
                    WHERE pkrq='%s' AND ptpch='%s' AND \
                    ( trim(%s)='%s' OR ( trim(%s) NOT IN( SELECT trim( resp_s ) FROM batch_mapresp WHERE mapid='%s' ) ) \
                    OR ( %s IS NULL ) )",\
                    DB_sTableName, sColumnD, sDest, sMsgD, sDestMsg, sPkrq, sPtpch,\
                    sColumnS, sSource , sColumnS, sResName, sColumnS );
            }
            else
            {
                snprintf(sSql1,sizeof(sSql1),"UPDATE %s SET %s='%s', %s='%s' \
                    WHERE pkrq='%s' AND ptpch='%s' AND trim(%s)='%s'",\
                    DB_sTableName, sColumnD, sDest, sMsgD, sDestMsg, sPkrq, sPtpch, sColumnS, sSource );
            }
        }
        else
        {
            /* Ĭ��ֵ���� */
            if( sDft[0] == '0' )  /* Ĭ��ֵ */
            {
                /* added by yangdong 20120508 ���Ӷ�NULL���ж� */
                snprintf(sSql1,sizeof(sSql1),"UPDATE %s SET %s='%s' \
                    WHERE pkrq='%s' AND ptpch='%s' AND \
                    ( trim(%s)='%s' OR ( trim(%s) NOT IN( SELECT trim( resp_s ) FROM batch_mapresp WHERE mapid='%s' ) ) \
                    OR ( %s IS NULL ) )",\
                    DB_sTableName, sColumnD, sDest, sPkrq, sPtpch, sColumnS, sSource , sColumnS, sResName, sColumnS );
            }
            else
            {
                snprintf(sSql1,sizeof(sSql1),"UPDATE %s SET %s='%s'  \
                    WHERE pkrq='%s' AND ptpch='%s' AND trim(%s)='%s'",\
                    DB_sTableName, sColumnD, sDest, sPkrq, sPtpch, sColumnS, sSource );
            }
        }

        /*ֻת����������Ӧ��ΪNULL�ļ�¼*/
        strcat( sSql1, " AND dsfxym is NULL " );

        /* added by yangdong 20130609 ����ת����Χ�ж� */
        /* ֻת�����ʧ����ϸ 
        if( sFlag[0] == '1' ) 
        {
            strcat( sSql1, " AND shzt='0' " );           
        }*/

        iRet = DCIExecuteDirect(sSql1);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            /*sql_RollbackTrans();*/
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_BATCH_RESP_CONV,MSG_BATCH_RESP_CONV );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
            return COMPRET_FAIL;
        }
        LOG(LM_STD,Fmtmsg("update resp[%s][%d]", sSql1, iResult ),"INFO")
    }    
    DCIFreeCursor(cur);
    
    /* add by yr 20120926 */
    /*if( sql_CommitTrans() !=MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIFreeCursor(cur);
        DCIRollback();
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* end */
    
    DCIFreeCursor(cur);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:SBATCH_EXPORT_BREAK
�������:BATCH_EXPORT_BREAK
�������: ����ҵ��ϵ����ݵ�������
�������:
 ��� ��������    ��������                 ��Դ���         ȱʡֵ    �ɿ�    ����˵��        
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_EXPORT_BREAK(HXMLTREE lXmlhandle)
{
    int iRet = -1;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    DCIBegin();/*add by tuql 20160606 ����:201606060219 */
    iRet = fprv_export_break( lXmlhandle );
    DCICommit();
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    return iRet; 
}

/************************************************************************
��̬�����������
�����������:SBATCH_TASK_CANCEL
�������:BATCH_TASK_CANCEL
�������: ����ҵ������ȡ��
�������:
 ��� ��������  ��������         ��Դ���          ȱʡֵ           �ɿ�  ����˵��    
  1   1-����   ҵ����      416XML�����ַ���  [/batch/req/ywbh]      N    
  2   2-����   �Ǽ�����      416XML�����ַ���  [/batch/req/djrq]      N   
  2   3-����   �Ǽ���ˮ��    416XML�����ַ���  [/batch/req/djlsh]     N   
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_TASK_CANCEL(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    int  iParas,iFlag;
    int  iRet = -1;
    int  iDjlsh=0;
    char sErrmsg[512];
    char sSql1[1024];
    char sDjrq[8+1];
    char sYwbh[16+1];
    BATCH_WBWJDJ sdb_batch_wbwjdj;
    BATCH_PLRW sdb_batch_plrw;
 
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");

    
    COMP_PARACOUNTCHK(3)        /* �������������� */
    memset(sBuf,0,sizeof(sBuf));
    memset(sYwbh,0,sizeof(sYwbh));
    COMP_GETPARSEPARAS(1, sBuf, "ҵ����"); 
    pstrcopy(sYwbh, sBuf, sizeof(sYwbh));
        
    memset(sBuf,0,sizeof(sBuf));
    memset(sDjrq,0,sizeof(sDjrq));
    COMP_GETPARSEPARAS(2, sBuf, "�Ǽ�����");
    pstrcopy(sDjrq, sBuf, sizeof(sDjrq));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "�Ǽ���ˮ��");
    iDjlsh=atoi(sBuf);
    
    memset(&sdb_batch_wbwjdj,0,sizeof(sdb_batch_wbwjdj));
    snprintf( sSql1, sizeof( sSql1 ), "SELECT pkrq, ptpch, pczt, lpwjm \
        FROM batch_wbwjdj WHERE djrq='%s' AND djlsh=%d", sDjrq, iDjlsh);
    iRet=DBSelectToMultiVar(sErrmsg,sSql1,sdb_batch_wbwjdj.pkrq,sdb_batch_wbwjdj.ptpch,sdb_batch_wbwjdj.pczt,sdb_batch_wbwjdj.lpwjm);
    if( iRet < 1 )
    {
        LOG(LM_STD,Fmtmsg("�������������ⲿ�ļ���Ϣ,[%s],[%d],sqlerr[%s]",\
            sDjrq,iDjlsh,DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_NOFUND,MSG_BATCH_WBWJDJ_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                
    }
    trim(sdb_batch_wbwjdj.ptpch);
    trim(sdb_batch_wbwjdj.pczt);
    trim(sdb_batch_wbwjdj.lpwjm);
    COMP_SOFTSETXML(XMLNM_BATCH_PKRQ, sdb_batch_wbwjdj.pkrq)
    COMP_SOFTSETXML(XMLNM_BATCH_PTPCH, sdb_batch_wbwjdj.ptpch)
    LOG(LM_DEBUG,Fmtmsg("BATCH: ��ȡ�ⲿ�ļ���Ϣ,pczt[%s]", sdb_batch_wbwjdj.pczt ),"DEBUG");
    memset(sSql1, 0x00, sizeof(sSql1));
    snprintf( sSql1, sizeof( sSql1 ), "SELECT dqbd,fzbd,bdzt,rwzt FROM BATCH_PLRW\
        WHERE pkrq='%s' AND ptpch = '%s'",sdb_batch_wbwjdj.pkrq, sdb_batch_wbwjdj.ptpch );
    iRet=DBSelectToMultiVar( sErrmsg, sSql1,sdb_batch_plrw.dqbd,sdb_batch_plrw.fzbd,sdb_batch_plrw.bdzt,sdb_batch_plrw.rwzt );
    if( iRet < 1 )
    {
        LOG(LM_STD,Fmtmsg("����������������������Ϣ,[%s],sqlerr[%s]",\
                   sdb_batch_wbwjdj.ptpch,DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_NOFUND,\
                           MSG_BATCH_WBWJDJ_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                
    }
    trim(sdb_batch_plrw.dqbd);
    trim(sdb_batch_plrw.fzbd);
    trim(sdb_batch_plrw.bdzt);
    trim(sdb_batch_plrw.rwzt);
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_DQBD, sdb_batch_plrw.dqbd)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_FZBD, sdb_batch_plrw.fzbd)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_BDZT, sdb_batch_plrw.bdzt)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_RWZT, sdb_batch_plrw.rwzt)

    switch(sdb_batch_wbwjdj.pczt[0])
    {
        case WBWJDJ_ZT_PRE: /* �����ϴ� */
            iFlag=-1;
            fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_PRE,Fmtmsg(MSG_BATCH_WBWJDJ_PRE,sdb_batch_wbwjdj.lpwjm));
            break;
        case WBWJDJ_ZT_READY: /* ���� */
            sql_BeginTrans();
            snprintf( sSql1, sizeof( sSql1 ),"UPDATE batch_wbwjdj SET pczt = 'X'\
                WHERE djrq='%s' AND djlsh=%d", sDjrq, iDjlsh );
            iRet = DCIExecuteDirect( sSql1 );
            if( iRet < 1 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }

            if( sql_CommitTrans() !=MID_SYS_SUCC )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            iFlag=1;
            break;
        
        /* modified by yangdong 20120424 ����ʧ�������� */
        case WBWJDJ_ZT_FAIL: /* ����ʧ�� */
        case WBWJDJ_ZT_RUNNING: /* ���ڴ��� */
        /* modified by yangdong 20120424 ״̬�ж�
        ����Ϊ���ύ���ĳɹ��������ύ���ģ�������ʧ��״̬ ��������
            if( atoi(sdb_batch_plrw.dqbd) < 4 )
        */
            if( atoi(sdb_batch_plrw.dqbd) > 3 ||
                ( atoi(sdb_batch_plrw.dqbd) == 3 && sdb_batch_plrw.bdzt[0] !='0' ) )
            {
                iFlag = -1;
                fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_RUNNING,\
                Fmtmsg(MSG_BATCH_WBWJDJ_RUNNING,sdb_batch_wbwjdj.lpwjm));
                break;        
            }
            iFlag=1;
            COMP_SOFTSETXML(XMLNM_BATCH_PLRW_DQBD,sdb_batch_plrw.dqbd)
            COMP_SOFTSETXML(XMLNM_BATCH_PKRQ,sdb_batch_plrw.pkrq)
            COMP_SOFTSETXML(XMLNM_BATCH_PTPCH,sdb_batch_wbwjdj.ptpch)
            COMP_SOFTSETXML(XMLNM_RESPMSG,"�����������ɹ�")
            break;
        case WBWJDJ_ZT_SUCC: /* �ѷ��� */
            iFlag=-1;
            fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_SUCC,\
                Fmtmsg(MSG_BATCH_WBWJDJ_SUCC,sdb_batch_wbwjdj.lpwjm));
            break;
        case WBWJDJ_ZT_CX: /* �ѳ��� */
            iFlag=-1;
            fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_CX,\
                Fmtmsg(MSG_BATCH_WBWJDJ_CX,sdb_batch_wbwjdj.lpwjm));
            break;
        default: /* ���� */
            iFlag=-1;
            fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_UNKNOWN,\
                 Fmtmsg(MSG_BATCH_WBWJDJ_UNKNOWN,sdb_batch_wbwjdj.lpwjm));
            break;
    }
    fpub_SetCompStatus(lXmlhandle,iFlag);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");

    return COMPRET_SUCC;
}
