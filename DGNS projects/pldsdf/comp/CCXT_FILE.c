/********************************************************************
 ��Ȩ����:�������ӹɷ����޹�˾
 ��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
 ��    ��:V3.0.00
 ����ϵͳ:AIX5.3
 �ļ�����:PLDSDF_FILE.c
 �ļ�����:����ҵ�����ļ�ӳ��-������ش���ת�������
 �� Ŀ ��:�м�ҵ����Ŀ��
 �� �� Ա:zengy
 ��������:2017-10-24
 ��    ��:
 �޸�����:  
 *********************************************************************/
/**********************************************************************
 ����˵��:
 ����˵��
 �����������                 �������                      ��������  ����Ա �޸����� �޸���
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gaps_head.h"
#include "xml.h"
#include "../eh/agent_batch_info.h"
#include "../../app/incl/APP_KHCPQY.h"

/************************************************************************
  ��̬�����������
  �����������: SPLDSDF_FILE_PRE_DEAL
  �������: �������մ����ļ�ǰ����

  �������: 
            �ļ�ǰ����: �ܱ������ܽ��У��; �ļ���ʽУ���
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: �м�ҵ����Ŀ��
  �� �� Ա: zhandd
  ��������: 2017��10��24��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SCCXTDS_FILE_PRE_DEAL(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas = 0;
    int iComStat = 0; /*���������*/
    long lTotCnt = 0; /*���ļ���ȡ�ı���*/
    double dTotAmt = 0.00;
    char line_count[20];
    char sSfbz[1+1];
    char sJybs[10];
    char sJyje[17];
    char sDsrq[8];
    char sDwbh[16+1];
    char sBuf[512];
    char sFileName[256+1];
    char sFilePath[256+1];
    char sNewFilePath[256+1];
    char sLine[1024];
    char sNewLine[1024];
    char sCmd[512];
    char sErrmsg[512];
    char sMd5[64];
    char sMd5_1[64];
    char sMd5_2[64];
    char sLast_line[256+1];
    char sWj_line[10]; /*�����ļ�����*/
    FILE *fp = NULL;

    SDB_AGENT_BATCH_INFO sdb_agent_batch_info;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG")

    /* ���������� */
    COMP_PARACOUNTCHKMIN(2)

    /* �ļ��� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sFileName, 0x00, sizeof(sFileName));
    COMP_GETPARSEPARAS(1, sBuf, "�����ļ���")
    trim(sBuf);
    pstrcopy(sFileName, sBuf, sizeof(sFileName));
    LOG(LM_DEBUG, Fmtmsg("�����ļ���[%s]", sFileName), "INFO")

    /* �ո���־ 1-��2-�� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sSfbz, 0x00, sizeof(sSfbz));
    COMP_GETPARSEPARAS(2, sBuf, "�ո���־")
    trim(sBuf);
    pstrcopy(sSfbz, sBuf, sizeof(sSfbz));
    LOG(LM_DEBUG, Fmtmsg("�ո���־[%s]", sSfbz), "INFO")

    memset(&sdb_agent_batch_info, 0x00, sizeof(sdb_agent_batch_info));

    /* ���κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/batch/req/shpch", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.batch_no, sBuf, sizeof(sdb_agent_batch_info.batch_no));
    LOG(LM_DEBUG, Fmtmsg("���κ�[%s]", sdb_agent_batch_info.batch_no), "INFO")

    /* ��Ʒ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/cpdm", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.cpdm, sBuf, sizeof(sdb_agent_batch_info.cpdm));
    LOG(LM_DEBUG, Fmtmsg("��Ʒ����[%s]", sdb_agent_batch_info.cpdm), "INFO")

    /* ��λ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.dwbh, sBuf, sizeof(sdb_agent_batch_info.dwbh));
    LOG(LM_DEBUG, Fmtmsg("��λ���[%s]", sdb_agent_batch_info.dwbh), "INFO")

    /* ԭ�ϴ��ļ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/ori_file_name", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.file_name, sBuf, sizeof(sdb_agent_batch_info.file_name));
    LOG(LM_DEBUG, Fmtmsg("ԭ�ϴ��ļ���[%s]", sdb_agent_batch_info.file_name), "INFO")

    /* �ϴ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zwrq", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.up_date, sBuf, sizeof(sdb_agent_batch_info.up_date));
    LOG(LM_DEBUG, Fmtmsg("�ϴ�����[%s]", sdb_agent_batch_info.up_date), "INFO")

    /* �ϴ���ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zhqzlsh", sBuf);
    sdb_agent_batch_info.up_seq_no = atol(sBuf);
    LOG(LM_DEBUG, Fmtmsg("�ϴ���ˮ��[%ld]", sdb_agent_batch_info.up_seq_no), "INFO")

    /* �ϴ�ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.up_time, sBuf, sizeof(sdb_agent_batch_info.up_time));
    LOG(LM_DEBUG, Fmtmsg("�ϴ�ʱ��[%s]", sdb_agent_batch_info.up_time), "INFO")

    /* �ϴ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/brc", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.up_unit, sBuf, sizeof(sdb_agent_batch_info.up_unit));
    LOG(LM_DEBUG, Fmtmsg("�ϴ�����[%s]", sdb_agent_batch_info.up_unit), "INFO")

    /* �ϴ���Ա */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/tel", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.up_teller, sBuf, sizeof(sdb_agent_batch_info.up_teller));
    LOG(LM_DEBUG, Fmtmsg("�ϴ���Ա[%s]", sdb_agent_batch_info.up_teller), "INFO")

    /* �ϴ�������ʶ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/qdbs", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.up_channel, sBuf, sizeof(sdb_agent_batch_info.up_channel));
    LOG(LM_DEBUG, Fmtmsg("�ϴ�������ʶ[%s]", sdb_agent_batch_info.up_channel), "INFO")

    /* �ϴ���ʽ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/scfs", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.upload_type, sBuf, sizeof(sdb_agent_batch_info.upload_type));
    LOG(LM_DEBUG, Fmtmsg("�ϴ���ʽ[%s]", sdb_agent_batch_info.upload_type), "INFO")

    /* �ո���־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/sfbz", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.dc_flag, sBuf, sizeof(sdb_agent_batch_info.dc_flag));
    LOG(LM_DEBUG, Fmtmsg("�ո���־[%s]", sdb_agent_batch_info.dc_flag), "INFO")

    /* ������������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/exec_date", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.exec_date, sBuf, sizeof(sdb_agent_batch_info.exec_date));
    LOG(LM_DEBUG, Fmtmsg("������������[%s]", sdb_agent_batch_info.exec_date), "INFO")
    if(strlen(sdb_agent_batch_info.exec_date) > 0 &&
        strcmp(sdb_agent_batch_info.exec_date, sdb_agent_batch_info.up_date) < 0)
    {
        fpub_SetMsg(lXmlhandle, 24103, "�����������ڲ���С�ڵ�ǰ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("�����������ڲ���С�ڵ�ǰ����"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    /* ժҪ���루�Ϻ���ʹ��) */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/batch/req/zydm", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.brief_code, sBuf, sizeof(sdb_agent_batch_info.brief_code));
    LOG(LM_DEBUG, Fmtmsg("ժҪ����[%s]", sdb_agent_batch_info.brief_code), "INFO")

    /* md5�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/MD5", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.md5_code, sBuf, sizeof(sdb_agent_batch_info.md5_code));
    LOG(LM_DEBUG, Fmtmsg("md5��[%s]", sdb_agent_batch_info.md5_code), "INFO")

    /* ״̬ 8-���������� */
    pstrcopy(sdb_agent_batch_info.stat, "8", sizeof(sdb_agent_batch_info.stat));
    
    /* �ļ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/wjlx", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.wjlx, sBuf, sizeof(sdb_agent_batch_info.wjlx));
    LOG(LM_DEBUG, Fmtmsg("�ļ�����[%s]", sdb_agent_batch_info.wjlx), "INFO")

    /* �����ļ��� */
    strcpy(sdb_agent_batch_info.ori_file_name, sFileName);
        
    memset(sFilePath, 0x00, sizeof(sFilePath));
    sprintf(sFilePath, "%s/file/batch/ccxt/%s", getenv("HOME"), sdb_agent_batch_info.ori_file_name);
    LOG(LM_DEBUG, Fmtmsg("ԭ���������ļ�[%s]", sFilePath), "INFO")
 
    /*�����ļ�����sWj_line*/
    iRet=fpub_ExecComp(lXmlhandle,"FILE_GetFileSize",&iComStat,3,sFilePath,"2","/agent/req/wj_line");
    if(iRet!=MID_SYS_SUCC || iComStat!=COMPSTATUS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, 24103, "�����ļ�����ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("�����ļ�����ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }
    memset(sWj_line, 0x00, sizeof(sWj_line));
    COMP_SOFTGETXML("/agent/req/wj_line", sWj_line);
    trim(sWj_line);
    LOG(LM_DEBUG, Fmtmsg("�ļ�����[%s]", sWj_line), "INFO")

    /*��ȡ�ļ����һ��,������Ϣ*/
    iRet=fpub_ExecComp(lXmlhandle,"FILE_LoadToX",&iComStat,5,"file_ccxt_hzxx",sFilePath,sWj_line,"0","/agent/file_hz");
    if(iRet!=MID_SYS_SUCC || iComStat!=COMPSTATUS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, 24103, "�����ļ�����ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("�����ļ�����ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/file_hz|1/zbs", sBuf);
    trim(sBuf);
    lTotCnt=atoi(sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/file_hz|1/zje", sBuf);
    trim(sBuf);
    dTotAmt=atof(sBuf); 
    sdb_agent_batch_info.tot_amt=dTotAmt;
    sdb_agent_batch_info.tot_cnt=lTotCnt;
    
    sprintf(sNewFilePath, "%s/file/pldsdf/%s.new",getenv("HOME"), sdb_agent_batch_info.ori_file_name);
    sprintf(sCmd,"cp %s %s",sFilePath,sNewFilePath);
    system(sCmd);
    
    if(lTotCnt != (atol(sWj_line)-1))
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("�ļ���������"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("�ļ��������� sWj_line=[%s] lTotCnt=[%d]",sWj_line,lTotCnt), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }
    if(lTotCnt <= 0)
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("�ļ���ϸ����Ϊ��"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("�ļ���ϸ����Ϊ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if(iRet != 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* �����������ո�������Ϣ�Ǽǲ� */
    iRet = DBInsert("agent_batch_info", SD_AGENT_BATCH_INFO, NUMELE(SD_AGENT_BATCH_INFO), &sdb_agent_batch_info, sErrmsg);
    if(iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        return COMPRET_FAIL;
    }

    if(DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        return COMPRET_FAIL;
    }
    LOG(LM_DEBUG, Fmtmsg("������ո�������Ϣ�Ǽǲ�agent_batch_info�ɹ�"), "INFO")

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG ,Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}
