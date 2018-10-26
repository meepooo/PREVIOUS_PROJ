/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.1)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:BAT_CTRL.c
�ļ�����:����ҵ��������������
�� �� Ա:chensy YangDong
��������:2011-08-01
�� �� Ա:YangDong
�޸�����:20141018
�޸�˵��:DCI����
 *********************************************************************/
#include <dlfcn.h>
#include "gaps_head.h"
/*#include "DCI.h"*/
#include "batch_head.h"
#include "app_macro.h"
#include "app_xmlmacro.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_CTRL.so</soname>\
        <sosrcname>BAT_CTRL.c</sosrcname>\
        <sonote>BATCH���̿����������</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"Chensy YangDong\" filesize=\"1266963\">HS-AgentV2.1����</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1266963\">DCI����</rec>\
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

/***************************************************************************
��̬�����������
�����������:SBATCH_TASKCTRL
�������:BATCH_TASKCTRL
�������:����ҵ��������� 
�������:
��� ��������  ��������          ��Դ���      ȱʡֵ     �ɿ�       ����˵��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
****************************************************************************/
IRESULT SBATCH_TASKCTRL(HXMLTREE lXmlhandle)
{
    char sBuf[128];
    char sYwbh[16+1];
    char sPkrq[8+1];
    char sSql1[1024];
    char sErrmsg[512];
    int  DB_iTaskRun;
    int  iParas;
    int  iBusiMax = 0 ;
    int  iRunctlMax = 0;
    int iRet = -1;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(3);
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sYwbh,0,sizeof(sYwbh));
    COMP_GETPARSEPARAS(1,sBuf,"ҵ����");
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBH_NULL,MSG_BATCH_YWBH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sYwbh,sBuf,sizeof(sYwbh));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"����Ӧ�������������");
    iBusiMax = atoi( sBuf );
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"��ҵ���������������")
    iRunctlMax = atoi( sBuf );
    
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sPkrq); /* �������� */
    
    /* У��Ӧ����������(����) */
    DB_iTaskRun=0; 
    if( iBusiMax > 0 )
    {
        LOG(LM_DEBUG,Fmtmsg("����ҵ�����������[%d]", iBusiMax),"DEBUG");
        memset( sBuf, 0x00, sizeof( sBuf ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT count(*) FROM batch_plrw\
        				WHERE   pkrq='%s' AND rwzt = '9'", sPkrq );
        iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
        if( iRet < 0 )        
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        DB_iTaskRun = atoi( sBuf );

        /* added by yangdong 20151202 �����������������Ҫ+1
           ��Ϊ�Զ�������ߵ���������ʱ�򣬲�û�в���������߸�������״̬ */
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_JYDM,sBuf); 
        trim( sBuf );
        if( strcmp( sBuf,"910002" ) != 0 &&  strcmp ( sBuf, "910020" ) != 0 )
            DB_iTaskRun ++;
        /* end of add */

        if( DB_iTaskRun > iBusiMax )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ����ҵ������������������,����������[%d],\
            						����������[%d]",iBusiMax,DB_iTaskRun),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_BUSITASKOVER,MSG_BATCH_BUSITASKOVER);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    
    /* У��ҵ������������ */ 
    DB_iTaskRun=0; 
    if( iRunctlMax > 0 )
    {
        LOG(LM_DEBUG,Fmtmsg("����ҵ��ҵ��[%s]�������[%d]", sYwbh, iRunctlMax ),"DEBUG");

        memset( sBuf, 0x00, sizeof( sBuf ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT count(*) FROM batch_plrw\
        				WHERE  ywbh='%s' AND pkrq='%s' AND rwzt = '9' ", sYwbh, sPkrq );
        iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
        if( iRet < 0 )        
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        DB_iTaskRun = atoi( sBuf );

        /* added by yangdong 20151202 �����������������Ҫ +1
           ��Ϊ�Զ�������ߵ���������ʱ�򣬲�û�в���������߸�������״̬ */
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_JYDM,sBuf); 
        trim( sBuf );

        if( strcmp( sBuf,"910002" ) != 0 &&  strcmp ( sBuf, "910020" ) != 0 )
            DB_iTaskRun ++;
        /* end of add */

        if( DB_iTaskRun > iRunctlMax )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ����������������,\
            						������[%d],������[%d]",iRunctlMax,DB_iTaskRun),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_PRODUCTTASKOVER,\
            						Fmtmsg(MSG_BATCH_PRODUCTTASKOVER,sYwbh));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/* �ͷ�������Դ */
void prv_FlowListFree()
{                         
    if( t_flowList )
    {
        i_list_delete(&t_flowList);
    }
}

/************************************************************************
��̬�����������
�����������:SBATCH_RUNCTRL
�������:BATCH_RUNCTRL
�������: ����ҵ������ִ���ܿ�
�������:
��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
1   1-����   ���̱�ʶ       416-�����ַ���            Y    ���̱�ʶ 
ʹ������:
�Ż�����,�ܿ�һ��ʼ�������̲��㵼���ڴ�������,�����ⲿ����
����Ӱ������ݿ��α���Դ(ʹ��˫��������),��Ҫ�ⲿ
�����жϻ��˳���������ѭ��
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_RUNCTRL(HXMLTREE lXmlhandle)
{
    int iStepCount,iFlag=0,iAttribCount,jflag;
    int iParas;
    char sXmlNode[128];
    char sStepFlow[128];
    char sAttribvalue[128];
    char sBuf[128];
    int  iBdcgbz,ret;
    char flowStatus[11];
    char sStepSN[2];
    char sStepNM[8];
    char sFlowID[51];
    char DB_sStepID[51];
    char sErrmsg[512];
    char sSql1[1024];
    CURSOR cur;
    int  iClcs;         /* ���㴦����� */
    BATCH_STEPCFG sdb_batch_stepcfg;
    int iRet = -1;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1);
    memset(sBuf,0,sizeof(sBuf));
    memset(sFlowID,0,sizeof(sFlowID));
    COMP_GETPARSEPARAS(1,sBuf,"���̱�ʶ");
    pstrcopy(sFlowID,sBuf,sizeof(sFlowID));
    
    /* ��ʼ�����̵��������� */
    trim(sFlowID);
    iStepCount=fprv_initBatchFlow(lXmlhandle, sFlowID, &t_flowList);
    if( iStepCount <=0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:�޶�Ӧ����[%s]������Ϣ",sFlowID),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FLOWCFG_NOFUND,\
            MSG_BATCH_FLOWCFG_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* ���̲���ѭ������ʼ */
    for( pflowIter = i_list_begin(t_flowList); 
        pflowIter!= i_list_end(t_flowList); 
        pflowIter = i_list_iter_next(pflowIter) )
    {
        
        pFlowcfg = (BATCH_FLOWCFG *)(pflowIter->data);
        /* modified by guoliang 20130506 */
        strncpy(DB_sStepID, pFlowcfg->stepid, sizeof(DB_sStepID)-1);
        /* end */                
        memset(sStepNM, 0, sizeof(sStepNM));
        
        /* ������������ȫ�ֽڵ�    */
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWID,pFlowcfg->flowid);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWNAME,pFlowcfg->flowname);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWSN,itoa(pFlowcfg->flowsn));
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPID,DB_sStepID);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_EXTFLD1,pFlowcfg->extfld1);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_EXTFLD2,pFlowcfg->extfld2);
        
        /*add by tuql 20150521 ֧�ּ�Ⱥ������Ƕ��  BEGIN*/
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPSN,itoa(pFlowcfg->stepsn));
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPNAME,pFlowcfg->stepname);
        /*add by tuql 20150521 ֧�ּ�Ⱥ������Ƕ��  BEGIN*/
        ret = fprv_enumStepID(pFlowcfg->stepid, sStepNM);
        if( ret != 0 )
        {
            prv_FlowListFree();
            fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
            return COMPRET_FAIL;
        }
        
        LOG(LM_STD,Fmtmsg("BATCH: ���������ܿ�-����[%s],�����ʶ[%s],�������[%s],��������[%s]ʼ",\
            sFlowID,DB_sStepID, itoa(pFlowcfg->flowsn) , sStepNM),"INFO");
        COMP_SOFTSETXML(XMLNM_BATCH_STEPSN,itoa(pFlowcfg->flowsn) );
        COMP_SOFTSETXML(XMLNM_BATCH_STEPID,DB_sStepID );
        
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM batch_stepcfg WHERE \
            flowid='%s' AND stepid='%s'", sFlowID, DB_sStepID );
        if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            prv_FlowListFree();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            prv_FlowListFree();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        
        /* ��ȡ���̲�������  */
        for ( iAttribCount=0, jflag=0 ; ;iAttribCount++)
        {
            memset(&sdb_batch_stepcfg,0,sizeof(sdb_batch_stepcfg));
            if( ( iRet = DBFetch(cur, SD_BATCH_STEPCFG, NUMELE(SD_BATCH_STEPCFG), &sdb_batch_stepcfg, sErrmsg ) ) <= 0 )
            {
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ��ȡ���̲������Դ���ʧ��,[%s]", DCILastError() ),"ERROR");
                    jflag = -1;
                }
                break;
            }
        
            memset(sXmlNode,0,sizeof(sXmlNode));
            trim(DB_sStepID);
            trim(sdb_batch_stepcfg.attribid);
            trim(sdb_batch_stepcfg.attribvalue );
            snprintf(sXmlNode,sizeof( sXmlNode ),\
                "/batch/%s/%s",DB_sStepID,sdb_batch_stepcfg.attribid);
            
            /* added by yangdong 20121316  �������Զ�xml�ڵ�֧�� */
            /* modified by yangdong 20130618 sdb_batch_stepcfg.attribvalue �����޷���Ž������ַ������� 
            if(xml_ParseXMLString(lXmlhandle,sdb_batch_stepcfg.attribvalue,sizeof(sdb_batch_stepcfg.attribvalue))==FAIL)
             */
            memset( sAttribvalue ,0,sizeof( sAttribvalue ));
            strcpy( sAttribvalue, sdb_batch_stepcfg.attribvalue );
            if(xml_ParseXMLString(lXmlhandle, sAttribvalue, sizeof( sAttribvalue ))==FAIL)
            {
                LOG(LM_STD,Fmtmsg("BATCH: ��ȡ���̲������Դ���ʧ��,[%s]", sAttribvalue ),"ERROR");
                jflag = -2 ;
                break;
            }
            
            COMP_SOFTSETXML(sXmlNode, sAttribvalue );
            LOG(LM_DEBUG,Fmtmsg("  -->�����ܿش�������[%s][%s], val[%s]", sXmlNode, sdb_batch_stepcfg.attribid, sAttribvalue ),"DEBUG");
            /* end of mod 20130618 */
        }
        DCIFreeCursor(cur);
        LOG(LM_DEBUG,Fmtmsg("����������[%d], flowid[%s], stepid[%s]",\
            iAttribCount,sFlowID,DB_sStepID),"DEBUG");
        if(jflag < 0) 
        {
            prv_FlowListFree();
            LOG(LM_STD,Fmtmsg("BATCH: ��ȡ���̲������Դ���ʧ��,[%d]",jflag),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        /* ���õ����������̴��� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        memset(sStepFlow,0,sizeof(sStepFlow));
        snprintf(sXmlNode,sizeof( sXmlNode ),\
            "/batch/%s/%s",DB_sStepID,BATCH_ATTRIBUTE_CLLCM);
        COMP_SOFTGETXML(sXmlNode,sStepFlow);
        
        LOG(LM_STD,Fmtmsg("����[%s]����,[%s]���̿�ʼ<--",DB_sStepID,sStepFlow),"INFO");
        trim(sStepFlow);
        if( fpub_CallFlow(lXmlhandle,sStepFlow) != MID_SYS_SUCC)
        {
            iFlag=-2 ;
            COMP_SOFTGETXML(XMLNM_RESPCODE,flowStatus);
            LOG(LM_STD,Fmtmsg("BATCH: ����[%s]����ʧ��,����״̬[%s]",\
                sStepFlow,flowStatus),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_EXEC_FLOW,\
                Fmtmsg(MSG_BATCH_EXEC_FLOW,sStepFlow));
            break;
        }
        
        memset(sBuf,0,sizeof(sBuf));
        /* �ⲿ���븳ֵ 0�ɹ���1ʧ�ܡ�2���� */
        COMP_SOFTGETXML(XMLNM_BATCH_BDCGBZ,sBuf);
        LOG(LM_STD,Fmtmsg("<<<<<<����[%s]����,[%s]���̽���[%s]>>>>>>",DB_sStepID,sStepFlow, sBuf),"INFO");
        iBdcgbz=atoi(sBuf);
        ret=fprv_isZero(sBuf);
        if( ret == 0 )
        {
            continue;        
        }
        else if( iBdcgbz == 1 ) /* ����ʧ�� */
        {    
            iFlag=-2 ;
            break;
        }
        else if( iBdcgbz == 2 ) /* ���ش��� - ����ѭ��*/
        {
            iFlag=1;        
            break;
        }
        /* by yr 20120927 */
        else if( iBdcgbz == 3 ) /* �ȴ����� - ����ѭ��*/
        {
            iFlag=1;        
            break;
        }
        /* end */
        else
        {
            LOG(LM_STD,Fmtmsg("BATCH: ����ɹ���־�Ƿ�[%s]",sBuf),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);        
            fpub_SetMsg(lXmlhandle,MID_BATCH_BDCGBZ_FF,Fmtmsg(MSG_BATCH_BDCGBZ_FF,sBuf));
            iFlag = -1;
            break;
        }
    }
    prv_FlowListFree();
    LOG(LM_STD,Fmtmsg("BATCH: ���������ܿ�-����[%s],��������[%d]--����",sFlowID,iStepCount),"INFO");
    if(iFlag < 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/* �ͷ�������Դ */
void prv_StepListFree()
{                   
    if( t_step_flowList )
    {
        i_list_delete(&t_step_flowList);
    }
}
/************************************************************************
��̬�����������
�����������:SBATCH_STEPCTRL
�������:BATCH_STEPCTRL
�������: ����ҵ�񲽵㴥������
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
1   1-����   ���̱�ʶ              416XML�����ַ���     *         N     
2   1-����   ��ǰ��������          416XML�����ַ���     *         N   
3   1-����   �Ƿ�Ϊ�ϵ�            416XML�����ַ���     *         N     
4   1-����   ִ�к��������־      416XML�����ַ���     *         N   
�����  
0   �ɹ�
-1  ʧ��
-2  �����ظ�ִ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_STEPCTRL(HXMLTREE lXmlhandle)
{
    char errmsg[256];
    int  iSetpCount,iflag=0,iAttribCount;
    int  iParas,iStepFlag=0;
    char sXmlNode[128];
    char sStepFlow[128];
    char sBuf[255];
    char sAttribvalue[128];
    char sCurrentStep[51];
    int  iBreakPoint,iNextFlag,iBdcgbz,iRet;
    char flowStatus[10+1];
    char sStepSN[1+1];
    char sStepNM[16+1];
    int  iCurStep;
    char sStepNum[1+1];
    char sNextStepID[100];
    char sFlowID[51];
    char DB_sStepID[51];
    char sBdzt[1+1];    /* ����״̬ */
    char sRwzt[1+1];    /* ����״̬ */
    char sSql1[1024];
    char sErrmsg[512];
    CURSOR cur;
    BATCH_STEPCFG sdb_batch_stepcfg;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(4);
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"���̱�ʶ");
    pstrcopy(sFlowID,sBuf,sizeof(sFlowID));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"��ǰ��������")
    pstrcopy(sStepSN,sBuf,sizeof(sStepSN));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"�Ƿ��Ƕϵ�") /* 1 �ϵ� 2���� */
    iBreakPoint=atoi(sBuf);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"ִ�к��������־") /*(0ִ�У�1��ִ��)*/
    iNextFlag=atoi(sBuf);
    
    memset(sCurrentStep, 0, sizeof(sCurrentStep));
    memset(sStepNM, 0, sizeof(sStepNM));
    
    /* ö�ٲ�����Ϣ */
    fprv_enumStepSN(sStepSN,sCurrentStep,sStepNM);
    iCurStep = atoi(sStepSN);
    trim(sFlowID);
    
    /* ��ʼ�����̵��������� --B*/
    iSetpCount=fprv_initStepFlow(sFlowID,&t_step_flowList,iCurStep );
    if ( iSetpCount <=0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_FLOWCFG_NOFUND,MSG_BATCH_FLOWCFG_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* ��ʼ�����̵��������� --E*/
    
    /*  ����ǰ��ֵ 0 �ɹ�����������̣��ɹ���־δ��ֵ���  */
    COMP_SOFTSETXML( XMLNM_BATCH_BDCGBZ,"0" );

    /* ���̲���ѭ������ʼ --B*/
    for( pflowIter = i_list_begin(t_step_flowList); 
        pflowIter!= i_list_end(t_step_flowList); 
        pflowIter = i_list_iter_next(pflowIter) )
    {
        pFlowcfg = (BATCH_FLOWCFG *)(pflowIter->data);
        /* modified by guoliang 20130506 */
        strncpy(DB_sStepID, pFlowcfg->stepid, sizeof(DB_sStepID)-1);
        /* end */
        trim(DB_sStepID);
        if ( iStepFlag == 0)
        {
            /*  ������Ҫ���еĲ��� */
            if ( 0 != memcmp(sCurrentStep,DB_sStepID,strlen(sCurrentStep) ) )
            {
                continue; 
            }
            iStepFlag=1; 
            
            /* �ж��Ƿ��Ѵ����ϵ�,����,ʧ��,�ȴ������� */
            memset( sBdzt, 0, sizeof( sBdzt ));
            memset( sRwzt, 0, sizeof( sRwzt ));
            
            iRet = prv_Proc( lXmlhandle, sCurrentStep, iBreakPoint,sBdzt, sRwzt );
            if( iRet<0 )
            {
                prv_StepListFree();
                return COMPSTATUS_FAIL;
            }
            
            /* �ϵ�ͷ��� */
            if ( iBreakPoint == 1 ) 
            {
                /* modify by yr 20120827  */    
                /* �˲���״̬Ϊ����,������һ������ */
                if( sBdzt[0] == '3'  ||  sRwzt[0] == '3' )
                    continue;
                
                /* ��ȡ����������Ĵ���ʱ�� */
                iRet=fprv_enumNextStepID( sFlowID, sCurrentStep, "",sNextStepID);
                if( iRet != 0 )
                {
                    prv_StepListFree();
                    fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return -2;
                }
                
                /* �˴�����״̬Ϊ�ϵ�,����ڴ���ʱ���������һ�����㿪ʼִ��,������Ǿ��˳� */
                iRet=prv_clsj( lXmlhandle, sNextStepID );
                if ( iRet<0 )
                { 
                    /* ����״̬ */
                    prv_StepListFree();
                    return COMPSTATUS_FAIL;
                }
                /* end */  
                continue;
            }
            /* add by yr 20120925  ʧ��,�ȴ� */
            if ( iBreakPoint==2 )
            {
                /* �˲���״̬Ϊ�ȴ�,���жϿ�ʼ����ʱ�����ִ�д˲��� */
                if( sBdzt[0] == '4'  ||  sRwzt[0] == '9' )
                { 
                    iRet=prv_clsj( lXmlhandle, sCurrentStep );
                    if ( iRet<0 )
                    { 
                        prv_StepListFree();
                        return COMPSTATUS_FAIL;
                    }
                    COMP_SOFTSETXML( "/batch/req/sjtjflag","1"); 
                }
                /* ������������ֱ�ӿ�ʼ�ظ����иò��� */
            }
            /* end */
        }
        
        memset(sStepNM, 0, sizeof(sStepNM));
        memset(sStepSN, 0, sizeof(sStepSN));
        
        /* ������������ȫ�ֽڵ�  --B*/
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWID,pFlowcfg->flowid);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWNAME,pFlowcfg->flowname);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWSN,itoa(pFlowcfg->flowsn));
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPID,DB_sStepID);
        fprv_enumStepID(pFlowcfg->stepid, sStepNM);
        
        LOG(LM_STD,Fmtmsg("STEP: ���������ܿ�-����[%s],�����ʶ[%s],��������[%s]--��ʼ",\
            sFlowID,DB_sStepID,sStepNM),"INFO");
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPSN,sStepSN);
        COMP_SOFTSETXML(XMLNM_BATCH_STEPSN,sStepSN);
        COMP_SOFTSETXML(XMLNM_BATCH_STEPID,DB_sStepID);
        
        /* ��ȡ���̲������� --B */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM batch_stepcfg \
            WHERE flowid='%s' AND stepid='%s'", sFlowID, DB_sStepID );
        if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            prv_StepListFree();
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
            DCIFreeCursor(cur);
            prv_StepListFree();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        
        for (iAttribCount=0; ;iAttribCount++)
        {
            memset(&sdb_batch_stepcfg,0,sizeof(sdb_batch_stepcfg));
            if( ( iRet = DBFetch(cur, SD_BATCH_STEPCFG, NUMELE(SD_BATCH_STEPCFG), &sdb_batch_stepcfg, sErrmsg ) ) < 0 )
            { 
                prv_StepListFree();
                fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( iRet == 0 )
                	break;
            
            memset(sXmlNode,0,sizeof(sXmlNode));
            trim(DB_sStepID);
            trim(sdb_batch_stepcfg.attribid);
            sprintf(sXmlNode,"/batch/%s/%s",DB_sStepID,sdb_batch_stepcfg.attribid);
            
            /* added by yangdong 20121316  �������Զ�xml�ڵ�֧�� */
            /* modified by yangdong 20130618 sdb_batch_stepcfg.attribvalue �����޷���Ž������ַ������� 
            	 if(xml_ParseXMLString(lXmlhandle,sdb_batch_stepcfg.attribvalue,sizeof(sdb_batch_stepcfg.attribvalue))==FAIL)
             */
            memset( sAttribvalue ,0,sizeof( sAttribvalue ));
            strcpy( sAttribvalue, sdb_batch_stepcfg.attribvalue );
            if(xml_ParseXMLString(lXmlhandle, sAttribvalue, sizeof( sAttribvalue ))==FAIL)
            { 
                prv_StepListFree();
                fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            
            COMP_SOFTSETXML(sXmlNode, sAttribvalue );
            LOG(LM_DEBUG,Fmtmsg("  -->�����ܿش�������[%s][%s], val[%s]", sXmlNode, sdb_batch_stepcfg.attribid, sAttribvalue ),"DEBUG");
            /* end of mod 20130618 */
        }
        DCIFreeCursor(cur);
        
        LOG(LM_STD,Fmtmsg("  -->�����ܿش���������[%d], flowid[%s], stepid[%s]",\
            iAttribCount,sFlowID,DB_sStepID),"INFO");
        
        memset(sXmlNode,0,sizeof(sXmlNode));
        trim(DB_sStepID);
        sprintf(sXmlNode,"/batch/%s/%s",DB_sStepID,BATCH_ATTRIBUTE_CLLCM);
        memset(sStepFlow,0,sizeof(sStepFlow));
        COMP_SOFTGETXML(sXmlNode,sStepFlow);
        /* Ĭ������ */
        if ( 0 == sStepFlow[0])
        {
            sprintf(sStepFlow,"flow_batch_step_%s",DB_sStepID);      
        }
        
        LOG(LM_STD,Fmtmsg("   -->��������[%s]����,[%s]���̿�ʼ<--     ",DB_sStepID,sStepFlow),"INFO")
        
        /* ���õ����������̴��� --B*/
        trim(sStepFlow);
        if(fpub_CallFlow(lXmlhandle,sStepFlow)!=MID_SYS_SUCC)
        {
            prv_StepListFree();
            LOG(LM_STD,Fmtmsg("BATCH: ����[%s]����ʧ��",sStepFlow ),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,MID_BATCH_EXEC_FLOW,Fmtmsg(MSG_BATCH_EXEC_FLOW,sStepFlow));
            return COMPRET_FAIL ;
        }
        LOG(LM_STD,Fmtmsg("<<<<<<��������[%s]����,[%s]���̽���>>>>>>",DB_sStepID,sStepFlow),"INFO");
        
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_BDCGBZ,sBuf); /*0�ɹ���1ʧ�ܡ�2����*/
        iBdcgbz=atoi(sBuf);
        iRet=fprv_isZero(sBuf);
        if ( iRet == 0 )
        {
            if ( iNextFlag == 1) 
            {
                /*  ��ִ����һ�� */
                break;    
            }
            continue;    
        }
        else if ( iBdcgbz == 1 )
        {  
            /* ����ɹ���־�� ʧ�� */
            iflag=-2 ;
            break;
        }
        else if ( iBdcgbz == 2 )
        {
            /* ����ɹ���־�� ����  */
            iflag=1;    
            break;
        }
        /* by yr 20120927 */
        else if( iBdcgbz == 3 ) /* �ȴ����� - ����ѭ��*/
        {
            iflag=1;        
            break;
        }
        /* end */
        else
        {
            iflag = -3;
            LOG(LM_STD,Fmtmsg("BATCH: ����ɹ���־�Ƿ�[%s]",sBuf),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_BDCGBZ_FF,Fmtmsg(MSG_BATCH_BDCGBZ_FF,sBuf));
        }
    } /* ����ѭ������ */
    prv_StepListFree();
    LOG(LM_STD,Fmtmsg("BATCH: ���������ܿ�-����[%s],��������[%d]--����",sFlowID,iSetpCount),"INFO");
    if (iflag < 0) 
    {
        LOG(LM_STD,Fmtmsg("  -->����[%s],����[%s]ִ��ʧ��,[%d]",sFlowID,DB_sStepID,iBdcgbz),"ERROR");
        return COMPRET_FAIL;
    }           
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_BREAK_CTRL
�������:BATCH_BREAK_CTRL
�������: ����ҵ��ϵ�����
�������:
��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
1    1-����   ������Ӧ��  416XML�����ַ���           N
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_BREAK_CTRL(HXMLTREE lXmlhandle)
{
    char    sStepID[21];
    char    sStepSN[2];
    char    sStepStatus[2];
    char    sTaskStatus[2];
    char  sBreak[1+1];
    char  sBuf[256];
    char  xmlNode[256]; 
    int   i,iParas;
    int   ret;
    int   iDDFlag = -1;     /* �ϵ��־ */
    int   /*iDdsj_ms=0,*/ iDdsj=0;
    char  sNextStepID[100];
    char  sAstStep[2+1];
    char  sFinalStep[100];
    char  sKsclsj[6+1];
    char  sFlowSn[2+1];
    char sFlowID[51];
    /*int   iAuto=60;    �Զ���ѵ���ʱ�� 60 Ϊ��λ */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")

    /* �����Ƿ�ɹ���ʶ --B*/
#if 0
    �����жϲ���ɹ���־,SBATCH_BREAK_CTRLֻ�ڳɹ�������
    COMP_HARDGETXML( XMLNM_RESPCODE, sBuf );
    pstrcopy(respCode,sBuf,sizeof(respCode));
    ret=fprv_isZero(respCode);
    if ( ret != 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
#endif
        return COMPRET_FAIL;  
    }
#endif

    /* ��ȡ��ǰ����ϵ����� */
    memset(sBreak, 0, sizeof(sBreak));
    memset(sStepID, 0, sizeof(sStepID));
    COMP_HARDGETXML(XMLNM_BATCH_FLOWCFG_STEPID ,sStepID);
    trim(sStepID);
    if ( strlen(sStepID) <=0 )
    {
        LOG(LM_STD, Fmtmsg("��ȡ��������: ��ǰ���㲻����[%s]=[%s]",\
            XMLNM_BATCH_FLOWCFG_STEPID,sStepID), "ERROR");
        return COMPRET_FAIL;
    }
    memset(sFlowSn, 0, sizeof(sFlowSn));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_FLOWCFG_FLOWSN , sBuf);
    pstrcopy(sFlowSn, sBuf, sizeof(sFlowSn));
    /* added by yangdong 20121115 ��ȡ��ǰ���̱�ʶ�����ڻ�ȡ��һ���� */
    memset(sFlowID, 0, sizeof(sFlowID));
    COMP_HARDGETXML(XMLNM_BATCH_RUNCTRL_FLOWID,sFlowID);
    trim(sFlowID);
    
    memset(xmlNode, 0, sizeof(xmlNode));
    snprintf(xmlNode, sizeof(xmlNode), "/batch/%s/%s",\
        sStepID, BATCH_ATTRIBUTE_DDBZ );
    COMP_SOFTGETXML(xmlNode,sBuf);
    trim( sBuf );
    snprintf( sBreak, sizeof( sBreak ), "%s", sBuf );

