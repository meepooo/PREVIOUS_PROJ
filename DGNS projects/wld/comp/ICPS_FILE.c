#include <math.h>
#include <dirent.h>

#define SOCOMPBUILDNO BUILDDATETIME#define SOCOMPVERSION "V1.0.0"
#include "DCI.h"
#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include "../tbh64/ICPS_DS_ACCOUNTING_FLOW_DIFF.h"

#define PRECISION 0.00001

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
        LOG(LM_STD, Fmtmsg("����:ICPS_FILE_INFO_INIT"), "ERROR")
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
�������:T-1��β������
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
    char sBuf[256];
    char sErrmsg[256];
    char sBusi_Date[8 + 1];
    char sClear_Date[8 + 1];
	char sDiff_Node[128]; /**β���Žڵ�**/
    char sSqlStr[1024];

    double provisions_bal = 0.00;
    double position_bal = 0.00;
    double trans_total_amt = 0.00;
    double sum_diff_amt = 0.00; /*β�����*/
    double interest_amt = 0.00; /*���ս�Ϣ���*/
    double daily_diff_amt; /*���ղ��*/
	double ds_split_diff_T; /**T+1�պ�T��A01��Ӧ�������**/
	double ds_split_diff_T2; /**A02��Ӧ�������**/
	double ds_split_diff_B1; /**B01��Ӧ�������**/
	double ds_split_diff_G1; /**G01��Ӧ�������**/
    //double diff_range; /*���ղ��췶Χ*/
	
	ICPS_DAILY_TC_DIFF icps_daily_tc_diff;
	memset(&icps_daily_tc_diff, 0x00, sizeof(icps_daily_tc_diff));
	
    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(2)
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sClear_Date, "��������");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, sBusi_Date, "ҵ������");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, sDiff_Node, "β���Žڵ�");
    LOG(LM_DEBUG, Fmtmsg("ҵ������[%s]", sBusi_Date), "");
    LOG(LM_DEBUG, Fmtmsg("��������[%s]", sClear_Date), "");
    LOG(LM_DEBUG, Fmtmsg("β���Žڵ�[%s]", sDiff_Node), "");

	pstrcopy(icps_daily_tc_diff.busi_date, sBusi_Date, sizeof(icps_daily_tc_diff.busi_date));
	pstrcopy(icps_daily_tc_diff.clear_date, sClear_Date, sizeof(icps_daily_tc_diff.clear_date));

    ICPS_GETXMLNODE_DOUBLE("/icps/req/provisions_bal", provisions_bal, "�����������");
    ICPS_GETXMLNODE_DOUBLE("/icps/req/position_bal", position_bal, "Ӱ���˻����");
    /**ICPS_GETXMLNODE_DOUBLE("/icps/req/trans_total_amt", trans_total_amt, "��������");ȡ����������---modify by wl 20180515**/
    LOG(LM_DEBUG, Fmtmsg("�����������[%.2f],Ӱ���˻����[%.2f],��������[%.2f]", provisions_bal, position_bal, trans_total_amt), "");
  //  ICPS_GETXMLNODE_DOUBLE("/icps/cskz/diff_range", diff_range, "���ղ��췶Χ");
	icps_daily_tc_diff.total_bal=position_bal;
	icps_daily_tc_diff.reserve_bal=provisions_bal;
	
    memset(sSqlStr, 0, sizeof(sSqlStr));
    snprintf(sSqlStr, sizeof(sSqlStr),
           /** "SELECT NVL(SUM(ERROR_AMT),0) AS SUM_DIFF_AMT FROM (SELECT CASE WHEN ERROR_TYPE='D01' AND TRANS_TYPE='D' THEN 0-ERROR_AMT ELSE ERROR_AMT END AS ERROR_AMT FROM ICPS_WB_DS_SPLIT_DIFF WHERE BUSI_DATE='%s')",**/
			 "select NVL(SUM(ERROR_AMT),0) AS SUM_DIFF_AMT from (select case when a.trans_type in ('C','DR') then a.ERROR_AMT when a.trans_type='D' then -a.ERROR_AMT end as ERROR_AMT from ICPS_WB_DS_SPLIT_DIFF a where a.busi_date='%s' and  a.trans_type in('C','DR','D') and a.error_type='D01')", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("ͳ��β������ܽ��[%s]", sSqlStr), "DEBUG");

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    trim(sBuf);
    sum_diff_amt = atof(sBuf);
	icps_daily_tc_diff.t_bal=sum_diff_amt;
    LOG(LM_DEBUG, Fmtmsg("β������ܽ��[%s][%f]", sBuf, sum_diff_amt), "DEBUG");

	/**����T�պ�T+1��A01��Ӧ�������**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select NVL(sum(ERROR_AMT), 0) from ICPS_WB_DS_SPLIT_DIFF where  busi_date in (to_char((to_date('%s','yyyymmdd')+1 days),'yyyymmdd'),'%s') and ERROR_TYPE='A01'",
			sBusi_Date, sBusi_Date);
	
    LOG(LM_DEBUG, Fmtmsg("A01��Ӧ�������[%s]", sSqlStr), "DEBUG");
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	trim(sBuf);
	ds_split_diff_T=atof(sBuf);
	icps_daily_tc_diff.reserve_diff=ds_split_diff_T;
    LOG(LM_DEBUG, Fmtmsg("ͳ��A01���[%f]",ds_split_diff_T ), "DEBUG");

	/**T�յ�DS_SPLIT_DIFF���е�A02��Ӧ����������**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select NVL(sum(ERROR_AMT), 0) from ICPS_WB_DS_SPLIT_DIFF where ERROR_TYPE='A02' and busi_date='%s'", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("A02��Ӧ�������[%s]", sSqlStr), "DEBUG");
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	trim(sBuf);
	ds_split_diff_T2=atof(sBuf);
	icps_daily_tc_diff.financial_diff=ds_split_diff_T2;
    LOG(LM_DEBUG, Fmtmsg("ͳ��A02���[%f]",ds_split_diff_T2 ), "DEBUG");

	/**T�յ�DS_SPLIT_DIFF���е�B01��Ӧ����������**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select NVL(sum(ERROR_AMT), 0) from ICPS_WB_DS_SPLIT_DIFF where ERROR_TYPE='B01' and busi_date='%s'", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("B01��Ӧ�������[%s]", sSqlStr), "DEBUG");
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	trim(sBuf);
	ds_split_diff_B1=atof(sBuf);
	icps_daily_tc_diff.person_diff=ds_split_diff_B1;
    LOG(LM_DEBUG, Fmtmsg("ͳ��B01���[%f]",ds_split_diff_B1 ), "DEBUG");

	/**T�յ�DS_SPLIT_DIFF���е�G01��Ӧ����������**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select NVL(sum(ERROR_AMT), 0) from ICPS_WB_DS_SPLIT_DIFF where ERROR_TYPE='G01' and busi_date='%s'", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("G01��Ӧ�������[%s]", sSqlStr), "DEBUG");
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	trim(sBuf);
	ds_split_diff_G1=atof(sBuf);
	icps_daily_tc_diff.overplay_diff=ds_split_diff_G1;
    LOG(LM_DEBUG, Fmtmsg("ͳ��G01���[%f]",ds_split_diff_G1 ), "DEBUG");

	/**ͳ�Ƶ����Ϣ���**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    snprintf(sSqlStr, sizeof(sSqlStr),
            "SELECT NVL(AMOUNT,0) FROM ICPS_WB_RSS_OTHER_DETAIL WHERE SUBSTR(BUSI_DATE,5,4) IN('0321','0621','0921','1221') AND DATA_TYPE='1' AND MEMO=''"); LOG(LM_DEBUG, Fmtmsg("ͳ�ƽ�Ϣ���[%s]", sSqlStr), "DEBUG");

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    trim(sBuf);
    interest_amt = atof(sBuf);
	icps_daily_tc_diff.interest_diff=interest_amt;
    LOG(LM_DEBUG, Fmtmsg("��Ϣ���[%f]", interest_amt), "DEBUG");

    daily_diff_amt = position_bal  - provisions_bal - sum_diff_amt - ds_split_diff_T - ds_split_diff_T2 - ds_split_diff_B1 - ds_split_diff_G1 + interest_amt;
	daily_diff_amt=fabs(daily_diff_amt);
	icps_daily_tc_diff.daily_diff=daily_diff_amt;
    LOG(LM_DEBUG, Fmtmsg("���ղ��[%f]", daily_diff_amt), "DEBUG");
   
   	memset(sErrmsg, 0x00, sizeof(sErrmsg));
   	iRet = APP_DBInsert("ICPS_DAILY_TC_DIFF", SD_ICPS_DAILY_TC_DIFF, NUMELE(SD_ICPS_DAILY_TC_DIFF), &icps_daily_tc_diff, sErrmsg);     
	if (iRet < 0)
    {
	    LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
	    return iRet;
	 }   
   	if (DCICommit() != MID_SYS_SUCC)
    {
        LOG(LM_STD, Fmtmsg("���ݿ��ύʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
       	return -1;
   	}
	
    memset(sBuf, 0, sizeof(sBuf));
	sprintf (sBuf, "%.2f", daily_diff_amt);
	trim(sBuf);
	COMP_HARDSETXML(sDiff_Node,sBuf);
	/**
	if (fabs(daily_diff_amt - diff_range) > PRECISION)
	{
        LOG(LM_STD, Fmtmsg("β�����"), "ERROR")
		COMP_HARDSETXML("/pub/diff_range", "1");
	}
    else
	{
        LOG(LM_STD, Fmtmsg("β���ڿɿط�Χ��"), "ERROR")
		COMP_HARDSETXML("/pub/diff_range", "0");
	}***/
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:ICPS_WBANK_TOTAL_CHECK
�������:ICPS_WBANK_DETAIL_CHECK
�������: ΢������ϸ������
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
  1   1-����   ��ϸ�ļ���               XML�����ַ���                      N    ��ϸ�ļ���
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_WBANK_TOTAL_CHECK(HXMLTREE lXmlhandle)
{
    int iParas = -1;
    int iRet = -1;
	int iDr_status= 0;
	int iCr_status= 0;
	int iDcount = 0; /**�跽��ϸ���ܱ���**/
	int iCcount = 0; /**��������**/
    char sBuf[1024];
    char sErrmsg[256];
    char sBusi_Date[8 + 1]; /**ҵ������**/
    char sBusi_No[16 + 1]; /**ҵ������**/
    char sSqlStr[1024];
    char sSqlStr2[1024];
	char sSubject[40];/**��Ŀ��**/
	char sZje1[40];
	char sZje2[40];
	char sTmp[128];
	double dDr_amt;/**�������������**/
	double dCr_amt;/**�跽���������**/
	double dDr_pmt;/**���մ���������**/
	double dCr_pmt;/**���ս跽������**/

	ICPS_DS_ACCOUNTING_FLOW_DIFF  ds_accounting_flow_diff;
    ICPS_WB_TM_GL_BAL tm_gl_bal;
	
	int iNum=0; /**��������**/
	int iSucc_flag= 0; /**0�ɹ���1ʧ��**/
	CURSOR cur;
    
    /*��ʼ�����*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(2)

    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sBusi_Date, "ҵ������");
	trim(sBusi_Date);
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, sBusi_No, "ҵ������");
	trim(sBusi_No);
    LOG(LM_DEBUG, Fmtmsg("ҵ������[%s]", sBusi_Date), "");
    LOG(LM_DEBUG, Fmtmsg("ҵ������[%s]", sBusi_No), "");
	
	/**��Ŀ�˶�**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    LOG(LM_DEBUG, Fmtmsg("1-[%s]", sBusi_Date), "");
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select subject,db_amt,db_count,cr_amt,cr_count,bank_group_id,product_cd from ICPS_WB_TM_GL_BAL	where busi_date='%s'", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("sSqlStr[%s]", sSqlStr), "");
	if(cur = DCIDeclareCursor(sSqlStr, DCI_STMT_LOCATOR) == -1)
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
    LOG(LM_DEBUG, Fmtmsg("2[%s]", sBusi_Date), "");
	while(1 == DCIFetch2(cur,DCI_FETCH_NEXT,0))
    {
   		 LOG(LM_DEBUG, Fmtmsg("3[%s]", sBusi_Date), "");
		 iDr_status= 0;
		 iCr_status= 0;
		 iDcount = 0; 
	 	 iCcount = 0;
	     memset(&tm_gl_bal, 0x00, sizeof(tm_gl_bal));
		 memset(&ds_accounting_flow_diff, 0x00, sizeof(&ds_accounting_flow_diff));
		 /**��Ŀ**/
         strncpy(tm_gl_bal.subject,DCIFieldAsString(cur,0),sizeof(tm_gl_bal.subject));
   		 LOG(LM_DEBUG, Fmtmsg("subject[%s]", tm_gl_bal.subject), "");
		 /**�跽������**/
		 memset(sTmp, 0x00, sizeof(sTmp));
         strncpy(sTmp, DCIFieldAsString(cur,1), sizeof(sTmp));
		 trim(sTmp);
   		 LOG(LM_DEBUG, Fmtmsg("sTmp[%s]", sTmp), "");
         tm_gl_bal.db_amt=atof(sTmp);
   		 LOG(LM_DEBUG, Fmtmsg("db_amt[%.2f]", tm_gl_bal.db_amt), "");
         /**�跽����**/
		 memset(sTmp, 0x00, sizeof(sTmp));
         strncpy(sTmp,DCIFieldAsString(cur,2), sizeof(sTmp));
		 trim(sTmp);
         tm_gl_bal.db_count=atoi(trim(sTmp));
   		 LOG(LM_DEBUG, Fmtmsg("db_count[%d]", tm_gl_bal.db_count), "");
		 /**����������**/
		 memset(sTmp, 0x00, sizeof(sTmp));
         strncpy(sTmp,DCIFieldAsString(cur,3), sizeof(sTmp));
		 trim(sTmp);
         tm_gl_bal.cr_amt=atof(sTmp);
   		 LOG(LM_DEBUG, Fmtmsg("cr_amt[%.2f]", tm_gl_bal.cr_amt), "");
		 /**��������**/
		 memset(sTmp, 0x00, sizeof(sTmp));
         strncpy(sTmp,DCIFieldAsString(cur,4), sizeof(sTmp));
		 trim(sTmp);
         tm_gl_bal.cr_count=atoi(trim(sTmp));
   		 LOG(LM_DEBUG, Fmtmsg("cr_count[%d]", tm_gl_bal.cr_count), "");
		 /**���ű��**/
         strncpy(tm_gl_bal.bank_group_id,DCIFieldAsString(cur,5),sizeof(tm_gl_bal.bank_group_id));
   		 LOG(LM_DEBUG, Fmtmsg("bank_group_id[%s]", tm_gl_bal.bank_group_id), "");
		 /**��Ʒ����**/
         strncpy(tm_gl_bal.product_cd,DCIFieldAsString(cur,6),sizeof(tm_gl_bal.product_cd));
   		 LOG(LM_DEBUG, Fmtmsg("tm_gl_bal.product_cd[%s]", tm_gl_bal.product_cd), "");
		 /**ͳ�ƻ���ձ����շ��������**/
		 /**���մ������=���մ������-���մ��������� \
		  	���ս跽���=���ս跽���+���ս跽������ \
			���մ���������=���մ�������������-���մ������������\
			���ս跽������=���ս跽����������-���ս跽���������***/

		/**�˶Խ跽������**/
		iDr_status = ffunc_mxzz_check(lXmlhandle, tm_gl_bal, sBusi_Date, "D", &dDr_amt, &iDcount);
		if (0 == iDr_status)
		{
			DCIFreeCursor(cur);
    		LOG(LM_DEBUG, Fmtmsg("�˶Խ跽������ʧ��!"), "");
	     	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		}
		/**�˶Դ���������**/
		iCr_status = ffunc_mxzz_check(lXmlhandle, tm_gl_bal, sBusi_Date, "C",  &dCr_amt, &iCcount);
		if (0 == iCr_status)
		{	
			DCIFreeCursor(cur);
    		LOG(LM_DEBUG, Fmtmsg("�˶Դ���������ʧ��!"), "");
	     	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		}
		sprintf (ds_accounting_flow_diff.dr_check_flag,"%d", iDr_status);
		sprintf (ds_accounting_flow_diff.cr_check_flag,"%d", iCr_status);
		ds_accounting_flow_diff.db_tcnt = tm_gl_bal.db_count;
		ds_accounting_flow_diff.cr_tcnt = tm_gl_bal.cr_count;
		ds_accounting_flow_diff.db_count = iDcount;
		ds_accounting_flow_diff.cr_count = iCcount;

		pstrcopy(ds_accounting_flow_diff.busi_date, sBusi_Date, sizeof(ds_accounting_flow_diff.busi_date));
		pstrcopy(ds_accounting_flow_diff.subject,tm_gl_bal.subject, sizeof(ds_accounting_flow_diff.subject));
		pstrcopy(ds_accounting_flow_diff.busi_no, sBusi_No, sizeof(ds_accounting_flow_diff.busi_no));
		pstrcopy(ds_accounting_flow_diff.product_cd, tm_gl_bal.product_cd, sizeof(ds_accounting_flow_diff.product_cd));
		pstrcopy(ds_accounting_flow_diff.bank_group_id, tm_gl_bal.bank_group_id, sizeof(ds_accounting_flow_diff.bank_group_id));
		ds_accounting_flow_diff.db_amt=dDr_amt;
		ds_accounting_flow_diff.cr_amt=dCr_amt;
		ds_accounting_flow_diff.db_pmt=tm_gl_bal.db_amt;
		ds_accounting_flow_diff.cr_pmt=tm_gl_bal.cr_amt;

    	memset(sErrmsg, 0x00, sizeof(sErrmsg));
     	iRet = APP_DBInsert("ICPS_DS_ACCOUNTING_FLOW_DIFF", SD_ICPS_DS_ACCOUNTING_FLOW_DIFF, NUMELE(SD_ICPS_DS_ACCOUNTING_FLOW_DIFF), &ds_accounting_flow_diff, sErrmsg);     
		if (iRet < 0)
	    {
		    LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
		    DCIRollback();
			DCIFreeCursor(cur);
	     	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		    return iRet;
		 }   
    
    	if (DCICommit() != MID_SYS_SUCC)
        {
            LOG(LM_STD, Fmtmsg("���ݿ��ύʧ��,sqlerr[%s]", DCILastError()), "ERROR")
	        DCIRollback();
			DCIFreeCursor(cur);
	     	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        	return -1;
    	}
	    if (iDr_status != 1 || iCr_status != 1)
		{
			iSucc_flag++;
		}
	}
	DCIFreeCursor(cur);
	if (iSucc_flag == 0)
	{
		COMP_HARDSETXML("/icps/req/chkstatus", "0"); 
	}
	else
	{
		COMP_HARDSETXML("/icps/req/chkstatus", "1"); 
		
	}
  	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   	return COMPRET_SUCC;

}	

