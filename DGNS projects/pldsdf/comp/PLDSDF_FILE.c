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
/*
   ����˵��:
   ����˵��
   �����������                 �������                      ��������  ����Ա �޸����� �޸���

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gaps_head.h"
#include "xml.h"
/*#include "DRC_esb_md5.h"*/
#include "../eh/agent_batch_info.h"
#include "../eh/batch_dsdf_detail.h"
#include "../eh/pldsdf_custom_detail.h"

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
  �� �� Ա: zengy
  ��������: 2017��10��24��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SPLDSDF_FILE_PRE_DEAL(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    double dTotAmt = 0.00;
    char sSfbz[1+1];
    char sDwbh[16+1];
    /*char sBuf[512];*/
    char sBuf[1024];
    char sFileName[256+1];
    char sFilePath[256+1];
    char sNewFilePath[256+1];
    /*char sLine[1024];*/
    char sLine[3072];
    /*char sNewLine[1024];*/
    char sNewLine[4072];
    char sCmd[512];
    char sErrmsg[512];
    char sMd5[64];
    char sMd5_1[64];
    char sMd5_2[64];
    FILE *fp = NULL;
    FILE *newfp = NULL;
    SDB_AGENT_BATCH_INFO sdb_agent_batch_info;
    
    char sUpdateflag[1+1];
    char sCondition[120+1];

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
    COMP_SOFTGETXML("/sys/sysdate", sBuf);
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
/*add by llh 20180319 begin*/    
    /* �ļ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/wjlx", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.wjlx, sBuf, sizeof(sdb_agent_batch_info.wjlx));
    LOG(LM_DEBUG, Fmtmsg("�ļ�����[%s]", sdb_agent_batch_info.wjlx), "INFO")
    
    /* �Զ����˱�־ 0-�� 1-��*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/zdrzbz", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.zdrzbz, sBuf, sizeof(sdb_agent_batch_info.zdrzbz));
    LOG(LM_DEBUG, Fmtmsg("�Զ����˱�־[%s]", sdb_agent_batch_info.zdrzbz), "INFO")
    
    /* ִ��ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/zxsj", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.zxsj, sBuf, sizeof(sdb_agent_batch_info.zxsj));
    LOG(LM_DEBUG, Fmtmsg("ִ��ʱ��[%s]", sdb_agent_batch_info.zxsj), "INFO")
/*add by llh 20180319 end*/    

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
    
/*modify by llh 20180319 begin*/
#if 0
    /* ״̬ 8-���������� */
    pstrcopy(sdb_agent_batch_info.stat, "8", sizeof(sdb_agent_batch_info.stat));
#endif
    if(strcmp(sdb_agent_batch_info.zdrzbz,"1") == 0)
    {
        /* ״̬ 8-���������� */
        pstrcopy(sdb_agent_batch_info.stat, "8", sizeof(sdb_agent_batch_info.stat));
    }else if(strcmp(sdb_agent_batch_info.zdrzbz,"0") == 0)
    {
        /* ״̬��ֵΪ�� */
        pstrcopy(sdb_agent_batch_info.stat, "", sizeof(sdb_agent_batch_info.stat));
    }
	/*�ļ�����Ϊ����ʱ�Ĵ���*/
	if(strcmp(sdb_agent_batch_info.wjlx,"0") == 0)
	{
		pstrcopy(sdb_agent_batch_info.fkfz,sdb_agent_batch_info.brief_code,sizeof(sdb_agent_batch_info.fkfz));
		pstrcopy(sdb_agent_batch_info.lqzjsj,sdb_agent_batch_info.zxsj,sizeof(sdb_agent_batch_info.lqzjsj));
		memset(sdb_agent_batch_info.brief_code,0x00,sizeof(sdb_agent_batch_info.brief_code));
		memset(sdb_agent_batch_info.zxsj,0x00,sizeof(sdb_agent_batch_info.zxsj));

	}
/*modify by llh 20180319 end*/
    
    /* �ܱ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/total_cnt", sBuf);
    sdb_agent_batch_info.tot_cnt = atol(sBuf);
    LOG(LM_DEBUG, Fmtmsg("�ܱ���[%ld]", sdb_agent_batch_info.tot_cnt), "INFO")

    /* �ܽ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/total_amt", sBuf);
    sdb_agent_batch_info.tot_amt = atof(sBuf);
    LOG(LM_DEBUG, Fmtmsg("�ܽ��[%.2lf]", sdb_agent_batch_info.tot_amt), "INFO")

    /* �ļ�������.zipѹ���ļ�����Ҫ���н�ѹ */
    if(strncmp(sFileName+strlen(sFileName)-4, ".zip", 4) == 0)
    {
        memset(sCmd, 0x00, sizeof(sCmd));
        sprintf(sCmd, "cd %s/file/batch/dsf && unzip -o %s 1>>/home/gapsv4/tmp/gapssh%s.std 2>>/home/gapsv4/tmp/gapssh%s.err",
            getenv("HOME"), sFileName, sdb_agent_batch_info.up_date, sdb_agent_batch_info.up_date);
        if(system(sCmd) != 0)
        {
            fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("��ѹ�ļ�[%s]ʧ��", sFileName));
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOG(LM_STD, Fmtmsg("��ѹ�ļ�[%s]ʧ��", sFileName), fpub_GetCompname(lXmlhandle))
            return COMPRET_FAIL;
        }

        /* �����ļ��� */
        strncpy(sdb_agent_batch_info.ori_file_name, sFileName, strlen(sFileName)-4);
    }
    else
    {
        /* �����ļ��� */
        strcpy(sdb_agent_batch_info.ori_file_name, sFileName);
    }
    memset(sFilePath, 0x00, sizeof(sFilePath));
    sprintf(sFilePath, "%s/file/batch/dsf/%s", getenv("HOME"), sdb_agent_batch_info.ori_file_name);

    LOG(LM_DEBUG, Fmtmsg("ԭ���������ļ�[%s]", sFilePath), "INFO")
    /*LOG(LM_DEBUG, Fmtmsg("aaaaaa"), "INFO")*/
    /* У��md5�룬�����������txt��ʽ�ļ���md5�룬���ѹ��Ƚ� */
    memset(sMd5, 0x00, sizeof(sMd5));
    DRC_getMd5File(sFilePath, sMd5);
	int iCompStat=1;