/*
          ����    ����   �ɹ���־
    �ϵ㣺3����   2�ϵ�  2����
    ���أ�3����   3����  2����
    ������9����   1����  0�ɹ�
*/    
    if ( sBreak[0] == BATCH_ATTRIBUTE_DDBZ_BREAK ) /* �ϵ� */
    {
        /* ����״̬ */
        strcpy( sTaskStatus, BATCH_TASK_STATUS_S_RETURN );
        /* ����״̬ */
        strcpy( sStepStatus, BATCH_STEP_STATUS_S_BREAK );
        /* modified by yangdong 20121105 ����״̬Ϊ���أ��ϵ����Զ����񴥷� */
        /* 
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_SUCC);
         */
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_RETURN);
    }
    else if ( sBreak[0] == BATCH_ATTRIBUTE_DDBZ_RETURN ) /* ���� */
    {
        /* ����״̬ */
        strcpy( sTaskStatus, BATCH_TASK_STATUS_S_RETURN );
        /* ����״̬ */
        strcpy( sStepStatus, BATCH_STEP_STATUS_S_RETURN );
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_RETURN);
    }
    /* Ĭ������-�޶ϵ� */
    else
    {
        /* ����״̬ */
        strcpy( sTaskStatus, BATCH_TASK_STATUS_S_RUNNING );
        /* ����״̬ */
        strcpy( sStepStatus, BATCH_STEP_STATUS_S_END );
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_SUCC);
    }

    /*  ������������idת��  */
    ret = fprv_enumStepNum( sStepID, sStepSN );
    if( ret != 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* added by yangdong 20121115 ��ȡ��һ���� */
    /* �ж��Ƿ����һ������ */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_FINAL_STEP, sBuf );
    pstrcopy(sFinalStep,sBuf,sizeof(sFinalStep));
    trim( sFinalStep );

    if( strcmp( sStepID , sFinalStep ) != 0 )  /* ��ǰ���㲻�����һ������ */
    {
        /* ��ȡ��һ������ */
        memset(sNextStepID, 0x00, sizeof(sNextStepID));
        ret=fprv_enumNextStepID( sFlowID, sStepID, sFlowSn, sNextStepID);
        if( ret != 0 )
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -2;
        }
      
        /* �����ύ��������⴦�� */
        /* ������������������ύʱ�䣬������ʱ��ʱ��Ϊ׼�������ѯ�������ԣ������ж��ռ�ҹ������*/
        if( strcmp( sNextStepID , BATCH_STEPNM_SJTJ ) == 0 )
        {
            /* ��ȡ����������Ĵ���ʱ�� */
            COMP_SOFTGETXML( XMLNM_BATCH_SJTJ_TIME, sBuf );
            trim( sBuf );
            if( strlen( sBuf ) == 6 ) /* �ж��Ƿ�Ϸ��������ύ����ʱ�� */
            {
                pstrcopy(sKsclsj,sBuf,sizeof(sKsclsj));
                iDDFlag = 1;
            }
            else                      /* �ж��Ƿ�ҹ������ */
            {
                /* ȡ���׷�ʽ */
                COMP_SOFTGETXML( XMLNM_APP_CPXX_JYFS, sBuf );
                trim( sBuf );
                if( sBuf[0] == '4' || sBuf[0] == '7' ) /* ���׷�ʽ: 4-ҹ������  7-������ҹ������ */
                {
                    /* ��ȡҹ����������ʱ�� */
                    COMP_SOFTGETXML( XMLNM_BATCH_NIGHT_TIME, sBuf );
                    trim( sBuf );
                    if( strlen( sBuf ) == 6 ) /* �ж��Ƿ�Ϸ��������ύ����ʱ�� */
                    {
                        pstrcopy(sKsclsj,sBuf,sizeof(sKsclsj));
                        iDDFlag = 1;
                    }else
                    {
                        /* ��ȡҹ����������ʱ�� */
                        COMP_SOFTGETXML( "/batch/sjtj/ksclsj", sBuf );
                        trim( sBuf );
                        if( strlen( sBuf ) == 6 ) /* �ж��Ƿ�Ϸ��������ύ����ʱ�� */
                        {
                            pstrcopy(sKsclsj,sBuf,sizeof(sKsclsj));
                            iDDFlag = 1;
                        }
                    }
                }
            }
            if( iDDFlag == 1 )
            {
                /* ǿ�����öϵ��־ */
                sBreak[0] = BATCH_ATTRIBUTE_DDBZ_BREAK ;
                /* ����״̬ */
                strcpy( sTaskStatus, BATCH_TASK_STATUS_S_RETURN );
                /* ����״̬ */
                strcpy( sStepStatus, BATCH_STEP_STATUS_S_BREAK );
                COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_RETURN);
            }
        }
        if( ( sBreak[0] == BATCH_ATTRIBUTE_DDBZ_BREAK ) && ( iDDFlag != 1 ) ) /* �ϵ㴦�� */
        {
            /* add by yr 20120921 ȡ��ʼ����ʱ�� */
            /* ȡ�ϵ�ʱ�� */
            memset(xmlNode, 0, sizeof(xmlNode));
            snprintf(xmlNode, sizeof(xmlNode), "/batch/%s/ddsj",sStepID );
            COMP_SOFTGETXML(xmlNode,sBuf);
            trim( sBuf );
            iDdsj= atoi( sBuf );
            /* �ϵ�ʱ�䲻�ܴ���ϵͳ��ϵ�ʱ�䣬Ĭ��24Сʱ86400�� */
            if( iDdsj > BATCH_MAX_BREAK_SECONDS )
                iDdsj = BATCH_MAX_BREAK_SECONDS;
            
            memset( sKsclsj, 0x00, sizeof( sKsclsj ) );
            prv_GetKsclsj( lXmlhandle, sNextStepID, iDdsj, sKsclsj );
        }
    }
    /*mod by tuql 20160606 begin
     * ����:201606060219
     */
    DCIBegin();
    memset(sAstStep, 0x00, sizeof(sAstStep));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_FZBD, sAstStep)
    if ( strcmp(sAstStep, BATCH_STEP_ASTSTEP_WRET) == 0 ||
         strcmp(sAstStep, BATCH_STEP_ASTSTEP_RETURN) == 0 
        )
    {/*����Ƕ��--������*/
        /* �������̸��²��� */
    }else
    {/*������������*/
        if( fprv_batch_upd_plrw( lXmlhandle, sStepSN, sAstStep, sStepStatus, sTaskStatus, sBreak, sKsclsj ) != 0 )
        {
            DCIRollback();/*add by tuql 20160606 ����:201606060219 */
            return COMPSTATUS_FAIL;
        }
    }

    if( fprv_batch_upd_plrwbd( lXmlhandle, sStepStatus, sStepSN ) != 0 )
    {
        DCIRollback();/*add by tuql 20160606 ����:201606060219 */
        return COMPSTATUS_FAIL;
    } 

    /* �����Ƿ�ϵ㣬���浱ǰ�ڵ���Ϣ */
    if( fprv_export_break( lXmlhandle ) != 0 )
    {
        DCIRollback();/*add by tuql 20160606 ����:201606060219 */
        return COMPSTATUS_FAIL;
    }
    DCICommit();/*add by tuql 20160606 ����:201606060219 */
    if( ( sBreak[0] == BATCH_ATTRIBUTE_DDBZ_BREAK ) && ( iDDFlag != 1 ) ) /* �ϵ㴦�� */
    {       
        /* modified by yangd 20121105 �ϵ�ʱ��С���Զ�������ѵʱ�䣬ֱ�Ӵ��� */
        if ( iDdsj <= BATCH_MIN_BREAK_AUTO )
        {
            sleep( iDdsj );
            ret = prv_BreakProc( lXmlhandle, sStepID  );
            if( ret < 0 )  /* ����ʧ�� ���Ѵ����ϵ� */
            {
                return COMPSTATUS_FAIL;
            }
            
            strcpy( sStepStatus, BATCH_STEP_STATUS_S_END );
            COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_SUCC);
            
            DCIBegin();/*add by tuql 20160606 ����:201606060219 */
            if( fprv_batch_upd_plrw( lXmlhandle, sStepSN, sAstStep, sStepStatus, sTaskStatus, sBreak, sKsclsj ) != 0 )
            {
                DCIRollback();/*add by tuql 20160606 ����:201606060219 */
                return COMPSTATUS_FAIL;
            }
            if( fprv_batch_upd_plrwbd2( lXmlhandle, sStepStatus, sStepSN ) != 0 )
            {
                DCIRollback();/*add by tuql 20160606 ����:201606060219 */
                return COMPSTATUS_FAIL;
            }
            DCICommit();/*add by tuql 20160606 ����:201606060219 */
        }
    }
    
    fpub_SetCompStatus(lXmlhandle, COMPRET_SUCC );

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    return COMPRET_SUCC;  
}

