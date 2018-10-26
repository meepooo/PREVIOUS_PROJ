#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include <iconv.h>
#include <stdio.h>
#include <string.h>

/**
 * ��������
 */
int ffunc_parse_wbankcar_file_to_db_tm_app_main(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_APP_MAIN sdb_icps_wbc_tm_app_main;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_APP_MAIN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fclose(fp_list);
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }
		    LOG(LM_STD,Fmtmsg("���ļ��ɹ���׼�����!"),"INFO");

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_app_main, 0x00, sizeof(sdb_icps_wbc_tm_app_main));
            pstrcopy(sdb_icps_wbc_tm_app_main.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_app_main.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_app_main.file_order = rcdCnt;
            

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_app_main.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_app_main.app_no, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_app_main.app_type, '\001', "��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_app_main.app_lmt, '\001', "������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_app_main.sug_lmt, '\001', "ϵͳ������");
           	ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_app_main.acc_lmt, '\001', "��׼���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_app_main.product_cd, '\001', "����Ʒ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_app_main.business_limit, '\001', "���񿨶��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_app_main.micro_loan_limit, '\001', "С�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_app_main.vehicle_loan, '\001', "ר���ȳ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_app_main.house_loan, '\001', "ר���ȷ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_app_main.renovation_loan, '\001', "ר����װ�޴�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_app_main.travel_loan, '\001', "ר�������δ�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_app_main.wedding_loan, '\001', "ר���Ȼ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_app_main.durable_loan, '\001', "ר����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_app_main.priority, '\001', "�ͻ��ȼ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_app_main.client_type, '\001', "�ͻ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_app_main.approve_quick_flag, '\001', "����������־");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_app_main.busns_num, '\001', "��˾���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_app_main.rtf_state, '\001', "����״̬");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_app_main.point_result, '\001', "����ֵ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_app_main.cust_rate_discount, '\001', "�ͻ����ʸ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_app_main.pro_num, '\001', "����ʵ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_app_main.pro_name, '\001', "���̽ڵ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_app_main.refuse_code, '\001', "�ܾ�ԭ����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_app_main.answer_err_cnt, '\001', "����ش�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_app_main.is_clt, '\001', "�Ƿ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_app_main.spreader_num, '\001', "�ƹ��˱��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_app_main.spreader_org, '\001', "�ƹ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_app_main.spreader_bank, '\001', "�ƹ�����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_app_main.spreader_way, '\001', "�ƹ㷽ʽ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_app_main.spreader_type, '\001', "�ƹ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_app_main.spreader_name, '\001', "�ƹ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_app_main.spreader_num_pre, '\001', "�ƹ㵥λԤ���˱��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_app_main.spreader_phone, '\001', "�ƹ����ֻ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_app_main.sales_ind, '\001', "�Ƿ�����ƹ��ʼ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_app_main.owning_branch, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_app_main.app_promotion_cd, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_app_main.app_source, '\001', "������Դ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_app_main.bank_customer_id, '\001', "���ڿͻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_app_main.dd_flag, '\001', "Լ���ۿ��Ƿ�ͨ��ʶ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_app_main.deduct_deal_no, '\001', "�Կ�Э���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_app_main.if_refuse, '\001', "�Ƿ�ܾ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_app_main.if_end, '\001', "�Ƿ�����ɼ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_app_main.apply_from_type, '\001', "������Դ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_app_main.appno_external, '\001', "������_�ⲿ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_app_main.appno_attach_external, '\001', "����������_�ⲿ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_app_main.remark, '\001', "��ע");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_app_main.create_user, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_app_main.update_user, '\001', "�޸���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_app_main.biz_no, '\001', "ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_app_main.trace_no, '\001', "������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_app_main.called_no, '\001', "��������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_app_main.result_code, '\001', "���������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_app_main.created_datetime, '\001', "����ʱ��");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_app_main.last_modified_datetime, '\001', "����޸�ʱ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_app_main.jpa_version, '\001', "�ֹ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_app_main.is_shared_credit_limit, '\001', "�Ƿ�����");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_app_main.approval_datetime, '\001', "����ͨ��ʱ��");

            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_app_main.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_app_main.is_check_flag));
            
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_APP_MAIN", SD_ICPS_WBC_TM_APP_MAIN, NUMELE(SD_ICPS_WBC_TM_APP_MAIN),
                    &sdb_icps_wbc_tm_app_main, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_app_main.app_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                		fclose(fp_list);
                		fclose(fp_check);
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            fclose(fp_list);
            fclose(fp_check);           
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ������������Ϣ��
 */
int ffunc_parse_wbankcar_file_to_db_tm_app_prim_applicant_info(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO sdb_icps_wbc_tm_app_prim_applicant_info;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fclose(fp_list);
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_app_prim_applicant_info, 0x00, sizeof(sdb_icps_wbc_tm_app_prim_applicant_info));
            pstrcopy(sdb_icps_wbc_tm_app_prim_applicant_info.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_app_prim_applicant_info.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_app_prim_applicant_info.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_app_prim_applicant_info.id, '\001',"��ʶ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_app_prim_applicant_info.org, '\001',"������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_app_prim_applicant_info.app_no, '\001',"��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_app_prim_applicant_info.if_selected_card, '\001',"�Ƿ���ѡ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_app_prim_applicant_info.card_no, '\001',"����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_app_prim_applicant_info.name, '\001',"����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_app_prim_applicant_info.emb_logo, '\001',"͹ӡ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_app_prim_applicant_info.gender, '\001',"�Ա�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_app_prim_applicant_info.nationality, '\001',"����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_app_prim_applicant_info.residency_country_cd, '\001',"���þ�ס�ع��Ҵ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_app_prim_applicant_info.id_type, '\001',"֤������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_app_prim_applicant_info.id_no, '\001',"֤������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_app_prim_applicant_info.id_last_date, '\001',"֤��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_app_prim_applicant_info.id_issuer_address, '\001',"��֤�������ڵ�ַ");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_app_prim_applicant_info.birthday, '\001',"����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_app_prim_applicant_info.liquid_asset, '\001',"�����ʲ�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_app_prim_applicant_info.year_income, '\001',"������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_app_prim_applicant_info.qualification, '\001',"����״��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_app_prim_applicant_info.marital_status, '\001',"����״��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_app_prim_applicant_info.home_addr_ctry_cd, '\001',"��ͥ���Ҵ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_app_prim_applicant_info.home_state, '\001',"��ͥ����ʡ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_app_prim_applicant_info.home_city, '\001',"��ͥ������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_app_prim_applicant_info.home_zone, '\001',"��ͥ��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_app_prim_applicant_info.house_ownership, '\001',"���ݳ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_app_prim_applicant_info.home_add, '\001',"��ͥ��ַ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_app_prim_applicant_info.home_postcode, '\001',"��ͥסլ�ʱ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_app_prim_applicant_info.home_phone, '\001',"��ͥ�绰");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_app_prim_applicant_info.home_stand_from, '\001',"��סַ��ס��ʼ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_app_prim_applicant_info.cellphone, '\001',"�ƶ��绰");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_app_prim_applicant_info.email, '\001',"��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_app_prim_applicant_info.qq_acct, '\001',"QQ�˺�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_app_prim_applicant_info.open_id, '\001',"���ں�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_app_prim_applicant_info.house_type, '\001',"סլ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_app_prim_applicant_info.family_member, '\001',"��ͥ�˿�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_app_prim_applicant_info.family_avge_venue, '\001',"��ͥ�˾�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_app_prim_applicant_info.bankmem_flag, '\001',"�Ƿ�����Ա��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_app_prim_applicant_info.bankmember_no, '\001',"����Ա����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_app_prim_applicant_info.corp_name, '\001',"��˾����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_app_prim_applicant_info.emp_addr_ctry_cd, '\001',"��˾���Ҵ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_app_prim_applicant_info.emp_province, '\001',"��˾����ʡ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_app_prim_applicant_info.emp_city, '\001',"��˾������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_app_prim_applicant_info.emp_zone, '\001',"��˾������/��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_app_prim_applicant_info.emp_add, '\001',"��˾��ַ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_app_prim_applicant_info.emp_postcode, '\001',"��˾�ʱ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_app_prim_applicant_info.emp_phone, '\001',"��˾�绰");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_app_prim_applicant_info.emp_depapment, '\001',"��ְ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_app_prim_applicant_info.emp_post, '\001',"ְ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_app_prim_applicant_info.emp_structure, '\001',"��˾����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_app_prim_applicant_info.emp_type, '\001',"��˾��ҵ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_app_prim_applicant_info.emp_workyears, '\001',"����˾��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_app_prim_applicant_info.corp_fax, '\001',"��˾����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_app_prim_applicant_info.occupation, '\001',"ְҵ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_app_prim_applicant_info.title_of_technical, '\001',"ְ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_app_prim_applicant_info.emp_stand_from, '\001',"�ֵ�λ������ʼ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_app_prim_applicant_info.pos_pin_verify_ind, '\001',"�Ƿ�����ƾ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_app_prim_applicant_info.photo_use_flag, '\001',"�Ƿ���տ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_app_prim_applicant_info.group_num, '\001',"�����Ű���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_app_prim_applicant_info.emp_stability, '\001',"�����ȶ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_app_prim_applicant_info.emp_status, '\001',"�Ƿ���ְ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_app_prim_applicant_info.pr_of_country, '\001',"�Ƿ����þ�ס");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_app_prim_applicant_info.other_ask, '\001',"Ԥ������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_app_prim_applicant_info.other_answer, '\001',"Ԥ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_app_prim_applicant_info.pri_name, '\001',"�Ƽ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_app_prim_applicant_info.pri_card_num, '\001',"�Ƽ��˿���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_app_prim_applicant_info.appno_external, '\001',"������_�ⲿ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_app_prim_applicant_info.bank_customer_id, '\001',"���ڿͻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_app_prim_applicant_info.ref_contact_id, '\001',"�Ƽ�����ϵ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_app_prim_applicant_info.ref_contact_type, '\001',"�Ƽ�����ϵ��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_app_prim_applicant_info.pledeg_type, '\001',"ѺƷ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_app_prim_applicant_info.update_user, '\001',"�޸���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_app_prim_applicant_info.create_user, '\001',"������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_app_prim_applicant_info.created_datetime, '\001',"����ʱ��");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_app_prim_applicant_info.last_modified_datetime, '\001',"����޸�ʱ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_app_prim_applicant_info.jpa_version, '\001',"�ֹ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_app_prim_applicant_info.cust_no, '\001',"�ͻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_app_prim_applicant_info.acct_no, '\001',"�˻���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 77, sdb_icps_wbc_tm_app_prim_applicant_info.product_cd, '\001',"��Ʒ���");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 78, sdb_icps_wbc_tm_app_prim_applicant_info.open_acc_datetime, '\001',"����ʱ��");
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_app_prim_applicant_info.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_app_prim_applicant_info.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO", SD_ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO, NUMELE(SD_ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO),
                    &sdb_icps_wbc_tm_app_prim_applicant_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_app_prim_applicant_info.app_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}



/**
 * �˻���Ϣ��
 */
