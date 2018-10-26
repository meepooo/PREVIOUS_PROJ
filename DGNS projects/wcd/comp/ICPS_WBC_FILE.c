#include <math.h>

#define SOCOMPBUILDNO BUILDDATETIME#define SOCOMPVERSION "V1.0.0"
#include "DCI.h"
#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include "../incl/tbh/ICPS_DS_ACCOUNTING_FLOW_DIFF.h"

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

    WBC_PARA_FILEPRECHK st_para_fileprechk;
    /*��ʼ�����*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(5)

    memset(&st_para_fileprechk, 0x00, sizeof(st_para_fileprechk));
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, st_para_fileprechk.date, "�ļ������ļ�������");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, st_para_fileprechk.busi_no, "ҵ����");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, st_para_fileprechk.bank_id, "���д���");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(4, sBuf, st_para_fileprechk.path, "���ش洢Ŀ¼");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(5, sBuf, st_para_fileprechk.gcdcpbh, "��������Ʒ���");
    LOG(LM_DEBUG,
            Fmtmsg("�ļ������ļ�������[%s]ҵ����[%s]���д���[%s]���ش洢Ŀ¼[%s]��������Ʒ���[%s]", st_para_fileprechk.date, st_para_fileprechk.busi_no,
                    st_para_fileprechk.bank_id, st_para_fileprechk.path,st_para_fileprechk.gcdcpbh), "DEBUG");

    if ((0 == strcmp(st_para_fileprechk.busi_no, "wbank")) || (0 == strcmp(st_para_fileprechk.busi_no, "WCD")))
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
    else if (0 == strcmp(st_para_fileinfoinit.busi_no, "WCD"))
    {
        iRet = ffunc_init_wbankcar_file_info(lXmlhandle, st_para_fileinfoinit);
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

    WBC_PARA_CHKFILEINS st_para_chkfileins;

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
    else if (0 == strcmp(st_para_chkfileins.busi_no, "WCD"))
    {
        LOG(LM_STD, Fmtmsg("��ʼ�����ļ�[%s]", st_para_chkfileins.busi_no), "INFO")
        iRet = ffunc_parse_wbankcar_file_to_db(lXmlhandle, st_para_chkfileins);
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
�����������:ICPS_WBC_CHKSUM
�������:ICPS_WBC_CHKSUM
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
#if 0
IRESULT ICPS_WBC_CHKSUM(HXMLTREE lXmlhandle)
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
    double ds_split_diff_A01; /**T+1�պ�T��A01��Ӧ�������**/
    double ds_split_diff_A02; /**A02��Ӧ�������**/
    double ds_split_diff_B01; /**B01��Ӧ�������**/
    double ds_split_diff_C01; /**C01��Ӧ�������**/ 
    double ds_split_diff_C02; /**C02��Ӧ�������**/

    ICPS_WBC_DAILY_TC_DIFF icps_wbc_daily_tc_diff;
    memset(&icps_wbc_daily_tc_diff, 0x00, sizeof(icps_wbc_daily_tc_diff));

    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(3)
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sClear_Date, "��������");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, sBusi_Date, "ҵ������");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, sDiff_Node, "β���Žڵ�");
    LOG(LM_DEBUG, Fmtmsg("��������[%s]", sClear_Date), "");
    LOG(LM_DEBUG, Fmtmsg("ҵ������[%s]", sBusi_Date), "");
    LOG(LM_DEBUG, Fmtmsg("β���Žڵ�[%s]", sDiff_Node), "");

    pstrcopy(icps_wbc_daily_tc_diff.busi_date, sBusi_Date, sizeof(icps_wbc_daily_tc_diff.busi_date));
    pstrcopy(icps_wbc_daily_tc_diff.clear_date, sClear_Date, sizeof(icps_wbc_daily_tc_diff.clear_date));

    ICPS_GETXMLNODE_DOUBLE("/icps/req/provisions_bal", provisions_bal, "�����������");
    ICPS_GETXMLNODE_DOUBLE("/icps/req/position_bal", position_bal, "Ӱ���˻����");
    LOG(LM_DEBUG, Fmtmsg("�����������[%.2f],Ӱ���˻����[%.2f]", provisions_bal, position_bal), "");
    icps_wbc_daily_tc_diff.total_bal=position_bal;
    icps_wbc_daily_tc_diff.reserve_bal=provisions_bal;

    /**����T+1��A01��Ӧ�������**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select NVL(sum(ERROR_AMT), 0) from ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF where  busi_date in (to_char((to_date('%s','yyyymmdd')+1 days),'yyyymmdd'),'%s') and ERROR_TYPE='A01'",
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
	icps_wbc_daily_tc_diff.reserve_diff=ds_split_diff_T;
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
	icps_wbc_daily_tc_diff.financial_diff=ds_split_diff_T2;
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
	icps_wbc_daily_tc_diff.person_diff=ds_split_diff_B1;
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
	icps_wbc_daily_tc_diff.overplay_diff=ds_split_diff_G1;
    LOG(LM_DEBUG, Fmtmsg("ͳ��G01���[%f]",ds_split_diff_G1 ), "DEBUG");

	/**ͳ�Ƶ����Ϣ���**/
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
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    trim(sBuf);
    interest_amt = atof(sBuf);
	icps_wbc_daily_tc_diff.interest_diff=interest_amt;
    LOG(LM_DEBUG, Fmtmsg("��Ϣ���[%f]", interest_amt), "DEBUG");

    daily_diff_amt = position_bal  - provisions_bal - sum_diff_amt - ds_split_diff_T - ds_split_diff_T2 - ds_split_diff_B1 - ds_split_diff_G1 + interest_amt;
	daily_diff_amt=fabs(daily_diff_amt);
	icps_wbc_daily_tc_diff.daily_diff=daily_diff_amt;
    LOG(LM_DEBUG, Fmtmsg("���ղ��[%f]", daily_diff_amt), "DEBUG");
   
   	memset(sErrmsg, 0x00, sizeof(sErrmsg));
   	iRet = APP_DBInsert("ICPS_DAILY_TC_DIFF", SD_ICPS_DAILY_TC_DIFF, NUMELE(SD_ICPS_DAILY_TC_DIFF), &icps_wbc_daily_tc_diff, sErrmsg);     
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

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
#endif