/* �ͷ�������Դ */
void batch_auditinglistFree()
{                        
    if( t_auditingList )
    {
        i_list_delete(&t_auditingList);
    }
}

/************************************************************************
��̬�����������
�����������:SBATCH_CHECKRULES
�������:BATCH_CHECKRULES
�������: ����ҵ��У��������
�������:
��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_CHECKRULES(HXMLTREE lXmlhandle)
{
    char sBuf[256+1],sShbs[50+1],sFlowname[128],sPath[128+1];
    int iRet,i,iFlag;
    int iAudiCount=0;
    IRESULT (*func)(HXMLTREE);
    void *dhl=NULL;
    char sFuncID[50+1];    
    char sFuncname[50+1],sDllname[32+1]; 
    char sSql1[1024];
    char sErrmsg[512];
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");

    memset(sFuncname,0,sizeof(sFuncname));
    memset(sDllname,0,sizeof(sDllname));
    memset(sShbs,0,sizeof(sShbs));
    memset(sPath,0,sizeof(sPath));
    memset(sFlowname,0,sizeof(sFlowname));
    
    /* ȡ������˱�ʶ���� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_BATCH_SJSH_SHBS, sBuf );
    trim(sBuf);
    pstrcopy(sShbs,sBuf,sizeof(sShbs));
    
    /* ����Ҫ��� */
    if( strlen(sShbs) <= 1 )
    {
        LOG(LM_STD, Fmtmsg("BATCH: �������->��ҵ����Ҫ���[%s]\n",sShbs),"INFO");
        /* ���óɹ���ʶ */
        fpub_SetMsg(lXmlhandle,MID_SYS_SUCC,MSG_SYS_SUCC);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)), "DEBUG");