int ffunc_parse_wbankcar_file_to_db_tm_account(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_ACCOUNT sdb_icps_wbc_tm_account;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_ACCOUNT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fclose(fp_list);
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_account, 0x00, sizeof(sdb_icps_wbc_tm_account));
            pstrcopy(sdb_icps_wbc_tm_account.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_account.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_account.file_order = rcdCnt;

           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_account.org, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_account.acct_no, '\001',"�˻����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_account.acct_type, '\001',"�˻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_account.cust_id, '\001',"�ͻ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_account.cust_limit_id, '\001',"�ͻ����ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_account.product_cd, '\001',"��Ʒ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_account.default_logical_card_no, '\001',"Ĭ���߼�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_account.curr_cd, '\001',"����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_account.credit_limit, '\001',"���ö��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_account.temp_limit, '\001',"��ʱ���");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_account.temp_limit_begin_date, '\001',"��ʱ��ȿ�ʼ����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_account.temp_limit_end_date, '\001',"��ʱ��Ƚ�������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_account.cash_limit_rt, '\001',"ȡ�ֶ�ȱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_account.ovrlmt_rate, '\001',"��Ȩ���ޱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_account.loan_limit_rt, '\001',"����ڷ��ڶ�ȱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_account.curr_bal, '\001',"��ǰ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_account.cash_bal, '\001',"ȡ�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_account.principal_bal, '\001',"�������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_account.loan_bal, '\001',"����ڷ������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_account.dispute_amt, '\001',"������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_account.begin_bal, '\001',"�ڳ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_account.pmt_due_day_bal, '\001',"���ڻ��������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_account.qual_grace_bal, '\001',"ȫ��Ӧ�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_account.grace_days_full_ind, '\001',"�Ƿ���ȫ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_account.point_begin_bal, '\001',"�ڳ��������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_account.ctd_earned_points, '\001',"������������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_account.ctd_disb_points, '\001',"���ڶһ�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_account.ctd_adj_points, '\001',"���ڵ�������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_account.point_bal, '\001',"�������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_account.setup_date, '\001',"��������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_account.dorment_date, '\001',"�˻�˯������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_account.reinstate_date, '\001',"�˻��ָ������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_account.ovrlmt_date, '\001',"��������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_account.ovrlmt_nbr_of_cyc, '\001',"������������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_account.name, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_account.gender, '\001',"�Ա�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_account.owning_branch, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_account.mobile_no, '\001',"�ƶ��绰");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_account.corp_name, '\001',"��˾����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_account.billing_cycle, '\001',"�˵�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_account.stmt_flag, '\001',"�˵���־");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_account.stmt_mail_addr_ind, '\001',"�˵����͵�ַ��־");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_account.stmt_media_type, '\001',"�˵���������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_account.stmt_country_cd, '\001',"�˵���ַ���Ҵ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_account.stmt_state, '\001',"�˵���ַʡ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_account.stmt_city, '\001',"�˵���ַ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_account.stmt_district, '\001',"�˵���ַ������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_account.stmt_address, '\001',"�˵���ַ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_account.stmt_zip, '\001',"�˵���ַ��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_account.email, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_account.block_code, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_account.age_cd, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_account.gl_age_cd, '\001',"��������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_account.unmatch_db, '\001',"δƥ���ǽ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_account.unmatch_cash, '\001',"δƥ��ȡ�ֽ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_account.unmatch_cr, '\001',"δƥ����ǽ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_account.dd_ind, '\001',"Լ����������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_account.dd_bank_name, '\001',"Լ��������������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_account.dd_bank_branch, '\001',"Լ��������к�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_account.dd_bank_acct_no, '\001',"Լ������ۿ��˺�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_account.dd_bank_acct_name, '\001',"Լ������ۿ��˻�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_account.last_dd_amt, '\001',"����Լ��������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_account.last_dd_date, '\001',"����Լ����������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_account.dual_billing_flag, '\001',"������ɿ���ָʾ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_account.last_pmt_amt, '\001',"�ϱʻ�����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_account.last_pmt_date, '\001',"�ϸ���������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_account.last_stmt_date, '\001',"�ϸ��˵�����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_account.last_pmt_due_date, '\001',"�ϸ����ڻ�������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_account.last_aging_date, '\001',"�ϸ�������������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_account.collect_date, '\001',"�������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_account.collect_out_date, '\001',"�����ն�������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_account.next_stmt_date, '\001',"�¸��˵�����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_account.pmt_due_date, '\001',"���ڻ�������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_account.dd_date, '\001',"Լ����������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_account.grace_date, '\001',"��������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_account.dlbl_date, '\001',"���һ��������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 77, sdb_icps_wbc_tm_account.closed_date, '\001',"������������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 78, sdb_icps_wbc_tm_account.first_stmt_date, '\001',"�׸��˵�����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 79, sdb_icps_wbc_tm_account.cancel_date, '\001',"������������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 80, sdb_icps_wbc_tm_account.charge_off_date, '\001',"ת��������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 81, sdb_icps_wbc_tm_account.first_purchase_date, '\001',"�״���������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 82, sdb_icps_wbc_tm_account.first_purchase_amt, '\001',"�״����ѽ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 83, sdb_icps_wbc_tm_account.tot_due_amt, '\001',"��С�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 84, sdb_icps_wbc_tm_account.curr_due_amt, '\001',"������С�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 85, sdb_icps_wbc_tm_account.past_due_amt1, '\001',"�ϸ�����С�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 86, sdb_icps_wbc_tm_account.past_due_amt2, '\001',"��2������С�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wbc_tm_account.past_due_amt3, '\001',"��3������С�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wbc_tm_account.past_due_amt4, '\001',"��4������С�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wbc_tm_account.past_due_amt5, '\001',"��5������С�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 90, sdb_icps_wbc_tm_account.past_due_amt6, '\001',"��6������С�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 91, sdb_icps_wbc_tm_account.past_due_amt7, '\001',"��7������С�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 92, sdb_icps_wbc_tm_account.past_due_amt8, '\001',"��8������С�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 93, sdb_icps_wbc_tm_account.ctd_cash_amt, '\001',"����ȡ�ֽ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 94, sdb_icps_wbc_tm_account.ctd_cash_cnt, '\001',"����ȡ�ֱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 95, sdb_icps_wbc_tm_account.ctd_retail_amt, '\001',"�������ѽ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 96, sdb_icps_wbc_tm_account.ctd_retail_cnt, '\001',"�������ѱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 97, sdb_icps_wbc_tm_account.ctd_payment_amt, '\001',"���ڻ�����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 98, sdb_icps_wbc_tm_account.ctd_payment_cnt, '\001',"���ڻ������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 99, sdb_icps_wbc_tm_account.ctd_db_adj_amt, '\001',"���ڽ�ǵ������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 100, sdb_icps_wbc_tm_account.ctd_db_adj_cnt, '\001',"���ڽ�ǵ�������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 101, sdb_icps_wbc_tm_account.ctd_cr_adj_amt, '\001',"���ڴ��ǵ������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 102, sdb_icps_wbc_tm_account.ctd_cr_adj_cnt, '\001',"���ڴ��ǵ�������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 103, sdb_icps_wbc_tm_account.ctd_fee_amt, '\001',"���ڷ��ý��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 104, sdb_icps_wbc_tm_account.ctd_fee_cnt, '\001',"���ڷ��ñ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 105, sdb_icps_wbc_tm_account.ctd_interest_amt, '\001',"������Ϣ���");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 106, sdb_icps_wbc_tm_account.ctd_interest_cnt, '\001',"������Ϣ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 107, sdb_icps_wbc_tm_account.ctd_refund_amt, '\001',"�����˻����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 108, sdb_icps_wbc_tm_account.ctd_refund_cnt, '\001',"�����˻�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 109, sdb_icps_wbc_tm_account.ctd_hi_ovrlmt_amt, '\001',"������߳��޽��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 110, sdb_icps_wbc_tm_account.mtd_retail_amt, '\001',"�������ѽ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 111, sdb_icps_wbc_tm_account.mtd_retail_cnt, '\001',"�������ѱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 112, sdb_icps_wbc_tm_account.mtd_cash_amt, '\001',"����ȡ�ֽ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 113, sdb_icps_wbc_tm_account.mtd_cash_cnt, '\001',"����ȡ�ֱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 114, sdb_icps_wbc_tm_account.mtd_refund_amt, '\001',"�����˻����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 115, sdb_icps_wbc_tm_account.mtd_refund_cnt, '\001',"�����˻�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 116, sdb_icps_wbc_tm_account.ytd_retail_amt, '\001',"�������ѽ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 117, sdb_icps_wbc_tm_account.ytd_retail_cnt, '\001',"�������ѱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 118, sdb_icps_wbc_tm_account.ytd_cash_amt, '\001',"����ȡ�ֽ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 119, sdb_icps_wbc_tm_account.ytd_cash_cnt, '\001',"����ȡ�ֱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 120, sdb_icps_wbc_tm_account.ytd_refund_amt, '\001',"�����˻����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 121, sdb_icps_wbc_tm_account.ytd_refund_cnt, '\001',"�����˻�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 122, sdb_icps_wbc_tm_account.ytd_ovrlmt_fee_amt, '\001',"���곬�޷���ȡ���");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 123, sdb_icps_wbc_tm_account.ytd_ovrlmt_fee_cnt, '\001',"���곬�޷���ȡ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 124, sdb_icps_wbc_tm_account.ytd_lpc_amt, '\001',"�������ɽ���ȡ���");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 125, sdb_icps_wbc_tm_account.ytd_lpc_cnt, '\001',"�������ɽ���ȡ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 126, sdb_icps_wbc_tm_account.ltd_retail_amt, '\001',"��ʷ���ѽ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 127, sdb_icps_wbc_tm_account.ltd_retail_cnt, '\001',"��ʷ���ѱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 128, sdb_icps_wbc_tm_account.ltd_cash_amt, '\001',"��ʷȡ�ֽ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 129, sdb_icps_wbc_tm_account.ltd_cash_cnt, '\001',"��ʷȡ�ֱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 130, sdb_icps_wbc_tm_account.ltd_refund_amt, '\001',"��ʷ�˻����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 131, sdb_icps_wbc_tm_account.ltd_refund_cnt, '\001',"��ʷ�˻�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 132, sdb_icps_wbc_tm_account.ltd_highest_principal, '\001',"��ʷ��߱���Ƿ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 133, sdb_icps_wbc_tm_account.ltd_highest_cr_bal, '\001',"��ʷ�����ɿ�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 134, sdb_icps_wbc_tm_account.ltd_highest_bal, '\001',"��ʷ������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 135, sdb_icps_wbc_tm_account.collect_times, '\001',"��ߴ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 136, sdb_icps_wbc_tm_account.collect_colr, '\001',"����Ա����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 137, sdb_icps_wbc_tm_account.collect_reason, '\001',"���ԭ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 138, sdb_icps_wbc_tm_account.age_hist, '\001',"������ʷ��Ϣ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 139, sdb_icps_wbc_tm_account.payment_hist, '\001',"������ʷ��Ϣ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 140, sdb_icps_wbc_tm_account.waive_ovlfee_ind, '\001',"�Ƿ�������޷�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 141, sdb_icps_wbc_tm_account.waive_cardfee_ind, '\001',"�Ƿ�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 142, sdb_icps_wbc_tm_account.waive_latefee_ind, '\001',"�Ƿ�������ɽ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 143, sdb_icps_wbc_tm_account.waive_svcfee_ind, '\001',"�Ƿ���������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 144, sdb_icps_wbc_tm_account.user_code1, '\001',"�û��Զ������1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 145, sdb_icps_wbc_tm_account.user_code2, '\001',"�û��Զ������2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 146, sdb_icps_wbc_tm_account.user_code3, '\001',"�û��Զ������3");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 147, sdb_icps_wbc_tm_account.user_code4, '\001',"�û��Զ������4");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 148, sdb_icps_wbc_tm_account.user_code5, '\001',"�û��Զ������5");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 149, sdb_icps_wbc_tm_account.user_code6, '\001',"�û��Զ������6");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 150, sdb_icps_wbc_tm_account.user_date1, '\001',"�û��Զ�������1");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 151, sdb_icps_wbc_tm_account.user_date2, '\001',"�ϴε�������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 152, sdb_icps_wbc_tm_account.user_date3, '\001',"�û��Զ�������3");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 153, sdb_icps_wbc_tm_account.user_date4, '\001',"�û��Զ�������4");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 154, sdb_icps_wbc_tm_account.user_date5, '\001',"�û��Զ�������5");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 155, sdb_icps_wbc_tm_account.user_date6, '\001',"�û��Զ�������6");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 156, sdb_icps_wbc_tm_account.user_number1, '\001',"�û��Զ������1");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 157, sdb_icps_wbc_tm_account.user_number2, '\001',"�û��Զ������2");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 158, sdb_icps_wbc_tm_account.user_number3, '\001',"�û��Զ������3");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 159, sdb_icps_wbc_tm_account.user_number4, '\001',"�û��Զ������4");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 160, sdb_icps_wbc_tm_account.user_number5, '\001',"�û��Զ������5");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 161, sdb_icps_wbc_tm_account.user_number6, '\001',"�û��Զ������6");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 162, sdb_icps_wbc_tm_account.user_field1, '\001',"�û��Զ�����1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 163, sdb_icps_wbc_tm_account.user_field2, '\001',"�û��Զ�����2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 164, sdb_icps_wbc_tm_account.user_field3, '\001',"�û��Զ�����3");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 165, sdb_icps_wbc_tm_account.user_field4, '\001',"�û��Զ�����4");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 166, sdb_icps_wbc_tm_account.user_field5, '\001',"�û��Զ�����5");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 167, sdb_icps_wbc_tm_account.user_field6, '\001',"�û��Զ�����6");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 168, sdb_icps_wbc_tm_account.user_amt1, '\001',"�û��Զ�����1");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 169, sdb_icps_wbc_tm_account.user_amt2, '\001',"�û��Զ�����2");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 170, sdb_icps_wbc_tm_account.user_amt3, '\001',"�û��Զ�����3");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 171, sdb_icps_wbc_tm_account.user_amt4, '\001',"�û��Զ�����4");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 172, sdb_icps_wbc_tm_account.user_amt5, '\001',"�û��Զ�����5");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 173, sdb_icps_wbc_tm_account.user_amt6, '\001',"���մ��ǿ���ŵ���");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 174, sdb_icps_wbc_tm_account.jpa_version, '\001',"�ֹ����汾��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 175, sdb_icps_wbc_tm_account.mtd_payment_amt, '\001',"���»�����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 176, sdb_icps_wbc_tm_account.mtd_payment_cnt, '\001',"���»������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 177, sdb_icps_wbc_tm_account.ytd_payment_amt, '\001',"���껹����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 178, sdb_icps_wbc_tm_account.ytd_payment_cnt, '\001',"���껹�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 179, sdb_icps_wbc_tm_account.ltd_payment_amt, '\001',"��ʷ������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 180, sdb_icps_wbc_tm_account.ltd_payment_cnt, '\001',"��ʷ�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 181, sdb_icps_wbc_tm_account.sms_ind, '\001',"���ŷ��ͱ�ʶ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 182, sdb_icps_wbc_tm_account.user_sms_amt, '\001',"���Ի����˶��ŷ�����ֵ");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 183, sdb_icps_wbc_tm_account.ytd_cycle_chag_cnt, '\001',"������˵����޸Ĵ���");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 184, sdb_icps_wbc_tm_account.last_post_date, '\001',"�ϸ���������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 185, sdb_icps_wbc_tm_account.last_modified_datetime, '\001',"�޸�ʱ��");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 186, sdb_icps_wbc_tm_account.lock_date, '\001',"�Զ�������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 187, sdb_icps_wbc_tm_account.last_sync_date, '\001',"��һ�����˵���������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 188, sdb_icps_wbc_tm_account.created_datetime, '\001',"����ʱ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 189, sdb_icps_wbc_tm_account.delay_bal, '\001',"�˻����ڽ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 190, sdb_icps_wbc_tm_account.bank_group_id, '\001',"���ű��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 191, sdb_icps_wbc_tm_account.customer_type, '\001',"��Ⱥ����");


            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_account.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_account.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_ACCOUNT", SD_ICPS_WBC_TM_ACCOUNT, NUMELE(SD_ICPS_WBC_TM_ACCOUNT),
                    &sdb_icps_wbc_tm_account, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tm_account.acct_no), "ERROR");
                fclose(fp_list);
                fclose(fp_check);
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                		fclose(fp_list);
                		fclose(fp_check);
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
        		fclose(fp_list);
        		fclose(fp_check);
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}


/**
 * �ͻ���Ϣ��
 */
int ffunc_parse_wbankcar_file_to_db_tm_customer(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_CUSTOMER sdb_icps_wbc_tm_customer;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_CUSTOMER WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        fclose(fp_list);
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_customer, 0x00, sizeof(sdb_icps_wbc_tm_customer));
            pstrcopy(sdb_icps_wbc_tm_customer.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_customer.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_customer.file_order = rcdCnt;
            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_customer.org, '\001',"������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_customer.cust_id, '\001',"�ͻ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_customer.id_no, '\001',"֤������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_customer.id_type, '\001',"֤������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_customer.title, '\001',"��ν");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_customer.name, '\001',"����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_customer.gender, '\001',"�Ա�");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_customer.birthday, '\001',"����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_customer.occupation, '\001',"ְҵ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_customer.bankmember_no, '\001',"����Ա����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_customer.nationality, '\001',"����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_customer.pr_of_country, '\001',"�Ƿ����þ�ס");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_customer.residency_country_cd, '\001',"���þ�ס�ع��Ҵ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_customer.marital_status, '\001',"����״��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_customer.qualification, '\001',"����״��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_customer.social_status, '\001',"�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_customer.id_issuer_address, '\001',"��֤�������ڵ�ַ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_customer.home_phone, '\001',"��ͥ�绰");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_customer.house_ownership, '\001',"���ݳ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_customer.house_type, '\001',"סլ����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_customer.home_stand_from, '\001',"��סַ��ס��ʼ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_customer.liquid_asset, '\001',"�����ʲ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_customer.mobile_no, '\001',"�ƶ��绰");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_customer.email, '\001',"��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_customer.emp_status, '\001',"��ҵ״̬");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_customer.nbr_of_dependents, '\001',"��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_customer.language_ind, '\001',"���Դ���");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_customer.setup_date, '\001',"��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_customer.social_ins_amt, '\001',"�籣�ɴ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_customer.drive_license_id, '\001',"��ʻ֤����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_customer.drive_lic_reg_date, '\001',"��ʻ֤�Ǽ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_customer.obligate_question, '\001',"Ԥ������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_customer.obligate_answer, '\001',"Ԥ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_customer.emp_stability, '\001',"�����ȶ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_customer.corp_name, '\001',"��˾����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_customer.user_code1, '\001',"�û��Զ������1");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_customer.user_code2, '\001',"�û��Զ������2");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_customer.user_code3, '\001',"�û��Զ������3");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_customer.user_code4, '\001',"�û��Զ������4");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_customer.user_code5, '\001',"�û��Զ������5");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_customer.user_code6, '\001',"�û��Զ������6");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_customer.user_date1, '\001',"�û��Զ�������1");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_customer.user_date2, '\001',"�û��Զ�������2");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_customer.user_date3, '\001',"�û��Զ�������3");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_customer.user_date4, '\001',"�û��Զ�������4");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_customer.user_date5, '\001',"�û��Զ�������5");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_customer.user_date6, '\001',"�û��Զ�������6");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_customer.user_number1, '\001',"�û��Զ������1");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_customer.user_number2, '\001',"�û��Զ������2");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_customer.user_number3, '\001',"�û��Զ������3");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_customer.user_number4, '\001',"�û��Զ������4");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_customer.user_number5, '\001',"�û��Զ������5");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_customer.user_number6, '\001',"�û��Զ������6");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_customer.user_field1, '\001',"�û��Զ�����1");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_customer.user_field2, '\001',"�û��Զ�����2");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_customer.user_field3, '\001',"�û��Զ�����3");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_customer.user_field4, '\001',"�û��Զ�����4");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_customer.user_field5, '\001',"�û��Զ�����5");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_customer.user_field6, '\001',"�û��Զ�����6");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_customer.user_amt1, '\001',"�û��Զ�����1");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_customer.user_amt2, '\001',"�û��Զ�����2");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_customer.user_amt3, '\001',"�û��Զ�����3");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_customer.user_amt4, '\001',"�û��Զ�����4");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_customer.user_amt5, '\001',"�û��Զ�����5");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_customer.user_amt6, '\001',"���մ��ǿ���ŵ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_customer.bank_customer_id, '\001',"����ͳһ�û���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_customer.emb_name, '\001',"͹ӡ����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_customer.jpa_version, '\001',"�ֹ����汾��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_customer.cust_limit_id, '\001',"�ͻ����ID");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_customer.last_modified_datetime, '\001',"�޸�ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_customer.cust_level, '\001',"�ͻ��ȼ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_customer.pledeg_type, '\001',"ѺƷ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_customer.surname, '\001',"����");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_customer.created_datetime, '\001',"����ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_customer.customer_type, '\001',"��Ⱥ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_customer.block_code, '\001',"������");


            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_customer.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_customer.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_CUSTOMER", SD_ICPS_WBC_TM_CUSTOMER, NUMELE(SD_ICPS_WBC_TM_CUSTOMER),
                    &sdb_icps_wbc_tm_customer, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tm_customer.cust_id), "ERROR");
                fclose(fp_list);
                fclose(fp_check);
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                		fclose(fp_list);
                		fclose(fp_check);
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
        		fclose(fp_list);
        		fclose(fp_check);
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
} 


/**
 * ���üƻ���
 */