/************************************************************************
��̬�����������
��������: ICPS_WB_CAV_INS
����: ΢���������ļ����
 
�������: ΢���������ļ����
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
************************************************************************/
IRESULT ICPS_WB_CAV_INS(HXMLTREE lXmlhandle)
{
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sCAVFile[255+1];      /*�ļ�������·����*/
  char sSignDate[8+1];       /*�Ǽ�����*/
  double dLoanInitPrin=0.00;		 /*��ݱ���*/

  ICPS_WB_CAV_INFO icps_wb_cav_info;

  FILE *fp;

  int incnt=0;                  /*�������*/
 
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  
  memset(sCAVFile, 0x00, sizeof(sCAVFile));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "�ļ�������·����");
  trim(sBuffer);
  pstrcopy(sCAVFile,sBuffer,sizeof(sCAVFile));
  
  memset(sSignDate, 0x00, sizeof(sSignDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "�Ǽ�����");
  trim(sBuffer);
  pstrcopy(sSignDate,sBuffer,sizeof(sSignDate));
  
  LOG(LM_STD, Fmtmsg("΢���������ļ�[%s],�Ǽ�����[%s]", sCAVFile, sSignDate), fpub_GetCompname(lXmlhandle)); 


  if(strlen(sCAVFile) == 0)
  {
      fpub_SetMsg(lXmlhandle, MID_SYS_OPENFILE, "΢���������ļ�������Ϊ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("�ļ�������Ϊ�գ�"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  fp = fopen(sCAVFile, "r");
  if ( fp == NULL )
  {
      fpub_SetMsg(lXmlhandle, MID_SYS_OPENFILE, "΢���������ļ���ʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("���ļ�%sʧ��",sCAVFile), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }

  DCIBegin();
  //��ϸ���
  while( !feof(fp) )
  {
		memset(&icps_wb_cav_info, 0x00, sizeof(icps_wb_cav_info));
		memset(sBuffer, 0x00, sizeof(sBuffer));     
		fgets(sBuffer, sizeof(sBuffer), fp);
		if( strlen(trim(sBuffer)) <= 0 )
		   continue;
		
		incnt++;
		
		/*1-CNC�ͻ�ID*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,1,sTmp,',','\\');
		trim(sTmp);
		memcpy(icps_wb_cav_info.CUST_ID,sTmp,sizeof(icps_wb_cav_info.CUST_ID)-1);
		
		/*2-�߼�����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,2,sTmp,',','\\');
		trim(sTmp);
		memcpy(icps_wb_cav_info.LOGICAL_CARD_NO,sTmp,sizeof(icps_wb_cav_info.LOGICAL_CARD_NO)-1);
		if(strlen(icps_wb_cav_info.LOGICAL_CARD_NO) == 0)
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "�߼����Ų���Ϊ��"), "INFO" );
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "�߼����Ų���Ϊ��");
			break;
		}
	 
		/*3-��Ʒ��*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,3,sTmp,',','\\');
		trim(sTmp);
		memcpy(icps_wb_cav_info.PRODUCT_CD,sTmp,sizeof(icps_wb_cav_info.PRODUCT_CD)-1);
		
		/*4-��ݺ�(���ײο���)*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,4,sTmp,',','\\');
		trim(sTmp);
		memcpy(icps_wb_cav_info.REF_NBR,sTmp,sizeof(icps_wb_cav_info.REF_NBR)-1);
		if(strlen(icps_wb_cav_info.REF_NBR) == 0)
		{
			 iResult = -1;
		   LOG( LM_DEBUG, Fmtmsg( "��ݺ�(���ײο���)����Ϊ��"), "INFO" );
		   fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "��ݺ�(���ײο���)����Ϊ��");
		   break;
		}
		
		/*5-��ݱ���*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,5,sTmp,',','\\');
   	dLoanInitPrin = atof(sTmp);
   	icps_wb_cav_info.LOAN_INIT_PRIN=dLoanInitPrin;
   	
		/*6-���ź�*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,6,sTmp,',','\\');
		trim(sTmp);
		memcpy(icps_wb_cav_info.BANK_GROUP_ID,sTmp,sizeof(icps_wb_cav_info.BANK_GROUP_ID)-1);
		
		/*�ļ����ޣ������ݿ�����Ҫ*/
		/*BUSI_DATE-ҵ������*/
		memcpy(icps_wb_cav_info.BUSI_DATE,sSignDate,sizeof(icps_wb_cav_info.BUSI_DATE)-1);
		
		/*���*/
		LOG(LM_STD,Fmtmsg("incnt=[%d],Insert,LOGICAL_CARD_NO=[%s],REF_NBR=[%s]", incnt, icps_wb_cav_info.LOGICAL_CARD_NO, icps_wb_cav_info.REF_NBR),"ERROR")
		memset(sTmp,0x00,sizeof(sTmp));
//		iRet = DBInsert( "ICPS_WB_CAV_INFO", SD_ICPS_WB_CAV_INFO, NUMELE( SD_ICPS_WB_CAV_INFO ), &icps_wb_cav_info,sTmp);
		iRet = APP_DBInsert("ICPS_WB_CAV_INFO", SD_ICPS_WB_CAV_INFO, NUMELE(SD_ICPS_WB_CAV_INFO), &icps_wb_cav_info,sTmp);
		if( iRet < 0 )
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "���΢����������Ϣ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "���΢����������Ϣ��");
			break;   
		}
  }

  fclose(fp);
  if( iResult < 0 )
  {
      DCIRollback();
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL ;         
  }    
  
  if( DCICommit() != 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( "�ύʱ������Ϣ=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "�����ύ����");
      return COMPRET_FAIL ;
  }
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
��������: ICPS_WB_CAV_PRE
����: ΢���������ļ�Ԥ���
 
�������: ΢���������ļ�Ԥ���
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
************************************************************************/
IRESULT ICPS_WB_CAV_PRE(HXMLTREE lXmlhandle)
{
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sFilePath[255+1];      /*ָ��·��*/
  char sNameString[255+1];      /*ָ��·��*/
  char sFileExistXML[255+1];      /*ָ��·��*/
  DIR *dirp;
  struct dirent *dp;
  char sFilesName[1024]={0};
  int iFileExistNum=0;
  
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  
  memset(sFilePath, 0x00, sizeof(sFilePath));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "ָ��·��");
  trim(sBuffer);
  pstrcopy(sFilePath,sBuffer,sizeof(sFilePath));
  
  memset(sNameString, 0x00, sizeof(sNameString));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "�ļ����������ַ���");
  trim(sBuffer);
  pstrcopy(sNameString,sBuffer,sizeof(sNameString));
  
  memset(sFileExistXML, 0x00, sizeof(sFileExistXML));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(3, sBuffer, "�����ļ�������Žڵ�");
  trim(sBuffer);
  pstrcopy(sFileExistXML,sBuffer,sizeof(sFileExistXML));
  
  LOG(LM_STD, Fmtmsg("ָ��·��[%s],�����ļ�������Žڵ�[%s]", sFilePath, sFileExistXML), fpub_GetCompname(lXmlhandle)); 

  if(strlen(sFilePath) == 0)
  {
    fpub_SetMsg(lXmlhandle, MID_SYS_OPENFILE, "ָ��·������Ϊ��");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    LOG(LM_STD, Fmtmsg("ָ��·������Ϊ�գ�"), fpub_GetCompname(lXmlhandle))
    return COMPRET_FAIL ;
  }
  
  if(strlen(sNameString) == 0)
  {
    pstrcopy(sNameString,".zip",sizeof(sNameString));
  }
  LOG(LM_STD, Fmtmsg("�ļ����������ַ���[%s]", sNameString), fpub_GetCompname(lXmlhandle)); 
  dirp = opendir(sFilePath);
  while((dp=readdir(dirp)) != NULL)
  {
    strcat(sFilesName,dp->d_name);
    strcat(sFilesName,"|");
    if(strstr(dp->d_name,sNameString) != NULL )
    {
      LOG(LM_STD, Fmtmsg("���ں����ļ�[%s]", dp->d_name), fpub_GetCompname(lXmlhandle));
      iFileExistNum += 1;
    }
  }
  LOG(LM_STD, Fmtmsg("�ļ���[%s]", sFilesName), fpub_GetCompname(lXmlhandle));
  closedir(dirp);
  COMP_HARDSETXML(sFileExistXML, itoa(iFileExistNum));
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}