#endif
        return COMPRET_SUCC;
    }

    /* ��ʼ��������ñ��������� */
    trim(sShbs);
    iAudiCount=fprv_initAuditingfunc(sShbs,&t_auditingList);
    if( iAudiCount <=0 )
    {
        LOG(LM_STD, Fmtmsg("BATCH: �������->��˺���������"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_AUDITING_NOFUND,\
            Fmtmsg(MSG_BATCH_AUDITING_NOFUND,sShbs));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* �������ѭ������ʼ */
    for( pauditingIter = i_list_begin(t_auditingList); 
        pauditingIter!= i_list_end(t_auditingList); 
        pauditingIter = i_list_iter_next(pauditingIter) )
    {
        
        pAuditingFunc = (BATCH_AUDITINGFUNC *)(pauditingIter->data); 
        trim(pAuditingFunc->funcid);
        trim(pAuditingFunc->auditingid);
        trim(pAuditingFunc->snote);
        
        memset(sFuncID, 0, sizeof(sFuncID));
        strncpy(sFuncID, pAuditingFunc->funcid, sizeof(sFuncID)-1);
        /* �������ݽڵ�  */
        COMP_HARDSETXML(XMLNM_BATCH_AUDITING_AUDIID,pAuditingFunc->auditingid);
        COMP_HARDSETXML(XMLNM_BATCH_AUDITING_AUDISN,itoa(pAuditingFunc->auditingsn));
        COMP_HARDSETXML(XMLNM_BATCH_AUDITING_FUNCID,pAuditingFunc->funcid);
        COMP_HARDSETXML(XMLNM_BATCH_AUDITING_SHSBBZ,pAuditingFunc->shsbbz);
        
        LOG(LM_DEBUG,Fmtmsg("BATCH: �������У�麯��ID[%s]",pAuditingFunc->funcid),"DEBUG");
        
        /* ��ȡУ�麯��ע�� */
        snprintf( sSql1, sizeof( sSql1 ) , "SELECT funcrun,funcfile FROM BATCH_AUDITINGREG WHERE funcid='%s'", sFuncID );
        iRet = DBSelectToMultiVar( sErrmsg, sSql1, sFuncname, sDllname) ;
        if( iRet < 1 )
        {
            batch_auditinglistFree();
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_AUDITINGREG_NOFUND,\
                Fmtmsg(MSG_BATCH_AUDITINGREG_NOFUND,sFuncID));
            LOG(LM_STD,Fmtmsg("BATCH: ������˺���δ�ҵ�[%s],���ȵǼ�!!!",\
                sFuncID),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        trim(sDllname);
        trim(sFuncname);
        memset(sPath, 0, sizeof(sPath));
        snprintf(sPath,sizeof(sPath), "%s/shlib/%s",getenv("HOME"),sDllname);
        LOG(LM_DEBUG,Fmtmsg("BATCH: ������˶�̬���ӿ�[%s]",sPath),"DEBUG");
        dhl = dlopen(sPath, RTLD_LAZY);
        if( dhl== NULL)
        {
            batch_auditinglistFree();
            fpub_SetMsg(lXmlhandle,MID_BATCH_SO_OPEN,MSG_BATCH_SO_OPEN);
            LOG(LM_STD,Fmtmsg("BATCH: ������˴򿪶�̬���ӿ�[%s]ʧ��",\
                sDllname),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        LOG(LM_DEBUG,Fmtmsg("BATCH:    ������˺���[%s]",sFuncname),"DEBUG");
        func = (IRESULT(*)(HXMLTREE))dlsym(dhl,sFuncname);
        if(func == NULL )
        {
            batch_auditinglistFree();
            dlclose(dhl);
            if( dlerror() )
            {
                LOG(LM_STD,Fmtmsg("BATCH:�رն�̬���ӿ�[%s][%s]",\
                    sDllname,dlerror()),"ERROR")
            }
            fpub_SetMsg(lXmlhandle,MID_BATCH_HSRK_NOFUND,MSG_BATCH_HSRK_NOFUND);
            LOG(LM_STD,Fmtmsg("BATCH:�������,���Һ���[%s]���ʧ��",\
                sFuncname),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        iRet=(*func)(lXmlhandle);
        #if 0
        if(iRet<0)
        {
            batch_auditinglistFree();
            dlclose(dhl);
            if( !dlerror() )
            {
                LOG(LM_STD,Fmtmsg("BATCH:�رն�̬���ӿ�[%s][%s]",\
                    sDllname,dlerror()),"ERROR");
                /* by yr 20121008 */
                fpub_SetMsg(lXmlhandle,MID_BATCH_JYHS_FAIL,MSG_BATCH_JYHS_FAIL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            }
            /* modified by yr at 20121008 �ú����еĴ�����Ա����� */
            /*
            	 fpub_SetMsg(lXmlhandle,MID_BATCH_JYHS_FAIL,MSG_BATCH_JYHS_FAIL);
             */
            LOG(LM_STD,Fmtmsg("BATCH:У�麯��[%s]У��ʧ��",sFuncname),"ERROR");
            /*
            	 fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             */
            return -1; 
        }
        #endif
        if(iRet<0)
        {
            batch_auditinglistFree();
            dlclose(dhl);
            LOG(LM_STD,Fmtmsg("BATCH:У�麯��[%s]У��ʧ��",sFuncname),"ERROR");
            return -1; 
        }
        dlclose(dhl);
        if( dlerror() )
        {
            LOG(LM_STD,Fmtmsg("BATCH:�رն�̬���ӿ�[%s][%s]",\
                sDllname, dlerror() ), "ERROR")
        }
    }
    
    batch_auditinglistFree();
    LOG(LM_STD,Fmtmsg("������˺�������[%d]",iAudiCount),"INFO");
    
    /* ���óɹ���ʶ */
    fpub_SetMsg(lXmlhandle,MID_SYS_SUCC,MSG_SYS_SUCC);
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");

    return COMPRET_SUCC;
}

/***************************************************************************
	�ϵ㴦��
 ****************************************************************************/
int  prv_BreakProc(HXMLTREE lXmlhandle, char* sStepID  )
{
    char sBuf[128];
    int  iRet;
    char sStepNum[1+1];
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sSql1[1024];
    char sErrmsg[512];
    char sBdzt[1+1];    /* ����״̬ */
    char sRwzt[1+1];    /* ����״̬ */
    char sDqbdNew[1+1]; /* ��ǰʵ�ʲ��� */
    
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf); 
    pstrcopy( sPkrq,sBuf,sizeof( sPkrq ) );
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf); 
    pstrcopy( sPtpch,sBuf,sizeof( sPtpch ) );
    
    /* ��ȡ��ǰ����״̬ */
    snprintf( sSql1, sizeof( sSql1 ), "SELECT dqbd, bdzt, rwzt FROM batch_plrw\
        WHERE pkrq='%s' AND ptpch='%s' ", sPkrq, sPtpch );
    iRet = DBSelectToMultiVar( sErrmsg, sSql1, sDqbdNew, sBdzt, sRwzt  );
    if( iRet < 1 )        
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_PLRW,\
            Fmtmsg(MSG_BATCH_SEL_PLRW,-1));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* ȡ����� */
    iRet = fprv_enumStepNum( sStepID, sStepNum );
    if( iRet != 0 )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    trim( sDqbdNew );
    trim( sStepNum );
    /* �Ƚϵ�ǰ������ */
    if( sStepNum[0] != sDqbdNew[0]  )
    {
        /* ���㲻һ�£����������Ѵ��� */
        LOG(LM_STD,Fmtmsg("BATCH: ����ҵ����㲻һ��[%s][%s]",\
            sStepNum, sDqbdNew ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_BREAK_LAUNCHED,MSG_BATCH_BREAK_LAUNCHED );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
        
    }
    /* modified by yangdong 20121116 rwzt����Ϊ ����״̬
    if( (sBdzt[0] != '2' ) || (sRwzt[0] != '9'  ))
     */
    if( sBdzt[0] != '2' )
    {
        /* ״̬��Ϊ�ϵ㣬�����Ѵ��� */
        LOG(LM_STD,Fmtmsg("BATCH: ����ҵ��״̬[%s] ����״̬[%s]",sRwzt, sBdzt ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_BREAK_LAUNCHED,MSG_BATCH_BREAK_LAUNCHED );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    return 0 ;
}

/***************************************************************************
��ǰ���д���
****************************************************************************/
int  prv_Proc(HXMLTREE lXmlhandle, char* sStepID, int iBreakPoint, char * sBdZt, char * sRwZt )
{
    char sBuf[128];
    int  iRet;
    char sStepNum[1+1];
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sBdzt[1+1];    /* ����״̬ */
    char sRwzt[1+1];    /* ����״̬ */
    char sDqbdNew[1+1]; /* ��ǰʵ�ʲ��� */
    char sErrmsg[512];
    char sSql1[1024];
    
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf); 
    pstrcopy( sPkrq,sBuf,sizeof( sPkrq ) );
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf); 
    pstrcopy( sPtpch,sBuf,sizeof( sPtpch ) );
    
    /* ��ȡ��ǰ����״̬ */
    snprintf( sSql1, sizeof( sSql1 ), "SELECT dqbd, bdzt, rwzt FROM batch_plrw\
        WHERE pkrq='%s' AND ptpch='%s' ", sPkrq, sPtpch );
    iRet = DBSelectToMultiVar( sErrmsg, sSql1, sDqbdNew, sBdzt, sRwzt  );
    if( iRet < 1 )        
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_PLRW,\
            Fmtmsg(MSG_BATCH_SEL_PLRW,-1));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* ȡ����� */
    iRet = fprv_enumStepNum( sStepID, sStepNum );
    if( iRet != 0 )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    trim( sDqbdNew );
    trim( sStepNum );
    /* �Ƚϵ�ǰ������ */
    if( sStepNum[0] != sDqbdNew[0]  )
    {
        /* ���㲻һ�£����������Ѵ��� */
        LOG(LM_STD,Fmtmsg("BATCH: ����ҵ����㲻һ��[%s][%s]",\
            sStepNum, sDqbdNew ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_BREAK_LAUNCHED,MSG_BATCH_BREAK_LAUNCHED );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;    
    }
    if( iBreakPoint==1 )  /* �ϵ� */
    {
        if( ( sBdzt[0] != '2' && sBdzt[0] != '3' ) || ( sRwzt[0] != '9' && sRwzt[0] != '3' ))
        {
            /* ״̬�Ѿ��ı�,�����Ѵ��� */
            LOG(LM_STD,Fmtmsg("BATCH: ����ҵ��״̬[%s] ����״̬[%s]",sRwzt, sBdzt ),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_BREAK_LAUNCHED,MSG_BATCH_BREAK_LAUNCHED );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    if( iBreakPoint==2 ) /* ���� */
    {
        if( (  sBdzt[0] != '0' && sBdzt[0] != '4' ) || (sRwzt[0] != '0' && sRwzt[0] != '9' ))
        {
            /* mod by yangdong 20121108 �ɹ��ظ�����ʱ */
            if(  sBdzt[0] == '1' && sRwzt[0] == '1' ) 
                ;
            else
            {
                /* ״̬�Ѿ��ı�,�����Ѵ��� */
                LOG(LM_STD,Fmtmsg("BATCH: ����ҵ��״̬[%s] ����״̬[%s]",sRwzt, sBdzt ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_BATCH_LAUNCHED,MSG_BATCH_LAUNCHED );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }
    strcpy( sBdZt, sBdzt );
    strcpy( sRwZt, sRwzt );
    
    return 0 ;
}

/************************************************************************
��̬�����������
�����������:SBATCH_AUTOTASK
�������: BATCH_AUTOTASK
�������: ����ҵ���Զ����񴥷�����(�ϵ�����ʧ��������)
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
1   1-����   ���̱�ʶ              416XML�����ַ���     *         N     
2   1-����   ��ǰ��������          416XML�����ַ���     *         N   
3   1-����   �Ƿ�Ϊ�ϵ�            416XML�����ַ���     *         N     
4   1-����   ִ�к��������־      416XML�����ַ���     *         N   
�����  
0   �ɹ�
-1  ʧ��
-2  �����ظ�ִ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_AUTOTASK(HXMLTREE lXmlhandle)
{
    char errmsg[256];
    int  iSetpCount,/*iflag=0,*/iAttribCount;
    int  iParas/*,iStepFlag=0*/;
    char sBuf[255];
    char sSql[512];
    char sSql1[1024];
    char sPkrq[8+1];
    char sKsrq[8+1];  /* ��ʼ���ڣ�Ĭ��ȡ��ǰ����ǰһ�� */
    char sCurrTime[6+1];  /* ��ǰϵͳʱ�� */
    char sDqbd[1+1];    /* ��ǰ���� */
    char sBdzt[1+1];    /* ����״̬ */
    char sRwzt[1+1];    /* ����״̬ */
    char sDqbdNew[1+1]; /* ��ǰʵ�ʲ��� */
    int  iBreakPoint,iRet;
    int  iClsbcs = 0;  /* ����ʧ�ܴ��� */
    int  iSjtj = 0;    /* �����ύ������ */
    int  iInterval = 0;    /* �����ύ������ */
    int  iClcs;         /* ���㴦����� */
    char sErrmsg[512];
    CURSOR cur;
    BATCH_PLRW sdb_batch_plrw;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(3);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������1 �ϵ� 2 ʧ������ Ĭ��ȫ��"); 
    iBreakPoint=atoi(sBuf);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"��������"); 
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"��ʼ����"); 
    pstrcopy(sKsrq,sBuf,sizeof(sKsrq));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEP_FAIL,sBuf); /* ʧ�����Դ��� */
    iClsbcs=atoi( sBuf );
    if( iClsbcs <= 0 )
        iClsbcs = BATCH_MAX_STEP_REPEAT; /* Ĭ��ʧ����������5 */
    
    /* ��ǰϵͳʱ�� */
    memset(sCurrTime,0,sizeof(sCurrTime));
    pstrcopy( sCurrTime, GetSysTime(), sizeof( sCurrTime ) );
    
    /* ��ѯ��Ҫ��������� */    
    memset( sSql, 0x00, sizeof( sSql ) );
    /* ����״̬ :  0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ�����  X ���� C���� */ 
    if( iBreakPoint == 1 ) /* �ϵ����� */
        snprintf(sSql,sizeof(sSql),"SELECT * FROM batch_plrw \
            WHERE  bdzt='2' AND clsj<='%s' AND rwzt='3' \
            AND pkrq>='%s'  and pkrq<='%s' ORDER BY taskpri desc", sCurrTime, sKsrq, sPkrq );
    else if( iBreakPoint == 2 )  /* ʧ������ */
        snprintf(sSql,sizeof(sSql),"SELECT * FROM batch_plrw \
            WHERE bdzt='0' AND rwzt='0' AND pkrq>='%s' AND pkrq<='%s' \
            ORDER BY taskpri desc", sKsrq, sPkrq );
    else  /* ʧ�ܻ��߶ϵ����� Ĭ�� */
        snprintf(sSql,sizeof(sSql),"SELECT * FROM batch_plrw \
            WHERE ( ( bdzt='0' AND rwzt='0' ) OR  ( bdzt='2' AND clsj<='%s'  AND rwzt='3' ) ) \
            AND pkrq>='%s' and pkrq<='%s' ORDER BY taskpri desc", sCurrTime, sKsrq, sPkrq );

    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    while( ( iRet = DBFetch(cur, SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), &sdb_batch_plrw, sErrmsg ) ) > 0 )
    {
        /* ����������Ϣ��ֵ */
        trim( sdb_batch_plrw.ywbh );
        
        COMP_SOFTSETXML( "/batch/req/pkrq", sdb_batch_plrw.pkrq );
        COMP_SOFTSETXML( "/batch/req/ptpch", sdb_batch_plrw.ptpch );
        COMP_SOFTSETXML( "/batch/req/ywbh", sdb_batch_plrw.ywbh );
        COMP_SOFTSETXML( "/batch/req/dqbd", sdb_batch_plrw.dqbd );
        
        if( sBdzt[0] == '2' ) /* �ϵ����񣬵��� 910004 */
        {
            COMP_SOFTSETXML( "/batch/req/jydm", "910004" );
            if( sDqbd[0] == '2' )
            {
                /* ���������ύ�ļ���ڼ䣬����һ��ɨ�������ڣ���Ҫ�ύ������������
                	 ��Ҫ���ڿ���ҹ��������ʱ�򣬺��Ĳ�����������
                	 �ռ�������һ�㲻���������ύǰ���öϵ� */
                if( iSjtj > 1 )
                {
                    memset( sBuf, 0x00, sizeof( sBuf ) );
                    COMP_SOFTGETXML( "/batch/sjtj/interval", sBuf );
                    iInterval = atoi( sBuf );
                    if( iInterval <= 0 )
                        iInterval = 3;
                    sleep( iInterval );
                }
                
                iSjtj ++;
                
                memset( sBuf, 0x00, sizeof( sBuf ) );
                COMP_SOFTGETXML( "/batch/sjtj/continue", sBuf );
                iInterval = atoi( sBuf );
                if( iInterval <= 0 )
                    iInterval = 5;
                if( iSjtj > iInterval )  /* �����ύ�ļ�������5���ȴ���һ��ѯ�����ٴ��� */
                {
                    LOG(LM_DEBUG,Fmtmsg("BATCH: ������ѯ���ύ����[%d]�ʣ����´��ٴ���",iSjtj ),"DEBUG")
                    continue;
                }
            }
        }
        else  /* ʧ�����񣬷ֱ���ö�Ӧ������������ */
        {
            /* ʧ�����񣬼���ظ����� */
            iClcs = 0;
            memset( sBuf, 0x00, sizeof( sBuf ) );
            snprintf( sSql1, sizeof( sSql1 ),"SELECT clcs FROM BATCH_plrwbd WHERE pkrq='%s'\
                AND ptpch='%s' AND czbd='%s'",sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch, sdb_batch_plrw.dqbd );
            iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
            if( iRet <  1 )
            {
                LOG(LM_STD,Fmtmsg("sqlerr[%s] ptpch[%s] dqbd[%s]��Ϣδ�ҵ�!",DCILastError(), sdb_batch_plrw.ptpch, sdb_batch_plrw.dqbd ),"ERROR");
                continue;
            }
            iClcs = atoi( sBuf );
            /* ���������0��ʼ */
            if( iClsbcs <= iClcs )
            {
                LOG(LM_DEBUG,Fmtmsg("BATCH: pkrq[%s]ptpch[%s]dqbd[%s]ʧ�ܴ������ޣ����ٴ���",
                    sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch, sdb_batch_plrw.dqbd ),"DEBUG")
                continue;
            }
            /* ���õ��������� */
            switch( sDqbd[0] )
            {
                case '0' :    /* ��ȡ���� */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910005" );
                    break;
                case '1' :    /* ������� */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910006" );
                    break;
                case '2' :    /* ������� */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910007" );
                    break;
                case '3' :    /* �����ύ */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910008" );
                    break;
                case '4' :    /* ������� */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910009" );
                    break;
                case '5' :    /* ���ݻ��� */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910010" );
                    break;
                default:
                    LOG(LM_STD,Fmtmsg("��ǰ����[%s],ϵͳ��", sDqbd ),"ERROR");
                    DCIFreeCursor(cur);
                    fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_PLRWBD,MSG_BATCH_SEL_PLRWBD);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL ;
            }
        }
        
        /* �������������� Ϊ���첽���ã���900016A����flow_batch_main*/
        if(fpub_CallFlow(lXmlhandle,"flow_batch_910016A")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("BATCH: ��������������ʧ��"),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,MID_BATCH_EXEC_FLOW,Fmtmsg(MSG_BATCH_EXEC_FLOW,"batch_flow_main"));
            return COMPRET_FAIL ;
        }
    }
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    DCIFreeCursor(cur);
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_SCANTASK
�������: BATCH_SCANTASK
�������: ����ҵ��ɨ��
�������:
 ����˵��    
�����  
0   �ɹ�
-1  ʧ��
-2  �����ظ�ִ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_SCANTASK(HXMLTREE lXmlhandle)
{
    char errmsg[256];
    char hostid[30];
    char sSql[512];
    int  iSetpCount;
    /*int iflag=1;*/
    char sBuf[255];
    int iRet= -1;
    /*int iCount= -1;*/
    int iFlag = -1;
    BATCH_ZJXX	sdb_batch_zjxx;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    memset(hostid, 0x00, sizeof(hostid));
    sprintf(hostid, "%s", getenv("HOST_ID"));
    trim(hostid);
    LOG(LM_DEBUG,Fmtmsg("[%s]",hostid),"DEBUG")
    
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( &sdb_batch_zjxx, 0x00, sizeof( BATCH_ZJXX ) );
    sprintf(sSql, "SELECT hostid,flag,status FROM BATCH_ZJXX WHERE hostid ='%s'", hostid );
    
    LOG(LM_DEBUG,Fmtmsg("[%s]ִ�п�ʼ",sSql),"DEBUG")
    iRet = DBSelectToMultiVar(errmsg, sSql, sdb_batch_zjxx.hostid, &sdb_batch_zjxx.flag, sdb_batch_zjxx.status, NULL);
    if(iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        return COMPRET_FAIL;
    }
    
    DCIBegin();
    /*���flagΪ0 �����һ����¼*/
    LOG(LM_DEBUG,Fmtmsg("������[%s]ִ�п�ʼ",sdb_batch_zjxx.hostid),"DEBUG")
    trim(sdb_batch_zjxx.hostid);
    if(strlen(sdb_batch_zjxx.hostid) == 0)	
    {
        memset( &sdb_batch_zjxx, 0x00, sizeof( BATCH_ZJXX ) );
        strcpy(sdb_batch_zjxx.hostid, hostid);
        sdb_batch_zjxx.flag = 1;
        strcpy(sdb_batch_zjxx.status, "0");
        
        iRet = DBInsert("batch_zjxx", SD_BATCH_ZJXX, NUMELE(SD_BATCH_ZJXX), &sdb_batch_zjxx, errmsg);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d|%s]",iRet,DCILastError() ),"ERROR")
            /*		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,MID_BATCH_INS_PLRW,MSG_BATCH_INS_PLRW); */
            DCIRollback();
            return COMPRET_FAIL;
        }
    }
    
    /* ��ѯ���Ȩ��ֵ */
    memset( sSql, 0x00, sizeof( sSql ) );
    strcpy(sSql, "SELECT max(flag) FROM BATCH_ZJXX " );
    iRet = DBSelectToVar(errmsg, &iFlag, sSql);
    LOG(LM_DEBUG,Fmtmsg("[%d|%d]ִ�п�ʼ",iFlag,sdb_batch_zjxx.flag),"DEBUG")
    if(iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d|%s]",iRet, DCILastError() ),"ERROR")
        /*   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);*/
        return COMPRET_FAIL;
    }
    
    /* �ж����Ȩ��ֵ�Ƿ����Լ� */
    if(sdb_batch_zjxx.flag != iFlag)
    {
        /* flag ��1,Ȼ�� exit*/
        sdb_batch_zjxx.flag = sdb_batch_zjxx.flag +1;
        memset( sSql, 0x00, sizeof( sSql ) );
        sprintf(sSql, "UPDATE BATCH_ZJXX SET flag = %d WHERE hostid = '%s'", sdb_batch_zjxx.flag, sdb_batch_zjxx.hostid);
        LOG(LM_DEBUG,Fmtmsg("[%s]ִ�п�ʼ",sSql),"DEBUG")
        iRet = DCIExecuteDirect(sSql);
        if(iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d|%s]",iRet, DCILastError() ),"ERROR")
            /*	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);*/
            DCIRollback();
            return COMPRET_FAIL;
        }
        
        /*fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);*/
        DCICommit();
        return COMPRET_SUCC;
    }
    
    /* flag ��1 ִ��ɨ������ */
    sdb_batch_zjxx.flag = sdb_batch_zjxx.flag +1;
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf(sSql, "UPDATE BATCH_ZJXX SET flag = %d WHERE hostid = '%s'", sdb_batch_zjxx.flag, sdb_batch_zjxx.hostid );
    iRet = DCIExecuteDirect(sSql);
    if(iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d|%s]",iRet, DCILastError() ),"ERROR")
        /*	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);*/
        DCIRollback();
        return COMPRET_FAIL;
    
    }
    DCICommit();
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
/************************************************************************
��̬�����������
�����������:SBATCH_SCANBATCH
�������: BATCH_SCANBATCH
�������: ����ҵ��ɨ��2
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    

�����  
0   �ɹ�
-1  ʧ��
-2  �����ظ�ִ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_SCANBATCH(HXMLTREE lXmlhandle)
{
    char errmsg[256];
    char hostid[30];
    char sSql[512];
    int  iSetpCount;
    /*int iflag=0;*/
    char sBuf[255];
    int iRet= -1;
    int iCount= -1;
    /*int iFlag = -1;*/
    BATCH_ZJXX	sdb_batch_zjxx;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /* ����Լ��Ƿ���� */
    memset( hostid, 0x00, sizeof(hostid) );
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( &sdb_batch_zjxx, 0x00, sizeof( sdb_batch_zjxx ) );
    
    sprintf( hostid, "%s", getenv("HOST_ID"));
    sprintf(sSql, "SELECT hostid, flag, status FROM BATCH_ZJXX WHERE hostid ='%s'", hostid );
    
    iRet = DBSelectToMultiVar(errmsg, sSql, sdb_batch_zjxx.hostid, &sdb_batch_zjxx.flag, sdb_batch_zjxx.status,NULL );
    if(iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*������������Ϣ,�����һ��*/
    DCIBegin();
    trim(sdb_batch_zjxx.hostid);
    if(strlen(sdb_batch_zjxx.hostid) == 0)	
    {
        strcpy(sdb_batch_zjxx.hostid, hostid);
        sdb_batch_zjxx.flag = 0;
        strcpy(sdb_batch_zjxx.status, "0");
        
        iRet = DBInsert("batch_zjxx", SD_BATCH_ZJXX, NUMELE(SD_BATCH_ZJXX), &sdb_batch_zjxx, errmsg);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            /*	fpub_SetMsg(lXmlhandle,MID_BATCH_INS_PLRW,MSG_BATCH_INS_PLRW);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);*/
            DCIRollback();
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG,Fmtmsg("û����Ϣ,����һ��[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG")
    }
    else
    {
        memset( sSql, 0x00, sizeof( sSql ) );
        sprintf(sSql, "UPDATE BATCH_ZJXX SET status='0' WHERE hostid ='%s'", hostid );
        iRet = DCIExecuteDirect(sSql);
        if(iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            /*	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);*/
            DCIRollback();
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG,Fmtmsg("�Ѿ�����,���״̬[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG")
    }
    
    /* �ж��Լ��Ƿ�������,���� ��������������flagΪ0 */
    if( sdb_batch_zjxx.flag == 1 && !strcmp(sdb_batch_zjxx.status, "0") )
    {
        memset( sSql, 0x00, sizeof( sSql ) );
        sprintf(sSql, "UPDATE BATCH_ZJXX SET flag = 0 WHERE hostid !='%s' and flag = 1", hostid );
        iRet = DCIExecuteDirect(sSql);
        if(iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            /*fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); */
            return COMPRET_FAIL;
        }
        /*	ִ��ɨ�蹤�� */
        LOG(LM_DEBUG,Fmtmsg("��������[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG")
    }
    else
    {
        /* �ж��Ƿ�����л�Ծ������ */
        LOG(LM_DEBUG,Fmtmsg("�Ҳ�������,���Ƿ��������[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG")
        memset( sSql, 0x00, sizeof( sSql ) );
        strcpy(sSql, "SELECT COUNT(*) FROM BATCH_ZJXX WHERE flag = 1 AND status = '0' " );
        iRet = DBSelectToVar(errmsg, &iCount, sSql);
        if(iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            /*fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); */
            return COMPRET_FAIL;
        }
        
        if(iCount == 0)
        {
            memset( sSql, 0x00, sizeof( sSql ) );
            sprintf(sSql, "UPDATE BATCH_ZJXX SET flag = 1 WHERE hostid ='%s'", hostid );
            LOG(LM_DEBUG,Fmtmsg("����������,���ұ������[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG")
        
            iRet = DCIExecuteDirect(sSql);
            if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                /*fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); */
                DCIRollback();
                return COMPRET_FAIL;
            }
        }
        else
        {
            LOG(LM_DEBUG,Fmtmsg("�ı�����������״̬��ͬʱ���Լ�����Ϊ����[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG");
            memset( sSql, 0x00, sizeof( sSql ) );
            sprintf(sSql, "UPDATE BATCH_ZJXX SET status = '1' WHERE flag = 1 AND hostid != '%s'", hostid );
            
            iRet = DCIExecuteDirect(sSql);
            if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                /*fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); */
                DCIRollback();
                return COMPRET_FAIL;
            }
            
            memset( sSql, 0x00, sizeof( sSql ) );
            sprintf(sSql, "UPDATE BATCH_ZJXX SET flag = 1 WHERE hostid = '%s'", hostid );
            
            iRet = DCIExecuteDirect(sSql);
            if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                /*fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); */
                DCIRollback();
                return COMPRET_FAIL;
            }
        }
    }
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    DCICommit();
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    return COMPRET_SUCC;
}

/**************************************************************************
��������:  int func_queryPlrwbdRecord(HXMLTREE lXmlhandle, BATCH_PLRWBD  *pstPlrwbd)
��������:  ��ѯ�������񲽵���Ϣ��
��������:  lXmlhandle     XML���
           
��������:  0  :�ɹ��� -1 :ʧ��
����˵��:
�޸�˵��:
**************************************************************************/
int func_queryPlrwbdRecord(HXMLTREE lXmlhandle, BATCH_PLRWBD  *pstPlrwbd)
{
    char sSql[256];
    int iRet = -1;
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), " select * from batch_plrwbd where pkrq='%s' and ptpch='%s' and czbd='%s'",
        pstPlrwbd->pkrq, pstPlrwbd->ptpch, pstPlrwbd->czbd);
    LOG(LM_STD,Fmtmsg("��ѯ�������񲽵���Ϣ��¼SQL[%s]", sSql),fpub_GetCompname(lXmlhandle))
    
    iRet = fprv_SelToStruct( sSql, SD_BATCH_PLRWBD, NUMELE(SD_BATCH_PLRWBD), pstPlrwbd );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    return iRet;
}
/**************************************************************************
��������:  int func_queryFlowSn(HXMLTREE lXmlhandle, BATCH_PLRWBD  *pstPlrwbd)
��������:  ��ѯ�������񲽵���Ϣ��
��������:  lXmlhandle     XML���
           
��������:  0  :�ɹ��� -1 :ʧ��
����˵��:
�޸�˵��:
**************************************************************************/
int func_queryFlowSn(HXMLTREE lXmlhandle, BATCH_PLRWBD  *pstPlrwbd)
{
    char sSql[256];
    char sErrmsg[256];
    int iRet = -1;
    int iFlowSn=0;
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), " select max(flowsn) from batch_plrwbd where pkrq='%s' and ptpch='%s' ",
        pstPlrwbd->pkrq, pstPlrwbd->ptpch);
    LOG(LM_STD,Fmtmsg("��ѯ�������񲽵���Ϣ��¼SQL[%s]", sSql),fpub_GetCompname(lXmlhandle))

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBSelectToVar(sErrmsg, &iFlowSn, sSql);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
LOG(LM_DEBUG,Fmtmsg("��ѯ�������񲽵���Ϣ��¼SQL,iFlowSn[%d]", iFlowSn),fpub_GetCompname(lXmlhandle))
    return iFlowSn;
}