int ffunc_parse_wbankcar_file_to_db_tm_plan(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_PLAN sdb_icps_wbc_tm_plan;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_PLAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_plan, 0x00, sizeof(sdb_icps_wbc_tm_plan));
            pstrcopy(sdb_icps_wbc_tm_plan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_plan.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_plan.file_order = rcdCnt;    
            
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_plan.org, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_plan.plan_id, '\001',"���üƻ�ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_plan.acct_no, '\001',"�˻����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_plan.acct_type, '\001',"�˻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_plan.logical_card_no, '\001',"�߼�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_plan.plan_nbr, '\001',"���üƻ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_plan.plan_type, '\001',"���üƻ�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_plan.product_cd, '\001',"��Ʒ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_plan.ref_nbr, '\001',"���ײο���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_plan.curr_bal, '\001',"��ǰ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_plan.begin_bal, '\001',"�ڳ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_plan.dispute_amt, '\001',"������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_plan.tot_due_amt, '\001',"��С�����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_plan.plan_add_date, '\001',"���üƻ���������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_plan.paid_out_date, '\001',"��������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_plan.past_principal, '\001',"�ѳ��˵�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_plan.past_interest, '\001',"�ѳ��˵���Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_plan.past_card_fee, '\001',"�ѳ��˵����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_plan.past_ovrlmt_fee, '\001',"�ѳ��˵����޷�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_plan.past_lpc, '\001',"�ѳ��˵����ɽ�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_plan.past_nsf_fee, '\001',"�ѳ��˵��ʽ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_plan.past_txn_fee, '\001',"�ѳ��˵����׷�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_plan.past_svc_fee, '\001',"�ѳ��˵������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_plan.past_ins, '\001',"�ѳ��˵����ս��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_plan.past_user_fee1, '\001',"�ѳ��˵��Զ������1");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_plan.past_user_fee2, '\001',"�ѳ��˵��Զ������2");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_plan.past_user_fee3, '\001',"�ѳ��˵��Զ������3");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_plan.past_user_fee4, '\001',"�ѳ��˵��Զ������4");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_plan.past_user_fee5, '\001',"�ѳ��˵��Զ������5");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_plan.past_user_fee6, '\001',"�ѳ��˵��Զ������6");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_plan.ctd_principal, '\001',"���ڱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_plan.ctd_interest, '\001',"������Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_plan.ctd_card_fee, '\001',"�������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_plan.ctd_ovrlmt_fee, '\001',"���ڳ��޷�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_plan.ctd_lpc, '\001',"�������ɽ�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_plan.ctd_nsf_fee, '\001',"�����ʽ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_plan.ctd_svc_fee, '\001',"���ڷ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_plan.ctd_txn_fee, '\001',"���ڽ��׷�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_plan.ctd_ins, '\001',"���ڱ��ս��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_plan.ctd_user_fee1, '\001',"���������Զ������1");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_plan.ctd_user_fee2, '\001',"���������Զ������2");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_plan.ctd_user_fee3, '\001',"���������Զ������3");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_plan.ctd_user_fee4, '\001',"���������Զ������4");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_plan.ctd_user_fee5, '\001',"���������Զ������5");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_plan.ctd_user_fee6, '\001',"���������Զ������6");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_plan.ctd_amt_db, '\001',"���ڽ�ǽ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_plan.ctd_amt_cr, '\001',"���ڴ��ǽ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_plan.ctd_nbr_db, '\001',"���ڽ�ǽ��ױ���");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_plan.ctd_nbr_cr, '\001',"���ڴ��ǽ��ױ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_plan.nodefbnp_int_acru, '\001',"���ӳ���Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_plan.beg_defbnp_int_acru, '\001',"�����ۻ���ʱ��Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_plan.ctd_defbnp_int_acru, '\001',"�����ۻ���ʱ��Ϣ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_plan.user_code1, '\001',"�û��Զ������1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_plan.user_code2, '\001',"�û��Զ������2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_plan.user_code3, '\001',"�û��Զ������3");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_plan.user_code4, '\001',"�û��Զ������4");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_plan.user_code5, '\001',"�û��Զ������5");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_plan.user_code6, '\001',"�û��Զ������6");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_plan.user_number1, '\001',"�û��Զ������1");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_plan.user_number2, '\001',"�û��Զ������2");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_plan.user_number3, '\001',"�û��Զ������3");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_plan.user_number4, '\001',"�û��Զ������4");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_plan.user_number5, '\001',"�û��Զ������5");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_plan.user_number6, '\001',"�û��Զ������6");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_plan.user_field1, '\001',"�û��Զ�����1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_plan.user_field2, '\001',"�û��Զ�����2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_plan.user_field3, '\001',"�û��Զ�����3");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_plan.user_field4, '\001',"�û��Զ�����4");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_plan.user_field5, '\001',"�û��Զ�����5");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_plan.user_field6, '\001',"�û��Զ�����6");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_plan.user_date1, '\001',"�û��Զ�������1");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_plan.user_date2, '\001',"�û��Զ�������2");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_plan.user_date3, '\001',"�û��Զ�������3");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_plan.user_date4, '\001',"�û��Զ�������4");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_plan.user_date5, '\001',"�û��Զ�������5");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_plan.user_date6, '\001',"�û��Զ�������6");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 77, sdb_icps_wbc_tm_plan.user_amt1, '\001',"�û��Զ�����1");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 78, sdb_icps_wbc_tm_plan.user_amt2, '\001',"�û��Զ�����2");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 79, sdb_icps_wbc_tm_plan.user_amt3, '\001',"�û��Զ�����3");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 80, sdb_icps_wbc_tm_plan.user_amt4, '\001',"�û��Զ�����4");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 81, sdb_icps_wbc_tm_plan.user_amt5, '\001',"�û��Զ�����5");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 82, sdb_icps_wbc_tm_plan.user_amt6, '\001',"���մ��ǿ���ŵ���");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 83, sdb_icps_wbc_tm_plan.jpa_version, '\001',"�ֹ����汾��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 84, sdb_icps_wbc_tm_plan.past_penalty, '\001',"���ڷ�Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 85, sdb_icps_wbc_tm_plan.ctd_penalty, '\001',"���ڷ�Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 86, sdb_icps_wbc_tm_plan.past_compound, '\001',"���ڸ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wbc_tm_plan.ctd_compound, '\001',"���ڸ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wbc_tm_plan.penalty_acru, '\001',"��Ϣ�ۼ�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wbc_tm_plan.compound_acru, '\001',"�����ۼ�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 90, sdb_icps_wbc_tm_plan.interest_rate, '\001',"��������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 91, sdb_icps_wbc_tm_plan.penalty_rate, '\001',"��Ϣ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 92, sdb_icps_wbc_tm_plan.compound_rate, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 93, sdb_icps_wbc_tm_plan.use_plan_rate, '\001',"�Ƿ�ʹ��plan������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 94, sdb_icps_wbc_tm_plan.last_pmt_date, '\001',"��һ��������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 95, sdb_icps_wbc_tm_plan.term, '\001',"���ڷ�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 96, sdb_icps_wbc_tm_plan.calc_type, '\001',"�Ʒ�����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 97, sdb_icps_wbc_tm_plan.calc_cycle, '\001',"�Ʒ�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 98, sdb_icps_wbc_tm_plan.fee_rate, '\001',"����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 99, sdb_icps_wbc_tm_plan.last_fee_date, '\001',"��һ�շ���");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 100, sdb_icps_wbc_tm_plan.next_fee_date, '\001',"��һ�շ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 101, sdb_icps_wbc_tm_plan.txn_seq, '\001',"������ˮ��");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 102, sdb_icps_wbc_tm_plan.first_dd_date, '\001',"�״�Լ����������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 103, sdb_icps_wbc_tm_plan.consumer_trans_id, '\001',"ҵ����ˮ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 104, sdb_icps_wbc_tm_plan.sys_trans_id, '\001',"ϵͳ������ˮ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 105, sdb_icps_wbc_tm_plan.qchannel_id, '\001',"�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 106, sdb_icps_wbc_tm_plan.sub_terminal_type, '\001',"�ն�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 107, sdb_icps_wbc_tm_plan.sub_merch_id, '\001',"�����̻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 108, sdb_icps_wbc_tm_plan.sub_merch_name, '\001',"�����̻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 109, sdb_icps_wbc_tm_plan.wares_desc, '\001',"��Ʒ��Ϣ");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 110, sdb_icps_wbc_tm_plan.last_modified_datetime, '\001',"�޸�ʱ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 111, sdb_icps_wbc_tm_plan.original_amt, '\001',"ԭʼ���ױ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 112, sdb_icps_wbc_tm_plan.interest_calc_base, '\001',"��Ϣ����");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 113, sdb_icps_wbc_tm_plan.created_datetime, '\001',"����ʱ��");

            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_plan.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_plan.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_PLAN", SD_ICPS_WBC_TM_PLAN, NUMELE(SD_ICPS_WBC_TM_PLAN),
                    &sdb_icps_wbc_tm_plan, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tm_plan.acct_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                		fclose(fp_list);
                		fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
} 

/**
 * �������˽��ױ�
 */
int ffunc_parse_wbankcar_file_to_db_tt_txn_post(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TT_TXN_POST sdb_icps_wbc_tt_txn_post;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TT_TXN_POST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tt_txn_post, 0x00, sizeof(sdb_icps_wbc_tt_txn_post));
            pstrcopy(sdb_icps_wbc_tt_txn_post.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tt_txn_post.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tt_txn_post.file_order = rcdCnt;  
            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tt_txn_post.org, '\001',"������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tt_txn_post.txn_seq, '\001',"������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tt_txn_post.acct_no, '\001',"�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tt_txn_post.acct_type, '\001',"�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tt_txn_post.card_no, '\001',"����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tt_txn_post.logical_card_no, '\001',"�߼�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tt_txn_post.bsc_logiccard_no, '\001',"�߼�����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tt_txn_post.product_cd, '\001',"��Ʒ����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tt_txn_post.txn_date, '\001',"��������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tt_txn_post.txn_time, '\001',"����ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tt_txn_post.post_txn_type, '\001',"���˽�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tt_txn_post.txn_code, '\001',"������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tt_txn_post.db_cr_ind, '\001',"�����־");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tt_txn_post.txn_amt, '\001',"���׽��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tt_txn_post.post_amt, '\001',"���˱��ֽ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tt_txn_post.post_date, '\001',"��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tt_txn_post.auth_code, '\001',"��Ȩ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tt_txn_post.card_block_code, '\001',"��Ƭ������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tt_txn_post.txn_curr_cd, '\001',"���ױ��ִ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tt_txn_post.post_curr_cd, '\001',"���˱��ִ���");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tt_txn_post.orig_trans_date, '\001',"ԭʼ��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tt_txn_post.plan_nbr, '\001',"���üƻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tt_txn_post.ref_nbr, '\001',"���ײο���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tt_txn_post.txn_desc, '\001',"��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tt_txn_post.txn_short_desc, '\001',"�˵���������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tt_txn_post.point, '\001',"������ֵ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tt_txn_post.posting_flag, '\001',"���˽����ʾ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tt_txn_post.pre_posting_flag, '\001',"�������˽����ʾ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tt_txn_post.rel_pmt_amt, '\001',"��˾��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tt_txn_post.orig_pmt_amt, '\001',"�����ԭʼ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tt_txn_post.acq_branch_id, '\001',"������д���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tt_txn_post.acq_terminal_id, '\001',"��������ն˱�ʶ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tt_txn_post.acq_acceptor_id, '\001',"�ܿ�����ʶ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tt_txn_post.acq_name_addr, '\001',"����������Ƶ�ַ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tt_txn_post.mcc, '\001',"�̻�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tt_txn_post.input_txn_code, '\001',"ԭ���׽�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tt_txn_post.input_txn_amt, '\001',"ԭ���׽��׽��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tt_txn_post.input_sett_amt, '\001',"ԭ����������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tt_txn_post.interchange_fee, '\001',"ԭ���׻���ת����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tt_txn_post.fee_payout, '\001',"������Ӧ��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tt_txn_post.fee_profit, '\001',"������Ӧ��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tt_txn_post.loan_issue_profit, '\001',"���ڽ��׷���������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tt_txn_post.stmt_date, '\001',"�˵�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tt_txn_post.voucher_no, '\001',"���۵�ƾ֤��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tt_txn_post.jpa_version, '\001',"�ֹ����汾��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tt_txn_post.term, '\001',"���ڷ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tt_txn_post.consumer_trans_id, '\001',"ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tt_txn_post.sys_trans_id, '\001',"ϵͳ������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tt_txn_post.qchannel_id, '\001',"�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tt_txn_post.sub_terminal_type, '\001',"�ն�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tt_txn_post.sub_merch_id, '\001',"�����̻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tt_txn_post.sub_merch_name, '\001',"�����̻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tt_txn_post.wares_desc, '\001',"��Ʒ��Ϣ");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tt_txn_post.last_modified_datetime, '\001',"�޸�ʱ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tt_txn_post.paid_stmt_date, '\001',"�����˵���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tt_txn_post.repay_amt, '\001',"Ӧ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tt_txn_post.counter_acct, '\001',"���ַ��˻�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tt_txn_post.counter_name, '\001',"���ַ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tt_txn_post.counter_brno, '\001',"���ַ��к�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tt_txn_post.counter_brname, '\001',"���ַ�����");

            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tt_txn_post.is_check_flag, "1", sizeof(sdb_icps_wbc_tt_txn_post.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TT_TXN_POST", SD_ICPS_WBC_TT_TXN_POST, NUMELE(SD_ICPS_WBC_TT_TXN_POST),
                    &sdb_icps_wbc_tt_txn_post, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tt_txn_post.txn_seq), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                		fclose(fp_list);
                		fclose(fp_check);
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
          	fclose(fp_list);
            fclose(fp_check);
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
} 

/**
 * ������Ϣ��
 */
