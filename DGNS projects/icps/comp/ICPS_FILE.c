#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"

IRESULT ICPS_SFTP_GETFILE(HXMLTREE lXmlhandle)
{
    char sBuf[10000];
    char sDate[8 + 1];
    char sPath[40 + 1];
    char sBusi_No[20];
    int iRet = -1;
    int iParas = 0;

    /*��ʼ�����*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(3)

    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sDate, "�ļ������ļ�������");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, sBusi_No, "ҵ����");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, sPath, "���ش洢Ŀ¼");
    LOG(LM_DEBUG, Fmtmsg("ҵ����[%s]���ش洢Ŀ¼[%s]", sBusi_No, sPath), "DEBUG");

    if (0 == strcmp(sBusi_No, "jiebei") || 0 == strcmp(sBusi_No, "jintiao"))
    {
        iRet = ffunc_getfile_to_local(lXmlhandle, sDate,sBusi_No, sPath);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("�ݲ�֧�ֵ�ҵ��"), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "�ݲ�֧�ֵ�ҵ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*TODO:���ļ����Ƹ�ֵ��xml�ڵ�*/
    iRet = ffunc_getfilename_to_xml(lXmlhandle, sBusi_No, sPath);

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/************************************************************************
��̬�����������
�����������:ICPS_FILE_PRE_CHECK
�������:ICPS_FILE_PRE_CHECK
�������: �ļ�Ԥ����
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
  1   1-����   ��ϸ�ļ���               XML�����ַ���                      N    ��ϸ�ļ���
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_FILE_PRE_CHECK(HXMLTREE lXmlhandle)
{
    char sBuf[10000];
    int iRet = -1;
    int iParas = 0;

    PARA_FILEPRECHK st_para_fileprechk;
    /*��ʼ�����*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(4)

    memset(&st_para_fileprechk, 0x00, sizeof(st_para_fileprechk));
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, st_para_fileprechk.date, "�ļ������ļ�������");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, st_para_fileprechk.busi_no, "ҵ����");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, st_para_fileprechk.bank_id, "���д���");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(4, sBuf, st_para_fileprechk.path, "���ش洢Ŀ¼");
    LOG(LM_DEBUG,
            Fmtmsg("�ļ������ļ�������[%s]ҵ����[%s]���д���[%s]���ش洢Ŀ¼[%s]", st_para_fileprechk.date, st_para_fileprechk.busi_no,
                    st_para_fileprechk.bank_id, st_para_fileprechk.path), "DEBUG");

    if (0 == strcmp(st_para_fileprechk.busi_no, "wbank"))
    {
        iRet = ffunc_file_pre_check(lXmlhandle, st_para_fileprechk);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("�ݲ�֧�ֵ�ҵ��"), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "�ݲ�֧�ֵ�ҵ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/************************************************************************
��̬�����������
�����������:ICPS_FILE_INFO_INIT
�������:ICPS_FILE_INFO_INIT
�������: ��ʼ���ļ�������Ϣ
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
  1   1-����   ��ϸ�ļ���               XML�����ַ���                      N    ��ϸ�ļ���
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_FILE_INFO_INIT(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];

    PARA_FILEINFOINIT st_para_fileinfoinit;

    /*��ʼ�����*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");

    memset(&st_para_fileinfoinit, 0, sizeof(st_para_fileinfoinit));
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, st_para_fileinfoinit.busi_date, "ҵ������");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, st_para_fileinfoinit.busi_no, "ҵ����");
    LOG(LM_STD, Fmtmsg("ҵ������=[%s],ҵ����=[%s]", st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no), "INFO");

    if (0 == strcmp(st_para_fileinfoinit.busi_no, "jiebei"))
    {
        iRet = ffunc_init_jiebei_file_info(lXmlhandle, st_para_fileinfoinit);
    }
    else if (0 == strcmp(st_para_fileinfoinit.busi_no, "jintiao"))
    {
        iRet = ffunc_init_jintiao_file_info(lXmlhandle, st_para_fileinfoinit);
    }
    else if (0 == strcmp(st_para_fileinfoinit.busi_no, "wbank"))
    {
        iRet = ffunc_init_wbank_file_info(lXmlhandle, st_para_fileinfoinit);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("�ݲ�֧�ֵ�ҵ��"), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "�ݲ�֧�ֵ�ҵ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/************************************************************************
��̬�����������
�����������:ICPS_CHK_FILE_INS
�������:ICPS_CHK_FILE_INS
�������: ������ϸ�ļ����
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
  1   1-����   ��ϸ�ļ���               XML�����ַ���                      N    ��ϸ�ļ���
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_CHK_FILE_INS(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    int fileins_status = -1;

    FILE *fp = NULL;

    PARA_CHKFILEINS st_para_chkfileins;

    memset(&st_para_chkfileins, 0, sizeof(st_para_chkfileins));
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, st_para_chkfileins.busi_date, "ҵ������");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, st_para_chkfileins.busi_no, "ҵ����");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, st_para_chkfileins.file_type, "�ļ�����");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(4, sBuf, st_para_chkfileins.file_path, "�ļ�·��");

    LOG(LM_STD,
            Fmtmsg("ҵ������=[%s],ҵ����=[%s],�ļ�����=[%s]\n�ļ�·��=[%s]", st_para_chkfileins.busi_date, st_para_chkfileins.busi_no,
                    st_para_chkfileins.file_type, st_para_chkfileins.file_path), "INFO");

    /*���£������򿪶����ļ��������*/
    if (0 == strcmp(st_para_chkfileins.busi_no, "jiebei") || 0 == strcmp(st_para_chkfileins.busi_no, "jintiao"))
    {
        if ((fp = fopen(st_para_chkfileins.file_path, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("�򿪶����ļ�ʧ��[%s]", st_para_chkfileins.file_path), "ERROR");
            fpub_SetMsg(lXmlhandle, MID_SYS_OPENFILE, "�ļ���ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if (0 == strcmp(st_para_chkfileins.busi_no, "jiebei"))
        {
            iRet = ffunc_parse_jiebei_file_to_db(lXmlhandle, fp, st_para_chkfileins);
        }
        else if (0 == strcmp(st_para_chkfileins.busi_no, "jintiao"))
        {
            iRet = ffunc_parse_jintiao_file_to_db(lXmlhandle, fp, st_para_chkfileins);
        }
    }
    else if (0 == strcmp(st_para_chkfileins.busi_no, "wbank"))
    {
        LOG(LM_STD, Fmtmsg("��ʼ�����ļ�[%s]", st_para_chkfileins.busi_no), "INFO")
        iRet = ffunc_parse_wbank_file_to_db(lXmlhandle, st_para_chkfileins);
    }
    else
    {
        if (fp)
        {
            fclose(fp);
            fp = NULL;
        }
        LOG(LM_STD, Fmtmsg("�ݲ�֧�ֵ�ҵ��"), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "�ݲ�֧�ֵ�ҵ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if (0 > iRet)
    {
        if (fp)
        {
            fclose(fp);
            fp = NULL;
        }
        LOG(LM_STD, Fmtmsg("�����ļ����ʧ��iRet[%d]", iRet), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "�ļ����ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}


/************************************************************************
��̬�����������
�����������:ICPS_JIEBEI_CHKSUM
�������:ICPS_JIEBEI_CHKSUM
�������: ���Ͻ��¶�����
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
  1   1-����   ��ϸ�ļ���               XML�����ַ���                      N    ��ϸ�ļ���
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_JIEBEI_CHKSUM(HXMLTREE lXmlhandle)
{
    int iParas = -1;
    int iRet = -1;
    char sBuf[255];
    char sBusi_Date[8 + 1];

    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(1)
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sBusi_Date, "ҵ������");

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:ICPS_JINTIAO_CHKSUM
�������:ICPS_JINTIAO_CHKSUM
�������: ��������������
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
  1   1-����   ��ϸ�ļ���               XML�����ַ���                      N    ��ϸ�ļ���
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_JINTIAO_CHKSUM(HXMLTREE lXmlhandle)
{
    int iParas = -1;
    int iRet = -1;
    char sBuf[255];
    char sBusi_Date[8 + 1];

    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(1)
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sBusi_Date, "ҵ������");

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:ICPS_WBANK_CHKSUM
�������:ICPS_WBANK_CHKSUM
�������: ΢����������
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
  1   1-����   ��ϸ�ļ���               XML�����ַ���                      N    ��ϸ�ļ���
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_WBANK_CHKSUM(HXMLTREE lXmlhandle)
{
    int iParas = -1;
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[256];
    char sBusi_Date[8 + 1];
    double provisions_bal = 0.00;
    double position_bal = 0.00;
    double trans_total_amt = 0.00;
    double sum_diff_amt = 0.00; /*β�����*/
    double interest_amt = 0.00; /*���ս�Ϣ���*/
    double daily_diff_amt; /*���ղ��*/
    double diff_range; /*���ղ��췶Χ*/
    char sSqlStr[1024];


    ICPS_WB_DS_SPLIT_DIFF sdb_icps_wb_ds_split_diff;

    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(1)
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sBusi_Date, "ҵ������");
    LOG(LM_DEBUG, Fmtmsg("ҵ������[%s]", sBusi_Date), "");

    ICPS_GETXMLNODE_DOUBLE("/icps/req/provisions_bal", provisions_bal, "�����������");
    ICPS_GETXMLNODE_DOUBLE("/icps/req/position_bal", position_bal, "Ӱ���˻����");
    ICPS_GETXMLNODE_DOUBLE("/icps/req/trans_total_amt", trans_total_amt, "��������");
    LOG(LM_DEBUG, Fmtmsg("�����������[%d],Ӱ���˻����[%d],��������[%d]", provisions_bal, position_bal, trans_total_amt), "");
    ICPS_GETXMLNODE_DOUBLE("/icps/cskz/diff_range", diff_range, "���ղ��췶Χ");

    memset(sSqlStr, 0, sizeof(sSqlStr));
    snprintf(sSqlStr, sizeof(sSqlStr),
            "SELECT NVL(SUM(ERROR_AMT),0) AS SUM_DIFF_AMT FROM (SELECT CASE WHEN ERROR_TYPE='C01' AND TRANS_TYPE='D' THEN 0-ERROR_AMT ELSE ERROR_AMT END AS ERROR_AMT FROM ICPS_WB_DS_SPLIT_DIFF WHERE BUSI_DATE='%s')",
            sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("ͳ��β������ܽ��[%s]", sSqlStr), "DEBUG");

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    trim(sBuf);
    sum_diff_amt = atof(sBuf);
    LOG(LM_DEBUG, Fmtmsg("β������ܽ��[%s][%f]", sBuf, sum_diff_amt), "DEBUG");

    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    snprintf(sSqlStr, sizeof(sSqlStr),
            "SELECT NVL(AMOUNT,0) FROM ICPS_WB_RSS_OTHER_DETAIL WHERE BUSI_DATE='%s' AND DATA_TYPE='1' AND MEMO IS NULL", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("ͳ�ƽ�Ϣ���[%s]", sSqlStr), "DEBUG");

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    trim(sBuf);
    interest_amt = atof(sBuf);
    LOG(LM_DEBUG, Fmtmsg("��Ϣ���[%f]", interest_amt), "DEBUG");

    daily_diff_amt = position_bal + trans_total_amt - provisions_bal - sum_diff_amt + interest_amt;
    LOG(LM_DEBUG, Fmtmsg("���ղ��[%f]", daily_diff_amt), "DEBUG");


    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}