/************************************************************************
��̬�����������
�����������:SBATCH_CONTROL
�������:SBATCH_CONTROL
�������: ����ҵ������ִ���ܿ�
�������:
��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    

ʹ������:

�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_CONTROL(HXMLTREE lXmlhandle)
{
    int iStepCount=0,iFlag=0,iAttribCount,jflag;
    int iParas;
    char sXmlNode[128];
    char sStepFlow[128];
    char sAttribvalue[128];
    char sBuf[128];
    int  iBdcgbz,ret;
    char flowStatus[11];
    char sStepSN[2];
    char sStepNM[8];
    char sPkRq[8+1];/*��������*/
    char sPtPch[8+1];/*ƽ̨���κ�*/
    char sDqbd[2+1];/*��ǰ����*/
    char sBdzt[1+1];/*����״̬*/
    char sFzbd[2+1];/*��������*/
    char sRwzt[1+1];/*����״̬*/
    char sFinalStep[4+1];/*��󲽵�*/
    char sFlowStep[4+1];
    int  iFlowSn = 0;
    int  iFinalFlowSn=0;
    int  iIsExe = 0;/*ִ�б�־ 0-δִ�� 1-��ִ��*/
    int iRet = -1;
    BATCH_PLRWBD sdb_plrwbd;
    BATCH_STEPCFG sdb_batch_stepcfg;
    char sErrmsg[512];
    char sSql1[1024];
    char sFlowID[51];
    CURSOR cur;

    fpub_InitSoComp(lXmlhandle);

    memset(sPkRq, 0x00, sizeof(sPkRq));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ, sBuf)
    pstrcopy(sPkRq, sBuf, sizeof(sPkRq));
    
    memset(sPtPch, 0x00, sizeof(sPtPch));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH, sBuf)
    pstrcopy(sPtPch, sBuf, sizeof(sPtPch));
        
    LOG(LM_STD,Fmtmsg("����ҵ�������ܿ�ִ�п�ʼ...pkrq&ptpch[%s%s]",
        sPkRq, sPtPch),fpub_GetCompname(lXmlhandle));
    
    /* ��ʼ�����̵��������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFlowID, 0x00, sizeof(sFlowID));
    COMP_SOFTGETXML(XMLNM_BATCH_RUNCTRL_FLOWID, sBuf)
    pstrcopy(sFlowID, sBuf, sizeof(sFlowID));
    trim(sFlowID);
    iRet=fprv_initBatchFlow(lXmlhandle, sFlowID, &t_flowList);
    if( iRet <=0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:�޶�Ӧ����[%s]������Ϣ",sFlowID),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FLOWCFG_NOFUND,MSG_BATCH_FLOWCFG_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*��ѯ���������*/
    memset(sDqbd, 0x00, sizeof(sDqbd));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_DQBD, sDqbd)
    memset(&sdb_plrwbd, 0x00, sizeof(sdb_plrwbd));
    pstrcopy(sdb_plrwbd.pkrq, sPkRq, sizeof(sdb_plrwbd.pkrq));
    pstrcopy(sdb_plrwbd.ptpch, sPtPch, sizeof(sdb_plrwbd.ptpch));
    pstrcopy(sdb_plrwbd.czbd, sDqbd, sizeof(sdb_plrwbd.czbd));
    iRet = func_queryPlrwbdRecord(lXmlhandle, &sdb_plrwbd);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("��ѯ�������񲽵���Ϣ��ʧ��[%d]", iRet),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("δ�ҵ��������񲽵���Ϣ��[%d],flowsn��plrwbd��ȡmax(flowsn)+1", iRet),fpub_GetCompname(lXmlhandle))
        /*sdb_plrwbd.flowsn = 1; */
        iRet = func_queryFlowSn(lXmlhandle, &sdb_plrwbd);
        /* mod by tuql 20151230 �ڲ�������Ҳ���ʱ������ֱ��+1 if ( iRet <= 0 ) */
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("��ѯ�������񲽵���Ϣ��ʧ��[%d]", iRet),fpub_GetCompname(lXmlhandle))
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        sdb_plrwbd.flowsn = iRet + 1;
    }
    iFlowSn = sdb_plrwbd.flowsn;
    LOG(LM_STD,Fmtmsg("BATCH: ����ҵ�������ܿ�,dqbd=[%s],iFlowSn[%d]",
        sdb_plrwbd.czbd, iFlowSn ), fpub_GetCompname(lXmlhandle));
    /* ���̲���ѭ������ʼ */
    for( pflowIter = i_list_begin(t_flowList); 
        pflowIter!= i_list_end(t_flowList); 
        pflowIter = i_list_iter_next(pflowIter) )
    {
        /*ȡ������Ϣ*/
        memset(sDqbd, 0x00, sizeof(sDqbd));
        memset(sBdzt, 0x00, sizeof(sBdzt));
        memset(sFzbd, 0x00, sizeof(sFzbd));
        memset(sRwzt, 0x00, sizeof(sRwzt));
        COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_DQBD, sDqbd)
        COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_BDZT, sBdzt)
        COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_FZBD, sFzbd)
        COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_RWZT, sRwzt)
        
        /*��ȷ��λ��Ԥ������*/
        pFlowcfg = (BATCH_FLOWCFG *)(pflowIter->data);
        trim(pFlowcfg->stepid);
        if ( iFlowSn > pFlowcfg->flowsn )
        {/*����,ֱ����λ��Ӧ����*/
            LOG(LM_STD,Fmtmsg("(����1)BATCH: ����ҵ�������ܿ�[%s,%s],��ǰ����[%s],��������[%d,%s],��������[%s]",\
                sPkRq, sPtPch, sDqbd, pFlowcfg->flowsn, 
                pFlowcfg->stepid, pFlowcfg->stepname), fpub_GetCompname(lXmlhandle));
            continue;
        }
        if ( ( sBdzt[0] == BATCH_STEP_STATUS_BREAK ||
               sBdzt[0] == BATCH_STEP_STATUS_END   ||
               sBdzt[0] == BATCH_STEP_STATUS_RETURN
              ) && iIsExe==0 
            )
        {/*������������ϵ㡢����,�л�����һ����*/
            if ( atoi(sDqbd) > 7 && strcmp(sFzbd, BATCH_STEP_ASTSTEP_WRET) == 0 )
            {/*����Ƕ�ף���������Ϊ10-������ʱ�����㻹δ����*/
                /*�����κδ���*/
            }else
            {
                LOG(LM_STD,Fmtmsg("(����2)BATCH: ����ҵ�������ܿ�[%s,%s],��ǰ����[%s],��������[%d,%s],��������[%s]",\
                    sPkRq, sPtPch, sDqbd, pFlowcfg->flowsn, 
                    pFlowcfg->stepid, pFlowcfg->stepname), fpub_GetCompname(lXmlhandle));
                pflowIter = i_list_iter_next(pflowIter);
                pFlowcfg = (BATCH_FLOWCFG *)(pflowIter->data);
                trim(pFlowcfg->stepid);
                
            }
        }
        LOG(LM_STD,Fmtmsg("BATCH: ����ҵ�������ܿ�[%s%s],��ǰ����[%s],ִ�в���[%d,%s],��������[%s]",\
            sPkRq, sPtPch, sDqbd, pFlowcfg->flowsn, pFlowcfg->stepid, pFlowcfg->stepname), fpub_GetCompname(lXmlhandle));
        memset(sFlowStep, 0x00, sizeof(sFlowStep));
        pstrcopy(sFlowStep, pFlowcfg->stepid, sizeof(sFlowStep));
        iFlowSn=pFlowcfg->flowsn;
        /*������������ȫ�ֽڵ�*/
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWID,pFlowcfg->flowid);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWNAME,pFlowcfg->flowname);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWSN,itoa(pFlowcfg->flowsn));
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPID,pFlowcfg->stepid);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPSN,itoa(pFlowcfg->stepsn));
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPNAME,pFlowcfg->stepname);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_EXTFLD1,pFlowcfg->extfld1);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_EXTFLD2,pFlowcfg->extfld2);
        
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM batch_stepcfg WHERE \
            flowid='%s' AND flowsn=%d AND stepid='%s'", 
            sFlowID, pFlowcfg->flowsn,pFlowcfg->stepid );
        if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
        {
            iFlag=-1 ;
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            break;
        }
        if (DCIExecute(cur) == -1)
        {
            iFlag=-2 ;
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            break;
        }
        
        /* ��ȡ���̲�������  */
        for ( iAttribCount=0, jflag=0 ; ;iAttribCount++)
        {
            memset(&sdb_batch_stepcfg,0,sizeof(sdb_batch_stepcfg));
            if( ( iRet = DBFetch(cur, SD_BATCH_STEPCFG, NUMELE(SD_BATCH_STEPCFG), &sdb_batch_stepcfg, sErrmsg ) ) <= 0 )
            {
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ��ȡ���̲������Դ���ʧ��,[%s]", DCILastError() ),"ERROR");
                    jflag = -1;
                }
                break;
            }
        
            memset(sXmlNode,0,sizeof(sXmlNode));
            trim(pFlowcfg->stepid);
            trim(sdb_batch_stepcfg.attribid);
            trim(sdb_batch_stepcfg.attribvalue );
            snprintf(sXmlNode,sizeof( sXmlNode ),\
                "/batch/%s/%s",pFlowcfg->stepid,sdb_batch_stepcfg.attribid);
            
            /* added by yangdong 20121316  �������Զ�xml�ڵ�֧�� */
            /* modified by yangdong 20130618 sdb_batch_stepcfg.attribvalue �����޷���Ž������ַ������� 
            if(xml_ParseXMLString(lXmlhandle,sdb_batch_stepcfg.attribvalue,sizeof(sdb_batch_stepcfg.attribvalue))==FAIL)
             */
            memset( sAttribvalue ,0,sizeof( sAttribvalue ));
            strcpy( sAttribvalue, sdb_batch_stepcfg.attribvalue );
            if(xml_ParseXMLString(lXmlhandle, sAttribvalue, sizeof( sAttribvalue ))==FAIL)
            {
                LOG(LM_STD,Fmtmsg("BATCH: ��ȡ���̲������Դ���ʧ��,[%s]", sAttribvalue ),"ERROR");
                jflag = -2 ;
                break;
            }
            
            COMP_SOFTSETXML(sXmlNode, sAttribvalue );
            LOG(LM_DEBUG,Fmtmsg("  -->�����ܿش�������[%s][%s], val[%s]", sXmlNode, sdb_batch_stepcfg.attribid, sAttribvalue ),"DEBUG");
            /* end of mod 20130618 */
        }
        DCIFreeCursor(cur);
        LOG(LM_DEBUG,Fmtmsg("����������[%d], flowid[%s], stepid[%s]",\
            iAttribCount,sFlowID,pFlowcfg->stepid),"DEBUG");
        if(jflag < 0) 
        {
            iFlag=jflag ;
            LOG(LM_STD,Fmtmsg("BATCH: ��ȡ���̲������Դ���ʧ��,[%d]",jflag),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
            break;
        }
        
        /* ���õ����������̴��� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        memset(sStepFlow,0,sizeof(sStepFlow));
        snprintf(sXmlNode,sizeof( sXmlNode ),\
            "/batch/%s/%s",pFlowcfg->stepid,BATCH_ATTRIBUTE_CLLCM);
        COMP_SOFTGETXML(sXmlNode,sStepFlow);
        
        LOG(LM_STD,Fmtmsg("����[%s]����,[%s]���̿�ʼ<--",pFlowcfg->stepid,sStepFlow),"INFO");
        trim(sStepFlow);
        if( fpub_CallFlow(lXmlhandle,sStepFlow) != MID_SYS_SUCC)
        {
            iFlag=-3 ;
            COMP_SOFTGETXML(XMLNM_RESPCODE,flowStatus);
            LOG(LM_STD,Fmtmsg("BATCH: ����[%s]����ʧ��,����״̬[%s]",\
                sStepFlow,flowStatus),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_EXEC_FLOW,\
                Fmtmsg(MSG_BATCH_EXEC_FLOW,sStepFlow));
            break;
        }
        iIsExe ++;
        iStepCount++;
        /* �ⲿ���븳ֵ 0�ɹ���1ʧ�ܡ�2���� */
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_BDCGBZ,sBuf);
        LOG(LM_STD,Fmtmsg("<<<<<<����[%s]����,[%s]���̽���[%s]>>>>>>",pFlowcfg->stepid,sStepFlow, sBuf),"INFO");
        iBdcgbz=atoi(sBuf);
        ret=fprv_isZero(sBuf);
        if( ret == 0 )
        {
            iFlag=0 ;
            continue;
        }
        else if( iBdcgbz == 1 ) /* ����ʧ�� */
        {    
            iFlag=-4 ;
            break;
        }
        else if( iBdcgbz == 2 ) /* ���ش��� - ����ѭ��*/
        {
            iFlag=2;        
            break;
        }
        /* by yr 20120927 */
        else if( iBdcgbz == 3 ) /* �ȴ����� - ����ѭ��*/
        {
            iFlag=3;        
            break;
        }
        /* end */
        else
        {
            iFlag = -5;
            LOG(LM_STD,Fmtmsg("BATCH: ����ɹ���־�Ƿ�[%s]",sBuf),"ERROR");        
            fpub_SetMsg(lXmlhandle,MID_BATCH_BDCGBZ_FF,Fmtmsg(MSG_BATCH_BDCGBZ_FF,sBuf));
            break;
        }
    }
    prv_FlowListFree();
    LOG(LM_STD,Fmtmsg("BATCH: ���������ܿ�-����[%s],��������[%d]--����iFlag[%d]",
        sFlowID,iStepCount, iFlag),"INFO");
    if(iFlag < 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*��ȡ��������󲽵�*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_FINAL_FLOWSN, sBuf );
    iFinalFlowSn = atoi(sBuf);

    if ( iFlowSn == iFinalFlowSn)
    {/*�����һ��Ϊ����*/
        LOG(LM_DEBUG,Fmtmsg("������󲽵㣬���óɹ���־[%d][%d]",
            iFlowSn, iFinalFlowSn),fpub_GetCompname(lXmlhandle))
        memset( sBuf, 0x00, sizeof( sBuf ) );
        memset(sFinalStep, 0x00, sizeof(sFinalStep));
        COMP_SOFTGETXML( XMLNM_BATCH_FINAL_STEP, sBuf );
        pstrcopy(sFinalStep, sBuf, sizeof(sFinalStep));
        memset(sFzbd, 0x00, sizeof(sFzbd));
        COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_FZBD, sFzbd)
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_FAIL);
        if ( strcmp(sFinalStep, BATCH_STEPNM_RWQT) == 0 &&
             strcmp(sFzbd, BATCH_STEP_ASTSTEP_RETURN) == 0
            )
        {
            COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_SUCC);
        }else if ( strcmp(sFinalStep, BATCH_STEPNM_RWQT) != 0 )
        {
            COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_SUCC);
        }
    }  
    
    LOG(LM_STD,Fmtmsg("����ҵ�������ܿ�ִ�н���...pkrq&ptpch[%s%s],iFinal[%d-%s],[%d-%s],fzbd[%s]",
        sPkRq, sPtPch, iFinalFlowSn, sFinalStep, iFlowSn, sFlowStep, sFzbd),fpub_GetCompname(lXmlhandle));

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/**************************************************************************
��������:  int func_queryPlrwRecord(HXMLTREE lXmlhandle, BATCH_PLRW  *pstPlrw)
��������:  ��ѯ����������Ϣ��
��������:  lXmlhandle     XML���
           
��������:  0  :�ɹ��� -1 :ʧ��
����˵��:
�޸�˵��:
**************************************************************************/
int func_queryPlrwRecord(HXMLTREE lXmlhandle, BATCH_PLRW  *pstPlrw)
{
    char sSql[256];
    int iRet = -1;
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), " select * from batch_plrw where pkrq='%s' and ptpch='%s'",
        pstPlrw->pkrq, pstPlrw->ptpch);
    LOG(LM_STD,Fmtmsg("��ѯ����������Ϣ��¼SQL[%s]", sSql),fpub_GetCompname(lXmlhandle))
    
    iRet = fprv_SelToStruct( sSql, SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), pstPlrw );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("δ�ҵ�����������Ϣ��¼,pkrq[%s],ptpch[%s]",
            pstPlrw->pkrq, pstPlrw->ptpch),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "δ�ҵ�����������Ϣ��¼");
        return COMPRET_FAIL;
    }

    return 0;
}