int ffunc_parse_wbankcar_file_to_db_tm_loan(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_LOAN sdb_icps_wbc_tm_loan;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_LOAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_loan, 0x00, sizeof(sdb_icps_wbc_tm_loan));
            pstrcopy(sdb_icps_wbc_tm_loan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_loan.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_loan.file_order = rcdCnt;
              
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_loan.org, '\001',"������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_loan.loan_id, '\001',"���ڼƻ�ID");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_loan.acct_no, '\001',"�˻����");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_loan.acct_type, '\001',"�˻�����");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_loan.ref_nbr, '\001',"���ײο���");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_loan.logical_card_no, '\001',"�߼�����");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_loan.card_no, '\001',"����");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_loan.register_date, '\001',"����ע������");
          ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_loan.request_time, '\001',"��������ʱ��");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_loan.loan_type, '\001',"��������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_loan.loan_status, '\001',"����״̬");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_loan.last_loan_status, '\001',"�����ϴ�״̬");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_loan.loan_init_term, '\001',"����������");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_loan.curr_term, '\001',"��ǰ����");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_loan.remain_term, '\001',"ʣ������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_loan.loan_init_prin, '\001',"�����ܱ���");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_loan.loan_fixed_pmt_prin, '\001',"����ÿ��Ӧ������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_loan.loan_first_term_prin, '\001',"��������Ӧ������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_loan.loan_final_term_prin, '\001',"����ĩ��Ӧ������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_loan.loan_init_fee1, '\001',"������������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_loan.loan_fixed_fee1, '\001',"����ÿ��������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_loan.loan_first_term_fee1, '\001',"��������������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_loan.loan_final_term_fee1, '\001',"����ĩ��������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_loan.unearned_prin, '\001',"δ���˵��ı���");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_loan.unearned_fee1, '\001',"δ���˵�������");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_loan.paid_out_date, '\001',"��������");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_loan.terminate_date, '\001',"��ǰ��ֹ����");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_loan.terminate_reason_cd, '\001',"������ֹԭ�����");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_loan.prin_paid, '\001',"�ѳ�������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_loan.int_paid, '\001',"�ѳ�����Ϣ");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_loan.fee_paid, '\001',"�ѳ�������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_loan.loan_curr_bal, '\001',"���ڵ�ǰ�����");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_loan.loan_bal_xfrout, '\001',"����δ�������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_loan.loan_bal_xfrin, '\001',"�����ѳ��˵����");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_loan.loan_bal_principal, '\001',"Ƿ���ܱ���");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_loan.loan_bal_interest, '\001',"Ƿ������Ϣ");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_loan.loan_bal_penalty, '\001',"Ƿ���ܷ�Ϣ");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_loan.loan_prin_xfrout, '\001',"����δ���ڱ���");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_loan.loan_prin_xfrin, '\001',"�����ѳ��˵�����");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_loan.loan_fee1_xfrout, '\001',"����δ����������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_loan.loan_fee1_xfrin, '\001',"�����ѳ��˵�������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_loan.orig_txn_amt, '\001',"ԭʼ���ױ��ֽ��");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_loan.orig_trans_date, '\001',"ԭʼ��������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_loan.orig_auth_code, '\001',"ԭʼ������Ȩ��");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_loan.jpa_version, '\001',"�ֹ����汾��");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_loan.loan_code, '\001',"���ڼƻ�����");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_loan.register_id, '\001',"��������˳���");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_loan.resch_init_prin, '\001',"չ�ڱ�����");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_loan.resch_date, '\001',"չ����Ч����");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_loan.bef_resch_fixed_pmt_prin, '\001',"չ��ǰÿ��Ӧ������");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_loan.bef_resch_init_term, '\001',"չ��ǰ������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_loan.bef_resch_first_term_prin, '\001',"չ��ǰ��������Ӧ������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_loan.bef_resch_final_term_prin, '\001',"չ��ǰ����ĩ��Ӧ������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_loan.bef_resch_init_fee1, '\001',"չ��ǰ������������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_loan.bef_resch_fixed_fee1, '\001',"����ÿ��������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_loan.bef_resch_first_term_fee1, '\001',"չ��ǰ��������������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_loan.bef_resch_final_term_fee1, '\001',"չ��ǰ����ĩ��������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_loan.resch_first_term_fee1, '\001',"չ�ں�����������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_loan.loan_fee_method, '\001',"������������ȡ��ʽ");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_loan.interest_rate, '\001',"��������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_loan.penalty_rate, '\001',"��Ϣ����");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_loan.compound_rate, '\001',"��������");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_loan.float_rate, '\001',"��������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_loan.loan_receipt_nbr, '\001',"��ݺ�");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_loan.loan_expire_date, '\001',"���������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_loan.loan_cd, '\001',"���������������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_loan.payment_hist, '\001',"24���»���״̬");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_loan.ctd_payment_amt, '\001',"���ڻ����");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_loan.past_resch_cnt, '\001',"��չ�ڴ���");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_loan.past_shorted_cnt, '\001',"�����ڴ���");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_loan.adv_pmt_amt, '\001',"��ǰ������");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_loan.last_action_date, '\001',"�ϴ��ж�����");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_loan.last_action_type, '\001',"�ϴ��ж�����");
          ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_loan.last_modified_datetime, '\001',"�޸�ʱ��");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_loan.activate_date, '\001',"��������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_loan.interest_calc_base, '\001',"��Ϣ����");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 77, sdb_icps_wbc_tm_loan.first_bill_date, '\001',"�׸��˵���");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 78, sdb_icps_wbc_tm_loan.age_cd, '\001',"����");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 79, sdb_icps_wbc_tm_loan.recalc_ind, '\001',"���������־");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 80, sdb_icps_wbc_tm_loan.recalc_date, '\001',"����������");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 81, sdb_icps_wbc_tm_loan.grace_date, '\001',"��������");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 82, sdb_icps_wbc_tm_loan.cancel_date, '\001',"��������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 83, sdb_icps_wbc_tm_loan.cancel_reason, '\001',"�����ԭ��");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 84, sdb_icps_wbc_tm_loan.bank_group_id, '\001',"���ű��");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 85, sdb_icps_wbc_tm_loan.due_days, '\001',"��ǰ��������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 86, sdb_icps_wbc_tm_loan.contract_ver, '\001',"��ͬ�汾��");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wbc_tm_loan.loan_init_interest, '\001',"��������Ϣ");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wbc_tm_loan.bef_init_interest, '\001',"ԭ��������Ϣ");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wbc_tm_loan.penalty_paid , '\001',"�ѻ���Ϣ");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 90, sdb_icps_wbc_tm_loan.compound_paid, '\001',"�ѻ�����");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 91, sdb_icps_wbc_tm_loan.late_charge_paid, '\001',"�ѻ����ɽ�");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 92, sdb_icps_wbc_tm_loan.loan_bal_late_charge, '\001',"Ƿ�������ɽ�");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 93, sdb_icps_wbc_tm_loan.next_xfr_date, '\001',"��һ��ת��");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 94, sdb_icps_wbc_tm_loan.next_late_charge_date, '\001',"��һ���ɽ���ȡ��");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 95, sdb_icps_wbc_tm_loan.fee_rate, '\001',"����");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 96, sdb_icps_wbc_tm_loan.late_charge_fee_rate, '\001',"���ɽ����");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 97, sdb_icps_wbc_tm_loan.adv_pmt_fee_rate, '\001',"��ǰ���������ѷ���");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 98, sdb_icps_wbc_tm_loan.loan_bal_adv_pmt_fee, '\001',"��ǰ������������Ƿ��");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 99, sdb_icps_wbc_tm_loan.adv_pmt_fee_paid, '\001',"�ѻ���ǰ����������");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 100, sdb_icps_wbc_tm_loan.last_xfr_date, '\001',"��һ��ת����");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 101, sdb_icps_wbc_tm_loan.loan_bal_fee, '\001',"Ƿ���ܷ���");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 102, sdb_icps_wbc_tm_loan.payee_card_no, '\001',"�տ��");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 103, sdb_icps_wbc_tm_loan.payee_bank_name, '\001',"�տ�������");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 104, sdb_icps_wbc_tm_loan.billing_cycle, '\001',"�˵���");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 105, sdb_icps_wbc_tm_loan.last_stmt_date, '\001',"�ϸ��˵�����");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 106, sdb_icps_wbc_tm_loan.next_stmt_date, '\001',"�¸��˵�����");

            

            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_loan.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_loan.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_LOAN", SD_ICPS_WBC_TM_LOAN, NUMELE(SD_ICPS_WBC_TM_LOAN),
                    &sdb_icps_wbc_tm_loan, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tm_loan.loan_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
} 


/**
 * ��������
 */
int ffunc_parse_wbankcar_file_to_db_tm_schedule(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_SCHEDULE sdb_icps_wbc_tm_schedule;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_SCHEDULE WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_schedule, 0x00, sizeof(sdb_icps_wbc_tm_schedule));
            pstrcopy(sdb_icps_wbc_tm_schedule.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_schedule.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_schedule.file_order = rcdCnt;
            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_schedule.schedule_id, '\001',"�����ID");                 
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_schedule.loan_id, '\001',"���ڼƻ�ID");                   
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_schedule.org, '\001',"������");                            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_schedule.acct_no, '\001',"�˻����");                     
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_schedule.acct_type, '\001',"�˻�����");                    
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_schedule.logical_card_no, '\001',"�߼�����");              
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_schedule.card_no, '\001',"����");                          
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_schedule.loan_init_prin, '\001',"�����ܱ���");             
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_schedule.loan_init_term, '\001',"����������");            
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_schedule.curr_term, '\001',"��ǰ����");                  
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_schedule.loan_term_prin, '\001',"Ӧ������");              
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_schedule.loan_term_fee1, '\001',"Ӧ������");              
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_schedule.loan_term_interest, '\001',"Ӧ����Ϣ");          
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_schedule.loan_pmt_due_date, '\001',"����ڻ�������");     
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_schedule.loan_grace_date, '\001',"������");                 
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_schedule.last_modified_datetime, '\001',"�޸�ʱ��");   
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_schedule.start_date, '\001',"��Ϣ��");                      
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_schedule.schedule_action, '\001',"����ƻ���������");     
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_schedule.prin_paid, '\001',"�ѳ�������");                 
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_schedule.int_paid, '\001',"�ѳ�����Ϣ");                  
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_schedule.penalty_paid, '\001',"�ѳ�����Ϣ");              
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_schedule.compound_paid, '\001',"�ѳ�������");             
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_schedule.fee_paid, '\001',"�ѳ�������");                  
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_schedule.late_charge_paid, '\001',"�ѳ������ɽ�");        
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_schedule.adv_pmt_fee_paid, '\001',"�ѳ�����ǰ����������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_schedule.paid_out_date, '\001',"��������");                 

            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_schedule.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_schedule.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_SCHEDULE", SD_ICPS_WBC_TM_SCHEDULE, NUMELE(SD_ICPS_WBC_TM_SCHEDULE),
                    &sdb_icps_wbc_tm_schedule, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tm_schedule.schedule_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_check);
            fclose(fp_list);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
} 

/**
 * �Զ�������Ϣ��-��Ȩ
 */
int ffunc_parse_wbankcar_file_to_db_tm_cust_limit_o(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_CUST_LIMIT_O sdb_icps_wbc_tm_cust_limit_o;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_CUST_LIMIT_O WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_cust_limit_o, 0x00, sizeof(sdb_icps_wbc_tm_cust_limit_o));
            pstrcopy(sdb_icps_wbc_tm_cust_limit_o.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_cust_limit_o.busi_date)); /*ҵ������*/           
            sdb_icps_wbc_tm_cust_limit_o.file_order = rcdCnt;
            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_cust_limit_o.org, '\001',"������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_cust_limit_o.cust_limit_id, '\001',"�ͻ����ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_cust_limit_o.limit_category, '\001',"�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_cust_limit_o.limit_type, '\001',"�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_cust_limit_o.credit_limit, '\001',"���ö��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_cust_limit_o.jpa_version, '\001',"�ֹ����汾��");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_cust_limit_o.last_modified_datetime, '\001',"�޸�ʱ��");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_cust_limit_o.created_datetime, '\001',"����ʱ��");

       
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_cust_limit_o.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_cust_limit_o.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_CUST_LIMIT_O", SD_ICPS_WBC_TM_CUST_LIMIT_O, NUMELE(SD_ICPS_WBC_TM_CUST_LIMIT_O),
                    &sdb_icps_wbc_tm_cust_limit_o, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tm_cust_limit_o.cust_limit_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
} 
/*
*��Ȩ������ʷ
*/
int ffunc_parse_wbankcar_file_to_db_tm_auth_hst(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_AUTH_HST sdb_icps_wbc_tm_auth_hst;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_AUTH_HST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_auth_hst, 0x00, sizeof(sdb_icps_wbc_tm_auth_hst));
            pstrcopy(sdb_icps_wbc_tm_auth_hst.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_auth_hst.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_auth_hst.file_order = rcdCnt;   
            
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_auth_hst.org, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_auth_hst.log_kv, '\001',"LOG�ļ�ֵ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_auth_hst.acct_no, '\001',"�˻����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_auth_hst.acct_type, '\001',"�˻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_auth_hst.logical_card_no, '\001',"�߼�����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_auth_hst.acq_ref_no, '\001',"����������ױ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_auth_hst.txn_amt, '\001',"���׽��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_auth_hst.txn_curr_cd, '\001',"���ױ��ִ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_auth_hst.auth_code, '\001',"��Ȩ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_auth_hst.acq_name_addr, '\001',"����������Ƶ�ַ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_auth_hst.chb_txn_amt, '\001',"�ֿ����˻����ֽ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_auth_hst.chb_curr_cd, '\001',"�ֿ����˻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_auth_hst.channel, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_auth_hst.mcc, '\001',"�̻�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_auth_hst.acq_branch_id, '\001',"������д���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_auth_hst.fwd_inst_id, '\001',"ת��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_auth_hst.transmission_timestamp, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_auth_hst.settle_date, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_auth_hst.txn_direction, '\001',"���׷���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_auth_hst.txn_terminal, '\001',"�����ն�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_auth_hst.txn_status, '\001',"����״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_auth_hst.txn_type, '\001',"��������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_auth_hst.log_ol_time, '\001',"LOG����ʱ��");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_auth_hst.log_biz_date, '\001',"����ҵ������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_auth_hst.mti, '\001',"�������ͱ�ʶ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_auth_hst.orig_txn_type, '\001',"ԭ��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_auth_hst.orig_fwd_inst_id, '\001',"ԭʼת��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_auth_hst.orig_acq_inst_id, '\001',"ԭʼ���������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_auth_hst.orig_mti, '\001',"ԭ����MTI");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_auth_hst.orig_trans_date, '\001',"ԭʼ��������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_auth_hst.orig_trace_no, '\001',"ԭʼϵͳ���ٺ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_auth_hst.orig_txn_proc, '\001',"ԭ���״�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_auth_hst.orig_txn_amt, '\001',"ԭʼ���ױ��ֽ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_auth_hst.orig_log_kv, '\001',"ԭ����LOG��ֵ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_auth_hst.orig_txn_val_1, '\001',"ԭ���׼�ֵ1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_auth_hst.orig_txn_val_2, '\001',"ԭ���׼�ֵ2");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_auth_hst.orig_chb_txn_amt, '\001',"ԭʼ���˱��ֽ��");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_auth_hst.orig_biz_date, '\001',"ԭ���׵�����ҵ��������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_auth_hst.last_reversal_date, '\001',"���һ�γ峷ʱ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_auth_hst.void_count, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_auth_hst.manual_auth_flag, '\001',"�˹���Ȩ��־");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_auth_hst.opera_id, '\001',"����ԱID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_auth_hst.brand, '\001',"Ʒ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_auth_hst.product_cd, '\001',"��Ʒ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_auth_hst.mcc_type, '\001',"�̻����ͷ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_auth_hst.final_reason, '\001',"��Ȩԭ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_auth_hst.final_action, '\001',"�����ж�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_auth_hst.comp_amt, '\001',"������Ȩ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_auth_hst.final_upd_direction, '\001',"���ո��·���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_auth_hst.final_upd_amt, '\001',"���ո��½��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_auth_hst.ic_ind, '\001',"�Ƿ�IC��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_auth_hst.the_3dsecure_type, '\001',"�Ƿ�3D���Ӱ�ȫ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_auth_hst.vip_status, '\001',"VIP״̬");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_auth_hst.curr_bal, '\001',"��ǰ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_auth_hst.cash_amt, '\001',"ȡ�ֽ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_auth_hst.otb, '\001',"���ö��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_auth_hst.cash_otb, '\001',"ȡ�ֿ��ö��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_auth_hst.cust_otb, '\001',"�ͻ����ö��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_auth_hst.card_black_flag, '\001',"�Ƿ��˻�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_auth_hst.merchant_black_flag, '\001',"�Ƿ��̻�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_auth_hst.expire_date, '\001',"��Ч����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_auth_hst.track_one_result, '\001',"һ�ŵ������Խ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_auth_hst.track_two_result, '\001',"���ŵ������Խ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_auth_hst.track_three_result, '\001',"���ŵ������Խ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_auth_hst.pwd_type, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_auth_hst.check_pwd_result, '\001',"��֤������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_auth_hst.pay_pwd_err_num, '\001',"֧������������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_auth_hst.check_cvv_result, '\001',"CVV��֤���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_auth_hst.check_cvv2_result, '\001',"CVV2��֤���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_auth_hst.check_icvn_result, '\001',"ICVN��֤���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_auth_hst.check_arqc_result, '\001',"ARQC��֤���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_auth_hst.check_atc_result, '\001',"ATC��֤���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_auth_hst.check_cvr_result, '\001',"CVR��֤���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_auth_hst.check_tvr_result, '\001',"TVR��֤���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_auth_hst.rej_reason, '\001',"�ܾ�ԭ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_auth_hst.unmatch_cr, '\001',"δƥ����ǽ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 77, sdb_icps_wbc_tm_auth_hst.unmatch_db, '\001',"δƥ���ǽ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 78, sdb_icps_wbc_tm_auth_hst.b002, '\001',"���ʿ���-B002");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 79, sdb_icps_wbc_tm_auth_hst.b003, '\001',"���״�����-B003");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 80, sdb_icps_wbc_tm_auth_hst.b007, '\001',"���״���ʱ��-B007");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 81, sdb_icps_wbc_tm_auth_hst.b011, '\001',"ϵͳ���ٺ�-B011");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 82, sdb_icps_wbc_tm_auth_hst.b022, '\001',"�����PIN��ȡ��-B022");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 83, sdb_icps_wbc_tm_auth_hst.b025, '\001',"�����������-B025");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 84, sdb_icps_wbc_tm_auth_hst.b032, '\001',"���������ʶ��-B032");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 85, sdb_icps_wbc_tm_auth_hst.b033, '\001',"����������Ƶ�ַ-B033");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 86, sdb_icps_wbc_tm_auth_hst.b039, '\001',"������-B039");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 87, sdb_icps_wbc_tm_auth_hst.b042, '\001',"�ܿ���(�̻�)��ʶ��-B042");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 88, sdb_icps_wbc_tm_auth_hst.b060, '\001',"�Զ�����-B060");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 89, sdb_icps_wbc_tm_auth_hst.b061, '\001',"�ֿ��������֤��Ϣ-B061");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 90, sdb_icps_wbc_tm_auth_hst.b090, '\001',"ԭʼ����Ԫ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 91, sdb_icps_wbc_tm_auth_hst.opera_term_id, '\001',"�����û��ն˱��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 92, sdb_icps_wbc_tm_auth_hst.jpa_version, '\001',"�ֹ����汾��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 93, sdb_icps_wbc_tm_auth_hst.b004, '\001',"���׻��ҽ��-B004");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 94, sdb_icps_wbc_tm_auth_hst.b006, '\001',"�˻����ҽ��-B006");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 95, sdb_icps_wbc_tm_auth_hst.b049, '\001',"���׻��Ҵ���-B049");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 96, sdb_icps_wbc_tm_auth_hst.b051, '\001',"�˻����Ҵ���-B051");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 97, sdb_icps_wbc_tm_auth_hst.b037, '\001',"�����ο���-B037");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 98, sdb_icps_wbc_tm_auth_hst.b028, '\001',"������-B028");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 99, sdb_icps_wbc_tm_auth_hst.b048, '\001',"��������-B048");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 100, sdb_icps_wbc_tm_auth_hst.b054, '\001',"�����������-B054");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 101, sdb_icps_wbc_tm_auth_hst.card_block_code, '\001',"��Ƭ������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 102, sdb_icps_wbc_tm_auth_hst.account_block_code, '\001',"�ʻ�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 103, sdb_icps_wbc_tm_auth_hst.medium_block_code, '\001',"����������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 104, sdb_icps_wbc_tm_auth_hst.consumer_trans_id, '\001',"ҵ����ˮ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 105, sdb_icps_wbc_tm_auth_hst.sys_trans_id, '\001',"ϵͳ������ˮ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 106, sdb_icps_wbc_tm_auth_hst.qchannel_id, '\001',"�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 107, sdb_icps_wbc_tm_auth_hst.sub_terminal_type, '\001',"�ն�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 108, sdb_icps_wbc_tm_auth_hst.sub_merch_id, '\001',"�����̻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 109, sdb_icps_wbc_tm_auth_hst.sub_merch_name, '\001',"�����̻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 110, sdb_icps_wbc_tm_auth_hst.wares_desc, '\001',"��Ʒ��Ϣ");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 111, sdb_icps_wbc_tm_auth_hst.last_modified_datetime, '\001',"�޸�ʱ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 112, sdb_icps_wbc_tm_auth_hst.part_month, '\001',"�����õ��·�");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 113, sdb_icps_wbc_tm_auth_hst.paid_stmt_date, '\001',"�����˵���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 114, sdb_icps_wbc_tm_auth_hst.repay_amt, '\001',"Ӧ�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 115, sdb_icps_wbc_tm_auth_hst.transfer_type, '\001',"ת������");


       
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_auth_hst.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_auth_hst.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AUTH_HST", SD_ICPS_WBC_TM_AUTH_HST, NUMELE(SD_ICPS_WBC_TM_AUTH_HST),
                    &sdb_icps_wbc_tm_auth_hst, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tm_auth_hst.log_kv), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    return 0;
} 