/************************************************************************
��̬�����������
�����������:ICPS_WBC_TOTAL_CHECK
�������:ICPS_WBC_TOTAL_CHECK
�������: ΢�����Կ�Ŀ��
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
  1   1-����   ��ϸ�ļ���               XML�����ַ���                      N    ��ϸ�ļ���
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_WBC_TOTAL_CHECK(HXMLTREE lXmlhandle)
{
    int iParas = -1;
    int iRet = -1;
	  int iDr_status= 0;
	  int iCr_status= 0;
	  int iDcount=0;/***�跽���ܱ���*/
	  int iCcount=0;/***��������***/
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
	double dDr_amt;/**�跽���������**/
	double dCr_amt;/**�������������**/
	double dDr_pmt;/**���ս跽������**/
	double dCr_pmt;/**���մ���������**/
	ICPS_DS_ACCOUNTING_FLOW_DIFF  ds_accounting_flow_diff;
    ICPS_WBC_TM_GL_BAL tm_gl_bal;
	
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
			"select subject,db_amt,db_count,cr_amt,cr_count,bank_group_id,product_cd from ICPS_WBC_TM_GL_BAL where busi_date='%s' ", sBusi_Date);
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
		 	iDcount=0;
		 	iCcount=0;
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
    	//LOG(LM_DEBUG, Fmtmsg("4[%s]", sBusi_Date), "");
		iDr_status = ffunc_check_mxzz(lXmlhandle, tm_gl_bal, sBusi_Date, "D", &dDr_amt, &iDcount);
		if (0 == iDr_status)
		{
			DCIFreeCursor(cur);
    		LOG(LM_DEBUG, Fmtmsg("�˶Խ跽������ʧ��!"), "");
	     	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		}
		/**�˶Դ���������**/
		iCr_status = ffunc_check_mxzz(lXmlhandle, tm_gl_bal, sBusi_Date, "C",  &dCr_amt, &iCcount);
		if (0 == iCr_status)
		{	
			DCIFreeCursor(cur);
    		LOG(LM_DEBUG, Fmtmsg("�˶Դ���������ʧ��!"), "");
	     	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		}
		/*mod by zhandongdong 20180827 ��ӱ����˶�*/
		if(tm_gl_bal.db_count != iDcount)
		{
			iDr_status=2;
		}
		if(tm_gl_bal.cr_count != iCcount)
		{
			iCr_status=3;
		}
		/*end by zhandongdong 20180827*/
		sprintf (ds_accounting_flow_diff.dr_check_flag,"%d", iDr_status);
		sprintf (ds_accounting_flow_diff.cr_check_flag,"%d", iCr_status);
		/********************************
		���������Ľ跽����������ds_accounting_flow_diff�����db_tcnt;
		��ϸ��ͳ�ƵĽ跽����������ds_accounting_flow_diff�����db_count;
		added by fuwd22392
		********************************/
		ds_accounting_flow_diff.db_tcnt = tm_gl_bal.db_count;
		ds_accounting_flow_diff.cr_tcnt = tm_gl_bal.cr_count;
		ds_accounting_flow_diff.db_count = iDcount;
		ds_accounting_flow_diff.cr_count = iCcount;
		
		LOG(LM_STD,Fmtmsg("ͳ�ƵĽ跽����[%d]",ds_accounting_flow_diff.db_count),"DEBUG");	
		LOG(LM_STD,Fmtmsg("ͳ�ƵĴ�����[%d]",ds_accounting_flow_diff.cr_count),"DEBUG");	

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