/**************************************************************************
��������:  int func_queryPlrwRecord2(HXMLTREE lXmlhandle, BATCH_PLRW  *pstPlrw)
��������:  ��ѯ����������Ϣ��
��������:  lXmlhandle     XML���
           
��������:  0  :�ɹ��� -1 :ʧ��
����˵��:
�޸�˵��:
**************************************************************************/
int func_queryPlrwRecord2(HXMLTREE lXmlhandle, BATCH_PLRW  *pstPlrw)
{
    char sSql[256];
    int iRet = -1;
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), " select * from batch_plrw where bqtpkrq='%s' and bqtptpch='%s'",
        pstPlrw->bqtpkrq, pstPlrw->bqtptpch);
    LOG(LM_STD,Fmtmsg("��ѯ����������Ϣ��¼SQL[%s]", sSql),fpub_GetCompname(lXmlhandle))
    
    iRet = fprv_SelToStruct( sSql, SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), pstPlrw );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    return iRet;
}

/**************************************************************************
��������:  int func_queryWbwjdjRecord(HXMLTREE lXmlhandle, BATCH_WBWJDJ  *pstWbwjdj)
��������:  ��ѯ�ⲿ�ļ��ǼǱ�
��������:  lXmlhandle     XML���
           
��������:  0  :�ɹ��� -1 :ʧ��
����˵��:
�޸�˵��:
**************************************************************************/
int func_queryWbwjdjRecord(HXMLTREE lXmlhandle, BATCH_WBWJDJ  *pstWbwjdj)
{
    char sSql[256];
    int iRet = -1;
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), " select * from batch_wbwjdj where pkrq='%s' and ptpch='%s'",
        pstWbwjdj->pkrq, pstWbwjdj->ptpch);
    LOG(LM_STD,Fmtmsg("��ѯ�ⲿ�ļ��ǼǼ�¼SQL[%s]", sSql),fpub_GetCompname(lXmlhandle))
    
    iRet = fprv_SelToStruct( sSql, SD_BATCH_WBWJDJ, NUMELE(SD_BATCH_WBWJDJ), pstWbwjdj );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("δ�ҵ���ѯ�ⲿ�ļ��Ǽ���Ϣ��¼,pkrq[%s],ptpch[%s]",
            pstWbwjdj->pkrq, pstWbwjdj->ptpch),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "δ�ҵ��ⲿ�ļ��Ǽ���Ϣ��¼");
        return COMPRET_FAIL;
    }

    return 0;
}