/**
 *��Ȩ��ˮ���Ų�ֱ�
 */
int ffunc_parse_wbankcar_file_to_db_tm_auth_bank_cost(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_AUTH_BANK_COST sdb_icps_wbc_tm_auth_bank_cost;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_tm_auth_bank_cost WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_auth_bank_cost, 0x00, sizeof(sdb_icps_wbc_tm_auth_bank_cost));
            pstrcopy(sdb_icps_wbc_tm_auth_bank_cost.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_auth_bank_cost.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_auth_bank_cost.file_order = rcdCnt;     
            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_auth_bank_cost.consumer_trans_id, '\001',"ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_auth_bank_cost.bank_group_id, '\001',"���ű��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_auth_bank_cost.bank_no, '\001',"���к�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_auth_bank_cost.reg_type, '\001',"�Ǽ�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_auth_bank_cost.reg_amt, '\001',"�Ǽǽ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_auth_bank_cost.reg_status, '\001',"�Ǽ�״̬");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_auth_bank_cost.biz_date, '\001',"ҵ������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_auth_bank_cost.reg_sys_id, '\001',"������ˮ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_auth_bank_cost.reg_date, '\001',"��������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_auth_bank_cost.reg_time, '\001',"��������ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_auth_bank_cost.recon_code, '\001',"������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_auth_bank_cost.ori_sys_id, '\001',"ԭ������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_auth_bank_cost.cust_id, '\001',"�ͻ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_auth_bank_cost.acct_no, '\001',"�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_auth_bank_cost.acct_type, '\001',"�˻�����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_auth_bank_cost.retry, '\001',"���Դ���");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_auth_bank_cost.created_datetime, '\001',"����ʱ��");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_auth_bank_cost.last_modified_datetime, '\001',"ʱ���");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_auth_bank_cost.jpa_version, '\001',"�ֹ����汾��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_auth_bank_cost.card_no, '\001',"����");            
        

            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_auth_bank_cost.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_auth_bank_cost.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AUTH_BANK_COST", SD_ICPS_WBC_TM_AUTH_BANK_COST, NUMELE(SD_ICPS_WBC_TM_AUTH_BANK_COST),
                    &sdb_icps_wbc_tm_auth_bank_cost, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_auth_bank_cost.consumer_trans_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}

/**
 *��Ȩ��ˮ���Ų����ϸ�� 
 */
int ffunc_parse_wbankcar_file_to_db_tm_auth_bank_cost_dtl(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_AUTH_BANK_COST_DTL sdb_icps_wbc_tm_auth_bank_cost_dtl;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_AUTH_BANK_COST_DTL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_auth_bank_cost_dtl, 0x00, sizeof(sdb_icps_wbc_tm_auth_bank_cost_dtl));
            pstrcopy(sdb_icps_wbc_tm_auth_bank_cost_dtl.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_auth_bank_cost_dtl.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_auth_bank_cost_dtl.file_order = rcdCnt;
            
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_auth_bank_cost_dtl.consumer_trans_id, '\001',"ҵ����ˮ��");     
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_auth_bank_cost_dtl.bank_group_id, '\001',"���ű��");           
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_auth_bank_cost_dtl.bank_no, '\001',"���к�");                   
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_auth_bank_cost_dtl.loan_receipt_nbr, '\001',"��ݺ�");          
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_auth_bank_cost_dtl.reg_type, '\001',"�Ǽ�����");                
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_auth_bank_cost_dtl.reg_amt, '\001',"�Ǽǽ��");                 
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_auth_bank_cost_dtl.biz_date, '\001',"ҵ������");                  
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_auth_bank_cost_dtl.cust_id, '\001',"�ͻ����");                
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_auth_bank_cost_dtl.acct_no, '\001',"�˻����");                
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_auth_bank_cost_dtl.acct_type, '\001',"�˻�����");              
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_auth_bank_cost_dtl.created_datetime, '\001',"����ʱ��");    
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_auth_bank_cost_dtl.last_modified_datetime, '\001',"ʱ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_auth_bank_cost_dtl.card_no, '\001',"����");                    
            
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_auth_bank_cost_dtl.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_auth_bank_cost_dtl.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AUTH_BANK_COST_DTL", SD_ICPS_WBC_TM_AUTH_BANK_COST_DTL, NUMELE(SD_ICPS_WBC_TM_AUTH_BANK_COST_DTL),
                    &sdb_icps_wbc_tm_auth_bank_cost_dtl, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_auth_bank_cost_dtl.consumer_trans_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*�����붨���*/


int ffunc_parse_wbankcar_file_to_db_tm_txn_cd(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_TXN_CD sdb_icps_wbc_tm_txn_cd;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_TXN_CD WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_txn_cd, 0x00, sizeof(sdb_icps_wbc_tm_txn_cd));
            pstrcopy(sdb_icps_wbc_tm_txn_cd.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_txn_cd.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_txn_cd.file_order = rcdCnt;   
            
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_txn_cd.flow_no, '\001',"FLOW_NO");   
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_txn_cd.org, '\001',"������");         
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_txn_cd.txn_code, '\001',"������");    
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_txn_cd.txn_desc, '\001',"��������");  
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_txn_cd.txn_class, '\001',"TXN_CLASS");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_txn_cd.bnp, '\001',"���ɷ�");       
          
          
                        
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_txn_cd.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_txn_cd.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_TXN_CD", SD_ICPS_WBC_TM_TXN_CD, NUMELE(SD_ICPS_WBC_TM_TXN_CD),
                    &sdb_icps_wbc_tm_txn_cd, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tm_txn_cd.flow_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*�������嵥��*/

int ffunc_parse_wbankcar_file_to_db_tm_loan_receipt_list(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_LOAN_RECEIPT_LIST sdb_icps_wbc_tm_loan_receipt_list;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_LOAN_RECEIPT_LIST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_loan_receipt_list, 0x00, sizeof(sdb_icps_wbc_tm_loan_receipt_list));
            pstrcopy(sdb_icps_wbc_tm_loan_receipt_list.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_loan_receipt_list.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_loan_receipt_list.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_loan_receipt_list.consumer_trans_id, '\001',"ҵ����ˮ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_loan_receipt_list.sys_trans_id, '\001',"ϵͳ������ˮ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_loan_receipt_list.loan_receipt_nbr, '\001',"��ݺ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_loan_receipt_list.acct_no, '\001',"�˻����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_loan_receipt_list.acct_type, '\001',"�˻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_loan_receipt_list.card_no, '\001',"����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_loan_receipt_list.post_date, '\001',"��������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_loan_receipt_list.last_modified_datetime, '\001',"ʱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_loan_receipt_list.pay_amt, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_loan_receipt_list.bank_group_id, '\001',"���ű��");

           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_loan_receipt_list.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_loan_receipt_list.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_LOAN_RECEIPT_LIST", SD_ICPS_WBC_TM_LOAN_RECEIPT_LIST, NUMELE(SD_ICPS_WBC_TM_LOAN_RECEIPT_LIST),
                    &sdb_icps_wbc_tm_loan_receipt_list, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_loan_receipt_list.consumer_trans_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }
    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*���˻�ƿ�Ŀ��*/

int ffunc_parse_wbankcar_file_to_db_tm_gl_bal(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_GL_BAL sdb_icps_wbc_tm_gl_bal;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_GL_BAL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_gl_bal, 0x00, sizeof(sdb_icps_wbc_tm_gl_bal));
            pstrcopy(sdb_icps_wbc_tm_gl_bal.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_gl_bal.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_gl_bal.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/    
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_gl_bal.org, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_gl_bal.subject, '\001',"��Ŀ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_gl_bal.branch_id, '\001',"��֧�к�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_gl_bal.db_bal, '\001',"�跽���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_gl_bal.cr_bal, '\001',"�������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_gl_bal.db_amt, '\001',"�跽������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_gl_bal.db_count, '\001',"�跽����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_gl_bal.cr_amt, '\001',"����������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_gl_bal.cr_count, '\001',"��������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_gl_bal.last_db_bal, '\001',"���ս跽���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_gl_bal.last_cr_bal, '\001',"���մ������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_gl_bal.last_mth_db_bal, '\001',"����ĩ�跽���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_gl_bal.last_mth_cr_bal, '\001',"����ĩ�������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_gl_bal.last_qtr_db_bal, '\001',"�ϼ�ĩ�跽���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_gl_bal.last_qtr_cr_bal, '\001',"�ϼ�ĩ�������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_gl_bal.last_yr_db_bal, '\001',"����ĩ�跽���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_gl_bal.last_yr_cr_bal, '\001',"����ĩ�������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_gl_bal.jpa_version, '\001',"�ֹ����汾��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_gl_bal.product_cd, '\001',"��Ʒ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_gl_bal.bal_id, '\001',"˳���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_gl_bal.bank_no, '\001',"���д���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_gl_bal.bank_group_id, '\001',"���Ŵ���");

           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_gl_bal.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_gl_bal.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_GL_BAL", SD_ICPS_WBC_TM_GL_BAL, NUMELE(SD_ICPS_WBC_TM_GL_BAL),
                    &sdb_icps_wbc_tm_gl_bal, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_gl_bal.subject), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*��Ʒ�¼�ձ���*/

int ffunc_parse_wbankcar_file_to_db_tm_accounting_flow(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_ACCOUNTING_FLOW sdb_icps_wbc_tm_accounting_flow;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_ACCOUNTING_FLOW WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_accounting_flow, 0x00, sizeof(sdb_icps_wbc_tm_accounting_flow));
            pstrcopy(sdb_icps_wbc_tm_accounting_flow.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_accounting_flow.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_accounting_flow.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_accounting_flow.org, '\001',"�ڲ�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_accounting_flow.cps_txn_seq, '\001',"���Ľ�����ˮ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_accounting_flow.card_no, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_accounting_flow.curr_cd, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_accounting_flow.txn_code, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_accounting_flow.txn_desc, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_accounting_flow.db_cr_ind, '\001',"������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_accounting_flow.post_amt, '\001',"���˽��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_accounting_flow.post_gl_ind, '\001',"���˷�ʽ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_accounting_flow.owning_branch, '\001',"֧��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_accounting_flow.subject, '\001',"��Ŀ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_accounting_flow.red_flag, '\001',"�����ֱ�ʶ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_accounting_flow.queue, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_accounting_flow.product_cd, '\001',"��Ʒ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_accounting_flow.ref_nbr, '\001',"��ݺ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_accounting_flow.age_group, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_accounting_flow.plan_nbr, '\001',"���üƻ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_accounting_flow.bnp_group, '\001',"���ɷ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_accounting_flow.bank_group_id, '\001',"���Ŵ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_accounting_flow.bank_no, '\001',"���д���");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_accounting_flow.term, '\001',"����");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_accounting_flow.batchdate, '\001',"����");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_accounting_flow.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_accounting_flow.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_ACCOUNTING_FLOW", SD_ICPS_WBC_TM_ACCOUNTING_FLOW, NUMELE(SD_ICPS_WBC_TM_ACCOUNTING_FLOW),
                    &sdb_icps_wbc_tm_accounting_flow, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR");
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_accounting_flow.card_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*Ӫ������Ϣ��*/

int ffunc_parse_wbankcar_file_to_db_tm_loan_vms(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_LOAN_VMS sdb_icps_wbc_tm_loan_vms;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_LOAN_VMS WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG")
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO")
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR")
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_loan_vms, 0x00, sizeof(sdb_icps_wbc_tm_loan_vms));
            pstrcopy(sdb_icps_wbc_tm_loan_vms.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_loan_vms.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_loan_vms.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_loan_vms.id, '\001',"��˰���ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_loan_vms.org, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_loan_vms.card_no, '\001',"���ʿ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_loan_vms.ref_nbr, '\001',"���ײο���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_loan_vms.bank_group_id, '\001',"���ű��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_loan_vms.bank_no, '\001',"���б��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_loan_vms.product_cd, '\001',"��Ʒ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_loan_vms.biz_tax_interest, '\001',"Ӫҵ˰�µ�Ӧ�ƺ�Ӧ��Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_loan_vms.vat_int_bal, '\001',"90���ڵ�Ӧ��˰Ϣ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_loan_vms.norevoke_vat_int_bal, '\001',"������㷨��Ӧ��˰Ϣ����90����+90���⻹��ǲ��֣�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_loan_vms.vat_tax, '\001',"������ֵ˰");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_loan_vms.loan_init_term, '\001',"����������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_loan_vms.last_modified_time, '\001',"�ϴ��޸�ʱ��");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_loan_vms.paid_out_date, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_loan_vms.age_cd, '\001',"����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_loan_vms.batch_date, '\001',"��������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_loan_vms.jpa_version, '\001',"�ֹ����汾��");

           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_loan_vms.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_loan_vms.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_LOAN_VMS", SD_ICPS_WBC_TM_LOAN_VMS, NUMELE(SD_ICPS_WBC_TM_LOAN_VMS),
                    &sdb_icps_wbc_tm_loan_vms, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_loan_vms.id), "ERROR")
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*nbs�ͻ���*/

int ffunc_parse_wbankcar_file_to_db_tm_nbs_cust(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_NBS_CUST sdb_icps_wbc_tm_nbs_cust;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_NBS_CUST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO")
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR")
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_nbs_cust, 0x00, sizeof(sdb_icps_wbc_tm_nbs_cust));
            pstrcopy(sdb_icps_wbc_tm_nbs_cust.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_nbs_cust.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_nbs_cust.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_nbs_cust.nbs_cust_id, '\001',"NBS�ͻ�ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_nbs_cust.name, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_nbs_cust.id_type, '\001',"֤������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_nbs_cust.id_no, '\001',"֤������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_nbs_cust.ecif_no, '\001',"ecif�ͻ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_nbs_cust.reserve1, '\001',"�����ֶ�1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_nbs_cust.reserve2, '\001',"���֤��Ч��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_nbs_cust.reserve3, '\001',"�����ֶ�3");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_nbs_cust.biz_date, '\001',"ҵ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_nbs_cust.created_datetime, '\001',"����ʱ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_nbs_cust.last_modified_datetime, '\001',"����ʱ������");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_nbs_cust.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_nbs_cust.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_NBS_CUST", SD_ICPS_WBC_TM_NBS_CUST, NUMELE(SD_ICPS_WBC_TM_NBS_CUST),
                    &sdb_icps_wbc_tm_nbs_cust, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_nbs_cust.nbs_cust_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*ƽ̨�ͻ���Ϣ��*/