/*	if(fpub_ExecComp(lXmlhandle,"DRC_GETMD5",&iCompStat,3,"1",sFilePath,"/agent/tmp/md5") != 0)
	{
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("MD5��У��ʧ��"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("MD5��У��ʧ��[%s]", sMd5), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
	}
    COMP_SOFTGETXML("/agent/tmp/md5", sMd5);*/
    trim(sMd5);
    LOG(LM_DEBUG, Fmtmsg("sFilePath[%s]sMd5[%s]", sFilePath,sMd5), "INFO")
    memset(sMd5_1, 0x00, sizeof(sMd5_1));
    memset(sMd5_2, 0x00, sizeof(sMd5_2));
    strcpy(sMd5_1, strtoupper(sdb_agent_batch_info.md5_code));
    strcpy(sMd5_2, strtoupper(sMd5));
    trim(sMd5_1);
    trim(sMd5_2);
    LOG(LM_DEBUG, Fmtmsg("sMd5_1[%s]sMd5_2[%s]", sMd5_1,sMd5_2), "INFO")
    if(strcmp(sMd5_1, sMd5_2) != 0)
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("MD5��У��ʧ��"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("MD5��У��ʧ��[%s]", sMd5), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    /* ���ļ� */
    memset(sNewFilePath, 0x00, sizeof(sNewFilePath));
    sprintf(sNewFilePath, "%s/file/pldsdf/%s.new", getenv("HOME"),sdb_agent_batch_info.ori_file_name);
    /*sprintf(sNewFilePath, "%s/file/pldsdf/%s/%s.new", getenv("HOME"), sdb_agent_batch_info.up_date,sdb_agent_batch_info.ori_file_name);*/

    /* ��ԭ�����ļ�����Ϊ�ɸ�ʽ����ת��Ϊ���ļ���ʽ */
    fp = fopen(sFilePath, "r");
    if(fp == NULL)
    {
        fpub_SetMsg(lXmlhandle, 24103, "���ļ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    newfp = fopen(sNewFilePath, "w");
    if(newfp == NULL)
    {
        fclose(fp);
        fpub_SetMsg(lXmlhandle, 24103, "���ļ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    memset(sLine, 0x00, sizeof(sLine));
    while(fgets(sLine, sizeof(sLine)-1, fp) != NULL)
    {
        /* �ж��Ƿ���У�����ֱ������ */
        memset(sNewLine, 0x00, sizeof(sNewLine));
        sprintf(sNewLine, "%s", sLine);
        trim(sNewLine);
        if(strlen(sNewLine) == 0)
        {
            continue;
        }

        /* ȥ�����һ�����з� */
        sLine[strlen(sLine)-1]=0;
        if(sLine[strlen(sLine)-1] == 0x0d) /* ȥ��ĩβ��(^M) */
        {
            sLine[strlen(sLine)-1]=0;
        }

        lTotCnt++;
        LOG(LM_DEBUG, Fmtmsg("sLine[%s]", sLine), "INFO")

        /* �ո���־ 1-�� 2-�� */
        if(strcmp(sSfbz, "1") == 0) /* ���� */
        {
            /* ����, �жϵ�λ����Ƿ�һ��, ���ո�ʽ��:��λ���=210344;version=1.2 */
            if(lTotCnt == 1)
            {
                memset(sDwbh, 0x00, sizeof(sDwbh));
                memset(sBuf, 0x00, sizeof(sBuf));
                GetListbyDiv(sLine, 1, sBuf, ';', '\\');
                strncpy(sDwbh, sBuf+9, 16);
                trim(sDwbh);

                if(strcmp(sDwbh, sdb_agent_batch_info.dwbh) != 0)
                {
                    fclose(fp);
                    fclose(newfp);
                    fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("��λ������ļ���[%s]��һ��", sDwbh));
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD, Fmtmsg("��λ������ļ���[%s]��һ��", sDwbh), fpub_GetCompname(lXmlhandle))
                    return COMPRET_FAIL;
                }

                /* ������д�����ļ� */
                fprintf(newfp, "��λ��ţ�%s;\n", sDwbh);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            /* ��ϸ�¸�ʽ����:
               ���|��ͬ��|��������|�ͻ��˺�|����|�ܽ��|ҵ����|����1|����2|��ע|
               ����|����3|����4|����5|
            */

            /* 6.��� */
            memset(sBuf, 0x00, sizeof(sBuf));
            GetListbyDiv(sLine, 6, sBuf, '|', '\\');
            dTotAmt += atof(sBuf);

            /* 10.��ע, ���ļ���ʽ������10����, ���ļ���ʽ��14����, �ɸ�ʽ���¸�ʽ����14�� */
            memset(sBuf, 0x00, sizeof(sBuf));
            if(GetListbyDiv(sLine, 10, sBuf, '|', '\\') == -1)
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            memset(sNewLine, 0x00, sizeof(sNewLine));
            if(GetListbyDiv(sLine, 11, sBuf, '|', '\\') == -1) /* 11.���� */
            {
                sprintf(sNewLine, "%s%-62s|%-13s|%-13|%-13s|",
                    sLine, " ", " ", " ", " ");

                /* ����ϸ��д�����ļ� */
                fprintf(newfp, "%s\n", sNewLine);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            if(GetListbyDiv(sLine, 14, sBuf, '|', '\\') == -1) /* 14.����5 */
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            if(GetListbyDiv(sLine, 15, sBuf, '|', '\\') > 0) /* ������15�� */
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            /* ����ϸ��д�����ļ� */
            fprintf(newfp, "%s\n", sLine);
            memset(sLine, 0x00, sizeof(sLine));
        }
        else /* ���� */
        {
            /* ����, �жϵ�λ����Ƿ�һ��, ������ʽ��:��λ��ţ�210344;version=1.2 */
            if(lTotCnt == 1)
            {
                memset(sDwbh, 0x00, sizeof(sDwbh));
                memset(sBuf, 0x00, sizeof(sBuf));
                GetListbyDiv(sLine, 1, sBuf, ';', '\\');
                strncpy(sDwbh, sBuf+10, 16);
                trim(sDwbh);

                if(strcmp(sDwbh, sdb_agent_batch_info.dwbh) != 0)
                {
                    fclose(fp);
                    fclose(newfp);
                    fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("��λ������ļ���[%s]��һ��", sDwbh));
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD, Fmtmsg("��λ������ļ���[%s]��һ��", sDwbh), fpub_GetCompname(lXmlhandle))
                    return COMPRET_FAIL;
                }

                /* ������д�����ļ� */
                fprintf(newfp, "��λ��ţ�%s;\n", sDwbh);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            /* ��ϸ�¸�ʽ����:
               ����|���|���׹�Ա|�����־|����|�˺�|���|����|֤������|֤������|֤����Ч��|�Ա�|��������|��ַ|��֤����|��������|�绰����|״̬|
               �Է��к�|�Է�������|����|��ע|ְҵ|������λ|˰�վ������|ת������|
            */

            /* 7.��� */
            memset(sBuf, 0x00, sizeof(sBuf));
            GetListbyDiv(sLine, 7, sBuf, '|', '\\');
            dTotAmt += atof(sBuf);

            /* 18.״̬, ���ļ���ʽ������18��22����, ���ļ���ʽ��25����, �ɸ�ʽ���¸�ʽ����25�� */
            memset(sBuf, 0x00, sizeof(sBuf));
            if(GetListbyDiv(sLine, 18, sBuf, '|', '\\') == -1)
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            memset(sNewLine, 0x00, sizeof(sNewLine));
            if(GetListbyDiv(sLine, 19, sBuf, '|', '\\') == -1) /* 19.�Է��к� */
            {
                /*sprintf(sNewLine, "%s%-14s|%-100s|%-62s|%-62s|%-10s|%-42s|%-1s|",
                    sLine, " ", " ", " ", " ", " ", " ", " ");*/
                sprintf(sNewLine, "%s%-14s|%-100s|%-62s|%-62s|%-10s|%-42s|%-1s|%s|%s|",
                    sLine, " ", " ", " ", " ", " ", " ", " "," "," ");

                /* ����ϸ��д�����ļ� */
                fprintf(newfp, "%s\n", sNewLine);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            if(GetListbyDiv(sLine, 22, sBuf, '|', '\\') == -1) /* 22.��ע */
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            if(GetListbyDiv(sLine, 23, sBuf, '|', '\\') == -1) /* 23.ְҵ */
            {
                /*sprintf(sNewLine, "%s%-10s|%-42s|%-1s|",
                    sLine, " ", " ", " ");*/
                sprintf(sNewLine, "%s%-10s|%-42s|%-1s|%s|%s|",
                    sLine, " ", " ", " "," "," ");

                /* ����ϸ��д�����ļ� */
                fprintf(newfp, "%s\n", sNewLine);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            if(GetListbyDiv(sLine, 25, sBuf, '|', '\\') == -1) /* 25.˰�վ������ */
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }
            
            if(GetListbyDiv(sLine, 26, sBuf, '|', '\\') == -1) /* 26.��չ1 */
            {
                sprintf(sNewLine, "%s%s|%s|",
                    sLine, " ", " ");

                /* ����ϸ��д�����ļ� */
                fprintf(newfp, "%s\n", sNewLine);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            /*if(GetListbyDiv(sLine, 26, sBuf, '|', '\\') >= 0)  ������26�� */
            if(GetListbyDiv(sLine, 28, sBuf, '|', '\\') >= 0) /* ������28�� */
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("��[%ld]���ļ���ϸ��ʽ����", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            /* ����ϸ��д�����ļ� */
            fprintf(newfp, "%s\n", sLine);
            memset(sLine, 0x00, sizeof(sLine));
        }
    }
    fclose(fp);
    fclose(newfp);

    lTotCnt = lTotCnt-1;
    if(lTotCnt <= 0)
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("�ļ���ϸ����Ϊ��"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("�ļ���ϸ����Ϊ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    /* У���ܱ������ܽ�� */
    if(sdb_agent_batch_info.tot_cnt != lTotCnt)
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("���ļ���ϸ�ܱ���[%ld]����", lTotCnt));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("���ļ���ϸ�ܱ���[%ld]����", lTotCnt), fpub_GetCompname(lXmlhandle))
		LOG(LM_DEBUG, Fmtmsg("aaaaaa"), "INFO");
        return COMPRET_FAIL;
    }
	LOG(LM_DEBUG, Fmtmsg("aaaaaa"), "INFO");

    if((sdb_agent_batch_info.tot_amt - dTotAmt) > 0.00001 ||
       (sdb_agent_batch_info.tot_amt - dTotAmt) < -0.00001)
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("���ļ���ϸ�ܽ��[%.2lf]����", dTotAmt));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("���ļ���ϸ�ܽ��[%.2lf]����", dTotAmt), fpub_GetCompname(lXmlhandle))
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
#if 0
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
#endif
/*add by llh 20180319 begin*/
    /* ���ݿ���±�־ 0-���� 1-����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sUpdateflag, 0x00, sizeof(sUpdateflag));
    COMP_SOFTGETXML("/agent/req/updateflag", sBuf);
    trim(sBuf);
    pstrcopy(sUpdateflag, sBuf, sizeof(sUpdateflag));
    LOG(LM_DEBUG, Fmtmsg("���ݿ���±�־[%s]", sUpdateflag), "INFO");
	sprintf(sdb_agent_batch_info.extfld1,"%s%s",sdb_agent_batch_info.up_date,sdb_agent_batch_info.up_time);
    
    if(strcmp(sUpdateflag,"0") == 0)
    {
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
    }else if(strcmp(sUpdateflag,"1") == 0)
    {
        memset(sCondition, 0x00, sizeof(sCondition));
        sprintf(sCondition,"batch_no='%s'",sdb_agent_batch_info.batch_no);
        /* �����������ո�������Ϣ�Ǽǲ� */
        iRet = DBUpdate("agent_batch_info", SD_AGENT_BATCH_INFO, NUMELE(SD_AGENT_BATCH_INFO), &sdb_agent_batch_info, sCondition, sErrmsg);
        if(iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            DCIRollback();
            return COMPRET_FAIL;
        }
    }
/*add by llh 20180319 end*/

    if(DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        return COMPRET_FAIL;
    }
    LOG(LM_DEBUG, Fmtmsg("������ո�������Ϣ�Ǽǲ�agent_batch_info�ɹ�"), "INFO")
	LOG(LM_DEBUG, Fmtmsg("aaaaaa"), "INFO");

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
	LOG(LM_DEBUG, Fmtmsg("aaaaaa"), "INFO");
    LOG(LM_DEBUG ,Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: SPLDSDF_FILE_GEN
  �������: �������մ��������ļ����ɴ���

  �������: 
            ���ɽ�������ļ�
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: �м�ҵ����Ŀ��
  �� �� Ա: zengy
  ��������: 2017��10��24��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SPLDSDF_FILE_GEN(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    char sBatchNo[32+1];
    char sSfbz[1+1];
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sDwbh[16+1];
    char sStat[1+1];
    char sDownFlag[1+1];
    char sBuf[512];
    char sFileName[256+1];
    char sFilePath[512+1];
    char sLine[1024];
    char sTableName[64];
    char sErrmsg[512];
    char sSql[1024];
    FILE *fp = NULL;
    SDB_BATCH_DSDF_DETAIL sdb_batch_dsdf_detail;
    CURSOR plcur;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG")

    /* ���������� */
    COMP_PARACOUNTCHKMIN(2)

    /* �̻����κ� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sBatchNo, 0x00, sizeof(sBatchNo));
    COMP_GETPARSEPARAS(1, sBuf, "�̻����κ�")
    trim(sBuf);
    pstrcopy(sBatchNo, sBuf, sizeof(sBatchNo));
    LOG(LM_DEBUG, Fmtmsg("�̻����κ�[%s]", sBatchNo), "INFO")

    /* �ո���־ 1-��2-�� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sSfbz, 0x00, sizeof(sSfbz));
    COMP_GETPARSEPARAS(2, sBuf, "�ո���־")
    trim(sBuf);
    pstrcopy(sSfbz, sBuf, sizeof(sSfbz));
    LOG(LM_DEBUG, Fmtmsg("�ո���־[%s]", sSfbz), "INFO")

    /* ҵ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTableName, 0x00, sizeof(sTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", sBuf);
    trim(sBuf);
    pstrcopy(sTableName, sBuf, sizeof(sTableName));
    LOG(LM_DEBUG, Fmtmsg("ҵ�����[%s]", sTableName), "INFO")

    /* �������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML("/batch/resp/pkrq", sBuf);
    trim(sBuf);
    pstrcopy(sPkrq, sBuf, sizeof(sPkrq));
    LOG(LM_DEBUG, Fmtmsg("��������[%s]", sPkrq), "INFO")

    /* ƽ̨���κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML("/batch/resp/ptpch", sBuf);
    trim(sBuf);
    pstrcopy(sPtpch, sBuf, sizeof(sPtpch));
    LOG(LM_DEBUG, Fmtmsg("ƽ̨���κ�[%s]", sPtpch), "INFO")

    /* ��λ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDwbh, 0x00, sizeof(sDwbh));
    COMP_SOFTGETXML("/agent/resp/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sDwbh, sBuf, sizeof(sDwbh));
    LOG(LM_DEBUG, Fmtmsg("��λ���[%s]", sDwbh), "INFO")

    /* �ļ����ر�־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDownFlag, 0x00, sizeof(sDownFlag));
    COMP_SOFTGETXML("/agent/req/down_flag", sBuf);
    trim(sBuf);
    pstrcopy(sDownFlag, sBuf, sizeof(sDownFlag));
    LOG(LM_DEBUG, Fmtmsg("�ļ����ر�־[%s]", sDownFlag), "INFO")

    /* ���̽���ļ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFileName, 0x00, sizeof(sFileName));
    memset(sFilePath, 0x00, sizeof(sFilePath));
    COMP_SOFTGETXML("/batch/stepcfg/info/hqsj/attribvalue", sBuf);
    trim(sBuf);
    sprintf(sFileName, "%s_%s_%s_RT"/*"%s_%s_%s_RT.txt"*/, sDwbh, sPkrq, sPtpch);
    sprintf(sFilePath, "%s/%s/%s", getenv("HOME"), sBuf, sFileName);
    LOG(LM_DEBUG, Fmtmsg("���ɻ��̽���ļ���[%s]", sFilePath), "INFO")

    fp = fopen(sFilePath, "w");
    if(fp == NULL)
    {
        fpub_SetMsg(lXmlhandle, 24103, "���ļ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select * from %s where wbpch='%s' order by wbxh asc", sTableName, sBatchNo);

    if((plcur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if(DCIExecute(plcur) == -1)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sql[%s] err[%s]", sSql, DCILastError()), "ERROR")
        DCIFreeCursor(plcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* д���� */
    fprintf(fp, "��λ��ţ�%s\n", sDwbh);

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    while((iRet = DBFetch(plcur, SD_BATCH_DSDF_DETAIL, NUMELE(SD_BATCH_DSDF_DETAIL), &sdb_batch_dsdf_detail, sErrmsg ) ) > 0 )
    {
        lTotCnt++;

        /* ���ݵļ�¼״̬��0����ʼ1���ɹ�2��ʧ�� */
        memset(sStat, 0x00, sizeof(sStat));
        trim(sdb_batch_dsdf_detail.cgbz);
        trim(sdb_batch_dsdf_detail.zjxym);
        trim(sdb_batch_dsdf_detail.zjxyxx);
        trim(sdb_batch_dsdf_detail.xym);
        trim(sdb_batch_dsdf_detail.xyxx);
        trim(sdb_batch_dsdf_detail.jlbs);
        /* �ɹ���־ 0-�ɹ� 1-���ֳɹ� 2-ʧ�� 9-��ʼ */
        /*sStat-��¼״̬��0-��ʼ 1-�ɹ� 2-ʧ��*/
        if(sdb_batch_dsdf_detail.cgbz[0] == '0' || sdb_batch_dsdf_detail.cgbz[0] == '1')
        {
            strcpy(sdb_batch_dsdf_detail.zjxym, "AGR0015");
            /*if(sdb_batch_dsdf_detail.jlbs[0] == '0')*/
            if(sdb_batch_dsdf_detail.jlbs[0] == '1'||
				sdb_batch_dsdf_detail.jlbs[0] == '2'||
				sdb_batch_dsdf_detail.jlbs[0] == '3')
            {
                strcpy(sdb_batch_dsdf_detail.zjxym, "AGR0056");  /* �����ɹ� */
            }
            strcpy(sdb_batch_dsdf_detail.zjxyxx, "���˳ɹ�");
            strcpy(sStat, "1");
        }
        else if(sdb_batch_dsdf_detail.cgbz[0] == '2') 
           /* strlen(sdb_batch_dsdf_detail.zjxym) == 0
            strlen(sdb_batch_dsdf_detail.zjxyxx) == 0)*/
        {
            if(strlen(sdb_batch_dsdf_detail.zjxym) == 0)
                strcpy(sdb_batch_dsdf_detail.zjxym, sdb_batch_dsdf_detail.xym);
            if(strlen(sdb_batch_dsdf_detail.zjxyxx) == 0)
                strcpy(sdb_batch_dsdf_detail.zjxyxx, sdb_batch_dsdf_detail.xyxx);

            strcpy(sStat, "2");
            if(strlen(sdb_batch_dsdf_detail.zjxyxx) == 0) /* ����ȫ��ʧ��ʱ���ǼǴ�����Ϣ��kzzd7�� */
            {
                strcpy(sdb_batch_dsdf_detail.zjxyxx, sdb_batch_dsdf_detail.kzzd7);
            }
        }
        else
        {
            strcpy(sStat, "2");
        }

        /* ������ķ�����Ӧ��Ϊ�գ���ʹ��ACR2938��ΪĬ�� */
        trim(sdb_batch_dsdf_detail.zjxym);
        if(strlen(sdb_batch_dsdf_detail.zjxym) == 0)
        {
            strcpy(sdb_batch_dsdf_detail.zjxym, "ACR2938");
        }

        /* �ո���־ 1-�� 2-�� */
        memset(sLine, 0x00, sizeof(sLine));
        if(strcmp(sSfbz, "1") == 0) /* ���� */
        {
            /*���ļ���ʽ
            ���
            ��ͬ��
            ��������
            ����
            �����˺�
            Ӧ���ܽ��
            ʵ���ܽ��
            Ӧ��ҵ�����
            ʵ��ҵ�����
            Ӧ�չ�������1
            ʵ�չ�������1
            Ӧ�չ�������2
            ʵ�չ�������2
            ��������
            ���з�����
            ���з���������˵��
            */
            sprintf(sLine,"%-7ld|%-20s|%-8s|%-42s|%-18s|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%-8s|%-4s|%-60s|",
                  sdb_batch_dsdf_detail.wbxh,
                  sdb_batch_dsdf_detail.yhh1,
                  sdb_batch_dsdf_detail.kxrq,
                  sdb_batch_dsdf_detail.fkrxm,
                  sdb_batch_dsdf_detail.fkrzh,
                  sdb_batch_dsdf_detail.jyje,
                  sdb_batch_dsdf_detail.sjje,
                  sdb_batch_dsdf_detail.ywje,
                  sdb_batch_dsdf_detail.sjywje,
                  sdb_batch_dsdf_detail.fyje1,
                  sdb_batch_dsdf_detail.sjfyje1,
                  sdb_batch_dsdf_detail.fyje2,
                  sdb_batch_dsdf_detail.sjfyje2,
                  sdb_batch_dsdf_detail.zwrq,
                  sdb_batch_dsdf_detail.xym,
                  sdb_batch_dsdf_detail.xyxx);
        }
        else /* ���� */
        {
            trim(sdb_batch_dsdf_detail.wbpch);
            trim(sdb_batch_dsdf_detail.skrzh);
            trim(sdb_batch_dsdf_detail.zjhm);
            trim(sdb_batch_dsdf_detail.kzzd6);
            trim(sdb_batch_dsdf_detail.zwrq);
            trim(sdb_batch_dsdf_detail.zjxym);
            trim(sdb_batch_dsdf_detail.zjxyxx);
            /* �ɸ�ʽ 
               ���������ļ���ʽ
                  ���κ�	16A
                  ���	7A
                  �ͻ��˺�	19A
                  ֤������	20A
                  ����	42A
                  �ͻ�Ӧ�����	13P2
                  �ͻ�ʵ�����	13P2
                  ��������	8P0
                  ��¼״̬	1A
                  ��Ϣ��ʶ	7A
                  ��ʶ����˵��	40A
            */
            sprintf(sLine, "%-16s|%07d|%-19s|%-20s|%-42s|%013.2lf|%013.2lf|%-8s|%-1s|%-7s|%-40s|",
            //sprintf(sLine, "%s|%d|%s|%s|%s|%lf|%f|%s|%s|%s|%s|",
                    sdb_batch_dsdf_detail.wbpch,
                    sdb_batch_dsdf_detail.wbxh,
                    sdb_batch_dsdf_detail.skrzh,
                    sdb_batch_dsdf_detail.zjhm,
                    sdb_batch_dsdf_detail.kzzd6,
                    sdb_batch_dsdf_detail.jyje,
                    sdb_batch_dsdf_detail.sjje,
                    sdb_batch_dsdf_detail.zwrq,
                    sStat,
                    sdb_batch_dsdf_detail.zjxym,
                    sdb_batch_dsdf_detail.zjxyxx);
        }

        /* д����ϸ�� */
        fprintf(fp, "%s\n", sLine);
        memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    }

    if(iRet < 0)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIFreeCursor(plcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(plcur);

    fclose(fp);

    LOG(LM_DEBUG, Fmtmsg("��д��[%ld]�ʼ�¼�����̽���ļ�", lTotCnt), "DEBUG")
    if(lTotCnt<=0)
    {
        fpub_SetMsg(lXmlhandle, 24103, "��ѯ������Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("��ѯ������Ϣʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML("/batch/resp/ret_file_name", sFileName);

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: SPLDSDF_SJTJ_DF
  �������: �������մ��������ύ���Ի�����_����

  �������: 
            �����ύ���Ի�����_����
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: �м�ҵ����Ŀ��
  �� �� Ա: zengy
  ��������: 2017��10��24��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SPLDSDF_SJTJ_DF(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    double dChargeAmt = 0.00;
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sDwbh[16+1];
    char sSxfbz[1+1];
    char sJlbs[32+1];
    char sBuf[512];
    char sTableName[64];
    char sErrmsg[512];
    char sSql[1024];
    char sUpdSql[1024];
    char jslx[1+1];
    char sxxkz[1+1];
    char sJscs[18];
    char sXxje[18];
    char sSxje[18];
    double jscs = 0.00;
    double xxje = 0.00;
    double sxje = 0.00;
    SDB_BATCH_DSDF_DETAIL sdb_batch_dsdf_detail;
    CURSOR plcurdel;
    
    char sBatchno[32+1];
    char sWjlx[1+1];

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG")

    /* ���������� */

    /* ҵ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTableName, 0x00, sizeof(sTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", sBuf);
    trim(sBuf);
    pstrcopy(sTableName, sBuf, sizeof(sTableName));
    LOG(LM_DEBUG, Fmtmsg("ҵ�����[%s]", sTableName), "INFO")

    /* �������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML("/batch/pkrq", sBuf);
    trim(sBuf);
    pstrcopy(sPkrq, sBuf, sizeof(sPkrq));
    LOG(LM_DEBUG, Fmtmsg("��������[%s]", sPkrq), "INFO")

    /* ƽ̨���κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML("/batch/ptpch", sBuf);
    trim(sBuf);
    pstrcopy(sPtpch, sBuf, sizeof(sPtpch));
    LOG(LM_DEBUG, Fmtmsg("ƽ̨���κ�[%s]", sPtpch), "INFO")
    
    /* ���κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sBatchno, 0x00, sizeof(sBatchno));
    COMP_SOFTGETXML("/agent/req/batch_no", sBuf);
    trim(sBuf);
    pstrcopy(sBatchno, sBuf, sizeof(sBatchno));
    LOG(LM_DEBUG, Fmtmsg("���κ�[%s]", sBatchno), "INFO")

    /* ��λ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDwbh, 0x00, sizeof(sDwbh));
    COMP_SOFTGETXML("/agent/req/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sDwbh, sBuf, sizeof(sDwbh));
    LOG(LM_DEBUG, Fmtmsg("��λ���[%s]", sDwbh), "INFO")

    /* �����ѱ�־ 0-��ȡ 1-����ȡ */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSxfbz, 0x00, sizeof(sSxfbz));
    COMP_SOFTGETXML("/agent/req/sxfbz", sBuf);
    trim(sBuf);
    pstrcopy(sSxfbz, sBuf, sizeof(sSxfbz));
    LOG(LM_DEBUG, Fmtmsg("�����ѱ�־[%s]", sSxfbz), "INFO")

    if(sSxfbz[0] == '0')
    {
        /* ��ѯ������Ϣ */
        memset(sSql, 0x00, sizeof(sSql));
        memset(jslx, 0x00, sizeof(jslx));
        memset(sxxkz, 0x00, sizeof(sxxkz));
        memset(sJscs, 0x00, sizeof(sJscs));
        memset(sXxje, 0x00, sizeof(sXxje));
        memset(sSxje, 0x00, sizeof(sSxje));
        jscs = 0.00;
        xxje = 0.00;
        sxje = 0.00;
        snprintf(sSql, sizeof(sSql), "SELECT jslx, jscs, sxxkz, xxje, sxje FROM APP_SXFFL WHERE flbs='%s' FETCH FIRST 1 ROWS ONLY", sDwbh);
        iRet = DBSelectToMultiVarChar(sErrmsg, sSql, jslx, sJscs, sxxkz, sXxje, sSxje);
        if(iRet == 0)
        {
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        else if(iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG, Fmtmsg("�����Ѳ���[%s][%s][%s][%s][%s]", jslx, sJscs, sxxkz, sXxje, sSxje), "INFO")
        jscs = atof(sJscs);
        xxje = atof(sXxje);
        sxje = atof(sSxje);
    }
    
    /******
    add by llh 20180509 begin
    ******/
    memset(sSql, 0x00, sizeof(sSql));
    memset(sWjlx, 0x00, sizeof(sWjlx));
    snprintf(sSql, sizeof(sSql), "select wjlx from agent_batch_info WHERE batch_no='%s'", sBatchno);
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql, sWjlx);
    if(iRet == 0)
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    else if(iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_DEBUG, Fmtmsg("sWjlx[%s]", sWjlx), "INFO")
    /******
    add by llh 20180509 end
    ******/

    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select * from %s where pkrq='%s' and ptpch='%s' and shzt !='1' and clzt='9'", sTableName, sPkrq, sPtpch);
    LOG(LM_DEBUG, Fmtmsg("sql[%s]", sSql), "INFO")
    if((plcurdel = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if(DCIExecute(plcurdel) == -1)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sql[%s] err[%s]", sSql, DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if(iRet != 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    while((iRet = DBFetch(plcurdel, SD_BATCH_DSDF_DETAIL, NUMELE(SD_BATCH_DSDF_DETAIL), &sdb_batch_dsdf_detail, sErrmsg ) ) > 0 )
    {
        dChargeAmt = 0.00;
        if(sSxfbz[0] == '0' && strcmp(sWjlx,"0")!= 0)
        {
            if(jslx[0] == '1') /* �����������Ϊ��� */
            {
                dChargeAmt = jscs;
            }
            else if(jslx[0] == '2') /* �����������Ϊ�ٷֱ� */
            {
                dChargeAmt = sdb_batch_dsdf_detail.jyje * jscs/100 ;
                LOG(LM_DEBUG, Fmtmsg("dChargeAmt[%f]", dChargeAmt), "INFO")
            }
            else
            {
                LOG(LM_STD, Fmtmsg("����������ʹ�[%s]", jslx), "ERROR")
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            if(sxxkz[0] == '0') /* �����޿��� */
            {
                /*dChargeAmt = max(sxje, min(dChargeAmt, xxje));*/
                /*���������С�ڵ���������ȡ����ֵ*/
                if(dChargeAmt <= xxje)
                    dChargeAmt=xxje;
                /*��������Ѵ�������ֵ*/
                else
                {
                    /*��������Ѵ��ڵ�������ֵ��ȡ����ֵ*/
                    if(dChargeAmt >= sxje)
                        dChargeAmt=sxje;
                    /*����ȡ�����ѱ���*/
                    else
                        ;
                }
            }
            /*
            LOG(LM_STD, Fmtmsg("���׽��[%.2lf]�����ѽ��[%.2lf]", sdb_batch_dsdf_detail.jyje, dChargeAmt), "DEBUG")
            */
        }
        else if(strcmp(sWjlx,"0") == 0)
        	  dChargeAmt=0.00;

        /* �Ƿ��¿�����־ 0-�� 9-��*/
        trim(sdb_batch_dsdf_detail.skrzh);
        if(strlen(sdb_batch_dsdf_detail.skrzh) == 0)
        {
            strcpy(sJlbs, "0");
        }
        else
        {
            strcpy(sJlbs, "9");
        }

        memset(sUpdSql, 0x00, sizeof(sUpdSql));
        sprintf(sUpdSql, "UPDATE %s SET sxfje=%.2f, jlbs='%s', skrxm=kzzd6 where pkrq='%s' and ptpch='%s' and lsxh=%d and wjxh=%d",
            sTableName, dChargeAmt, sJlbs,
            sPkrq, sPtpch, sdb_batch_dsdf_detail.lsxh, sdb_batch_dsdf_detail.wjxh);
        LOG(LM_DEBUG, Fmtmsg("sUpdSql[%s]", sUpdSql), "INFO")
        iRet = DCIExecuteDirect(sUpdSql);
        if(iRet < 1)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s][%d][%s]", DCILastError(), iRet, sUpdSql), "ERROR")
            DCIFreeCursor(plcurdel);
            DCIRollback();
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        lTotCnt++;
        if(lTotCnt%80 == 0)
        {
            if(DCICommit()!= 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            if(DCIBegin()!= 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }

    if(iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if(DCICommit()!= 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(plcurdel);

    LOG(LM_DEBUG, Fmtmsg("������[%ld]�ʼ�¼", lTotCnt), "DEBUG")

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: PLDSDF_SJTJ_DS
  �������: �������մ��������ύ���Ի�����_����

  �������: 
            �����ύ���Ի�����_����
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: �м�ҵ����Ŀ��
  �� �� Ա: lilinghai
  ��������: 2018��01��10��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT PLDSDF_SJTJ_DS(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    double dChargeAmt = 0.00;
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sDwbh[16+1];
    char sSxfbz[1+1];
    char sJlbs[32+1];
    char sBuf[512];
    char sTableName[64];
    char sErrmsg[512];
    char sSql[1024];
    char sUpdSql[1024];
    char jslx[1+1];
    char sxxkz[1+1];
    char sJscs[18];
    char sXxje[18];
    char sSxje[18];
    double jscs = 0.00;
    double xxje = 0.00;
    double sxje = 0.00;
    SDB_BATCH_DSDF_DETAIL sdb_batch_dsdf_detail;
    CURSOR plcurdel;

    char sSxfgsbz[1+1];
    char sKzzd7[20+1];

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG")

    /* ���������� */

    /* ҵ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTableName, 0x00, sizeof(sTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", sBuf);
    trim(sBuf);
    pstrcopy(sTableName, sBuf, sizeof(sTableName));
    LOG(LM_DEBUG, Fmtmsg("ҵ�����[%s]", sTableName), "INFO")

    /* �������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML("/batch/pkrq", sBuf);
    trim(sBuf);
    pstrcopy(sPkrq, sBuf, sizeof(sPkrq));
    LOG(LM_DEBUG, Fmtmsg("��������[%s]", sPkrq), "INFO")

    /* ƽ̨���κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML("/batch/ptpch", sBuf);
    trim(sBuf);
    pstrcopy(sPtpch, sBuf, sizeof(sPtpch));
    LOG(LM_DEBUG, Fmtmsg("ƽ̨���κ�[%s]", sPtpch), "INFO")

    /* ��λ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDwbh, 0x00, sizeof(sDwbh));
    COMP_SOFTGETXML("/agent/req/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sDwbh, sBuf, sizeof(sDwbh));
    LOG(LM_DEBUG, Fmtmsg("��λ���[%s]", sDwbh), "INFO")

    /* �����ѱ�־ 0-��ȡ 1-����ȡ */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSxfbz, 0x00, sizeof(sSxfbz));
    COMP_SOFTGETXML("/agent/req/sxfbz", sBuf);
    trim(sBuf);
    pstrcopy(sSxfbz, sBuf, sizeof(sSxfbz));
    LOG(LM_DEBUG, Fmtmsg("�����ѱ�־[%s]", sSxfbz), "INFO")
    
    /* �����ѹ�����־ 0-��λ��1-������2-���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSxfgsbz, 0x00, sizeof(sSxfgsbz));
    COMP_SOFTGETXML("/agent/req/sxfgsbz", sBuf);
    trim(sBuf);
    pstrcopy(sSxfgsbz, sBuf, sizeof(sSxfgsbz));
    LOG(LM_DEBUG, Fmtmsg("�����ѹ�����־[%s]", sSxfgsbz), "INFO")

    if(sSxfbz[0] == '0')
    {
        /* ��ѯ������Ϣ */
        memset(sSql, 0x00, sizeof(sSql));
        memset(jslx, 0x00, sizeof(jslx));
        memset(sxxkz, 0x00, sizeof(sxxkz));
        memset(sJscs, 0x00, sizeof(sJscs));
        memset(sXxje, 0x00, sizeof(sXxje));
        memset(sSxje, 0x00, sizeof(sSxje));
        jscs = 0.00;
        xxje = 0.00;
        sxje = 0.00;
        snprintf(sSql, sizeof(sSql), "SELECT jslx, jscs, sxxkz, xxje, sxje FROM APP_SXFFL WHERE flbs='%s' FETCH FIRST 1 ROWS ONLY", sDwbh);
        iRet = DBSelectToMultiVarChar(sErrmsg, sSql, jslx, sJscs, sxxkz, sXxje, sSxje);
        if(iRet == 0)
        {
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        else if(iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG, Fmtmsg("�����Ѳ���[%s][%s][%s][%s][%s]", jslx, sJscs, sxxkz, sXxje, sSxje), "INFO")
        jscs = atof(sJscs);
        xxje = atof(sXxje);
        sxje = atof(sSxje);
    }

    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select * from %s where pkrq='%s' and ptpch='%s' and shzt !='1' and clzt='9'", sTableName, sPkrq, sPtpch);
    LOG(LM_DEBUG, Fmtmsg("sql[%s]", sSql), "INFO")
    if((plcurdel = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if(DCIExecute(plcurdel) == -1)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sql[%s] err[%s]", sSql, DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if(iRet != 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    while((iRet = DBFetch(plcurdel, SD_BATCH_DSDF_DETAIL, NUMELE(SD_BATCH_DSDF_DETAIL), &sdb_batch_dsdf_detail, sErrmsg ) ) > 0 )
    {
        dChargeAmt = 0.00;
        if(sSxfbz[0] == '0')
        {
            if(jslx[0] == '1') /* �����������Ϊ��� */
            {
                dChargeAmt = jscs;
            }
            else if(jslx[0] == '2') /* �����������Ϊ�ٷֱ� */
            {
                dChargeAmt = sdb_batch_dsdf_detail.jyje * jscs/100 ;
            }
            else
            {
                LOG(LM_STD, Fmtmsg("����������ʹ�[%s]", jslx), "ERROR")
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            if(sxxkz[0] == '0') /* �����޿��� */
            {
                /*dChargeAmt = max(sxje, min(dChargeAmt, xxje));*/
                /*���������С�ڵ���������ȡ����ֵ*/
                if(dChargeAmt <= xxje)
                    dChargeAmt=xxje;
                /*��������Ѵ�������ֵ*/
                else
                {
                    /*��������Ѵ��ڵ�������ֵ��ȡ����ֵ*/
                    if(dChargeAmt >= sxje)
                        dChargeAmt=sxje;
                    /*����ȡ�����ѱ���*/
                    else
                        ;
                }
            }
            /*
            LOG(LM_STD, Fmtmsg("���׽��[%.2lf]�����ѽ��[%.2lf]", sdb_batch_dsdf_detail.jyje, dChargeAmt), "DEBUG")
            */
        }
        
        /*
         * ��ȡ����������ʱ,������ۼӵ����׽�����
         * 1-���� 2-����
         * */
        if(strcmp(sSxfgsbz,"2") == 0)
        {
            /*���潻�׽��+�����ѵ���ֵ*/
            sdb_batch_dsdf_detail.kzzd10=dChargeAmt+sdb_batch_dsdf_detail.jyje;
        }
        else
        {
            sdb_batch_dsdf_detail.kzzd10=sdb_batch_dsdf_detail.jyje;
        }

        memset(sUpdSql, 0x00, sizeof(sUpdSql));
        sprintf(sUpdSql, "UPDATE %s SET sxfje=%.2f,kzzd10=%.2f where pkrq='%s' and ptpch='%s' and lsxh=%d and wjxh=%d",
            sTableName, dChargeAmt, sdb_batch_dsdf_detail.kzzd10,
            sPkrq, sPtpch, sdb_batch_dsdf_detail.lsxh, sdb_batch_dsdf_detail.wjxh);
        iRet = DCIExecuteDirect(sUpdSql);
        if(iRet < 1)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s][%d][%s]", DCILastError(), iRet, sUpdSql), "ERROR")
            DCIFreeCursor(plcurdel);
            DCIRollback();
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        lTotCnt++;
        if(lTotCnt%80 == 0)
        {
            if(DCICommit()!= 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            if(DCIBegin()!= 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }

    if(iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if(DCICommit()!= 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(plcurdel);

    LOG(LM_DEBUG, Fmtmsg("������[%ld]�ʼ�¼", lTotCnt), "DEBUG")

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: PLDSDF_DS_PTCHECK
  �������: ������������Э��У��

  �������: 
            ������������Э��У��
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: �м�ҵ����Ŀ��
  �� �� Ա: lilinghai
  ��������: 2018��01��19��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT PLDSDF_DS_PTCHECK(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    double dChargeAmt = 0.00;
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sQyzt[1+1];
    char sFkrzh[32+1];
    char sSubstrFkrzh[32+1];
    char sBuf[512];
    char sTableName[64];
    char sErrmsg[512];
    char sSql[1024];
    char sUpdSql[1024];
    char sSfbz[1+1];
    char sJyqy[1+1];
    char sCpdm[16+1];
    char sQyms[1+1];
    
    SDB_BATCH_DSDF_DETAIL sdb_batch_dsdf_detail;
    CURSOR plcurdel;

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG")
    
    memset(sPkrq, 0x00, sizeof(sPkrq));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    memset(sQyzt, 0x00, sizeof(sQyzt));
    memset(sFkrzh, 0x00, sizeof(sFkrzh));
    memset(sSubstrFkrzh, 0x00, sizeof(sSubstrFkrzh));
    memset(sTableName, 0x00, sizeof(sTableName));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(sSql, 0x00, sizeof(sSql));
    memset(sUpdSql, 0x00, sizeof(sUpdSql));
    memset(sSfbz, 0x00, sizeof(sSfbz));
    memset(sJyqy, 0x00, sizeof(sJyqy));
    memset(sCpdm, 0x00, sizeof(sCpdm));
    memset(sQyms, 0x00, sizeof(sQyms));
    
    /* �ո���־ 1-��2-�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/sfbz", sBuf);
    trim(sBuf);
    pstrcopy(sSfbz, sBuf, sizeof(sSfbz));
    LOG(LM_DEBUG, Fmtmsg("�ո���־[%s]", sSfbz), "INFO")
    if(strcmp(sSfbz,"2") == 0)
    {    
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        return 0;
    }

    /* У��ǩԼ��־ 0-��У�� 1-У�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/jyqy", sBuf);
    trim(sBuf);
    pstrcopy(sJyqy, sBuf, sizeof(sJyqy));
    LOG(LM_DEBUG, Fmtmsg("У��Э���־[%s]", sJyqy), "INFO")
    if(strcmp(sJyqy,"0") == 0)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        return 0;
    }

    /* ҵ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTableName, 0x00, sizeof(sTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", sBuf);
    trim(sBuf);
    pstrcopy(sTableName, sBuf, sizeof(sTableName));
    LOG(LM_DEBUG, Fmtmsg("ҵ�����[%s]", sTableName), "INFO")

    /* �������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML("/batch/pkrq", sBuf);
    trim(sBuf);
    pstrcopy(sPkrq, sBuf, sizeof(sPkrq));
    LOG(LM_DEBUG, Fmtmsg("��������[%s]", sPkrq), "INFO")

    /* ƽ̨���κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML("/batch/ptpch", sBuf);
    trim(sBuf);
    pstrcopy(sPtpch, sBuf, sizeof(sPtpch));
    LOG(LM_DEBUG, Fmtmsg("ƽ̨���κ�[%s]", sPtpch), "INFO")
    
    /* ��Ʒ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/cpdm", sBuf);
    trim(sBuf);
    pstrcopy(sCpdm, sBuf, sizeof(sCpdm));
    LOG(LM_DEBUG, Fmtmsg("��Ʒ����[%s]", sCpdm), "INFO")
    
    /*ǩԼģʽ*/
    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select qyms from app_cpxx where cpdm='%s'", sCpdm);
    LOG(LM_DEBUG, Fmtmsg("sql[%s]", sSql), "INFO")
    iRet = DBSelectToVarChar(sErrmsg, sQyms, sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*��ѯ���������м�¼,��У��Э���Ƿ���Ч����ȷ*/
    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select * from %s where pkrq='%s' and ptpch='%s'", sTableName, sPkrq, sPtpch);
    LOG(LM_DEBUG, Fmtmsg("sql[%s]", sSql), "INFO")
    if((plcurdel = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if(DCIExecute(plcurdel) == -1)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sql[%s] err[%s]", sSql, DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if(iRet != 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    while((iRet = DBFetch(plcurdel,SD_BATCH_DSDF_DETAIL,NUMELE(SD_BATCH_DSDF_DETAIL),&sdb_batch_dsdf_detail,sErrmsg))> 0)
    {
        trim(sdb_batch_dsdf_detail.fkrzh);
        LOG(LM_DEBUG,Fmtmsg("fkrzh[%s]",sdb_batch_dsdf_detail.fkrzh),"DEBUG");
        
        memset(sUpdSql, 0x00, sizeof(sUpdSql));
        trim(sdb_batch_dsdf_detail.yhh1);
        trim(sdb_batch_dsdf_detail.fkrzh);
#if 0
        sprintf(sUpdSql, "select qyzh, qyzt from app_khcpqy where trim(yhh1)='%s' and trim(ywbh)='%s'",
				sdb_batch_dsdf_detail.yhh1,sdb_batch_dsdf_detail.ywbh);
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", sUpdSql), "INFO")
        iRet = DBSelectToMultiVarChar(sErrmsg, sUpdSql, sFkrzh, sQyzt);
		if(0 == iRet)
		{
            sprintf(sUpdSql, "select qyzh, qyzt from app_khcpqy where trim(xybh)='%s' and trim(ywbh)='%s'",
					sdb_batch_dsdf_detail.yhh1,sdb_batch_dsdf_detail.ywbh);
            LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", sUpdSql), "INFO")
            iRet = DBSelectToMultiVarChar(sErrmsg, sUpdSql, sFkrzh, sQyzt);
		    if(0 == iRet)
			{
                sprintf(sUpdSql, "select qyzh, qyzt from app_khcpqy where trim(qyzh)='%s' and trim(ywbh)='%s'",
			    		sdb_batch_dsdf_detail.fkrzh,sdb_batch_dsdf_detail.ywbh);
                LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", sUpdSql), "INFO")
                iRet = DBSelectToMultiVarChar(sErrmsg, sUpdSql, sFkrzh, sQyzt);
			}
		}
#endif
		/* ��Ʒ����+�����ʺ�Ψһ */
        if ( strcmp(sQyms,"1") == 0 )
        {
            /* �����ʺŲ���Ϊ�� */
            if ( 0 == strlen(sdb_batch_dsdf_detail.fkrzh) )
            {
                 fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("�����ʺŲ���Ϊ��"));
                 fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                 return -1;    
            }
            if ( 19 == strlen(sdb_batch_dsdf_detail.fkrzh) )
            {
                sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy WHERE ( qyzh = '%s' or qyzh = substr('%s',7) ) AND cpdm ='%s'",\
                            sdb_batch_dsdf_detail.fkrzh ,sdb_batch_dsdf_detail.fkrzh , sCpdm);
			}
			else
			{
                sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy WHERE qyzh = '%s' AND cpdm ='%s'",\
                            sdb_batch_dsdf_detail.fkrzh , sCpdm);
			}
        }
        else /* ��Ʒ����+�����ʺ�+�û����Ψһ ǩԼ����3 */
        if ( strcmp(sQyms,"3") == 0 )
        {
            /* �����ʺŲ���Ϊ�� */
            if ( 0 == strlen(sdb_batch_dsdf_detail.fkrzh) )
            {
                DCIRollback();
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("�����ʺŲ���Ϊ��"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
        
            /* �û���Ų���Ϊ�� */
            if ( 0 == strlen(sdb_batch_dsdf_detail.yhh1) )
            {
                DCIRollback();
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("�û���Ų���Ϊ��"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            if ( 19 == strlen(sdb_batch_dsdf_detail.fkrzh) )
            {
                sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy WHERE ( qyzh = '%s' or qyzh = substr('%s',7) ) AND yhh1 = '%s' AND cpdm ='%s'",\
                            sdb_batch_dsdf_detail.fkrzh ,sdb_batch_dsdf_detail.fkrzh ,sdb_batch_dsdf_detail.yhh1 ,sCpdm);
			}
			else
			{
                sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy WHERE qyzh = '%s' AND yhh1 = '%s' AND cpdm ='%s'",\
                            sdb_batch_dsdf_detail.fkrzh ,sdb_batch_dsdf_detail.yhh1 ,sCpdm);
			}
        }
        else /* ҵ����+�û����Ψһ */
        if ( strcmp(sQyms,"4") == 0 )
        {
            /* �û���Ų���Ϊ�� */
            if ( 0 == strlen(sdb_batch_dsdf_detail.yhh1) )
            {
                DCIRollback();
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("�û���Ų���Ϊ��"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy WHERE yhh1 = '%s' AND ywbh='%s'", \
                         sdb_batch_dsdf_detail.yhh1 ,sdb_batch_dsdf_detail.ywbh );
        }
        else
        /* ��Ʒ����+�û����Ψһ  Ĭ��ֵ*/
        {
            /* �û���Ų���Ϊ�� */
            if ( 0 == strlen(sdb_batch_dsdf_detail.yhh1) )
            {
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("�û���Ų���Ϊ��"));
                 fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                 return -1;    
            }
            sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy \
                        WHERE yhh1 = '%s' AND cpdm='%s'",sdb_batch_dsdf_detail.yhh1 ,sCpdm);
        }
        LOG(LM_DEBUG, Fmtmsg("sUpdSql[%s]", sUpdSql), "INFO")
        iRet = DBSelectToMultiVarChar(sErrmsg, sUpdSql, sFkrzh, sQyzt);
        if (iRet <= 0)
        {
            /*��ѯЭ��ʧ��ʱ�����������մ�������ϸʧ��*/
            LOG(LM_STD, Fmtmsg("��ѯ�ͻ�Э���ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            memset(sUpdSql, 0x00, sizeof(sUpdSql));
            sprintf(sUpdSql, "update %s set shzt='1',clzt='1',cgbz='2',xym='2',xyxx='У��Э��ʱ��ѯЭ��ʧ��' where pkrq='%s' and ptpch='%s' and lsxh='%d' and wjxh='%d'",sTableName,sPkrq,sPtpch,sdb_batch_dsdf_detail.lsxh,sdb_batch_dsdf_detail.wjxh);
            LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", sUpdSql), "INFO")
            iRet = DCIExecuteDirect(sUpdSql);
            if(iRet < 1)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s][%d][%s]", DCILastError(), iRet, sUpdSql), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            continue;
        }
        /*У��Э�鸶������Ϣ&&Э��״̬*/
        trim(sFkrzh);
        /*��ȡ�ļ���ϸ�������˺ź�13λ*/
        memcpy(sSubstrFkrzh,sdb_batch_dsdf_detail.fkrzh+6,sizeof(sSubstrFkrzh));
        if(strcmp(sdb_batch_dsdf_detail.fkrzh,sFkrzh) != 0 || strcmp(sQyzt,"0") != 0)
        {
            if(strcmp(sSubstrFkrzh,sFkrzh) != 0)   
            {
                LOG(LM_STD, Fmtmsg("Э��У��ʧ��"), "ERROR")
                LOG(LM_STD, Fmtmsg("Э�鸶����[%s],�ļ���ϸ��¼������[%s]", sFkrzh, sdb_batch_dsdf_detail.fkrzh), "ERROR")
                LOG(LM_STD, Fmtmsg("Э��״̬[%s] 0-��Ч 1-����", sQyzt), "ERROR")
                memset(sUpdSql, 0x00, sizeof(sUpdSql));
                sprintf(sUpdSql, "update %s set shzt='1',clzt='1',cgbz='2',xym='2',xyxx='Э��У��ʧ��' where pkrq='%s' and ptpch='%s' and lsxh='%d' and wjxh='%d'",sTableName,sPkrq,sPtpch,sdb_batch_dsdf_detail.lsxh,sdb_batch_dsdf_detail.wjxh);
                LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", sUpdSql), "INFO")
                iRet = DCIExecuteDirect(sUpdSql);
                if(iRet < 1)
                {
                    LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s][%d][%s]", DCILastError(), iRet, sUpdSql), "ERROR")
                    DCIFreeCursor(plcurdel);
                    DCIRollback();
                    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                continue;
            }
        }

        lTotCnt++;
        if(lTotCnt%80 == 0)
        {
            if(DCICommit()!= 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            if(DCIBegin()!= 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }

    if(iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if(DCICommit()!= 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(plcurdel);

    LOG(LM_DEBUG, Fmtmsg("������[%ld]�ʼ�¼", lTotCnt), "DEBUG")

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: PLDSDF_PTC_PLWJDR
  �������: �����ļ�Э����µ����ļ�����֯�����ļ�

  �������: 
            �����ļ�Э����µ����ļ�����֯�����ļ�
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: �м�ҵ����Ŀ��
  �� �� Ա: 
  ��������: 
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT PLDSDF_PTC_PLWJDR(HXMLTREE lXmlhandle)
{
    FILE *fp=NULL;
    FILE *fp2=NULL;
    char sBuf[1024+1];
    char sLine[1024+1];
    char sBatchno[32+1];
    char sFilename[120+1];
    char sNewFilename[120+1];
    char sNewPathFilename[120+1];
    char sDwbh[16+1];
    char sSysdate[8+1];
    char sSystime[6+1];
    char sXyxljz[8+1];
    char sQygy[16+1];
    char sQdbs[4+1];
    char sJyjg[16+1];
    char sCmd[521+1];
    char sCurrvalue[10+1];
    char cErrmsg[521+1];
    char sSignType[1+1];
    char sCpdm[16+1];
    SDB_PLDSDF_CUSTOM_DETAIL sdb_pldsdf_custom_detail;
    
    int iNum=0;
    int iRet=0;

    memset(sBuf,0x00,sizeof(sBuf));
    memset(sLine,0x00,sizeof(sLine));
    memset(sBatchno,0x00,sizeof(sBatchno));
    memset(sFilename,0x00,sizeof(sFilename));
    memset(sNewFilename,0x00,sizeof(sNewFilename));
    memset(sNewPathFilename,0x00,sizeof(sNewPathFilename));
    memset(sDwbh,0x00,sizeof(sDwbh));
    memset(sSysdate,0x00,sizeof(sSysdate));
    memset(sSystime,0x00,sizeof(sSystime));
    memset(sXyxljz,0x00,sizeof(sXyxljz));
    memset(sQygy,0x00,sizeof(sQygy));
    memset(sQdbs,0x00,sizeof(sQdbs));
    memset(sJyjg,0x00,sizeof(sJyjg));
    memset(sCmd,0x00,sizeof(sCmd));
    memset(sCurrvalue,0x00,sizeof(sCurrvalue));
    memset(cErrmsg,0x00,sizeof(cErrmsg));
    memset(sSignType,0x00,sizeof(sSignType));
    memset(sCpdm,0x00,sizeof(sCpdm));
    
    char gnm[1+1];
    char qystlx[1+1];
    char jyqd[10+1];
    char sXybh[20+1];
    char sSql1[1024+1];
    char sFilestr[1024+1];
       
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG")
    
    /* ���κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/batch/req/batch_no", sBuf);
    trim(sBuf);
    pstrcopy(sBatchno, sBuf, sizeof(sBatchno));
    LOG(LM_DEBUG, Fmtmsg("���κ�[%s]", sBatchno), "INFO")
    
    /* ���������ļ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/localpathfile_name", sBuf);
    trim(sBuf);
    pstrcopy(sFilename, sBuf, sizeof(sFilename));
    LOG(LM_DEBUG, Fmtmsg("���������ļ���[%s]", sFilename), "INFO")
    
    /* ��λ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sDwbh, sBuf, sizeof(sDwbh));
    LOG(LM_DEBUG, Fmtmsg("��λ���[%s]", sDwbh), "INFO")
    
    /* ϵͳ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf);
    trim(sBuf);
    pstrcopy(sSysdate, sBuf, sizeof(sSysdate));
    
    /* ϵͳʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf);
    trim(sBuf);
    pstrcopy(sSystime, sBuf, sizeof(sSystime));
    
    /* Э�����м�ֵ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/app/cpxx/xyxljz", sBuf);
    trim(sBuf);
    pstrcopy(sXyxljz, sBuf, sizeof(sXyxljz));
    
    /* ǩԼ��Ա */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/tel", sBuf);
    trim(sBuf);
    pstrcopy(sQygy, sBuf, sizeof(sQygy));
    
    /* ������־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/qdbs", sBuf);
    trim(sBuf);
    pstrcopy(sQdbs, sBuf, sizeof(sQdbs));
    
    /* ���׻��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/brc", sBuf);
    trim(sBuf);
    pstrcopy(sJyjg, sBuf, sizeof(sJyjg));
    
    /* ǩԼģʽ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/app/cpxx/qyms", sBuf);
    trim(sBuf);
    pstrcopy(sSignType, sBuf, sizeof(sSignType));
    
    /* ��Ʒ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/app/cpxx/cpdm", sBuf);
    trim(sBuf);
    pstrcopy(sCpdm, sBuf, sizeof(sCpdm));
    
    sprintf(sNewFilename,"%s_%s_%s.req",sDwbh,sSysdate,sSystime);
    sprintf(sNewPathFilename,"%s/file/batch/0041000/%s/%s_%s_%s.req",getenv("HOME"),sSysdate,sDwbh,sSysdate,sSystime);
    LOG(LM_DEBUG, Fmtmsg("���ͺ����ļ���[%s]", sNewPathFilename), "INFO")
    
    /*�򿪹����ļ�*/
    fp=fopen(sFilename,"r");
    if(fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�򿪹����ļ�ʧ��"), "")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*�����ͺ����ļ�*/
    fp2 = fopen(sNewPathFilename, "w");
    if(fp2 == NULL)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("�����ͺ����ļ�ʧ��"), "")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
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
    
    memset(sLine,0x00,sizeof(sLine));
    while(fgets(sLine, sizeof(sLine)-1, fp) != NULL)
    {
        iNum++;
        trim(sLine);
        if(strlen(sLine)==0)
            continue;
        
        LOG(LM_DEBUG, Fmtmsg("��[%d]���ļ���ϸ��¼",iNum),"DEBUG");
        LOG(LM_DEBUG, Fmtmsg("sLine[%s]",sLine),"DEBUG");
        memset(gnm,0x00,sizeof(gnm));
        memset(qystlx,0x00,sizeof(qystlx));
        memset(jyqd,0x00,sizeof(jyqd));
        memset(sXybh,0x00,sizeof(sXybh));
        memset(sFilestr,0x00,sizeof(sFilestr));
        memset(cErrmsg,0x00,sizeof(cErrmsg));
        memset(&sdb_pldsdf_custom_detail,0x00,sizeof(sdb_pldsdf_custom_detail));
        
        pstrcopy(sdb_pldsdf_custom_detail.pch,sBatchno,sizeof(sdb_pldsdf_custom_detail.pch));
        pstrcopy(sdb_pldsdf_custom_detail.wjmc,sFilename,sizeof(sdb_pldsdf_custom_detail.wjmc));
        pstrcopy(sdb_pldsdf_custom_detail.qygy,sQygy,sizeof(sdb_pldsdf_custom_detail.qygy));
        pstrcopy(sdb_pldsdf_custom_detail.qyjg,sJyjg,sizeof(sdb_pldsdf_custom_detail.qyjg));
        
        /*��1��ֵ--���*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 1, sBuf, '|', '\\');
        trim(sBuf);
        sdb_pldsdf_custom_detail.wjxh=atoi(sBuf);
        
        /*��4��ֵ--�����˺�����*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 4, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.yhzhmc,sBuf,sizeof(sdb_pldsdf_custom_detail.yhzhmc));

        /*��5��ֵ--֤������*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 5, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.zjhm,sBuf,sizeof(sdb_pldsdf_custom_detail.zjhm));

        /*��8��ֵ--��ϵ��ַ*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 8, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.lxdz,sBuf,sizeof(sdb_pldsdf_custom_detail.lxdz));

        /*��9��ֵ--��ע*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 9, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.bz,sBuf,sizeof(sdb_pldsdf_custom_detail.bz));

        /*��10��ֵ--����1*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 10, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.bz1,sBuf,sizeof(sdb_pldsdf_custom_detail.bz1));

        /*��11��ֵ--����2*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 11, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.bz2,sBuf,sizeof(sdb_pldsdf_custom_detail.bz2));
        
        /*��6��ֵ--Э���¼״̬*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 6, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.xyjlzt,sBuf,sizeof(sdb_pldsdf_custom_detail.xyjlzt));
        if(strcmp(sBuf,"0")==0)
            strcpy(gnm,"A");
        else if(strcmp(sBuf,"1")==1)
            strcpy(gnm,"C");
        else
            continue;
        
        /*����Э�����к�*/
        memset(sCmd,0x00,sizeof(sCmd));
        sprintf(sCmd,"select curr_value from  app_xlkz where pkey='%s'",sXyxljz);
        iRet=DBSelectToVarChar(cErrmsg,sCurrvalue,sCmd);
        if (0 > iRet)
        {
            LOG(LM_STD, Fmtmsg("��ȡЭ�����к�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        sprintf(sdb_pldsdf_custom_detail.xybh,"%s%s",sSysdate,sCurrvalue);
        
        memset(sCmd,0x00,sizeof(sCmd));
        sprintf(sCmd,"update app_xlkz set curr_value=curr_value+1");
        iRet=DCIExecuteDirect(sCmd);
        if (0 >= iRet)
        {
            LOG(LM_STD, Fmtmsg("��ȡЭ�����к�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        /*��2��ֵ--��ͬ��*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 2, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.hth,sBuf,sizeof(sdb_pldsdf_custom_detail.hth));
        
        strcpy(sdb_pldsdf_custom_detail.xydm,"10000030");
        strcpy(qystlx,"1");
        
        /*��3��ֵ--�����˺�*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 3, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.yhzh,sBuf,sizeof(sdb_pldsdf_custom_detail.yhzh));
        
        /*��7��ֵ--��ϵ�绰*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 7, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.lxdh,sBuf,sizeof(sdb_pldsdf_custom_detail.lxdh));
        
        strcpy(sdb_pldsdf_custom_detail.qysxrq,sSysdate);
        strcpy(sdb_pldsdf_custom_detail.qydqrq,"29991230");
        strcpy(sdb_pldsdf_custom_detail.qyrq,sSysdate);
        strcpy(jyqd,"80");
        
        /* ���������ͻ�ǩԼ��ϸ�� */
        LOG(LM_DEBUG,Fmtmsg("pch[%s]",sdb_pldsdf_custom_detail.pch),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("wjxh[%d]",sdb_pldsdf_custom_detail.wjxh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("wjmc[%s]",sdb_pldsdf_custom_detail.wjmc),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("hth[%s]",sdb_pldsdf_custom_detail.hth),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("tyxybh[%s]",sdb_pldsdf_custom_detail.tyxybh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("xybh[%s]",sdb_pldsdf_custom_detail.xybh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("xydm[%s]",sdb_pldsdf_custom_detail.xydm),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("khh[%s]",sdb_pldsdf_custom_detail.khh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("yhzh[%s]",sdb_pldsdf_custom_detail.yhzh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("yhzhmc[%s]",sdb_pldsdf_custom_detail.yhzhmc),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("zjhm[%s]",sdb_pldsdf_custom_detail.zjhm),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("xyjlzt[%s]",sdb_pldsdf_custom_detail.xyjlzt),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("lxdh[%s]",sdb_pldsdf_custom_detail.lxdh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("lxdz[%s]",sdb_pldsdf_custom_detail.lxdz),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("qysxrq[%s]",sdb_pldsdf_custom_detail.qysxrq),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("qydqrq[%s]",sdb_pldsdf_custom_detail.qydqrq),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("qyrq[%s]",sdb_pldsdf_custom_detail.qyrq),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("jyrq[%s]",sdb_pldsdf_custom_detail.jyrq),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("qygy[%s]",sdb_pldsdf_custom_detail.qygy),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("jygy[%s]",sdb_pldsdf_custom_detail.jygy),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("qyjg[%s]",sdb_pldsdf_custom_detail.qyjg),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("fhxxm[%s]",sdb_pldsdf_custom_detail.fhxxm),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("cwzwms[%s]",sdb_pldsdf_custom_detail.cwzwms),"DEBUG");
        
        /**************����Ƿ���ǩԼ*****************/
        /* ��Ʒ����+�����ʺ�Ψһ */
		memset(sSql1,0x00,sizeof(sSql1));
        if ( sSignType[0] == '1' )
        {
            snprintf( sSql1, sizeof( sSql1 ), "SELECT xybh FROM app_khcpqy WHERE \
                qyzh='%s' AND cpdm='%s' and qyzt='0' ",sdb_pldsdf_custom_detail.yhzh, sCpdm );
        }
        else
        /* ��Ʒ����+�����ʺ�+�û����Ψһ ǩԼ����3 ΪĬ��ֵ */
        if ( sSignType[0] == '3' )
        {
            snprintf( sSql1, sizeof( sSql1 ), "SELECT xybh FROM app_khcpqy WHERE \
                qyzh='%s' AND yhh1='%s'  AND cpdm='%s' and qyzt='0' ",sdb_pldsdf_custom_detail.yhzh, sdb_pldsdf_custom_detail.hth, sCpdm );
        }
        
        else
        /* ҵ����+�û����Ψһ */
        if ( sSignType[0] == '4' )
        {
            snprintf( sSql1, sizeof( sSql1 ), "SELECT xybh FROM app_khcpqy WHERE\
                yhh1='%s'  AND ywbh='%s' and qyzt='0' ",sdb_pldsdf_custom_detail.hth, sDwbh);
        }
        
        else
        /* ��Ʒ����+�û����Ψһ */
        {
            snprintf( sSql1, sizeof( sSql1 ), "SELECT xybh FROM app_khcpqy WHERE\
                yhh1='%s'  AND cpdm='%s' and qyzt='0' ", sdb_pldsdf_custom_detail.hth, sCpdm );
        }
        LOG(LM_DEBUG, Fmtmsg("sSql1[%s]",sSql1), "INFO")
        iRet = DBSelectToMultiVar( cErrmsg, sSql1, sXybh ) ;
        LOG(LM_DEBUG, Fmtmsg("iRet[%d]  sXybh[%s]",iRet,sXybh), "INFO")
        if ( iRet == 0 )  /* ��¼������ */
        {
            /*д������ļ�*/
            sprintf(sFilestr,"%-26s%-26s%-1s%-60s%-10s%-32s%-8s%-1s%-32s%-1s%-32s%-18s%-8s%-8s%-8s%-8s%-5s\
                        %-5s%-20s%-32s%-6s%-5s%-20s%-122s%-122s%-30s%-7s%-60s\n",
               " "," ",gnm,sdb_pldsdf_custom_detail.xybh," ",sdb_pldsdf_custom_detail.yhzh,sdb_pldsdf_custom_detail.xydm,qystlx,
               sdb_pldsdf_custom_detail.yhzh," "," ",sdb_pldsdf_custom_detail.lxdh,sdb_pldsdf_custom_detail.qysxrq,sdb_pldsdf_custom_detail.qydqrq,
               sdb_pldsdf_custom_detail.qyrq,"00000000",sdb_pldsdf_custom_detail.qygy," "," ",sQdbs,sQdbs,sdb_pldsdf_custom_detail.qyjg,
               " "," "," "," "," "," ");
            fwrite(sFilestr,strlen(sFilestr),1,fp2);
        }
        else  /*  ��ѯʧ�ܻ��߲�ѯ��ǩԼ��¼ */
        {
            if(iRet < 0)
            {
                strcpy(sdb_pldsdf_custom_detail.djzt,"2");/*ǩԼʧ��*/
                strcpy(sdb_pldsdf_custom_detail.fhxxm,"999999");
                strcpy(sdb_pldsdf_custom_detail.cwzwms,"��ѯ���ݿ�ʧ��");                
            }
            else if(iRet > 0)
            {
                strcpy(sdb_pldsdf_custom_detail.djzt,"3");/*�ظ�ǩԼ*/
                strcpy(sdb_pldsdf_custom_detail.fhxxm,"999999");
                strcpy(sdb_pldsdf_custom_detail.cwzwms,"�ظ�ǩԼ");   
            }
        }
        
        /**************����Ƿ���ǩԼ*****************/

        iRet = DBInsert("pldsdf_custom_detail", SD_PLDSDF_CUSTOM_DETAIL, NUMELE(SD_PLDSDF_CUSTOM_DETAIL), &sdb_pldsdf_custom_detail, cErrmsg);
        if(iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            DCIRollback();
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG, Fmtmsg("���������ͻ�ǩԼ��ϸ��pldsdf_custom_detail�ɹ�"), "INFO")
        
        memset(sLine,0x00,sizeof(sLine));
        memset(&sdb_pldsdf_custom_detail,0x00,sizeof(sdb_pldsdf_custom_detail));
    }
    
    if(DCICommit()!= 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    fclose(fp);
    fclose(fp2);
    
    COMP_SOFTSETXML("/agent/req/hxfilename",sNewFilename);
    COMP_SOFTSETXML("/agent/req/hxpathfilename",sNewPathFilename);

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}
/************************************************************************
  ��̬�����������
  �����������: SPLDS_FILEGEN
  �������: �������յ��ʽɷѲ�ѯ�ļ�����

  �������: 
            ���ɽ�������ļ�
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: �м�ҵ����Ŀ��
  �� �� Ա: llh
  ��������: 2018��09��21��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SPLDS_FILEGEN(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    char sBatchNo[32+1];
    char sSfbz[1+1];
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sDwbh[16+1];
    char sStat[1+1];
    char sDownFlag[1+1];
    char sBuf[512];
    char sFileName[256+1];
    char sFilePath[512+1];
    char sLine[1024];
    char sTableName[64];
    char sErrmsg[512];
    char sSql[1024];
    FILE *fp = NULL;
    SDB_BATCH_DSDF_DETAIL sdb_batch_dsdf_detail;
    CURSOR plcur;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG")

    /* ���������� */
    COMP_PARACOUNTCHKMIN(2)

    /* �̻����κ� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sBatchNo, 0x00, sizeof(sBatchNo));
    COMP_GETPARSEPARAS(1, sBuf, "�̻����κ�")
    trim(sBuf);
    pstrcopy(sBatchNo, sBuf, sizeof(sBatchNo));
    LOG(LM_DEBUG, Fmtmsg("�̻����κ�[%s]", sBatchNo), "INFO")

    /* �ո���־ 1-��2-�� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sSfbz, 0x00, sizeof(sSfbz));
    COMP_GETPARSEPARAS(2, sBuf, "�ո���־")
    trim(sBuf);
    pstrcopy(sSfbz, sBuf, sizeof(sSfbz));
    LOG(LM_DEBUG, Fmtmsg("�ո���־[%s]", sSfbz), "INFO")

    /* ҵ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTableName, 0x00, sizeof(sTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", sBuf);
    trim(sBuf);
    pstrcopy(sTableName, sBuf, sizeof(sTableName));
    LOG(LM_DEBUG, Fmtmsg("ҵ�����[%s]", sTableName), "INFO")

    /* �������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML("/batch/resp/pkrq", sBuf);
    trim(sBuf);
    pstrcopy(sPkrq, sBuf, sizeof(sPkrq));
    LOG(LM_DEBUG, Fmtmsg("��������[%s]", sPkrq), "INFO")

    /* ƽ̨���κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML("/batch/resp/ptpch", sBuf);
    trim(sBuf);
    pstrcopy(sPtpch, sBuf, sizeof(sPtpch));
    LOG(LM_DEBUG, Fmtmsg("ƽ̨���κ�[%s]", sPtpch), "INFO")

    /* ��λ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDwbh, 0x00, sizeof(sDwbh));
    COMP_SOFTGETXML("/agent/resp/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sDwbh, sBuf, sizeof(sDwbh));
    LOG(LM_DEBUG, Fmtmsg("��λ���[%s]", sDwbh), "INFO")

    /* �ļ����ر�־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDownFlag, 0x00, sizeof(sDownFlag));
    COMP_SOFTGETXML("/agent/req/down_flag", sBuf);
    trim(sBuf);
    pstrcopy(sDownFlag, sBuf, sizeof(sDownFlag));
    LOG(LM_DEBUG, Fmtmsg("�ļ����ر�־[%s]", sDownFlag), "INFO")

    /* ���̽���ļ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFileName, 0x00, sizeof(sFileName));
    memset(sFilePath, 0x00, sizeof(sFilePath));
    COMP_SOFTGETXML("/batch/stepcfg/info/hqsj/attribvalue", sBuf);
    trim(sBuf);
    sprintf(sFileName, "%s_%s_%s_RT"/*"%s_%s_%s_RT.txt"*/, sDwbh, sPkrq, sPtpch);
    sprintf(sFilePath, "%s/%s/%s", getenv("HOME"), sBuf, sFileName);
    LOG(LM_DEBUG, Fmtmsg("���ɻ��̽���ļ���[%s]", sFilePath), "INFO")

    fp = fopen(sFilePath, "w");
    if(fp == NULL)
    {
        fpub_SetMsg(lXmlhandle, 24103, "���ļ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select * from %s where wbpch='%s' order by wbxh asc", sTableName, sBatchNo);

    if((plcur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if(DCIExecute(plcur) == -1)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sql[%s] err[%s]", sSql, DCILastError()), "ERROR")
        DCIFreeCursor(plcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* д���� */
    fprintf(fp, "��λ��ţ�%s\n", sDwbh);

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    while((iRet = DBFetch(plcur, SD_BATCH_DSDF_DETAIL, NUMELE(SD_BATCH_DSDF_DETAIL), &sdb_batch_dsdf_detail, sErrmsg ) ) > 0 )
    {
        lTotCnt++;

        /* ���ݵļ�¼״̬��0����ʼ1���ɹ�2��ʧ�� */
        memset(sStat, 0x00, sizeof(sStat));
        trim(sdb_batch_dsdf_detail.cgbz);
        trim(sdb_batch_dsdf_detail.zjxym);
        trim(sdb_batch_dsdf_detail.zjxyxx);
        trim(sdb_batch_dsdf_detail.xym);
        trim(sdb_batch_dsdf_detail.xyxx);
        trim(sdb_batch_dsdf_detail.jlbs);
        /* �ɹ���־ 0-�ɹ� 1-���ֳɹ� 2-ʧ�� 9-��ʼ */
        /*sStat-��¼״̬��0-��ʼ 1-�ɹ� 2-ʧ��*/
        if(sdb_batch_dsdf_detail.cgbz[0] == '0' || sdb_batch_dsdf_detail.cgbz[0] == '1')
        {
            strcpy(sdb_batch_dsdf_detail.zjxym, "AGR0015");
            /*if(sdb_batch_dsdf_detail.jlbs[0] == '0')*/
            if(sdb_batch_dsdf_detail.jlbs[0] == '1'||
				sdb_batch_dsdf_detail.jlbs[0] == '2'||
				sdb_batch_dsdf_detail.jlbs[0] == '3')
            {
                strcpy(sdb_batch_dsdf_detail.zjxym, "AGR0056");  /* �����ɹ� */
            }
            strcpy(sdb_batch_dsdf_detail.zjxyxx, "���˳ɹ�");
            strcpy(sStat, "1");
        }
        else if(sdb_batch_dsdf_detail.cgbz[0] == '2') 
           /* strlen(sdb_batch_dsdf_detail.zjxym) == 0
            strlen(sdb_batch_dsdf_detail.zjxyxx) == 0)*/
        {
            if(strlen(sdb_batch_dsdf_detail.zjxym) == 0)
                strcpy(sdb_batch_dsdf_detail.zjxym, sdb_batch_dsdf_detail.xym);
            if(strlen(sdb_batch_dsdf_detail.zjxyxx) == 0)
                strcpy(sdb_batch_dsdf_detail.zjxyxx, sdb_batch_dsdf_detail.xyxx);

            strcpy(sStat, "2");
            if(strlen(sdb_batch_dsdf_detail.zjxyxx) == 0) /* ����ȫ��ʧ��ʱ���ǼǴ�����Ϣ��kzzd7�� */
            {
                strcpy(sdb_batch_dsdf_detail.zjxyxx, sdb_batch_dsdf_detail.kzzd7);
            }
        }
        else
        {
            strcpy(sStat, "2");
        }

        /* ������ķ�����Ӧ��Ϊ�գ���ʹ��ACR2938��ΪĬ�� */
        trim(sdb_batch_dsdf_detail.zjxym);
        if(strlen(sdb_batch_dsdf_detail.zjxym) == 0)
        {
            strcpy(sdb_batch_dsdf_detail.zjxym, "ACR2938");
        }

        /* �ո���־ 1-�� 2-�� */
        memset(sLine, 0x00, sizeof(sLine));
        if(strcmp(sSfbz, "1") == 0) /* ���� */
        {
            /*���ļ���ʽ
            ���
            ��ͬ��
            ��������
            ����
            �����˺�
            Ӧ���ܽ��
            ʵ���ܽ��
            Ӧ��ҵ�����
            ʵ��ҵ�����
            Ӧ�չ�������1
            ʵ�չ�������1
            Ӧ�չ�������2
            ʵ�չ�������2
            ��������
            ���з�����
            ���з���������˵��
            */
            sprintf(sLine,"%-7ld|%-20s|%-8s|%-42s|%-18s|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%-8s|%-4s|%-60s|",
                  sdb_batch_dsdf_detail.wbxh,
                  sdb_batch_dsdf_detail.yhh1,
                  sdb_batch_dsdf_detail.kxrq,
                  sdb_batch_dsdf_detail.fkrxm,
                  sdb_batch_dsdf_detail.fkrzh,
                  sdb_batch_dsdf_detail.jyje,
                  sdb_batch_dsdf_detail.sjje,
                  sdb_batch_dsdf_detail.ywje,
                  sdb_batch_dsdf_detail.sjywje,
                  sdb_batch_dsdf_detail.fyje1,
                  sdb_batch_dsdf_detail.sjfyje1,
                  sdb_batch_dsdf_detail.fyje2,
                  sdb_batch_dsdf_detail.sjfyje2,
                  sdb_batch_dsdf_detail.zwrq,
                  sdb_batch_dsdf_detail.xym,
                  sdb_batch_dsdf_detail.xyxx);
        }
        else /* ���� */
        {
            trim(sdb_batch_dsdf_detail.wbpch);
            trim(sdb_batch_dsdf_detail.skrzh);
            trim(sdb_batch_dsdf_detail.zjhm);
            trim(sdb_batch_dsdf_detail.kzzd6);
            trim(sdb_batch_dsdf_detail.zwrq);
            trim(sdb_batch_dsdf_detail.zjxym);
            trim(sdb_batch_dsdf_detail.zjxyxx);
            /* �ɸ�ʽ 
               ���������ļ���ʽ
                  ���κ�	16A
                  ���	7A
                  �ͻ��˺�	19A
                  ֤������	20A
                  ����	42A
                  �ͻ�Ӧ�����	13P2
                  �ͻ�ʵ�����	13P2
                  ��������	8P0
                  ��¼״̬	1A
                  ��Ϣ��ʶ	7A
                  ��ʶ����˵��	40A
            */
            sprintf(sLine, "%-16s|%07d|%-19s|%-20s|%-42s|%013.2lf|%013.2lf|%-8s|%-1s|%-7s|%-40s|",
            //sprintf(sLine, "%s|%d|%s|%s|%s|%lf|%f|%s|%s|%s|%s|",
                    sdb_batch_dsdf_detail.wbpch,
                    sdb_batch_dsdf_detail.wbxh,
                    sdb_batch_dsdf_detail.skrzh,
                    sdb_batch_dsdf_detail.zjhm,
                    sdb_batch_dsdf_detail.kzzd6,
                    sdb_batch_dsdf_detail.jyje,
                    sdb_batch_dsdf_detail.sjje,
                    sdb_batch_dsdf_detail.zwrq,
                    sStat,
                    sdb_batch_dsdf_detail.zjxym,
                    sdb_batch_dsdf_detail.zjxyxx);
        }

        /* д����ϸ�� */
        fprintf(fp, "%s\n", sLine);
        memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    }

    if(iRet < 0)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIFreeCursor(plcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(plcur);

    fclose(fp);

    LOG(LM_DEBUG, Fmtmsg("��д��[%ld]�ʼ�¼�����̽���ļ�", lTotCnt), "DEBUG")
    if(lTotCnt<=0)
    {
        fpub_SetMsg(lXmlhandle, 24103, "��ѯ������Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("��ѯ������Ϣʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML("/batch/resp/ret_file_name", sFileName);

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}