/************************************************************************
��̬�����������
�����������:SBATCH_RULECHECK
�������:SBATCH_RULECHECK
�������: ����ҵ�����̹�����
�������:
��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    

ʹ������:

�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_RULECHECK(HXMLTREE lXmlhandle)
{
    int iParas;
    char sPkRq[8+1];/*��������*/
    char sPtPch[8+1];/*ƽ̨���κ�*/
    char sDqbd[2+1];/*��ǰ����*/
    char sBdzt[1+1];/*����״̬*/
    char sFzbd[2+1];/*��������*/
    char sRwzt[1+1];/*����״̬*/
    char sNextStep[1+1];/*��һ��*/
    char sFinalStep[4+1];/*��󲽵�*/
    char sBuf[256];
    /*int  iFlowSn = 0;*/
    int iRet = -1;
    BATCH_PLRW sdb_plrw;
    BATCH_WBWJDJ sdb_wbwjdj;

    fpub_InitSoComp(lXmlhandle);

    memset(sPkRq, 0x00, sizeof(sPkRq));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ, sBuf)
    pstrcopy(sPkRq, sBuf, sizeof(sPkRq));
    
    memset(sPtPch, 0x00, sizeof(sPtPch));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH, sBuf)
    pstrcopy(sPtPch, sBuf, sizeof(sPtPch));

    memset(sNextStep, 0x00, sizeof(sNextStep));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_NEXTSTEP, sBuf)
    sNextStep[0] = sBuf[0];

    /*��ȡ��������󲽵�*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_FINAL_FLOWSN, sBuf );
    pstrcopy(sFinalStep,sBuf,sizeof(sFinalStep));
    trim( sFinalStep );
        
    LOG(LM_STD,Fmtmsg("����ҵ�������ִ�п�ʼ...pkrq[%s],ptpch[%s],nextstep[%s],finalstep[%s]",
        sPkRq, sPtPch, sNextStep, sFinalStep),fpub_GetCompname(lXmlhandle));  

    /*�ⲿ���ͨ��*/
    if (sNextStep[0] == '3' )
    {
        COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_DQBD, "0")/*��ȡ����*/
        COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_BDZT, BATCH_STEP_STATUS_S_WAIT)
        COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_FZBD, BATCH_STEP_ASTSTEP_INIT)
        COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_RWZT, BATCH_TASK_STATUS_S_PAUSE)
    }

    memset(sDqbd, 0x00, sizeof(sDqbd));
    memset(sBdzt, 0x00, sizeof(sBdzt));
    memset(sFzbd, 0x00, sizeof(sFzbd));
    memset(sRwzt, 0x00, sizeof(sRwzt));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_DQBD, sDqbd)
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_BDZT, sBdzt)
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_FZBD, sFzbd)
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_RWZT, sRwzt)
    
    LOG(LM_STD,Fmtmsg("��Χ���벽����Ϣ,dqbd[%s],bdzt[%s],fzbd[%s],rwzt[%s]",
        sDqbd, sBdzt, sFzbd, sRwzt),fpub_GetCompname(lXmlhandle))
    
    /*��ѯ���������*/
    memset(&sdb_plrw, 0x00, sizeof(sdb_plrw));
    pstrcopy(sdb_plrw.pkrq, sPkRq, sizeof(sdb_plrw.pkrq));
    pstrcopy(sdb_plrw.ptpch, sPtPch, sizeof(sdb_plrw.ptpch));
    iRet = func_queryPlrwRecord(lXmlhandle, &sdb_plrw);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("��ѯ����������Ϣ��ʧ��[%d]", iRet),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("��ѯ�������Ϣ,dqbd[%s],bdzt[%s],fzbd[%s],rwzt[%s]",
        sdb_plrw.dqbd, sdb_plrw.bdzt, sdb_plrw.fzbd, sdb_plrw.rwzt),fpub_GetCompname(lXmlhandle))
    /*�Ƚϲ�����Ϣһ����*/
    if ( strcmp(sDqbd, sdb_plrw.dqbd) != 0 ||
         strcmp(sBdzt, sdb_plrw.bdzt) != 0 ||
         strcmp(sFzbd, sdb_plrw.fzbd) != 0 ||
         strcmp(sRwzt, sdb_plrw.rwzt) != 0 
        )
    {
        LOG(LM_STD,Fmtmsg(MSG_BATCH_STEPINFO),fpub_GetCompname(lXmlhandle))
        fpub_SetMsg(lXmlhandle, MID_BATCH_STEPINFO, MSG_BATCH_STEPINFO);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*����״̬Ϊ9-���ڴ����еģ������ȴ����Ժ���*/
    if ( sBdzt[0] == BATCH_STEP_STATUS_RUNNING )
    {
        LOG(LM_STD,Fmtmsg(MSG_BATCH_PROCING),fpub_GetCompname(lXmlhandle))
        fpub_SetMsg(lXmlhandle, MID_BATCH_PROCING, MSG_BATCH_PROCING);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }    
    /*��Ϊ��ȡ����,�����ȿ�һ���Ƿ���Ҫ�ⲿ�ļ����*/
    if (sdb_plrw.dqbd[0] == BATCH_STEPSN_HQSJ)
    {
        memset(&sdb_wbwjdj, 0x00, sizeof(sdb_wbwjdj));
        pstrcopy(sdb_wbwjdj.pkrq, sPkRq, sizeof(sdb_wbwjdj.pkrq));
        pstrcopy(sdb_wbwjdj.ptpch, sPtPch, sizeof(sdb_wbwjdj.ptpch));
        iRet = func_queryWbwjdjRecord(lXmlhandle, &sdb_wbwjdj);
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("��ѯ�����ⲿ�ļ��ǼǱ�ʧ��[%d]", iRet),fpub_GetCompname(lXmlhandle))
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        LOG(LM_STD,Fmtmsg("��ǰΪ��ȡ���ݲ��㣬�ж��Ƿ���Ҫ�ⲿ�ļ����[%s]", 
            sdb_wbwjdj.shzt),fpub_GetCompname(lXmlhandle))
        if (sdb_wbwjdj.shzt[0] != WBWJDJ_SHZT_YES )
        {
            LOG(LM_STD,Fmtmsg(MSG_BATCH_SH_WBWJDJ),fpub_GetCompname(lXmlhandle))
            fpub_SetMsg(lXmlhandle, MID_BATCH_SH_WBWJDJ, MSG_BATCH_SH_WBWJDJ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    
    /*���������ǳ����������,�������ٴη���*/
    if ( strcmp(sRwzt, BATCH_TASK_STATUS_S_CANCEL) == 0 ||
         strcmp(sRwzt, BATCH_TASK_STATUS_S_CORRECT) == 0 ||
         strcmp(sRwzt, BATCH_TASK_STATUS_S_TERM) == 0
        )
    {
        LOG(LM_STD,Fmtmsg(MSG_BATCH_CANCELED),fpub_GetCompname(lXmlhandle))
        fpub_SetMsg(lXmlhandle, MID_BATCH_CANCELED, MSG_BATCH_CANCELED);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*����ֻ����ĳ����ʧ��ʱ����ֱ�ӻ���*/
    if (sNextStep[0] == '1' )
    {
        if (sdb_plrw.bdzt[0] != BATCH_STEP_STATUS_STOP )
        {
            LOG(LM_STD,Fmtmsg(MSG_BATCH_DIRRETURN),fpub_GetCompname(lXmlhandle))
            fpub_SetMsg(lXmlhandle, MID_BATCH_DIRRETURN, MSG_BATCH_DIRRETURN);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    /*��Ƕ��������ֱ����ֹ*/
    if (sNextStep[0] == '2' )
    {
        /*��ѯ���������*/
        memset(&sdb_plrw, 0x00, sizeof(sdb_plrw));
        pstrcopy(sdb_plrw.bqtpkrq, sPkRq, sizeof(sdb_plrw.bqtpkrq));
        pstrcopy(sdb_plrw.bqtptpch, sPtPch, sizeof(sdb_plrw.bqtptpch));
        iRet = func_queryPlrwRecord2(lXmlhandle, &sdb_plrw);
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("��ѯ����������Ϣ��ʧ��[%d]", iRet),fpub_GetCompname(lXmlhandle))
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet > 0 )
        {/*���ҵ�˵���Ǳ�Ƕ������*/
            LOG(LM_STD,Fmtmsg("��Ƕ�������ܱ�ֱ����ֹ[%d]", iRet),fpub_GetCompname(lXmlhandle))
            fpub_SetMsg(lXmlhandle, MID_BATCH_DIRFORCE, MSG_BATCH_DIRFORCE);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    /*����������������̬���������ٴη���
    if ( sDqbd[0] == BATCH_STEPSN_FINL && sBdzt[0] == BATCH_STEP_STATUS_END )
    */
    if ( strcmp(sFzbd, BATCH_STEP_ASTSTEP_END) == 0 )
    {
        LOG(LM_STD,Fmtmsg(MSG_BATCH_STEP_SUCC),fpub_GetCompname(lXmlhandle))
        fpub_SetMsg(lXmlhandle, MID_BATCH_STEP_SUCC, MSG_BATCH_STEP_SUCC);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    LOG(LM_STD,Fmtmsg("����ҵ�������ִ�н���"),fpub_GetCompname(lXmlhandle))

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;      
}

/************************************************************************
��̬�����������
�����������:SBATCH_AUTOTASK2
�������: BATCH_AUTOTASK2
�������: ����ҵ���Զ����񴥷�����(�ϵ�����ʧ��������)
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    

�����  
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
int func_autotask2_assig(HXMLTREE lXmlhandle, int iDbTaskRun, char *psKsrq, char *psPkrq, char *psTaskPri, int *piProcCnt, int *piPriProcHighReal )
{
    int  iBusiMax = 0 ;
    int  iBusiProc = 0 ;/*�ܴ������*/
    int  iPriProcHigh = 0;
    int  iPriProcHighReal=*piPriProcHighReal;
    int  iProcCnt = *piProcCnt;
    int  iClsbcs = 0;  /* ����ʧ�ܴ��� */
    char iAbornAuto=1; /*���������쳣����0-������ 1-����(ȱʡ)*/
    char sCurrTime[6+1];  /* ��ǰϵͳʱ�� */
    char sBuf[255];
    char sSql[512];
    char sZwrq[8+1];
    char sCljg[16+1];
    char sClgy[16+1];
    char sErrmsg[512];
    int iRet = -1;
    int iFlag = 0;
    int iClcs = 0;
    BATCH_PLRW sdb_batch_plrw;
    CURSOR cur;
    int iBreakPoint=0;/*��������*/
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_MAXTASKNUM, sBuf)
    iBusiMax = atoi( sBuf );

    /*���δ�������=��������� - ���ڴ����� - �Ѵ�������*/
    iBusiProc = iBusiMax - iDbTaskRun - *piProcCnt;
    if ( psTaskPri[0] == BATCH_TASKPRI_LOWER && iBusiProc <= 0 )
    {/*0-�ͼ�����ͨ�������� */
        LOG(LM_STD,Fmtmsg("�����Զ������Ѵ�����������[%d]", iBusiProc),"INFO");
        iFlag=1;
        return iFlag;
    }
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PRIHIGHPROC, sBuf)
    iPriProcHigh = atoi( sBuf );

    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_ABORNAUTO, sBuf)
    if ( sBuf[0] == '\0')
    { /*���������쳣����0-������ 1-����(ȱʡ)*/
        sBuf[0] = '1';
    }
    iAbornAuto = atoi( sBuf );
    
    LOG(LM_STD,Fmtmsg("����ҵ���Զ����񴥷�,taskpri[%s],maxtasknum[%d],dbRunTask[%d],iAbornAuto[%d]",
        psTaskPri, iBusiMax, iDbTaskRun, iAbornAuto),fpub_GetCompname(lXmlhandle));

    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEP_FAIL,sBuf); /* ʧ�����Դ��� */
    iClsbcs=atoi( sBuf );
    if( iClsbcs <= 0 )
        iClsbcs = BATCH_MAX_STEP_REPEAT; /* Ĭ��ʧ����������5 */
    /*��������1 �ϵ� 2 ʧ������ Ĭ��ȫ��*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/systask/wjbz", sBuf)
    if (sBuf[0] == '\0')
    {
        sBuf[0]='0';
    }
    iBreakPoint=atoi(sBuf);
    /* ��ǰϵͳʱ�� */
    memset(sCurrTime,0,sizeof(sCurrTime));
    pstrcopy( sCurrTime, GetSysTime(), sizeof( sCurrTime ) );
    LOG(LM_STD,Fmtmsg("����ҵ���Զ����񴥷�,clsbcs[%d],breakpoint[%d],currtime[%s]",
        iClsbcs, iBreakPoint, sCurrTime),fpub_GetCompname(lXmlhandle));

    /* ��ѯ��Ҫ������и߼����� */
    memset( sSql, 0x00, sizeof( sSql ) );
    /* ����״̬ :  0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ�����  X ���� C���� */
    if (iBreakPoint==1)
    {/*1-�ϵ�*/
        snprintf(sSql,sizeof(sSql),"SELECT a.* FROM batch_plrw a WHERE a.pkrq>='%s' AND a.pkrq<='%s' AND a.bdzt='2' AND a.rwzt='3' AND a.clsj<='%s' AND a.taskpri='%s'  ORDER BY a.pkrq , a.ptpch ", psKsrq, psPkrq, sCurrTime, psTaskPri ); 
    }else if (iBreakPoint==2)
    {/*2-ʧ��*/
        snprintf(sSql,sizeof(sSql),"SELECT a.* FROM batch_plrw a WHERE a.pkrq>='%s' AND a.pkrq<='%s' AND a.bdzt='0' AND a.rwzt='0' AND a.taskpri='%s'  ORDER BY a.pkrq , a.ptpch ", psKsrq, psPkrq, psTaskPri ); 
    }else
    {/*0-ȱʡ*/
        snprintf(sSql,sizeof(sSql),"SELECT a.* FROM batch_plrw a WHERE a.pkrq>='%s' AND a.pkrq<='%s' AND ( ( a.bdzt='0' AND a.rwzt='0') OR ( a.bdzt='4' AND a.rwzt='4' AND a.clsj<='%s') OR ( a.bdzt='2' AND a.rwzt='3' AND a.clsj<='%s' ) ) AND a.taskpri='%s'  ORDER BY a.pkrq , a.ptpch ", psKsrq, psPkrq, sCurrTime, sCurrTime, psTaskPri ); 
    }
    
    LOG(LM_STD,Fmtmsg("auto task sql:[%s]", sSql),"ERROR");
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    memset(&sdb_batch_plrw, 0x00, sizeof(sdb_batch_plrw));
    while( ( iRet = DBFetch(cur, SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), &sdb_batch_plrw, sErrmsg ) ) > 0 )
    {
        /*LOG(LM_STD,Fmtmsg("[%d] ? [%d],[%s],[%s]", 
            atoi(psPkrq) ,atoi(sdb_batch_plrw.clrq), sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch),"ERROR");
        */
        if ( atoi(psPkrq) < atoi(sdb_batch_plrw.clrq) )
        {
            LOG(LM_STD,Fmtmsg("����,�����Զ�����[%s%s]δ���ﴥ������[%s]<[%s]", 
                sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch, psPkrq, sdb_batch_plrw.clrq),"ERROR");
            continue;
        }
        
        if ( sdb_batch_plrw.taskpri[0] == BATCH_TASKPRI_LOWER )
        {/*0-�ͼ�����ͨ�������� */
            if ( iBusiProc <= 0 )
            {
                LOG(LM_STD,Fmtmsg("�����Զ������Ѵ�����������[%d]", iBusiProc),"ERROR");
                iFlag=1;
                break;
            }
        }else
        {/*1,2-�и߼���Ӽ�/�ؼ��������� */
            if ( *piPriProcHighReal >= iPriProcHigh && iPriProcHigh > 0 )
            {
                LOG(LM_STD,Fmtmsg("�����и߼������Ѵ����ȴ�����[%d]>=[%d]", 
                    *piPriProcHighReal, iPriProcHigh),"ERROR");
                iFlag=2;
                break;
            }
            iPriProcHighReal ++;
        }
        /* ����������Ϣ��ֵ */
        trim( sdb_batch_plrw.pkrq );
        trim( sdb_batch_plrw.ptpch );
        trim( sdb_batch_plrw.ywbh );
        trim( sdb_batch_plrw.dqbd );
        
        if ( sdb_batch_plrw.bdzt[0] == '0' && iAbornAuto != 1 )
        {/*ʧ�ܲ����Ҳ����Զ�����,����*/
            continue;
        }
        
        memset(sSql, 0x00, sizeof(sSql));
        snprintf(sSql, sizeof(sSql), "select clcs,cljg,clgy from batch_plrwbd where pkrq='%s' and ptpch='%s' and czbd='%s'",
            sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch, sdb_batch_plrw.dqbd);
        iClcs = 0;
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sCljg, 0x00, sizeof(sCljg));
        memset(sClgy, 0x00, sizeof(sClgy));
        iRet = DBSelectToMultiVar(sErrmsg, sSql, &iClcs, sCljg, sClgy);
        /*iRet = DBSelectToVarChar(sErrmsg, sBuf,  sSql); */
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ���ݿ����ʧ��[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            iFlag = -1;
            break;
        }
        /*iClcs = atoi(sBuf);*/
        if ( iClcs >= iClsbcs )
        {/*��������Ѵ����,����*/
            continue;
        }
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_JYDM, "910031" );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_YWBH, sdb_batch_plrw.ywbh );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_PKRQ, sdb_batch_plrw.pkrq );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_PTPCH, sdb_batch_plrw.ptpch );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_NEXTSTEP, "0");/*0-�ϲ�����*/
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_DQBD, sdb_batch_plrw.dqbd );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_BDZT, sdb_batch_plrw.bdzt );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_FZBD, sdb_batch_plrw.fzbd );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_RWZT, sdb_batch_plrw.rwzt );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_JYJG, sCljg );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_JYGY, sClgy );
        
        iBusiProc --;
        iProcCnt ++;
        LOG(LM_STD,Fmtmsg("[%d]��������[%s%s%s],���ȼ�[%s],״̬[%s,%s]����������", 
            iProcCnt, sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch, sdb_batch_plrw.dqbd, 
            sdb_batch_plrw.taskpri,sdb_batch_plrw.bdzt, sdb_batch_plrw.rwzt),"INFO");
        /* �������������� Ϊ���첽���ã���900016A����flow_batch_960031*/
        if(fpub_CallFlow(lXmlhandle,"flow_batch_910016A")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("BATCH: ��������ҵ��������ʧ��,flow_batch_910016A"),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_EXEC_FLOW,Fmtmsg(MSG_BATCH_EXEC_FLOW,"flow_batch_910016A"));
            iFlag = -2;
            break;
        }
        memset(&sdb_batch_plrw, 0x00, sizeof(sdb_batch_plrw));
    }
    DCIFreeCursor(cur);
    if( iFlag < 0 )
    {
        LOG(LM_STD,Fmtmsg("�����Զ�����ѭ����������ʧ��,sqlerr[%d]",iFlag ),"ERROR");
        return iFlag;
    }
    *piProcCnt = iProcCnt;
    *piPriProcHighReal = iPriProcHighReal;
    return iFlag;    
}
IRESULT SBATCH_AUTOTASK2(HXMLTREE lXmlhandle)
{
    int  iSetpCount/*,iflag=0*/,iAttribCount;
    int  iParas/*,iStepFlag=0*/;
    char sBuf[255];
    char sPkrq[8+1];
    char sKsrq[8+1];  /* ��ʼ���ڣ�Ĭ��ȡ��ǰ����ǰһ�� */
    char sSql[512];
    char sErrmsg[512];
    /*int  iSjtj = 0;     �����ύ������ */
    /*int  iInterval = 0;     �����ύ������ */
    /*int  iRunctlMax = 0;*/
    int  iDbTaskRun = 0;
    int  iProcCnt = 0;
    int  iPriProcHighReal = 0;
    int  iRet = -1;


    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHKMIN(2);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������"); 
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"��ʼ����");
    pstrcopy(sKsrq,sBuf,sizeof(sKsrq));

    /* У��Ӧ����������(����) */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf( sSql, sizeof( sSql ), "SELECT count(pkrq) FROM batch_plrw WHERE  pkrq = '%s' and rwzt = '9' ", sPkrq );
    memset(sBuf, 0x00, sizeof(sBuf));
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql);
    if( iRet < 0 )        
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    iDbTaskRun = atoi( sBuf );
    
    /*�߼��������ȴ���*/
    iRet = func_autotask2_assig(lXmlhandle, iDbTaskRun, sKsrq, sPkrq, "2", &iProcCnt, &iPriProcHighReal);
    if( iRet < 0 )        
    {
        LOG(LM_STD,Fmtmsg("�����Զ����񴥷�3-�߼�ʧ��[%d]", iRet ),"ERROR")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*�м�����ڶ�����*/
    iRet = func_autotask2_assig(lXmlhandle, iDbTaskRun, sKsrq, sPkrq, "1", &iProcCnt, &iPriProcHighReal);
    if( iRet < 0 )        
    {
        LOG(LM_STD,Fmtmsg("�����Զ����񴥷�2-�м�ʧ��[%d]", iRet ),"ERROR")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*�ͼ����������*/
    iRet = func_autotask2_assig(lXmlhandle, iDbTaskRun, sKsrq, sPkrq, "0", &iProcCnt, &iPriProcHighReal);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("�����Զ����񴥷�1-�ͼ�ʧ��[%d]", iRet ),"ERROR")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_DEBUG,Fmtmsg("����ҵ���Զ�����ִ�н���,������[%d]������",iProcCnt), fpub_GetCompname(lXmlhandle));
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_GETFLOWSN
�������:SBATCH_GETFLOWSN
�������: ����ҵ���ȡ�������
�������:
��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    