int ffunc_parse_wbankcar_file_to_db_tm_merchant_cust(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_MERCHANT_CUST sdb_icps_wbc_tm_merchant_cust;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_MERCHANT_CUST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_merchant_cust, 0x00, sizeof(sdb_icps_wbc_tm_merchant_cust));
            pstrcopy(sdb_icps_wbc_tm_merchant_cust.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_merchant_cust.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_merchant_cust.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_merchant_cust.user_id, '\001',"ƽ̨�Ŀͻ�ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_merchant_cust.merchant_id, '\001',"ƽ̨ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_merchant_cust.nbs_cust_id, '\001',"NBS�ͻ�ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_merchant_cust.user_name, '\001',"ƽ̨ע��Ŀͻ�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_merchant_cust.user_mobile, '\001',"ƽ̨�Ǽǵ��û��ֻ���");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_merchant_cust.apply_datetime, '\001',"ƽ̨ID����ʱ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_merchant_cust.reg_mobile, '\001',"ע���ֻ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_merchant_cust.qq_openid, '\001',"QQ_OPENID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_merchant_cust.wx_openid, '\001',"WX_OPENID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_merchant_cust.login_id, '\001',"΢��WEB��¼ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_merchant_cust.company_name, '\001',"��λ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_merchant_cust.company_phone, '\001',"��λ�绰");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_merchant_cust.address, '\001',"��ס��ַ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_merchant_cust.contact_name, '\001',"��ϵ������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_merchant_cust.contact_phone, '\001',"��ϵ���ֻ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_merchant_cust.contact_relation, '\001',"��ϵ�˹�ϵ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_merchant_cust.reserve1, '\001',"�����ֶ�1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_merchant_cust.reserve2, '\001',"�����ֶ�2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_merchant_cust.reserve3, '\001',"�����ֶ�3");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_merchant_cust.biz_date, '\001',"ҵ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_merchant_cust.created_datetime, '\001',"����ʱ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_merchant_cust.last_modified_datetime, '\001',"����ʱ������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_merchant_cust.contact_addr, '\001',"��ϵ�˵�ַ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_merchant_cust.contact_id_no, '\001',"��ϵ�����֤��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_merchant_cust.co_licenses, '\001',"Ӫҵִ�պ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_merchant_cust.driver_license, '\001',"��ʻ֤����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_merchant_cust.company_addr, '\001',"��˾��ַ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_merchant_cust.home_phone, '\001',"��ͥ�̻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_merchant_cust.occupation, '\001',"ְҵ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_merchant_cust.ss_ave_amt_mtly, '\001',"ÿ���籣ƽ���ɽ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_merchant_cust.salary_ave_mtly, '\001',"ÿ��ƽ�����ʽ�����ˮ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_merchant_cust.is_home_visited, '\001',"���޼ҷ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_merchant_cust.house_info, '\001',"������Ϣ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_merchant_cust.mer_apply_result, '\001',"�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_merchant_cust.mer_apply_view, '\001',"�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_merchant_cust.mer_refuse_reason, '\001',"�ܾ�ԭ�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_merchant_cust.cust_value, '\001',"�ͻ���Ϣ�����ֶΣ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_merchant_cust.is_guarantor, '\001',"���޵�����");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_merchant_cust.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_merchant_cust.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_MERCHANT_CUST", SD_ICPS_WBC_TM_MERCHANT_CUST, NUMELE(SD_ICPS_WBC_TM_MERCHANT_CUST),
                    &sdb_icps_wbc_tm_merchant_cust, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_merchant_cust.user_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*ƽ̨�ͻ���Ʒ��Ϣ��*/

int ffunc_parse_wbankcar_file_to_db_tm_merchant_product_cust(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_MERCHANT_PRODUCT_CUST sdb_icps_wbc_tm_merchant_product_cust;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_MERCHANT_PRODUCT_CUST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_merchant_product_cust, 0x00, sizeof(sdb_icps_wbc_tm_merchant_product_cust));
            pstrcopy(sdb_icps_wbc_tm_merchant_product_cust.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_merchant_product_cust.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_merchant_product_cust.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_merchant_product_cust.user_id, '\001',"ƽ̨�Ŀͻ�ID");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_merchant_product_cust.merchant_id, '\001',"ƽ̨ID");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_merchant_product_cust.product_cd, '\001',"��ƷCD");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_merchant_product_cust.cnc_card_no, '\001',"�����");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_merchant_product_cust.debit_card_no, '\001',"���н�ǿ���");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_merchant_product_cust.wb_debit_card_no, '\001',"���н�ǿ���");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_merchant_product_cust.nbs_cust_id, '\001',"NBS�ͻ�ID");
			ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_merchant_product_cust.aps_app_time, '\001',"APS��������ʱ��");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_merchant_product_cust.aps_app_no, '\001',"APS���������");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_merchant_product_cust.aps_app_no_status, '\001',"APS�����״̬");
			ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_merchant_product_cust.aps_app_count, '\001',"�����������");
			ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_merchant_product_cust.aps_approval_date, '\001',"APS����ͨ������");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_merchant_product_cust.aps_result_level, '\001',"APS��������ȼ�");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_merchant_product_cust.aps_rej_code, '\001',"APS�����ܾ���");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_merchant_product_cust.aps_rej_date, '\001',"APS�����ܾ�ʱ��");
			ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_merchant_product_cust.cnc_setup_date, '\001',"���������");
			ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_merchant_product_cust.aps_credit_limit, '\001',"����ʱ���Ŷ��");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_merchant_product_cust.gid, '\001',"����ԴGID");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_merchant_product_cust.oper_ip, '\001',"����ԴIP");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_merchant_product_cust.os_type, '\001',"����ϵͳ");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_merchant_product_cust.lbs, '\001',"LBS");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_merchant_product_cust.ios_idfa, '\001',"IOS��ʾ��");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_merchant_product_cust.android_imei, '\001',"ANDROID������ַ");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_merchant_product_cust.submitted_entry, '\001',"�ύ���");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_merchant_product_cust.submitted_city, '\001',"�������");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_merchant_product_cust.reserve1, '\001',"�����ֶ�1");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_merchant_product_cust.reserve2, '\001',"�����ֶ�2");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_merchant_product_cust.reserve3, '\001',"�����ֶ�3");
			ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_merchant_product_cust.biz_date, '\001',"ҵ������");
			ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_merchant_product_cust.created_datetime, '\001',"����ʱ������");
			ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_merchant_product_cust.last_modified_datetime, '\001',"����ʱ������");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_merchant_product_cust.app_biz_seq_no, '\001',"����ҵ����ˮ��");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_merchant_product_cust.aps_rej_reason, '\001',"����ܾ�ԭ��");
			ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_merchant_product_cust.app_expiry_date, '\001',"����ʧЧ����");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_merchant_product_cust.agent_id, '\001',"���������id");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_merchant_product_cust.agent_name, '\001',"����������");

           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_merchant_product_cust.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_merchant_product_cust.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_MERCHANT_PRODUCT_CUST", SD_ICPS_WBC_TM_MERCHANT_PRODUCT_CUST, NUMELE(SD_ICPS_WBC_TM_MERCHANT_PRODUCT_CUST),
                    &sdb_icps_wbc_tm_merchant_product_cust, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_merchant_product_cust.merchant_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*Э���*/

int ffunc_parse_wbankcar_file_to_db_tm_agreement(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_AGREEMENT sdb_icps_wbc_tm_agreement;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_AGREEMENT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_agreement, 0x00, sizeof(sdb_icps_wbc_tm_agreement));
            pstrcopy(sdb_icps_wbc_tm_agreement.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_agreement.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_agreement.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_agreement.agreement_no, '\001',"ƽ̨������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_agreement.merchant_id, '\001',"ƽ̨ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_agreement.product_cd, '\001',"��ƷCD");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_agreement.product_stcode, '\001',"��Ʒ�ṹ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_agreement.nbs_cust_id, '\001',"NBS�ͻ�ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_agreement.user_id, '\001',"ƽ̨�Ŀͻ�ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_agreement.cnc_card_no, '\001',"�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_agreement.debit_card_no, '\001',"���н�ǿ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_agreement.wb_debit_card_no, '\001',"���н�ǿ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_agreement.last_txn_status, '\001',"��һ��ҵ��״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_agreement.txn_status, '\001',"��ǰҵ��״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_agreement.last_native_staus, '\001',"��һ����״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_agreement.native_staus, '\001',"��ǰ����״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_agreement.billing_cycle, '\001',"�˵�����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_agreement.first_stmt_date, '\001',"�׸��˵���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_agreement.agreement_amt, '\001',"Э����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_agreement.pct_id, '\001',"���ۿ��Ʊ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_agreement.fee_rate, '\001',"��������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_agreement.interest_rate, '\001',"��Ϣ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_agreement.penalty_rate, '\001',"��Ϣ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_agreement.liquidated_damages, '\001',"ΥԼ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_agreement.curr_term, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_agreement.curr_deduct_stage, '\001',"��ǰ�ۿ�׶�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_agreement.deduct_stage_hst, '\001',"�ۿ�׶���ʷ��¼");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_agreement.credit_interest_rate, '\001',"���ô�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_agreement.credit_penalty_rate, '\001',"���ô���Ϣ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_agreement.credit_curr_deduct_stage, '\001',"���ô���ǰ�ۿ�׶�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_agreement.credit_deduct_stage_hst, '\001',"���ô��ۿ�׶���ʷ��¼");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_agreement.master_card_flag, '\001',"�������ʶ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_agreement.reserve1, '\001',"�����ֶ�1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_agreement.reserve2, '\001',"�����ֶ�2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_agreement.reserve3, '\001',"�����ֶ�3");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_agreement.biz_date, '\001',"ҵ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_agreement.created_datetime, '\001',"����ʱ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_agreement.last_modified_datetime, '\001',"����ʱ������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_agreement.loan_init_term, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_agreement.order_type, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_agreement.fund_status, '\001',"�ʽ�ռѹ״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_agreement.fee_curr_deduct_stage, '\001',"���ô���ǰ�ۿ�׶�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_agreement.profit_ratio, '\001',"�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_agreement.product_category, '\001',"��Ʒ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_agreement.fee_deduct_stage_hst, '\001',"���ô��ۿ�׶���ʷ��¼");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_agreement.reserve4, '\001',"�����ֶ�4");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_agreement.reserve5, '\001',"�����ֶ�5");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_agreement.reserve6, '\001',"�����ֶ�6");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_agreement.reserve7, '\001',"�����ֶ�7");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_agreement.reserve8, '\001',"�����ֶ�8");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_agreement.reserve9, '\001',"�����ֶ�9");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_agreement.reserve10, '\001',"�����ֶ�10");

           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_agreement.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_agreement.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AGREEMENT", SD_ICPS_WBC_TM_AGREEMENT, NUMELE(SD_ICPS_WBC_TM_AGREEMENT),
                    &sdb_icps_wbc_tm_agreement, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_agreement.agreement_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*Э�鸽�ӱ�(��)*/

int ffunc_parse_wbankcar_file_to_db_tm_agreement_car(HXMLTREE lXmlhandle,WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_AGREEMENT_CAR sdb_icps_wbc_tm_agreement_car;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_AGREEMENT_CAR WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_agreement_car, 0x00, sizeof(sdb_icps_wbc_tm_agreement_car));
            pstrcopy(sdb_icps_wbc_tm_agreement_car.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_agreement_car.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_agreement_car.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_agreement_car.agreement_no, '\001',"ƽ̨������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_agreement_car.merchant_id, '\001',"ƽ̨ID��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_agreement_car.product_cd, '\001',"��Ʒ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_agreement_car.mer_order_no, '\001',"ƽ̨Э���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_agreement_car.is_new_car, '\001',"�Ƿ��³�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_agreement_car.car_id, '\001',"����ID");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_agreement_car.car_price, '\001',"�������ۼ�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_agreement_car.car_inquiry_price, '\001',"�ⲿ����Դ��ѯ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_agreement_car.assess_amount, '\001',"������ֵ");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_agreement_car.assess_time, '\001',"��������ʱ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_agreement_car.assess_class, '\001',"������⼶��");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_agreement_car.registrate_time, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_agreement_car.vehicle_id, '\001',"�������ܺ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_agreement_car.engine_no, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_agreement_car.mileage, '\001',"��ʻ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_agreement_car.xfr_times, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_agreement_car.coty, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_agreement_car.motorcycle_type, '\001',"��������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_agreement_car.ins_expire_date, '\001',"���յ�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_agreement_car.dealer_id, '\001',"����ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_agreement_car.dealer_name, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_agreement_car.is_stage_guarantee_dealer, '\001',"�Ƿ�׶��Ե�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_agreement_car.car_name, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_agreement_car.is_second_hand_car, '\001',"�Ƿ���ֳ�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_agreement_car.car_actual_price, '\001',"����ʵ�ʳɽ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_agreement_car.down_payment, '\001',"�׸��ܽ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_agreement_car.car_context, '\001',"������Ϣ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_agreement_car.driver_license, '\001',"��ʻ֤����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_agreement_car.home_phone, '\001',"��ͥ�̻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_agreement_car.occupation, '\001',"ְҵ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_agreement_car.ss_ave_amt_mtly, '\001',"ÿ���籣ƽ���ɽ����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_agreement_car.salary_ave_mtly, '\001',"ÿ��ƽ�����ʽ�����ˮ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_agreement_car.is_home_visited, '\001',"���޼ҷ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_agreement_car.house_info, '\001',"������Ϣ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_agreement_car.mer_apply_result, '\001',"�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_agreement_car.mer_apply_view, '\001',"�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_agreement_car.mer_refuse_reason, '\001',"�ܾ�ԭ�����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_agreement_car.biz_date, '\001',"ҵ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_agreement_car.created_datetime, '\001',"����ʱ��");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_agreement_car.last_modified_datetime, '\001',"����ʱ��");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_agreement_car.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_agreement_car.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AGREEMENT_CAR", SD_ICPS_WBC_TM_AGREEMENT_CAR, NUMELE(SD_ICPS_WBC_TM_AGREEMENT_CAR),
                    &sdb_icps_wbc_tm_agreement_car, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_agreement_car.agreement_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*������ӳ���*/

int ffunc_parse_wbankcar_file_to_db_tm_agreement_no_map(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_AGREEMENT_NO_MAP sdb_icps_wbc_tm_agreement_no_map;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_AGREEMENT_NO_MAP WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_agreement_no_map, 0x00, sizeof(sdb_icps_wbc_tm_agreement_no_map));
            pstrcopy(sdb_icps_wbc_tm_agreement_no_map.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_agreement_no_map.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_agreement_no_map.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_agreement_no_map.agreement_no, '\001',"NBS������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_agreement_no_map.merchant_id, '\001',"ƽ̨ID��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_agreement_no_map.mer_order_no, '\001',"ƽ̨������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_agreement_no_map.txn_status, '\001',"ƽ̨Э��״̬");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_agreement_no_map.biz_data, '\001',"ҵ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_agreement_no_map.created_datetime, '\001',"����ʱ��");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_agreement_no_map.last_modified_datetime, '\001',"�޸�ʱ��");
          
		  


            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_agreement_no_map.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_agreement_no_map.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AGREEMENT_NO_MAP", SD_ICPS_WBC_TM_AGREEMENT_NO_MAP, NUMELE(SD_ICPS_WBC_TM_AGREEMENT_NO_MAP),
                    &sdb_icps_wbc_tm_agreement_no_map, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_agreement_no_map.agreement_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}