ʹ������:

�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_GETFLOWSN(HXMLTREE lXmlhandle)
{
    int /*iStepCount=0,*/iFlag=0,iAttribCount,jflag;
    int iParas;
    char sXmlNode[128];
    char sStepFlow[128];
    char sAttribvalue[128];
    char sBuf[128];
    int  iBdcgbz,ret;
    char flowStatus[11];
    char sStepSN[2];
    char sStepNm[8+1];
    char sFlowSnNode[64+1];
    char sPkRq[8+1];/*��������*/
    char sPtPch[8+1];/*ƽ̨���κ�*/
    char sDqbd[2+1];/*��ǰ����*/
    char sBdzt[1+1];/*����״̬*/
    char sFzbd[2+1];/*��������*/
    char sRwzt[1+1];/*����״̬*/
    char sFinalStep[4+1];/*��󲽵�*/
    char sFlowID[51];
    int  iFlowSn = 0;
    /*int  iIsExe = 0;ִ�б�־ 0-δִ�� 1-��ִ��*/
    int iRet = -1;
    BATCH_PLRWBD sdb_plrwbd;

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHKMIN(1)
  
    memset(sBuf,0,sizeof(sBuf));
    memset(sStepNm, 0x00, sizeof(sStepNm));
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    trim(sBuf);
    pstrcopy(sStepNm,sBuf,sizeof(sStepNm));
  
    memset(sBuf,0,sizeof(sBuf));
    memset(sFlowSnNode, 0x00, sizeof(sFlowSnNode));
    COMP_GETPARSEPARAS(2,sBuf,"������Ž��")
    trim(sBuf);
    pstrcopy(sFlowSnNode,sBuf,sizeof(sFlowSnNode));

    memset(sPkRq, 0x00, sizeof(sPkRq));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ, sBuf)
    pstrcopy(sPkRq, sBuf, sizeof(sPkRq));
    
    memset(sPtPch, 0x00, sizeof(sPtPch));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH, sBuf)
    pstrcopy(sPtPch, sBuf, sizeof(sPtPch));
    
    /* ��ʼ�����̵��������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFlowID, 0x00, sizeof(sFlowID));
    COMP_SOFTGETXML(XMLNM_BATCH_RUNCTRL_FLOWID, sBuf)
    pstrcopy(sFlowID, sBuf, sizeof(sFlowID));
    trim(sFlowID);
    LOG(LM_STD,Fmtmsg("����ҵ���ȡ�������ִ�п�ʼ...pkrq&ptpch[%s%s],FLOWID[%s]",
        sPkRq, sPtPch, sFlowID),fpub_GetCompname(lXmlhandle));
    iRet=fprv_initBatchFlow(lXmlhandle, sFlowID, &t_flowList);
    if( iRet <=0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:�޶�Ӧ����[%s]������Ϣ",sFlowID),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FLOWCFG_NOFUND,MSG_BATCH_FLOWCFG_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    iFlowSn = 1;
    /* ���̲���ѭ������ʼ */
    for( pflowIter = i_list_begin(t_flowList); 
        pflowIter!= i_list_end(t_flowList); 
        pflowIter = i_list_iter_next(pflowIter) )
    {        
        /*��ȷ��λ��Ԥ������*/
        pFlowcfg = (BATCH_FLOWCFG *)(pflowIter->data);
        trim(pFlowcfg->stepid);
        if ( strcmp(pFlowcfg->stepid, sStepNm) != 0 )
        {/*����,ֱ����λ��Ӧ����*/
            LOG(LM_STD,Fmtmsg("(����1)BATCH: ����ҵ���ȡ�������[%s,%s],��ǰ����[%s],��������[%d,%s],��������[%s]",\
                sPkRq, sPtPch, pFlowcfg->flowsn, 
                pFlowcfg->stepid, pFlowcfg->stepname), fpub_GetCompname(lXmlhandle));
            continue;
        }
        iFlowSn = pFlowcfg->flowsn;
        LOG(LM_STD,Fmtmsg("BATCH: ����ҵ���ȡ�������[%s%s],��ǰ����[%s],ִ�в���[%d,%s],��������[%s]",\
            sPkRq, sPtPch, sDqbd, pFlowcfg->flowsn, pFlowcfg->stepid, pFlowcfg->stepname), fpub_GetCompname(lXmlhandle));
    }
    prv_FlowListFree();
    LOG(LM_STD,Fmtmsg("BATCH: ����ҵ���ȡ�������-����[%s]--����iFlag[%d]",
        sFlowID, iFlag),"INFO");
    if(iFlag < 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    COMP_SOFTSETXML(sFlowSnNode, itoa(iFlowSn))

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