/*���������ݺ�ӳ��*/
int ffunc_parse_wbankcar_file_to_db_tm_loan_yx(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_LOAN_YX sdb_icps_wbc_tm_loan_yx;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_LOAN_YX WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_loan_yx, 0x00, sizeof(sdb_icps_wbc_tm_loan_yx));
            pstrcopy(sdb_icps_wbc_tm_loan_yx.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_loan_yx.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_loan_yx.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_loan_yx.loan_receipt_nbr, '\001',"��ݺ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_loan_yx.merchant_id, '\001',"ƽ̨ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_loan_yx.product_cd, '\001',"��ƷCD");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_loan_yx.agreement_no, '\001',"ƽ̨Э���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_loan_yx.cnc_card_no, '\001',"�����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_loan_yx.loan_init_term, '\001',"������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_loan_yx.curr_term, '\001',"��������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_loan_yx.remain_term, '\001',"ʣ������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_loan_yx.interest_rate, '\001',"��Ϣ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_loan_yx.loan_status, '\001',"״̬");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_loan_yx.loan_prin, '\001',"�ܱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_loan_yx.loan_paid, '\001',"�ѻ�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_loan_yx.loan_init_interest, '\001',"����Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_loan_yx.int_paid, '\001',"�ѻ���Ϣ");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_loan_yx.loan_expire_date , '\001',"��������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_loan_yx.grace_date, '\001',"������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_loan_yx.due_days, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_loan_yx.loan_paidout_flg, '\001',"�����ʶ");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_loan_yx.loan_paidout_date, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_loan_yx.terminate_reason_cd, '\001',"��ֹԭ�����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_loan_yx.batch_date, '\001',"����ͬ������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_loan_yx.batch_no, '\001',"���κ�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_loan_yx.loan_bal_late_charge, '\001',"Ƿ�������ɽ�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_loan_yx.loan_bal_adv_pmt_fee, '\001',"Ƿ������ǰ����������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_loan_yx.loan_bal_fee, '\001',"Ƿ���ܷ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_loan_yx.late_charge_paid, '\001',"�ѻ����ɽ�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_loan_yx.adv_pmt_fee_paid, '\001',"�ѻ���ǰ����������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_loan_yx.fee_paid, '\001',"�ѻ�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_loan_yx.next_prin, '\001',"���ڱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_loan_yx.next_fee, '\001',"����������");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_loan_yx.register_date, '\001',"���ע������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_loan_yx.prin_bal, '\001',"Ƿ���ܱ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_loan_yx.int_bal, '\001',"Ƿ������Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_loan_yx.penalty_bal, '\001',"Ƿ���ܷ�Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_loan_yx.penalty_paid, '\001',"�ѻ���Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_loan_yx.penalty_rate, '\001',"��Ϣ����");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_loan_yx.biz_date, '\001',"ҵ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_loan_yx.created_datetime, '\001',"����ʱ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_loan_yx.last_modified_datetime, '\001',"����ʱ������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_loan_yx.loan_type, '\001',"�������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_loan_yx.unearned_prin, '\001',"δ���ڱ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_loan_yx.inst_return_flag, '\001',"�Ƿ�����Ϣ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_loan_yx.paid_out_return_status, '\001',"�����˱���Ϣ״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_loan_yx.ref_nbr, '\001',"���׼�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_loan_yx.loan_merge_type, '\001',"��ݺϲ�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_loan_yx.bef_init_interest, '\001',"ԭ��������Ϣ");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_loan_yx.orig_init_term, '\001',"ԭʼ��������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_loan_yx.gl_term, '\001',"�����������������������Ҫ���Ի������Լӹ�");

           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_loan_yx.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_loan_yx.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_LOAN_YX", SD_ICPS_WBC_TM_LOAN_YX, NUMELE(SD_ICPS_WBC_TM_LOAN_YX),
                    &sdb_icps_wbc_tm_loan_yx, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_loan_yx.loan_receipt_nbr), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}

/*nbs�ͻ���չ��*/

int ffunc_parse_wbankcar_file_to_db_tm_nbs_cust_ext_info(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_NBS_CUST_EXT_INFO sdb_icps_wbc_tm_nbs_cust_ext_info;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_NBS_CUST_EXT_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_nbs_cust_ext_info, 0x00, sizeof(sdb_icps_wbc_tm_nbs_cust_ext_info));
            pstrcopy(sdb_icps_wbc_tm_nbs_cust_ext_info.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_nbs_cust_ext_info.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_nbs_cust_ext_info.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_nbs_cust_ext_info.nbs_cust_id, '\001',"NBS�ͻ�ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_nbs_cust_ext_info.product_cd, '\001',"��Ʒ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_nbs_cust_ext_info.merchant_id, '\001',"ƽ̨ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_nbs_cust_ext_info.name, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_nbs_cust_ext_info.id_type, '\001',"֤������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_nbs_cust_ext_info.id_no, '\001',"֤������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_nbs_cust_ext_info.id_no_expiry, '\001',"���֤��Ч��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_nbs_cust_ext_info.residential_address, '\001',"��ַ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_nbs_cust_ext_info.gender, '\001',"�Ա�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_nbs_cust_ext_info.nationality, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_nbs_cust_ext_info.marriage, '\001',"����״��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_nbs_cust_ext_info.education, '\001',"ѧ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf1, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf2, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf3, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf4, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf5, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf6, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf7, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf8, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf9, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf10, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf11, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf12, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf13, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf14, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf15, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf16, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf17, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf18, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf19, '\001',"�����ֶ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf20, '\001',"�����ֶ�");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_nbs_cust_ext_info.created_datetime, '\001',"����ʱ������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_nbs_cust_ext_info.last_modified_datetime, '\001',"����ʱ������");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_nbs_cust_ext_info.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_nbs_cust_ext_info.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_NBS_CUST_EXT_INFO", SD_ICPS_WBC_TM_NBS_CUST_EXT_INFO, NUMELE(SD_ICPS_WBC_TM_NBS_CUST_EXT_INFO),
                    &sdb_icps_wbc_tm_nbs_cust_ext_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_nbs_cust_ext_info.nbs_cust_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*���պ��������˺ţ����˺���������д�����ϸ��*/

int ffunc_parse_wbankcar_file_to_db_kdpl_zhminx(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_KDPL_ZHMINX sdb_icps_wbc_kdpl_zhminx;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_KDPL_ZHMINX WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_kdpl_zhminx, 0x00, sizeof(sdb_icps_wbc_kdpl_zhminx));
            pstrcopy(sdb_icps_wbc_kdpl_zhminx.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_kdpl_zhminx.busi_date)); /*ҵ������*/
            sdb_icps_wbc_kdpl_zhminx.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_kdpl_zhminx.zhanghao, '\001',"��ծ�˺�");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_kdpl_zhminx.mxixuhao, '\001',"��ϸ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_kdpl_zhminx.jiaoyirq, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_kdpl_zhminx.khjymxlb, '\001',"�ͻ�������ϸ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_kdpl_zhminx.jyyyjigo, '\001',"����Ӫҵ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_kdpl_zhminx.kaihjigo, '\001',"�˻���������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_kdpl_zhminx.zhhuzwmc, '\001',"�˻�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_kdpl_zhminx.jiedaibz, '\001',"�����־");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_kdpl_zhminx.jiaoybiz, '\001',"���ױ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_kdpl_zhminx.chaohubz, '\001',"�˻������־");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_kdpl_zhminx.jiaoyije, '\001',"���׽��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_kdpl_zhminx.zhanghye, '\001',"�˻����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_kdpl_zhminx.kahaoooo, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_kdpl_zhminx.kehuzhao, '\001',"�ͻ��˺�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_kdpl_zhminx.zhhaoxuh, '\001',"���˻����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_kdpl_zhminx.pngzzlei, '\001',"ƾ֤����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_kdpl_zhminx.pngzxhao, '\001',"ƾ֤��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_kdpl_zhminx.zhaiyodm, '\001',"ժҪ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_kdpl_zhminx.zhaiyoms, '\001',"ժҪ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_kdpl_zhminx.duifjgdm, '\001',"�Է����ڻ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_kdpl_zhminx.duifjgmc, '\001',"�Է����ڻ�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_kdpl_zhminx.duifkhzh, '\001',"�Է��ͻ��˺�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_kdpl_zhminx.duifminc, '\001',"�Է�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_kdpl_zhminx.duifbezh, '\001',"�Է���ע");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_kdpl_zhminx.beizhuuu, '\001',"��ע");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_kdpl_zhminx.qixiriqi, '\001',"��Ϣ����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_kdpl_zhminx.qdaoleix, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_kdpl_zhminx.waibclma, '\001',"���˴���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_kdpl_zhminx.nbjoyima, '\001',"�ڲ�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_kdpl_zhminx.xianzzbz, '\001',"��ת��־");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_kdpl_zhminx.guiylius, '\001',"��Ա��ˮ(��������ˮ)");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_kdpl_zhminx.caozguiy, '\001',"������Ա");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_kdpl_zhminx.zhujriqi, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_kdpl_zhminx.zjyilush, '\001',"��������ˮ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_kdpl_zhminx.yewulush, '\001',"ҵ����ˮ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_kdpl_zhminx.jiaoyisj, '\001',"����ʱ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_kdpl_zhminx.bchongbz, '\001',"������ϸ״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_kdpl_zhminx.cuozriqi, '\001',"ԭ��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_kdpl_zhminx.cuozlius, '\001',"ԭ���˽�����ˮ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_kdpl_zhminx.yszjylsh, '\001',"ԭʼ��������ˮ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_kdpl_zhminx.ysyewush, '\001',"ԭʼҵ����ˮ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_kdpl_zhminx.czczflei, '\001',"�������˷���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_kdpl_zhminx.mozhanbz, '\001',"Ĩ�˱�־");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_kdpl_zhminx.tokennnn, '\001',"token");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_kdpl_zhminx.dsftoken, '\001',"���ַ�token");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_kdpl_zhminx.lilvlilv, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_kdpl_zhminx.jioyshij, '\001',"�����¼�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_kdpl_zhminx.huidxhao, '\001',"�ص����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_kdpl_zhminx.farendma, '\001',"���˴���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_kdpl_zhminx.weihguiy, '\001',"ά����Ա");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_kdpl_zhminx.weihjigo, '\001',"ά������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_kdpl_zhminx.weihriqi, '\001',"ά������");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_kdpl_zhminx.shijchuo, '\001',"ʱ���");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_kdpl_zhminx.is_check_flag, "1", sizeof(sdb_icps_wbc_kdpl_zhminx.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_KDPL_ZHMINX", SD_ICPS_WBC_KDPL_ZHMINX, NUMELE(SD_ICPS_WBC_KDPL_ZHMINX),
                    &sdb_icps_wbc_kdpl_zhminx, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_kdpl_zhminx.zhanghao), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}

/*�����˲�����Ϣ��*/

int ffunc_parse_wbankcar_file_to_db_tm_psb_check_info(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_PSB_CHECK_INFO sdb_icps_wbc_tm_psb_check_info;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_PSB_CHECK_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_psb_check_info, 0x00, sizeof(sdb_icps_wbc_tm_psb_check_info));
            pstrcopy(sdb_icps_wbc_tm_psb_check_info.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_psb_check_info.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_psb_check_info.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_psb_check_info.seq_no, '\001',"��ѯ��ˮ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_psb_check_info.org, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_psb_check_info.app_no, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_psb_check_info.id_type, '\001',"֤������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_psb_check_info.id_no, '\001',"֤������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_psb_check_info.name, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_psb_check_info.gender, '\001',"�Ա�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_psb_check_info.result_person_id, '\001',"֤������˲���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_psb_check_info.result_person_name, '\001',"�����˲���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_psb_check_info.photo_id, '\001',"��Ƭ�ļ�id");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_psb_check_info.nation, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_psb_check_info.photo_md5, '\001',"��Ƭmd5ֵ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_psb_check_info.old_name, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_psb_check_info.birth, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_psb_check_info.native_place, '\001',"����ʡ���أ�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_psb_check_info.address, '\001',"סַ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_psb_check_info.work_place, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_psb_check_info.marital_status, '\001',"����״��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_psb_check_info.degree_of_education, '\001',"�Ļ��̶�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_psb_check_info.issued_authority, '\001',"ǩ������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_psb_check_info.birth_place, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_psb_check_info.occupation, '\001',"ְҵ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_psb_check_info.bl0, '\001',"����״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_psb_check_info.bl1, '\001',"Υ��״̬");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_psb_check_info.created_datetime, '\001',"����ʱ��");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_psb_check_info.last_modified_datetime, '\001',"����޸�ʱ��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_psb_check_info.jpa_version, '\001',"�ֹ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_psb_check_info.product_cd, '\001',"��Ʒ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_psb_check_info.msg_serv_error, '\001',"�����쳣����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_psb_check_info.msg_id_error, '\001',"��ѯ�������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_psb_check_info.flag, '\001',"�����ȡ����");

           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_psb_check_info.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_psb_check_info.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_PSB_CHECK_INFO", SD_ICPS_WBC_TM_PSB_CHECK_INFO, NUMELE(SD_ICPS_WBC_TM_PSB_CHECK_INFO),
                    &sdb_icps_wbc_tm_psb_check_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_psb_check_info.seq_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*�����Ϣ*/

int ffunc_parse_wbankcar_file_to_db_tm_psb_personal_info(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_PSB_PERSONAL_INFO sdb_icps_wbc_tm_psb_personal_info;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_PSB_PERSONAL_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_psb_personal_info, 0x00, sizeof(sdb_icps_wbc_tm_psb_personal_info));
            pstrcopy(sdb_icps_wbc_tm_psb_personal_info.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_psb_personal_info.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_psb_personal_info.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_psb_personal_info.id, '\001',"ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_psb_personal_info.app_no, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_psb_personal_info.certi_type, '\001',"֤������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_psb_personal_info.certi_no, '\001',"���֤��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_psb_personal_info.name, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_psb_personal_info.sex, '\001',"�Ա�");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_psb_personal_info.birth_date, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_psb_personal_info.marrystate, '\001',"����״��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_psb_personal_info.mobile, '\001',"�ֻ�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_psb_personal_info.homephone, '\001',"��ͥ�绰");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_psb_personal_info.compphone, '\001',"��λ�绰");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_psb_personal_info.qualification, '\001',"ѧ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_psb_personal_info.degree, '\001',"ѧλ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_psb_personal_info.address, '\001',"ͨѶ��ַ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_psb_personal_info.reside_addr, '\001',"������ַ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_psb_personal_info.mate_certp, '\001',"��ż֤������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_psb_personal_info.mate_cerno, '\001',"��ż֤������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_psb_personal_info.mate_name, '\001',"��ż����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_psb_personal_info.mate_corp, '\001',"��ż������λ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_psb_personal_info.mate_phone, '\001',"��ż��ϵ�绰");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_psb_personal_info.addr, '\001',"��ס��ַ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_psb_personal_info.reside_state, '\001',"��ס״��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_psb_personal_info.comp_nm, '\001',"������λ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_psb_personal_info.comp_addr, '\001',"��λ��ַ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_psb_personal_info.profess, '\001',"ְҵ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_psb_personal_info.comp_trade, '\001',"��ҵ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_psb_personal_info.business, '\001',"ְ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_psb_personal_info.teach_pose, '\001',"ְ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_psb_personal_info.work_date, '\001',"����λ������ʼ���");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_psb_personal_info.infodate, '\001',"��Ϣ��������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_psb_personal_info.create_time, '\001',"����ʱ��");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_psb_personal_info.psb_query_date, '\001',"���б����ѯʱ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_psb_personal_info.reportsn, '\001',"���б�����");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_psb_personal_info.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_psb_personal_info.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_PSB_PERSONAL_INFO", SD_ICPS_WBC_TM_PSB_PERSONAL_INFO, NUMELE(SD_ICPS_WBC_TM_PSB_PERSONAL_INFO),
                    &sdb_icps_wbc_tm_psb_personal_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tm_psb_personal_info.id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*���о��߽����*/

int ffunc_parse_wbankcar_file_to_db_tm_bank_credit_result(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_BANK_CREDIT_RESULT sdb_icps_wbc_tm_bank_credit_result;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_BANK_CREDIT_RESULT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_bank_credit_result, 0x00, sizeof(sdb_icps_wbc_tm_bank_credit_result));
            pstrcopy(sdb_icps_wbc_tm_bank_credit_result.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_bank_credit_result.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_bank_credit_result.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_bank_credit_result.seq_no, '\001',"������ˮ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_bank_credit_result.bank_no, '\001',"���б��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_bank_credit_result.bank_name, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_bank_credit_result.id_no, '\001',"֤����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_bank_credit_result.id_type, '\001',"֤������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_bank_credit_result.name, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_bank_credit_result.nbs_order_no, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_bank_credit_result.credit_info, '\001',"������Ϣ");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_bank_credit_result.rule_action_type, '\001',"���Ź�������״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_bank_credit_result.rule_code, '\001',"���Ź������ܾ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_bank_credit_result.ruile_desc, '\001',"���������߾ܾ�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_bank_credit_result.is_bl_rej, '\001',"����������״̬");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_bank_credit_result.bl_rej_code, '\001',"�������ܾ�����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_bank_credit_result.bl_rej_desc, '\001',"�������ܾ�����");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_bank_credit_result.credit_datetime, '\001',"�����ж�ʱ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_bank_credit_result.result_code, '\001',"���߽��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_bank_credit_result.result_desc, '\001',"���߽������");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_bank_credit_result.created_datetime, '\001',"����ʱ��");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_bank_credit_result.last_modified_datetime, '\001',"����ʱ��");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_bank_credit_result.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_bank_credit_result.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_BANK_CREDIT_RESULT", SD_ICPS_WBC_TM_BANK_CREDIT_RESULT, NUMELE(SD_ICPS_WBC_TM_BANK_CREDIT_RESULT),
                    &sdb_icps_wbc_tm_bank_credit_result, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_bank_credit_result.seq_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*���б�*/

int ffunc_parse_wbankcar_file_to_db_tm_bank(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_BANK sdb_icps_wbc_tm_bank;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_BANK WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_bank, 0x00, sizeof(sdb_icps_wbc_tm_bank));
            pstrcopy(sdb_icps_wbc_tm_bank.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_bank.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_bank.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_bank.bank_no, '\001',"���к�");          
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_bank.bank_name, '\001',"��������");      
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_bank.paying_acct, '\001',"�������˻���"); /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_bank.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_bank.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_BANK", SD_ICPS_WBC_TM_BANK, NUMELE(SD_ICPS_WBC_TM_BANK),
                    &sdb_icps_wbc_tm_bank, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_tm_bank.bank_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*�������ñ�*/

int ffunc_parse_wbankcar_file_to_db_tm_bank_group_member(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_TM_BANK_GROUP_MEMBER sdb_icps_wbc_tm_bank_group_member;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_BANK_GROUP_MEMBER WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_bank_group_member, 0x00, sizeof(sdb_icps_wbc_tm_bank_group_member));
            pstrcopy(sdb_icps_wbc_tm_bank_group_member.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_bank_group_member.busi_date)); /*ҵ������*/
            sdb_icps_wbc_tm_bank_group_member.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_bank_group_member.member_id, '\001',"˳���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_bank_group_member.bank_group_id, '\001',"���ű��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_bank_group_member.bank_no, '\001',"���к�");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_bank_group_member.bank_proportion, '\001',"���г��ʱ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_bank_group_member.product_category, '\001',"��Ʒ����");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_bank_group_member.priority, '\001',"�������ȼ�");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_tm_bank_group_member.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_bank_group_member.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_BANK_GROUP_MEMBER", SD_ICPS_WBC_TM_BANK_GROUP_MEMBER, NUMELE(SD_ICPS_WBC_TM_BANK_GROUP_MEMBER),
                    &sdb_icps_wbc_tm_bank_group_member, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_tm_bank_group_member.member_id), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*�������ʽ��������*/

int ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_tot(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT sdb_icps_wbc_rrs_bdm_udf_clear_tot;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_rrs_bdm_udf_clear_tot, 0x00, sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_tot));
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_tot.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_tot.busi_date)); /*ҵ������*/
            sdb_icps_wbc_rrs_bdm_udf_clear_tot.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_rrs_bdm_udf_clear_tot.data_dt, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_rrs_bdm_udf_clear_tot.acct_no, '\001',"�������ʺ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_rrs_bdm_udf_clear_tot.ccy, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_rrs_bdm_udf_clear_tot.acct_name, '\001',"����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_rrs_bdm_udf_clear_tot.last_balance, '\001',"�����˻����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_rrs_bdm_udf_clear_tot.balance, '\001',"�����˻����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_rrs_bdm_udf_clear_tot.payment_amt, '\001',"���շſ��ܽ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_rrs_bdm_udf_clear_tot.repayment_amt, '\001',"���ջ����ܽ��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_rrs_bdm_udf_clear_tot.other_credit_amt, '\001',"���������������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_rrs_bdm_udf_clear_tot.other_debit_amt, '\001',"����������������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_rrs_bdm_udf_clear_tot.ds, '\001',"���ڷ���");

           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_tot.is_check_flag, "1", sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_tot.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT", SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT, NUMELE(SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT),
                    &sdb_icps_wbc_rrs_bdm_udf_clear_tot, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_rrs_bdm_udf_clear_tot.acct_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*�������ʽ�������ϸ*/

int ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_detail(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL sdb_icps_wbc_rrs_bdm_udf_clear_detail;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_rrs_bdm_udf_clear_detail, 0x00, sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_detail));
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_detail.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_detail.busi_date)); /*ҵ������*/
            sdb_icps_wbc_rrs_bdm_udf_clear_detail.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_rrs_bdm_udf_clear_detail.data_dt, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_rrs_bdm_udf_clear_detail.acct_no, '\001',"�������ʺ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_rrs_bdm_udf_clear_detail.ccy, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_rrs_bdm_udf_clear_detail.bank_group_code, '\001',"���ű��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_rrs_bdm_udf_clear_detail.data_type, '\001',"��������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_rrs_bdm_udf_clear_detail.amount, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_rrs_bdm_udf_clear_detail.ds, '\001',"���ڷ���");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_detail.is_check_flag, "1", sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_detail.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL", SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL, NUMELE(SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL),
                    &sdb_icps_wbc_rrs_bdm_udf_clear_detail, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_rrs_bdm_udf_clear_detail.acct_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*���������������ʽ���ϸ*/

int ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_other_detail(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL sdb_icps_wbc_rrs_bdm_udf_clear_other_detail;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_rrs_bdm_udf_clear_other_detail, 0x00, sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_other_detail));
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.busi_date)); /*ҵ������*/
            sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.data_dt, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.acct_no, '\001',"�������ʺ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.ccy, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.bank_group_code, '\001',"���ű��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.data_type, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.ser_no, '\001',"��ϸ���");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.amount, '\001',"������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.memo, '\001',"��ע");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.ds, '\001',"���ڷ���");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.is_check_flag, "1", sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL", SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL, NUMELE(SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL),
                    &sdb_icps_wbc_rrs_bdm_udf_clear_other_detail, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%d']", rcdCnt, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.acct_no), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*β�������*/

int ffunc_parse_wbankcar_file_to_db_bank_group_dfq_split_diff(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF sdb_icps_wbc_bank_group_dfq_split_diff;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_bank_group_dfq_split_diff, 0x00, sizeof(sdb_icps_wbc_bank_group_dfq_split_diff));
            pstrcopy(sdb_icps_wbc_bank_group_dfq_split_diff.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_bank_group_dfq_split_diff.busi_date)); /*ҵ������*/
            sdb_icps_wbc_bank_group_dfq_split_diff.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_bank_group_dfq_split_diff.partition_date, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_bank_group_dfq_split_diff.product_cd , '\001',"��Ʒ���");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_bank_group_dfq_split_diff.error_type, '\001',"�쳣����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_bank_group_dfq_split_diff.bank_group_id, '\001',"���ű��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_bank_group_dfq_split_diff.bank_no, '\001',"���б��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_bank_group_dfq_split_diff.consumer_trans_id, '\001',"ҵ����ˮ��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_bank_group_dfq_split_diff.reg_type, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_bank_group_dfq_split_diff.name, '\001',"����");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_bank_group_dfq_split_diff.logical_card_no, '\001',"�߼�����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_bank_group_dfq_split_diff.bf_amt, '\001',"������������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_bank_group_dfq_split_diff.account_amt, '\001',"CNC���˽��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_bank_group_dfq_split_diff.error_amt, '\001',"Ӧ�������");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_bank_group_dfq_split_diff.is_check_flag, "1", sizeof(sdb_icps_wbc_bank_group_dfq_split_diff.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF", SD_ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF, NUMELE(SD_ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF),
                    &sdb_icps_wbc_bank_group_dfq_split_diff, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_bank_group_dfq_split_diff.partition_date), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*CBS�������ϸ����*/

int ffunc_parse_wbankcar_file_to_db_report_cbs_ptjr_car_data_paid_detail_day_coop(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop, 0x00, sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop));
            pstrcopy(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.busi_date)); /*ҵ������*/
            sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/ 
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.partition_date, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.bank_group_id, '\001',"���ű��");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.org_no, '\001',"������������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.fee_name, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.loan_receipt_nbr, '\001',"��ݺ�");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.txn_date, '\001',"���׷�����������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.clearing_calc_day_amt, '\001',"ʵ����Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.clearing_day_amt, '\001',"ƽ̨��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.clearing_day_no_vat_amt, '\001',"����ƽ̨�ѣ�����˰��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.clearing_day_vat_amt, '\001',"����ƽ̨�ѣ�˰��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.interest_rate, '\001',"����");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.fund_ratio, '\001',"�ʽ𶨼�");

           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.is_check_flag, "1", sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP", SD_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP, NUMELE(SD_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP),
                    &sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.partition_date), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*CBS�������ܱ���*/

int ffunc_parse_wbankcar_file_to_db_report_cbs_ptjr_car_data_paid_sum_day_coop(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[20480], sFileLineGBK[20480], sFileLineList[128];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fclose(fp_list);
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop, 0x00, sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop));
            pstrcopy(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.busi_date)); /*ҵ������*/
            sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.partition_date, '\001',"��������");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.bank_group_id, '\001',"���ű��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.clearing_calc_day_amt, '\001',"ʵ����Ϣ");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.clearing_day_no_vat_amt, '\001',"����ƽ̨�ѣ�����˰��");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.clearing_day_vat_amt, '\001',"����ƽ̨�ѣ�˰��");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.txn_num , '\001',"������");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.clearing_day_amt, '\001',"ƽ̨��");
           
            /*������˱�־*/
            pstrcopy(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.is_check_flag, "1", sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP", SD_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP, NUMELE(SD_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP),
                    &sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.partition_date), "ERROR");
                DCIRollback();
                fclose(fp_list);
                fclose(fp_check);
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    fclose(fp_list);
                    fclose(fp_check);
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            fclose(fp_list);
            fclose(fp_check);
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}


int ffunc_parse_wbankcar_file_to_db(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int fileins_status = -1;

    if (0 == strcmp(st_para_chkfileins.file_type, "tm_app_main"))
    {
        /*��������*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_app_main(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_app_prim_applicant_info"))
    {
        /*������������Ϣ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_app_prim_applicant_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_account"))
    {
        /*�˻���Ϣ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_account(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_customer"))
    {
        /*�ͻ���Ϣ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_customer(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_plan"))
    {
        /*���üƻ���*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_plan(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tt_txn_post"))
    {
        /*�������˽��ױ�*/
        iRet = ffunc_parse_wbankcar_file_to_db_tt_txn_post(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan"))
    {
        /*������Ϣ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_loan(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_schedule"))
    {
        /*��������*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_schedule(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_cust_limit_o"))
    {
        /*�Զ�������Ϣ��-��Ȩ*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_cust_limit_o(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_auth_hst"))
    {
        /*��Ȩ������ʷ*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_auth_hst(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_auth_bank_cost"))
    {
        /*��Ȩ��ˮ���Ų�ֱ�*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_auth_bank_cost(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_auth_bank_cost_dtl"))
    {
        /*��Ȩ��ˮ���Ų����ϸ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_auth_bank_cost_dtl(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_txn_cd"))
    {
        /*�����붨���*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_txn_cd(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_receipt_list"))
    {
        /*�������嵥��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_loan_receipt_list(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_gl_bal"))
    {
        /*���˻�ƿ�Ŀ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_gl_bal(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_accounting_flow"))
    {
        /*��Ʒ�¼�ձ���*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_accounting_flow(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_vms"))
    {
        /*Ӫ������Ϣ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_loan_vms(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_nbs_cust"))
    {
        /*nbs�ͻ���*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_nbs_cust(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_merchant_cust"))
    {
        /*ƽ̨�ͻ���Ϣ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_merchant_cust(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_merchant_product_cust"))
    {
        /*ƽ̨�ͻ���Ʒ��Ϣ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_merchant_product_cust(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_agreement"))
    {
        /*Э���*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_agreement(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_agreement_car"))
    {
        /*Э�鸽�ӱ�(��) */
        iRet = ffunc_parse_wbankcar_file_to_db_tm_agreement_car(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_agreement_no_map"))
    {
        /*������ӳ���*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_agreement_no_map(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_yx"))
    {
        /*���������ݺ�ӳ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_loan_yx(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_nbs_cust_ext_info"))
    {
        /*nbs�ͻ���չ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_nbs_cust_ext_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "kdpl_zhminx"))
    {
        /*���պ��������˺ţ����˺���������д�����ϸ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_kdpl_zhminx(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_psb_check_info"))
    {
        /*�����˲�����Ϣ��*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_psb_check_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_psb_personal_info"))
    {
        /*�����Ϣ*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_psb_personal_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_bank_credit_result"))
    {
        /*���о��߽����*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_bank_credit_result(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_bank"))
    {
        /*���б�*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_bank(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_bank_group_member"))
    {
        /*�������ñ�*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_bank_group_member(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_tot"))
    {
        /*�������ʽ��������*/
        iRet = ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_tot(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_detail"))
    {
        /*�������ʽ�������ϸ*/
        iRet = ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_detail(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_other_detail"))
    {
        /*���������������ʽ���ϸ*/
        iRet = ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_other_detail(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "bank_group_dfq_split_diff"))
    {
        /*β�������*/
        iRet = ffunc_parse_wbankcar_file_to_db_bank_group_dfq_split_diff(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "report_cbs_ptjr_car_data_paid_detail_day_coop"))
    {
        /*CBS�������ϸ����*/
        iRet = ffunc_parse_wbankcar_file_to_db_report_cbs_ptjr_car_data_paid_detail_day_coop(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "report_cbs_ptjr_car_data_paid_sum_day_coop"))
    {
        /*CBS�������ܱ���*/
        iRet = ffunc_parse_wbankcar_file_to_db_report_cbs_ptjr_car_data_paid_sum_day_coop(lXmlhandle, st_para_chkfileins);
    }
    
    else
    {
        LOG(LM_STD, Fmtmsg("�ļ����ʹ���"), "ERROR");
        return -2;
    }

    COMP_SOFTGETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, sBuf);
    fileins_status = atoi(trim(sBuf));
    LOG(LM_STD, Fmtmsg("Ŀǰ�ļ����״̬[%d]", fileins_status), "INFO")

    if (9 == fileins_status) /*��ʼ*/
    {
        if (0 == iRet) /*�ɹ�*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "0") /*�ɹ�*/
        else if (-404 == iRet) /*���ļ�*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "9") /*��ʼ*/
        else
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "2") /*ʧ��*/
    }
    else if (0 == fileins_status) /*�ɹ�*/
    {
        if (0 == iRet) /*�ɹ�*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "0") /*�ɹ�*/
        else
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "1") /*���ֳɹ�*/
    }
    else if (2 == fileins_status) /*ʧ��*/
    {
        if (0 == iRet || -404 == iRet)
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "1") /*���ֳɹ�*/
    }
    COMP_SOFTGETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, sBuf);
    fileins_status = atoi(trim(sBuf));
    LOG(LM_STD, Fmtmsg("���ļ�����״̬[%d]", fileins_status), "INFO")
    iRet = ffunc_upd_file_info(st_para_chkfileins.busi_date, st_para_chkfileins.busi_no, st_para_chkfileins.file_type, iRet);

    return iRet;
}

int ffunc_init_wbankcar_file_info(HXMLTREE lXmlhandle, PARA_FILEINFOINIT st_para_fileinfoinit)
{
    int iRet;

    /*��������*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_app_main");
    /*������������Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_app_prim_applicant_info");
    /*�˻���Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_account");
    /*�ͻ���Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_customer");
    /*���üƻ���*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_plan");
    /*�������˽��ױ�*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tt_txn_post");
    /*������Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan");
    /*��������*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_schedule");
    /*�Զ�������Ϣ��-��Ȩ*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_cust_limit_o");
    /*��Ȩ������ʷ*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_auth_hst");
    /*��Ȩ��ˮ���Ų�ֱ�*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_auth_bank_cost");
    /*��Ȩ��ˮ���Ų����ϸ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_auth_bank_cost_dtl");
    /*�����붨���*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_txn_cd");
    /*�������嵥��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_receipt_list");
    /*���˻�ƿ�Ŀ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_gl_bal");
    /*��Ʒ�¼�ձ���*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_accounting_flow");
    /*Ӫ������Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_vms");
    /*nbs�ͻ���*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_nbs_cust");
    /*ƽ̨�ͻ���Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_merchant_cust");
    /*ƽ̨�ͻ���Ʒ��Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_merchant_product_cust");
    /*Э���*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_agreement");
    /*Э�鸽�ӱ�(��)*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_agreement_car");
    /*������ӳ���*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_agreement_no_map");
    /*���������ݺ�ӳ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_yx");
    /*nbs�ͻ���չ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_nbs_cust_ext_info");
    /*���պ��������˺ţ����˺���������д�����ϸ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "kdpl_zhminx");
    /*�����˲�����Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_psb_check_info");
    /*�����Ϣ*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_psb_personal_info");
    /*���о��߽����*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_bank_credit_result");
    /*���б�*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_bank");
    /*�������ñ�*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_bank_group_member");
    /*�������ʽ��������*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_tot");    
     /* �������ʽ�������ϸ */
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_detail");
      /*���������������ʽ���ϸ*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_other_detail");
     /* β�������*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "bank_group_dfq_split_diff");            
     /* CBS�������ϸ����*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "report_cbs_ptjr_car_data_paid_detail_day_coop");   
     /*CBS�������ܱ��� */
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "report_cbs_ptjr_car_data_paid_sum_day_coop");
    return 0;
}
