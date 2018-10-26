#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include <iconv.h>
#include <stdio.h>
#include <string.h>

/**
 * 申请主表
 */
int ffunc_parse_wbankcar_file_to_db_tm_app_main(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_APP_MAIN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }
		    LOG(LM_STD,Fmtmsg("打开文件成功，准备入库!"),"INFO");

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_app_main, 0x00, sizeof(sdb_icps_wbc_tm_app_main));
            pstrcopy(sdb_icps_wbc_tm_app_main.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_app_main.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_app_main.file_order = rcdCnt;
            

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_app_main.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_app_main.app_no, '\001', "申请件编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_app_main.app_type, '\001', "申请类型");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_app_main.app_lmt, '\001', "申请额度");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_app_main.sug_lmt, '\001', "系统建议额度");
           	ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_app_main.acc_lmt, '\001', "核准额度");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_app_main.product_cd, '\001', "卡产品代码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_app_main.business_limit, '\001', "商务卡额度");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_app_main.micro_loan_limit, '\001', "小额贷款额度");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_app_main.vehicle_loan, '\001', "专项额度车贷");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_app_main.house_loan, '\001', "专项额度房贷");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_app_main.renovation_loan, '\001', "专项额度装修贷");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_app_main.travel_loan, '\001', "专项额度旅游贷");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_app_main.wedding_loan, '\001', "专项额度婚庆贷");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_app_main.durable_loan, '\001', "专项额度耐消贷");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_app_main.priority, '\001', "客户等级");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_app_main.client_type, '\001', "客户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_app_main.approve_quick_flag, '\001', "快速审批标志");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_app_main.busns_num, '\001', "公司编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_app_main.rtf_state, '\001', "审批状态");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_app_main.point_result, '\001', "评分值");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_app_main.cust_rate_discount, '\001', "客户利率浮动比例");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_app_main.pro_num, '\001', "流程实例号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_app_main.pro_name, '\001', "流程节点名称");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_app_main.refuse_code, '\001', "拒绝原因码");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_app_main.answer_err_cnt, '\001', "问题回答错误次数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_app_main.is_clt, '\001', "是否集体件");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_app_main.spreader_num, '\001', "推广人编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_app_main.spreader_org, '\001', "推广机构");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_app_main.spreader_bank, '\001', "推广人所属分行");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_app_main.spreader_way, '\001', "推广方式");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_app_main.spreader_type, '\001', "推广渠道");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_app_main.spreader_name, '\001', "推广人姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_app_main.spreader_num_pre, '\001', "推广单位预审人编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_app_main.spreader_phone, '\001', "推广人手机号码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_app_main.sales_ind, '\001', "是否接受推广邮件");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_app_main.owning_branch, '\001', "发卡网点");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_app_main.app_promotion_cd, '\001', "促销码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_app_main.app_source, '\001', "申请来源");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_app_main.bank_customer_id, '\001', "行内客户号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_app_main.dd_flag, '\001', "约定扣款是否开通标识");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_app_main.deduct_deal_no, '\001', "自扣协议号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_app_main.if_refuse, '\001', "是否拒绝");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_app_main.if_end, '\001', "是否处理完成件");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_app_main.apply_from_type, '\001', "申请来源类别");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_app_main.appno_external, '\001', "申请编号_外部送入");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_app_main.appno_attach_external, '\001', "附卡申请编号_外部送入");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_app_main.remark, '\001', "备注");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_app_main.create_user, '\001', "创建人");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_app_main.update_user, '\001', "修改人");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_app_main.biz_no, '\001', "业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_app_main.trace_no, '\001', "调起方流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_app_main.called_no, '\001', "被调方流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_app_main.result_code, '\001', "审批结果码");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_app_main.created_datetime, '\001', "创建时间");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_app_main.last_modified_datetime, '\001', "最后修改时间");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_app_main.jpa_version, '\001', "乐观锁");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_app_main.is_shared_credit_limit, '\001', "是否共享额度");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_app_main.approval_datetime, '\001', "审批通过时间");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_app_main.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_app_main.is_check_flag));
            
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_APP_MAIN", SD_ICPS_WBC_TM_APP_MAIN, NUMELE(SD_ICPS_WBC_TM_APP_MAIN),
                    &sdb_icps_wbc_tm_app_main, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_app_main.app_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 申请人主卡信息表
 */
int ffunc_parse_wbankcar_file_to_db_tm_app_prim_applicant_info(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_app_prim_applicant_info, 0x00, sizeof(sdb_icps_wbc_tm_app_prim_applicant_info));
            pstrcopy(sdb_icps_wbc_tm_app_prim_applicant_info.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_app_prim_applicant_info.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_app_prim_applicant_info.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_app_prim_applicant_info.id, '\001',"标识");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_app_prim_applicant_info.org, '\001',"机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_app_prim_applicant_info.app_no, '\001',"申请件编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_app_prim_applicant_info.if_selected_card, '\001',"是否自选卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_app_prim_applicant_info.card_no, '\001',"卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_app_prim_applicant_info.name, '\001',"姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_app_prim_applicant_info.emb_logo, '\001',"凸印名称");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_app_prim_applicant_info.gender, '\001',"性别");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_app_prim_applicant_info.nationality, '\001',"国籍");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_app_prim_applicant_info.residency_country_cd, '\001',"永久居住地国家代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_app_prim_applicant_info.id_type, '\001',"证件类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_app_prim_applicant_info.id_no, '\001',"证件号码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_app_prim_applicant_info.id_last_date, '\001',"证件到期日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_app_prim_applicant_info.id_issuer_address, '\001',"发证机关所在地址");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_app_prim_applicant_info.birthday, '\001',"生日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_app_prim_applicant_info.liquid_asset, '\001',"个人资产类型");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_app_prim_applicant_info.year_income, '\001',"年收入");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_app_prim_applicant_info.qualification, '\001',"教育状况");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_app_prim_applicant_info.marital_status, '\001',"婚姻状况");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_app_prim_applicant_info.home_addr_ctry_cd, '\001',"家庭国家代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_app_prim_applicant_info.home_state, '\001',"家庭所在省");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_app_prim_applicant_info.home_city, '\001',"家庭所在市");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_app_prim_applicant_info.home_zone, '\001',"家庭所在区县");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_app_prim_applicant_info.house_ownership, '\001',"房屋持有类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_app_prim_applicant_info.home_add, '\001',"家庭地址");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_app_prim_applicant_info.home_postcode, '\001',"家庭住宅邮编");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_app_prim_applicant_info.home_phone, '\001',"家庭电话");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_app_prim_applicant_info.home_stand_from, '\001',"现住址居住起始年月");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_app_prim_applicant_info.cellphone, '\001',"移动电话");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_app_prim_applicant_info.email, '\001',"电子邮箱");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_app_prim_applicant_info.qq_acct, '\001',"QQ账号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_app_prim_applicant_info.open_id, '\001',"公众号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_app_prim_applicant_info.house_type, '\001',"住宅类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_app_prim_applicant_info.family_member, '\001',"家庭人口");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_app_prim_applicant_info.family_avge_venue, '\001',"家庭人均年收入");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_app_prim_applicant_info.bankmem_flag, '\001',"是否行内员工");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_app_prim_applicant_info.bankmember_no, '\001',"本行员工号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_app_prim_applicant_info.corp_name, '\001',"公司名称");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_app_prim_applicant_info.emp_addr_ctry_cd, '\001',"公司国家代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_app_prim_applicant_info.emp_province, '\001',"公司所在省");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_app_prim_applicant_info.emp_city, '\001',"公司所在市");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_app_prim_applicant_info.emp_zone, '\001',"公司所在区/县");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_app_prim_applicant_info.emp_add, '\001',"公司地址");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_app_prim_applicant_info.emp_postcode, '\001',"公司邮编");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_app_prim_applicant_info.emp_phone, '\001',"公司电话");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_app_prim_applicant_info.emp_depapment, '\001',"任职部门");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_app_prim_applicant_info.emp_post, '\001',"职务");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_app_prim_applicant_info.emp_structure, '\001',"公司性质");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_app_prim_applicant_info.emp_type, '\001',"公司行业类别");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_app_prim_applicant_info.emp_workyears, '\001',"本公司工作年限");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_app_prim_applicant_info.corp_fax, '\001',"公司传真");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_app_prim_applicant_info.occupation, '\001',"职业");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_app_prim_applicant_info.title_of_technical, '\001',"职称");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_app_prim_applicant_info.emp_stand_from, '\001',"现单位工作起始年月");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_app_prim_applicant_info.pos_pin_verify_ind, '\001',"是否消费凭密");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_app_prim_applicant_info.photo_use_flag, '\001',"是否彩照卡");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_app_prim_applicant_info.group_num, '\001',"申请团办编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_app_prim_applicant_info.emp_stability, '\001',"工作稳定性");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_app_prim_applicant_info.emp_status, '\001',"是否在职");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_app_prim_applicant_info.pr_of_country, '\001',"是否永久居住");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_app_prim_applicant_info.other_ask, '\001',"预留问题");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_app_prim_applicant_info.other_answer, '\001',"预留答案");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_app_prim_applicant_info.pri_name, '\001',"推荐人姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_app_prim_applicant_info.pri_card_num, '\001',"推荐人卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_app_prim_applicant_info.appno_external, '\001',"申请编号_外部送入");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_app_prim_applicant_info.bank_customer_id, '\001',"行内客户号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_app_prim_applicant_info.ref_contact_id, '\001',"推荐人联系号码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_app_prim_applicant_info.ref_contact_type, '\001',"推荐人联系号码类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_app_prim_applicant_info.pledeg_type, '\001',"押品类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_app_prim_applicant_info.update_user, '\001',"修改人");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_app_prim_applicant_info.create_user, '\001',"创建人");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_app_prim_applicant_info.created_datetime, '\001',"创建时间");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_app_prim_applicant_info.last_modified_datetime, '\001',"最后修改时间");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_app_prim_applicant_info.jpa_version, '\001',"乐观锁");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_app_prim_applicant_info.cust_no, '\001',"客户号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_app_prim_applicant_info.acct_no, '\001',"账户号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 77, sdb_icps_wbc_tm_app_prim_applicant_info.product_cd, '\001',"产品编号");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 78, sdb_icps_wbc_tm_app_prim_applicant_info.open_acc_datetime, '\001',"开户时间");
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_app_prim_applicant_info.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_app_prim_applicant_info.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO", SD_ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO, NUMELE(SD_ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO),
                    &sdb_icps_wbc_tm_app_prim_applicant_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_app_prim_applicant_info.app_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}



/**
 * 账户信息表
 */
int ffunc_parse_wbankcar_file_to_db_tm_account(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_ACCOUNT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_account, 0x00, sizeof(sdb_icps_wbc_tm_account));
            pstrcopy(sdb_icps_wbc_tm_account.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_account.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_account.file_order = rcdCnt;

           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_account.org, '\001',"机构号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_account.acct_no, '\001',"账户编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_account.acct_type, '\001',"账户类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_account.cust_id, '\001',"客户编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_account.cust_limit_id, '\001',"客户额度ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_account.product_cd, '\001',"产品代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_account.default_logical_card_no, '\001',"默认逻辑卡号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_account.curr_cd, '\001',"币种");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_account.credit_limit, '\001',"信用额度");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_account.temp_limit, '\001',"临时额度");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_account.temp_limit_begin_date, '\001',"临时额度开始日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_account.temp_limit_end_date, '\001',"临时额度结束日期");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_account.cash_limit_rt, '\001',"取现额度比例");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_account.ovrlmt_rate, '\001',"授权超限比例");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_account.loan_limit_rt, '\001',"额度内分期额度比例");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_account.curr_bal, '\001',"当前余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_account.cash_bal, '\001',"取现余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_account.principal_bal, '\001',"本金余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_account.loan_bal, '\001',"额度内分期余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_account.dispute_amt, '\001',"争议金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_account.begin_bal, '\001',"期初余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_account.pmt_due_day_bal, '\001',"到期还款日余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_account.qual_grace_bal, '\001',"全部应还款额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_account.grace_days_full_ind, '\001',"是否已全额还款");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_account.point_begin_bal, '\001',"期初积分余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_account.ctd_earned_points, '\001',"当期新增积分");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_account.ctd_disb_points, '\001',"当期兑换积分");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_account.ctd_adj_points, '\001',"当期调整积分");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_account.point_bal, '\001',"积分余额");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_account.setup_date, '\001',"创建日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_account.dorment_date, '\001',"账户睡眠日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_account.reinstate_date, '\001',"账户恢复活动日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_account.ovrlmt_date, '\001',"超限日期");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_account.ovrlmt_nbr_of_cyc, '\001',"连续超限账期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_account.name, '\001',"姓名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_account.gender, '\001',"性别");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_account.owning_branch, '\001',"发卡网点");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_account.mobile_no, '\001',"移动电话");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_account.corp_name, '\001',"公司名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_account.billing_cycle, '\001',"账单周期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_account.stmt_flag, '\001',"账单标志");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_account.stmt_mail_addr_ind, '\001',"账单寄送地址标志");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_account.stmt_media_type, '\001',"账单介质类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_account.stmt_country_cd, '\001',"账单地址国家代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_account.stmt_state, '\001',"账单地址省份");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_account.stmt_city, '\001',"账单地址城市");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_account.stmt_district, '\001',"账单地址行政区");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_account.stmt_address, '\001',"账单地址");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_account.stmt_zip, '\001',"账单地址邮政编码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_account.email, '\001',"电子邮箱");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_account.block_code, '\001',"锁定码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_account.age_cd, '\001',"账龄");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_account.gl_age_cd, '\001',"总账账龄");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_account.unmatch_db, '\001',"未匹配借记金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_account.unmatch_cash, '\001',"未匹配取现金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_account.unmatch_cr, '\001',"未匹配贷记金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_account.dd_ind, '\001',"约定还款类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_account.dd_bank_name, '\001',"约定还款银行名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_account.dd_bank_branch, '\001',"约定还款开户行号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_account.dd_bank_acct_no, '\001',"约定还款扣款账号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_account.dd_bank_acct_name, '\001',"约定还款扣款账户姓名");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_account.last_dd_amt, '\001',"上期约定还款金额");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_account.last_dd_date, '\001',"上期约定还款日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_account.dual_billing_flag, '\001',"本币溢缴款还外币指示");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_account.last_pmt_amt, '\001',"上笔还款金额");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_account.last_pmt_date, '\001',"上个还款日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_account.last_stmt_date, '\001',"上个账单日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_account.last_pmt_due_date, '\001',"上个到期还款日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_account.last_aging_date, '\001',"上个账龄提升日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_account.collect_date, '\001',"入催日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_account.collect_out_date, '\001',"出催收队列日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_account.next_stmt_date, '\001',"下个账单日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_account.pmt_due_date, '\001',"到期还款日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_account.dd_date, '\001',"约定还款日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_account.grace_date, '\001',"宽限日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_account.dlbl_date, '\001',"本币还外币日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 77, sdb_icps_wbc_tm_account.closed_date, '\001',"最终销户日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 78, sdb_icps_wbc_tm_account.first_stmt_date, '\001',"首个账单日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 79, sdb_icps_wbc_tm_account.cancel_date, '\001',"销卡销户日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 80, sdb_icps_wbc_tm_account.charge_off_date, '\001',"转呆账日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 81, sdb_icps_wbc_tm_account.first_purchase_date, '\001',"首次消费日期");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 82, sdb_icps_wbc_tm_account.first_purchase_amt, '\001',"首次消费金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 83, sdb_icps_wbc_tm_account.tot_due_amt, '\001',"最小还款额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 84, sdb_icps_wbc_tm_account.curr_due_amt, '\001',"当期最小还款额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 85, sdb_icps_wbc_tm_account.past_due_amt1, '\001',"上个月最小还款额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 86, sdb_icps_wbc_tm_account.past_due_amt2, '\001',"上2个月最小还款额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wbc_tm_account.past_due_amt3, '\001',"上3个月最小还款额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wbc_tm_account.past_due_amt4, '\001',"上4个月最小还款额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wbc_tm_account.past_due_amt5, '\001',"上5个月最小还款额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 90, sdb_icps_wbc_tm_account.past_due_amt6, '\001',"上6个月最小还款额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 91, sdb_icps_wbc_tm_account.past_due_amt7, '\001',"上7个月最小还款额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 92, sdb_icps_wbc_tm_account.past_due_amt8, '\001',"上8个月最小还款额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 93, sdb_icps_wbc_tm_account.ctd_cash_amt, '\001',"当期取现金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 94, sdb_icps_wbc_tm_account.ctd_cash_cnt, '\001',"当期取现笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 95, sdb_icps_wbc_tm_account.ctd_retail_amt, '\001',"当期消费金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 96, sdb_icps_wbc_tm_account.ctd_retail_cnt, '\001',"当期消费笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 97, sdb_icps_wbc_tm_account.ctd_payment_amt, '\001',"当期还款金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 98, sdb_icps_wbc_tm_account.ctd_payment_cnt, '\001',"当期还款笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 99, sdb_icps_wbc_tm_account.ctd_db_adj_amt, '\001',"当期借记调整金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 100, sdb_icps_wbc_tm_account.ctd_db_adj_cnt, '\001',"当期借记调整笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 101, sdb_icps_wbc_tm_account.ctd_cr_adj_amt, '\001',"当期贷记调整金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 102, sdb_icps_wbc_tm_account.ctd_cr_adj_cnt, '\001',"当期贷记调整笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 103, sdb_icps_wbc_tm_account.ctd_fee_amt, '\001',"当期费用金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 104, sdb_icps_wbc_tm_account.ctd_fee_cnt, '\001',"当期费用笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 105, sdb_icps_wbc_tm_account.ctd_interest_amt, '\001',"当期利息金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 106, sdb_icps_wbc_tm_account.ctd_interest_cnt, '\001',"当期利息笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 107, sdb_icps_wbc_tm_account.ctd_refund_amt, '\001',"当期退货金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 108, sdb_icps_wbc_tm_account.ctd_refund_cnt, '\001',"当期退货笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 109, sdb_icps_wbc_tm_account.ctd_hi_ovrlmt_amt, '\001',"当期最高超限金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 110, sdb_icps_wbc_tm_account.mtd_retail_amt, '\001',"本月消费金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 111, sdb_icps_wbc_tm_account.mtd_retail_cnt, '\001',"本月消费笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 112, sdb_icps_wbc_tm_account.mtd_cash_amt, '\001',"本月取现金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 113, sdb_icps_wbc_tm_account.mtd_cash_cnt, '\001',"本月取现笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 114, sdb_icps_wbc_tm_account.mtd_refund_amt, '\001',"本月退货金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 115, sdb_icps_wbc_tm_account.mtd_refund_cnt, '\001',"本月退货笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 116, sdb_icps_wbc_tm_account.ytd_retail_amt, '\001',"本年消费金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 117, sdb_icps_wbc_tm_account.ytd_retail_cnt, '\001',"本年消费笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 118, sdb_icps_wbc_tm_account.ytd_cash_amt, '\001',"本年取现金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 119, sdb_icps_wbc_tm_account.ytd_cash_cnt, '\001',"本年取现笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 120, sdb_icps_wbc_tm_account.ytd_refund_amt, '\001',"本年退货金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 121, sdb_icps_wbc_tm_account.ytd_refund_cnt, '\001',"本年退货笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 122, sdb_icps_wbc_tm_account.ytd_ovrlmt_fee_amt, '\001',"本年超限费收取金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 123, sdb_icps_wbc_tm_account.ytd_ovrlmt_fee_cnt, '\001',"本年超限费收取笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 124, sdb_icps_wbc_tm_account.ytd_lpc_amt, '\001',"本年滞纳金收取金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 125, sdb_icps_wbc_tm_account.ytd_lpc_cnt, '\001',"本年滞纳金收取笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 126, sdb_icps_wbc_tm_account.ltd_retail_amt, '\001',"历史消费金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 127, sdb_icps_wbc_tm_account.ltd_retail_cnt, '\001',"历史消费笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 128, sdb_icps_wbc_tm_account.ltd_cash_amt, '\001',"历史取现金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 129, sdb_icps_wbc_tm_account.ltd_cash_cnt, '\001',"历史取现笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 130, sdb_icps_wbc_tm_account.ltd_refund_amt, '\001',"历史退货金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 131, sdb_icps_wbc_tm_account.ltd_refund_cnt, '\001',"历史退货笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 132, sdb_icps_wbc_tm_account.ltd_highest_principal, '\001',"历史最高本金欠款");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 133, sdb_icps_wbc_tm_account.ltd_highest_cr_bal, '\001',"历史最高溢缴款");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 134, sdb_icps_wbc_tm_account.ltd_highest_bal, '\001',"历史最高余额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 135, sdb_icps_wbc_tm_account.collect_times, '\001',"入催次数");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 136, sdb_icps_wbc_tm_account.collect_colr, '\001',"催收员代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 137, sdb_icps_wbc_tm_account.collect_reason, '\001',"入催原因");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 138, sdb_icps_wbc_tm_account.age_hist, '\001',"账龄历史信息");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 139, sdb_icps_wbc_tm_account.payment_hist, '\001',"还款历史信息");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 140, sdb_icps_wbc_tm_account.waive_ovlfee_ind, '\001',"是否免除超限费");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 141, sdb_icps_wbc_tm_account.waive_cardfee_ind, '\001',"是否免除年费");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 142, sdb_icps_wbc_tm_account.waive_latefee_ind, '\001',"是否免除滞纳金");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 143, sdb_icps_wbc_tm_account.waive_svcfee_ind, '\001',"是否免除服务费");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 144, sdb_icps_wbc_tm_account.user_code1, '\001',"用户自定义代码1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 145, sdb_icps_wbc_tm_account.user_code2, '\001',"用户自定义代码2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 146, sdb_icps_wbc_tm_account.user_code3, '\001',"用户自定义代码3");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 147, sdb_icps_wbc_tm_account.user_code4, '\001',"用户自定义代码4");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 148, sdb_icps_wbc_tm_account.user_code5, '\001',"用户自定义代码5");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 149, sdb_icps_wbc_tm_account.user_code6, '\001',"用户自定义代码6");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 150, sdb_icps_wbc_tm_account.user_date1, '\001',"用户自定义日期1");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 151, sdb_icps_wbc_tm_account.user_date2, '\001',"上次调额日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 152, sdb_icps_wbc_tm_account.user_date3, '\001',"用户自定义日期3");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 153, sdb_icps_wbc_tm_account.user_date4, '\001',"用户自定义日期4");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 154, sdb_icps_wbc_tm_account.user_date5, '\001',"用户自定义日期5");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 155, sdb_icps_wbc_tm_account.user_date6, '\001',"用户自定义日期6");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 156, sdb_icps_wbc_tm_account.user_number1, '\001',"用户自定义笔数1");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 157, sdb_icps_wbc_tm_account.user_number2, '\001',"用户自定义笔数2");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 158, sdb_icps_wbc_tm_account.user_number3, '\001',"用户自定义笔数3");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 159, sdb_icps_wbc_tm_account.user_number4, '\001',"用户自定义笔数4");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 160, sdb_icps_wbc_tm_account.user_number5, '\001',"用户自定义笔数5");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 161, sdb_icps_wbc_tm_account.user_number6, '\001',"用户自定义笔数6");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 162, sdb_icps_wbc_tm_account.user_field1, '\001',"用户自定义域1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 163, sdb_icps_wbc_tm_account.user_field2, '\001',"用户自定义域2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 164, sdb_icps_wbc_tm_account.user_field3, '\001',"用户自定义域3");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 165, sdb_icps_wbc_tm_account.user_field4, '\001',"用户自定义域4");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 166, sdb_icps_wbc_tm_account.user_field5, '\001',"用户自定义域5");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 167, sdb_icps_wbc_tm_account.user_field6, '\001',"用户自定义域6");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 168, sdb_icps_wbc_tm_account.user_amt1, '\001',"用户自定义金额1");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 169, sdb_icps_wbc_tm_account.user_amt2, '\001',"用户自定义金额2");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 170, sdb_icps_wbc_tm_account.user_amt3, '\001',"用户自定义金额3");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 171, sdb_icps_wbc_tm_account.user_amt4, '\001',"用户自定义金额4");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 172, sdb_icps_wbc_tm_account.user_amt5, '\001',"用户自定义金额5");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 173, sdb_icps_wbc_tm_account.user_amt6, '\001',"昨日贷记卡承诺余额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 174, sdb_icps_wbc_tm_account.jpa_version, '\001',"乐观锁版本号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 175, sdb_icps_wbc_tm_account.mtd_payment_amt, '\001',"当月还款金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 176, sdb_icps_wbc_tm_account.mtd_payment_cnt, '\001',"当月还款笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 177, sdb_icps_wbc_tm_account.ytd_payment_amt, '\001',"当年还款金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 178, sdb_icps_wbc_tm_account.ytd_payment_cnt, '\001',"当年还款笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 179, sdb_icps_wbc_tm_account.ltd_payment_amt, '\001',"历史还款金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 180, sdb_icps_wbc_tm_account.ltd_payment_cnt, '\001',"历史还款笔数");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 181, sdb_icps_wbc_tm_account.sms_ind, '\001',"短信发送标识");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 182, sdb_icps_wbc_tm_account.user_sms_amt, '\001',"个性化动账短信发送阈值");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 183, sdb_icps_wbc_tm_account.ytd_cycle_chag_cnt, '\001',"本年度账单日修改次数");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 184, sdb_icps_wbc_tm_account.last_post_date, '\001',"上个入账日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 185, sdb_icps_wbc_tm_account.last_modified_datetime, '\001',"修改时间");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 186, sdb_icps_wbc_tm_account.lock_date, '\001',"自动锁定日");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 187, sdb_icps_wbc_tm_account.last_sync_date, '\001',"上一次入账的批量日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 188, sdb_icps_wbc_tm_account.created_datetime, '\001',"创建时间");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 189, sdb_icps_wbc_tm_account.delay_bal, '\001',"账户逾期金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 190, sdb_icps_wbc_tm_account.bank_group_id, '\001',"银团编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 191, sdb_icps_wbc_tm_account.customer_type, '\001',"客群分类");


            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_account.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_account.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_ACCOUNT", SD_ICPS_WBC_TM_ACCOUNT, NUMELE(SD_ICPS_WBC_TM_ACCOUNT),
                    &sdb_icps_wbc_tm_account, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tm_account.acct_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}


/**
 * 客户信息表
 */
int ffunc_parse_wbankcar_file_to_db_tm_customer(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_CUSTOMER WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_customer, 0x00, sizeof(sdb_icps_wbc_tm_customer));
            pstrcopy(sdb_icps_wbc_tm_customer.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_customer.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_customer.file_order = rcdCnt;
            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_customer.org, '\001',"机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_customer.cust_id, '\001',"客户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_customer.id_no, '\001',"证件号码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_customer.id_type, '\001',"证件类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_customer.title, '\001',"称谓");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_customer.name, '\001',"姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_customer.gender, '\001',"性别");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_customer.birthday, '\001',"生日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_customer.occupation, '\001',"职业");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_customer.bankmember_no, '\001',"本行员工号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_customer.nationality, '\001',"国籍");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_customer.pr_of_country, '\001',"是否永久居住");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_customer.residency_country_cd, '\001',"永久居住地国家代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_customer.marital_status, '\001',"婚姻状况");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_customer.qualification, '\001',"教育状况");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_customer.social_status, '\001',"风险情况");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_customer.id_issuer_address, '\001',"发证机关所在地址");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_customer.home_phone, '\001',"家庭电话");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_customer.house_ownership, '\001',"房屋持有类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_customer.house_type, '\001',"住宅类型");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_customer.home_stand_from, '\001',"现住址居住起始年月");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_customer.liquid_asset, '\001',"个人资产类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_customer.mobile_no, '\001',"移动电话");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_customer.email, '\001',"电子邮箱");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_customer.emp_status, '\001',"就业状态");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_customer.nbr_of_dependents, '\001',"抚养人数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_customer.language_ind, '\001',"语言代码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_customer.setup_date, '\001',"创建日期");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_customer.social_ins_amt, '\001',"社保缴存金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_customer.drive_license_id, '\001',"驾驶证号码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_customer.drive_lic_reg_date, '\001',"驾驶证登记日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_customer.obligate_question, '\001',"预留问题");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_customer.obligate_answer, '\001',"预留答案");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_customer.emp_stability, '\001',"工作稳定性");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_customer.corp_name, '\001',"公司名称");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_customer.user_code1, '\001',"用户自定义代码1");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_customer.user_code2, '\001',"用户自定义代码2");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_customer.user_code3, '\001',"用户自定义代码3");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_customer.user_code4, '\001',"用户自定义代码4");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_customer.user_code5, '\001',"用户自定义代码5");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_customer.user_code6, '\001',"用户自定义代码6");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_customer.user_date1, '\001',"用户自定义日期1");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_customer.user_date2, '\001',"用户自定义日期2");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_customer.user_date3, '\001',"用户自定义日期3");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_customer.user_date4, '\001',"用户自定义日期4");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_customer.user_date5, '\001',"用户自定义日期5");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_customer.user_date6, '\001',"用户自定义日期6");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_customer.user_number1, '\001',"用户自定义笔数1");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_customer.user_number2, '\001',"用户自定义笔数2");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_customer.user_number3, '\001',"用户自定义笔数3");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_customer.user_number4, '\001',"用户自定义笔数4");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_customer.user_number5, '\001',"用户自定义笔数5");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_customer.user_number6, '\001',"用户自定义笔数6");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_customer.user_field1, '\001',"用户自定义域1");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_customer.user_field2, '\001',"用户自定义域2");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_customer.user_field3, '\001',"用户自定义域3");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_customer.user_field4, '\001',"用户自定义域4");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_customer.user_field5, '\001',"用户自定义域5");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_customer.user_field6, '\001',"用户自定义域6");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_customer.user_amt1, '\001',"用户自定义金额1");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_customer.user_amt2, '\001',"用户自定义金额2");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_customer.user_amt3, '\001',"用户自定义金额3");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_customer.user_amt4, '\001',"用户自定义金额4");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_customer.user_amt5, '\001',"用户自定义金额5");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_customer.user_amt6, '\001',"昨日贷记卡承诺余额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_customer.bank_customer_id, '\001',"行内统一用户号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_customer.emb_name, '\001',"凸印姓名");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_customer.jpa_version, '\001',"乐观锁版本号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_customer.cust_limit_id, '\001',"客户额度ID");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_customer.last_modified_datetime, '\001',"修改时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_customer.cust_level, '\001',"客户等级");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_customer.pledeg_type, '\001',"押品类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_customer.surname, '\001',"姓氏");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_customer.created_datetime, '\001',"创建时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_customer.customer_type, '\001',"客群分类");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_customer.block_code, '\001',"锁定码");


            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_customer.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_customer.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_CUSTOMER", SD_ICPS_WBC_TM_CUSTOMER, NUMELE(SD_ICPS_WBC_TM_CUSTOMER),
                    &sdb_icps_wbc_tm_customer, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tm_customer.cust_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
} 


/**
 * 信用计划表
 */
int ffunc_parse_wbankcar_file_to_db_tm_plan(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_PLAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_plan, 0x00, sizeof(sdb_icps_wbc_tm_plan));
            pstrcopy(sdb_icps_wbc_tm_plan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_plan.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_plan.file_order = rcdCnt;    
            
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_plan.org, '\001',"机构号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_plan.plan_id, '\001',"信用计划ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_plan.acct_no, '\001',"账户编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_plan.acct_type, '\001',"账户类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_plan.logical_card_no, '\001',"逻辑卡号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_plan.plan_nbr, '\001',"信用计划号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_plan.plan_type, '\001',"信用计划类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_plan.product_cd, '\001',"产品代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_plan.ref_nbr, '\001',"交易参考号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_plan.curr_bal, '\001',"当前余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_plan.begin_bal, '\001',"期初余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_plan.dispute_amt, '\001',"争议金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_plan.tot_due_amt, '\001',"最小还款额");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_plan.plan_add_date, '\001',"信用计划建立日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_plan.paid_out_date, '\001',"还清日期");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_plan.past_principal, '\001',"已出账单本金");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_plan.past_interest, '\001',"已出账单利息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_plan.past_card_fee, '\001',"已出账单年费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_plan.past_ovrlmt_fee, '\001',"已出账单超限费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_plan.past_lpc, '\001',"已出账单滞纳金");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_plan.past_nsf_fee, '\001',"已出账单资金不足费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_plan.past_txn_fee, '\001',"已出账单交易费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_plan.past_svc_fee, '\001',"已出账单服务费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_plan.past_ins, '\001',"已出账单保险金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_plan.past_user_fee1, '\001',"已出账单自定义费用1");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_plan.past_user_fee2, '\001',"已出账单自定义费用2");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_plan.past_user_fee3, '\001',"已出账单自定义费用3");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_plan.past_user_fee4, '\001',"已出账单自定义费用4");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_plan.past_user_fee5, '\001',"已出账单自定义费用5");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_plan.past_user_fee6, '\001',"已出账单自定义费用6");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_plan.ctd_principal, '\001',"当期本金");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_plan.ctd_interest, '\001',"当期利息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_plan.ctd_card_fee, '\001',"当期年费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_plan.ctd_ovrlmt_fee, '\001',"当期超限费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_plan.ctd_lpc, '\001',"当期滞纳金");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_plan.ctd_nsf_fee, '\001',"当期资金不足费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_plan.ctd_svc_fee, '\001',"当期服务费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_plan.ctd_txn_fee, '\001',"当期交易费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_plan.ctd_ins, '\001',"当期保险金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_plan.ctd_user_fee1, '\001',"当期新增自定义费用1");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_plan.ctd_user_fee2, '\001',"当期新增自定义费用2");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_plan.ctd_user_fee3, '\001',"当期新增自定义费用3");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_plan.ctd_user_fee4, '\001',"当期新增自定义费用4");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_plan.ctd_user_fee5, '\001',"当期新增自定义费用5");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_plan.ctd_user_fee6, '\001',"当期新增自定义费用6");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_plan.ctd_amt_db, '\001',"当期借记金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_plan.ctd_amt_cr, '\001',"当期贷记金额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_plan.ctd_nbr_db, '\001',"当期借记交易笔数");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_plan.ctd_nbr_cr, '\001',"当期贷记交易笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_plan.nodefbnp_int_acru, '\001',"非延迟利息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_plan.beg_defbnp_int_acru, '\001',"往期累积延时利息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_plan.ctd_defbnp_int_acru, '\001',"当期累积延时利息");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_plan.user_code1, '\001',"用户自定义代码1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_plan.user_code2, '\001',"用户自定义代码2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_plan.user_code3, '\001',"用户自定义代码3");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_plan.user_code4, '\001',"用户自定义代码4");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_plan.user_code5, '\001',"用户自定义代码5");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_plan.user_code6, '\001',"用户自定义代码6");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_plan.user_number1, '\001',"用户自定义笔数1");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_plan.user_number2, '\001',"用户自定义笔数2");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_plan.user_number3, '\001',"用户自定义笔数3");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_plan.user_number4, '\001',"用户自定义笔数4");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_plan.user_number5, '\001',"用户自定义笔数5");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_plan.user_number6, '\001',"用户自定义笔数6");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_plan.user_field1, '\001',"用户自定义域1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_plan.user_field2, '\001',"用户自定义域2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_plan.user_field3, '\001',"用户自定义域3");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_plan.user_field4, '\001',"用户自定义域4");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_plan.user_field5, '\001',"用户自定义域5");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_plan.user_field6, '\001',"用户自定义域6");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_plan.user_date1, '\001',"用户自定义日期1");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_plan.user_date2, '\001',"用户自定义日期2");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_plan.user_date3, '\001',"用户自定义日期3");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_plan.user_date4, '\001',"用户自定义日期4");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_plan.user_date5, '\001',"用户自定义日期5");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_plan.user_date6, '\001',"用户自定义日期6");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 77, sdb_icps_wbc_tm_plan.user_amt1, '\001',"用户自定义金额1");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 78, sdb_icps_wbc_tm_plan.user_amt2, '\001',"用户自定义金额2");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 79, sdb_icps_wbc_tm_plan.user_amt3, '\001',"用户自定义金额3");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 80, sdb_icps_wbc_tm_plan.user_amt4, '\001',"用户自定义金额4");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 81, sdb_icps_wbc_tm_plan.user_amt5, '\001',"用户自定义金额5");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 82, sdb_icps_wbc_tm_plan.user_amt6, '\001',"昨日贷记卡承诺余额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 83, sdb_icps_wbc_tm_plan.jpa_version, '\001',"乐观锁版本号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 84, sdb_icps_wbc_tm_plan.past_penalty, '\001',"往期罚息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 85, sdb_icps_wbc_tm_plan.ctd_penalty, '\001',"当期罚息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 86, sdb_icps_wbc_tm_plan.past_compound, '\001',"往期复利");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wbc_tm_plan.ctd_compound, '\001',"当期复利");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wbc_tm_plan.penalty_acru, '\001',"罚息累计");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wbc_tm_plan.compound_acru, '\001',"复利累计");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 90, sdb_icps_wbc_tm_plan.interest_rate, '\001',"基础利率");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 91, sdb_icps_wbc_tm_plan.penalty_rate, '\001',"罚息利率");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 92, sdb_icps_wbc_tm_plan.compound_rate, '\001',"复利利率");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 93, sdb_icps_wbc_tm_plan.use_plan_rate, '\001',"是否使用plan的利率");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 94, sdb_icps_wbc_tm_plan.last_pmt_date, '\001',"上一还款日期");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 95, sdb_icps_wbc_tm_plan.term, '\001',"所在分期期数");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 96, sdb_icps_wbc_tm_plan.calc_type, '\001',"计费类型");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 97, sdb_icps_wbc_tm_plan.calc_cycle, '\001',"计费周期");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 98, sdb_icps_wbc_tm_plan.fee_rate, '\001',"费率");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 99, sdb_icps_wbc_tm_plan.last_fee_date, '\001',"上一收费日");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 100, sdb_icps_wbc_tm_plan.next_fee_date, '\001',"下一收费日");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 101, sdb_icps_wbc_tm_plan.txn_seq, '\001',"交易流水号");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 102, sdb_icps_wbc_tm_plan.first_dd_date, '\001',"首次约定还款日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 103, sdb_icps_wbc_tm_plan.consumer_trans_id, '\001',"业务流水号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 104, sdb_icps_wbc_tm_plan.sys_trans_id, '\001',"系统调用流水号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 105, sdb_icps_wbc_tm_plan.qchannel_id, '\001',"渠道编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 106, sdb_icps_wbc_tm_plan.sub_terminal_type, '\001',"终端类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 107, sdb_icps_wbc_tm_plan.sub_merch_id, '\001',"二级商户编码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 108, sdb_icps_wbc_tm_plan.sub_merch_name, '\001',"二级商户名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 109, sdb_icps_wbc_tm_plan.wares_desc, '\001',"商品信息");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 110, sdb_icps_wbc_tm_plan.last_modified_datetime, '\001',"修改时间");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 111, sdb_icps_wbc_tm_plan.original_amt, '\001',"原始交易本金");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 112, sdb_icps_wbc_tm_plan.interest_calc_base, '\001',"计息基数");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 113, sdb_icps_wbc_tm_plan.created_datetime, '\001',"创建时间");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_plan.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_plan.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_PLAN", SD_ICPS_WBC_TM_PLAN, NUMELE(SD_ICPS_WBC_TM_PLAN),
                    &sdb_icps_wbc_tm_plan, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tm_plan.acct_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
} 

/**
 * 当日入账交易表
 */
int ffunc_parse_wbankcar_file_to_db_tt_txn_post(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TT_TXN_POST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tt_txn_post, 0x00, sizeof(sdb_icps_wbc_tt_txn_post));
            pstrcopy(sdb_icps_wbc_tt_txn_post.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tt_txn_post.busi_date)); /*业务日期*/
            sdb_icps_wbc_tt_txn_post.file_order = rcdCnt;  
            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tt_txn_post.org, '\001',"机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tt_txn_post.txn_seq, '\001',"交易流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tt_txn_post.acct_no, '\001',"账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tt_txn_post.acct_type, '\001',"账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tt_txn_post.card_no, '\001',"卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tt_txn_post.logical_card_no, '\001',"逻辑卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tt_txn_post.bsc_logiccard_no, '\001',"逻辑卡主卡卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tt_txn_post.product_cd, '\001',"产品代码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tt_txn_post.txn_date, '\001',"交易日期");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tt_txn_post.txn_time, '\001',"交易时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tt_txn_post.post_txn_type, '\001',"入账交易类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tt_txn_post.txn_code, '\001',"交易码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tt_txn_post.db_cr_ind, '\001',"借贷标志");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tt_txn_post.txn_amt, '\001',"交易金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tt_txn_post.post_amt, '\001',"入账币种金额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tt_txn_post.post_date, '\001',"入账日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tt_txn_post.auth_code, '\001',"授权码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tt_txn_post.card_block_code, '\001',"卡片锁定码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tt_txn_post.txn_curr_cd, '\001',"交易币种代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tt_txn_post.post_curr_cd, '\001',"入账币种代码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tt_txn_post.orig_trans_date, '\001',"原始交易日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tt_txn_post.plan_nbr, '\001',"信用计划号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tt_txn_post.ref_nbr, '\001',"交易参考号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tt_txn_post.txn_desc, '\001',"交易描述");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tt_txn_post.txn_short_desc, '\001',"账单交易描述");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tt_txn_post.point, '\001',"积分数值");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tt_txn_post.posting_flag, '\001',"入账结果标示码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tt_txn_post.pre_posting_flag, '\001',"往日入账结果标示码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tt_txn_post.rel_pmt_amt, '\001',"公司卡还款金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tt_txn_post.orig_pmt_amt, '\001',"还款交易原始金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tt_txn_post.acq_branch_id, '\001',"受理分行代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tt_txn_post.acq_terminal_id, '\001',"受理机构终端标识码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tt_txn_post.acq_acceptor_id, '\001',"受卡方标识码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tt_txn_post.acq_name_addr, '\001',"受理机构名称地址");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tt_txn_post.mcc, '\001',"商户类别代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tt_txn_post.input_txn_code, '\001',"原交易交易码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tt_txn_post.input_txn_amt, '\001',"原交易交易金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tt_txn_post.input_sett_amt, '\001',"原交易清算金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tt_txn_post.interchange_fee, '\001',"原交易货币转换费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tt_txn_post.fee_payout, '\001',"发卡方应付手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tt_txn_post.fee_profit, '\001',"发卡方应得手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tt_txn_post.loan_issue_profit, '\001',"分期交易发卡行收益");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tt_txn_post.stmt_date, '\001',"账单日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tt_txn_post.voucher_no, '\001',"销售单凭证号");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tt_txn_post.jpa_version, '\001',"乐观锁版本号");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tt_txn_post.term, '\001',"所在分期期数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tt_txn_post.consumer_trans_id, '\001',"业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tt_txn_post.sys_trans_id, '\001',"系统调用流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tt_txn_post.qchannel_id, '\001',"渠道编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tt_txn_post.sub_terminal_type, '\001',"终端类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tt_txn_post.sub_merch_id, '\001',"二级商户编码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tt_txn_post.sub_merch_name, '\001',"二级商户名称");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tt_txn_post.wares_desc, '\001',"商品信息");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tt_txn_post.last_modified_datetime, '\001',"修改时间");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tt_txn_post.paid_stmt_date, '\001',"还款账单日");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tt_txn_post.repay_amt, '\001',"应还款额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tt_txn_post.counter_acct, '\001',"对手方账户");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tt_txn_post.counter_name, '\001',"对手方姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tt_txn_post.counter_brno, '\001',"对手方行号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tt_txn_post.counter_brname, '\001',"对手方行名");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tt_txn_post.is_check_flag, "1", sizeof(sdb_icps_wbc_tt_txn_post.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TT_TXN_POST", SD_ICPS_WBC_TT_TXN_POST, NUMELE(SD_ICPS_WBC_TT_TXN_POST),
                    &sdb_icps_wbc_tt_txn_post, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tt_txn_post.txn_seq), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
} 

/**
 * 分期信息表
 */
int ffunc_parse_wbankcar_file_to_db_tm_loan(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_LOAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_loan, 0x00, sizeof(sdb_icps_wbc_tm_loan));
            pstrcopy(sdb_icps_wbc_tm_loan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_loan.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_loan.file_order = rcdCnt;
              
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_loan.org, '\001',"机构号");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_loan.loan_id, '\001',"分期计划ID");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_loan.acct_no, '\001',"账户编号");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_loan.acct_type, '\001',"账户类型");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_loan.ref_nbr, '\001',"交易参考号");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_loan.logical_card_no, '\001',"逻辑卡号");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_loan.card_no, '\001',"卡号");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_loan.register_date, '\001',"分期注册日期");
          ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_loan.request_time, '\001',"请求日期时间");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_loan.loan_type, '\001',"分期类型");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_loan.loan_status, '\001',"分期状态");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_loan.last_loan_status, '\001',"分期上次状态");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_loan.loan_init_term, '\001',"分期总期数");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_loan.curr_term, '\001',"当前期数");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_loan.remain_term, '\001',"剩余期数");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_loan.loan_init_prin, '\001',"分期总本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_loan.loan_fixed_pmt_prin, '\001',"分期每期应还本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_loan.loan_first_term_prin, '\001',"分期首期应还本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_loan.loan_final_term_prin, '\001',"分期末期应还本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_loan.loan_init_fee1, '\001',"分期总手续费");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_loan.loan_fixed_fee1, '\001',"分期每期手续费");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_loan.loan_first_term_fee1, '\001',"分期首期手续费");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_loan.loan_final_term_fee1, '\001',"分期末期手续费");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_loan.unearned_prin, '\001',"未出账单的本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_loan.unearned_fee1, '\001',"未出账单手续费");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_loan.paid_out_date, '\001',"还清日期");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_loan.terminate_date, '\001',"提前终止日期");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_loan.terminate_reason_cd, '\001',"分期终止原因代码");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_loan.prin_paid, '\001',"已偿还本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_loan.int_paid, '\001',"已偿还利息");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_loan.fee_paid, '\001',"已偿还费用");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_loan.loan_curr_bal, '\001',"分期当前总余额");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_loan.loan_bal_xfrout, '\001',"分期未到期余额");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_loan.loan_bal_xfrin, '\001',"分期已出账单余额");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_loan.loan_bal_principal, '\001',"欠款总本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_loan.loan_bal_interest, '\001',"欠款总利息");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_loan.loan_bal_penalty, '\001',"欠款总罚息");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_loan.loan_prin_xfrout, '\001',"分期未到期本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_loan.loan_prin_xfrin, '\001',"分期已出账单本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_loan.loan_fee1_xfrout, '\001',"分期未到期手续费");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_loan.loan_fee1_xfrin, '\001',"分期已出账单手续费");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_loan.orig_txn_amt, '\001',"原始交易币种金额");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_loan.orig_trans_date, '\001',"原始交易日期");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_loan.orig_auth_code, '\001',"原始交易授权码");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_loan.jpa_version, '\001',"乐观锁版本号");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_loan.loan_code, '\001',"分期计划代码");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_loan.register_id, '\001',"分期申请顺序号");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_loan.resch_init_prin, '\001',"展期本金金额");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_loan.resch_date, '\001',"展期生效日期");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_loan.bef_resch_fixed_pmt_prin, '\001',"展期前每期应还本金");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_loan.bef_resch_init_term, '\001',"展期前总期数");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_loan.bef_resch_first_term_prin, '\001',"展期前分期首期应还本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_loan.bef_resch_final_term_prin, '\001',"展期前分期末期应还本金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_loan.bef_resch_init_fee1, '\001',"展期前分期总手续费");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_loan.bef_resch_fixed_fee1, '\001',"分期每期手续费");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_loan.bef_resch_first_term_fee1, '\001',"展期前分期首期手续费");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_loan.bef_resch_final_term_fee1, '\001',"展期前分期末期手续费");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_loan.resch_first_term_fee1, '\001',"展期后首期手续费");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_loan.loan_fee_method, '\001',"分期手续费收取方式");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_loan.interest_rate, '\001',"基础利率");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_loan.penalty_rate, '\001',"罚息利率");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_loan.compound_rate, '\001',"复利利率");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_loan.float_rate, '\001',"浮动比例");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_loan.loan_receipt_nbr, '\001',"借据号");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_loan.loan_expire_date, '\001',"贷款到期日期");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_loan.loan_cd, '\001',"贷款逾期最大期数");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_loan.payment_hist, '\001',"24个月还款状态");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_loan.ctd_payment_amt, '\001',"当期还款额");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_loan.past_resch_cnt, '\001',"已展期次数");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_loan.past_shorted_cnt, '\001',"已缩期次数");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_loan.adv_pmt_amt, '\001',"提前还款金额");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_loan.last_action_date, '\001',"上次行动日期");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_loan.last_action_type, '\001',"上次行动类型");
          ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_loan.last_modified_datetime, '\001',"修改时间");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_loan.activate_date, '\001',"激活日期");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_loan.interest_calc_base, '\001',"计息基数");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 77, sdb_icps_wbc_tm_loan.first_bill_date, '\001',"首个账单日");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 78, sdb_icps_wbc_tm_loan.age_cd, '\001',"账龄");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 79, sdb_icps_wbc_tm_loan.recalc_ind, '\001',"利率重算标志");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 80, sdb_icps_wbc_tm_loan.recalc_date, '\001',"利率重算日");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 81, sdb_icps_wbc_tm_loan.grace_date, '\001',"宽限日期");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 82, sdb_icps_wbc_tm_loan.cancel_date, '\001',"撤销日期");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 83, sdb_icps_wbc_tm_loan.cancel_reason, '\001',"贷款撤销原因");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 84, sdb_icps_wbc_tm_loan.bank_group_id, '\001',"银团编号");
          ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 85, sdb_icps_wbc_tm_loan.due_days, '\001',"当前逾期天数");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 86, sdb_icps_wbc_tm_loan.contract_ver, '\001',"合同版本号");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wbc_tm_loan.loan_init_interest, '\001',"贷款总利息");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wbc_tm_loan.bef_init_interest, '\001',"原贷款总利息");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wbc_tm_loan.penalty_paid , '\001',"已还罚息");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 90, sdb_icps_wbc_tm_loan.compound_paid, '\001',"已还复利");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 91, sdb_icps_wbc_tm_loan.late_charge_paid, '\001',"已还滞纳金");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 92, sdb_icps_wbc_tm_loan.loan_bal_late_charge, '\001',"欠款总滞纳金");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 93, sdb_icps_wbc_tm_loan.next_xfr_date, '\001',"下一结转日");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 94, sdb_icps_wbc_tm_loan.next_late_charge_date, '\001',"下一滞纳金收取日");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 95, sdb_icps_wbc_tm_loan.fee_rate, '\001',"费率");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 96, sdb_icps_wbc_tm_loan.late_charge_fee_rate, '\001',"滞纳金费率");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 97, sdb_icps_wbc_tm_loan.adv_pmt_fee_rate, '\001',"提前还款手续费费率");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 98, sdb_icps_wbc_tm_loan.loan_bal_adv_pmt_fee, '\001',"提前还款手续费总欠款");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 99, sdb_icps_wbc_tm_loan.adv_pmt_fee_paid, '\001',"已还提前还款手续费");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 100, sdb_icps_wbc_tm_loan.last_xfr_date, '\001',"上一结转日期");
          ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 101, sdb_icps_wbc_tm_loan.loan_bal_fee, '\001',"欠款总费用");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 102, sdb_icps_wbc_tm_loan.payee_card_no, '\001',"收款卡号");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 103, sdb_icps_wbc_tm_loan.payee_bank_name, '\001',"收款行名称");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 104, sdb_icps_wbc_tm_loan.billing_cycle, '\001',"账单日");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 105, sdb_icps_wbc_tm_loan.last_stmt_date, '\001',"上个账单日期");
          ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 106, sdb_icps_wbc_tm_loan.next_stmt_date, '\001',"下个账单日期");

            

            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_loan.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_loan.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_LOAN", SD_ICPS_WBC_TM_LOAN, NUMELE(SD_ICPS_WBC_TM_LOAN),
                    &sdb_icps_wbc_tm_loan, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tm_loan.loan_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
} 


/**
 * 贷款分配表
 */
int ffunc_parse_wbankcar_file_to_db_tm_schedule(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_SCHEDULE WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_schedule, 0x00, sizeof(sdb_icps_wbc_tm_schedule));
            pstrcopy(sdb_icps_wbc_tm_schedule.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_schedule.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_schedule.file_order = rcdCnt;
            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_schedule.schedule_id, '\001',"分配表ID");                 
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_schedule.loan_id, '\001',"分期计划ID");                   
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_schedule.org, '\001',"机构号");                            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_schedule.acct_no, '\001',"账户编号");                     
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_schedule.acct_type, '\001',"账户类型");                    
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_schedule.logical_card_no, '\001',"逻辑卡号");              
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_schedule.card_no, '\001',"卡号");                          
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_schedule.loan_init_prin, '\001',"分期总本金");             
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_schedule.loan_init_term, '\001',"分期总期数");            
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_schedule.curr_term, '\001',"当前期数");                  
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_schedule.loan_term_prin, '\001',"应还本金");              
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_schedule.loan_term_fee1, '\001',"应还费用");              
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_schedule.loan_term_interest, '\001',"应还利息");          
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_schedule.loan_pmt_due_date, '\001',"到款到期还款日期");     
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_schedule.loan_grace_date, '\001',"宽限日");                 
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_schedule.last_modified_datetime, '\001',"修改时间");   
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_schedule.start_date, '\001',"起息日");                      
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_schedule.schedule_action, '\001',"还款计划操作动作");     
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_schedule.prin_paid, '\001',"已偿还本金");                 
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_schedule.int_paid, '\001',"已偿还利息");                  
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_schedule.penalty_paid, '\001',"已偿还罚息");              
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_schedule.compound_paid, '\001',"已偿还复利");             
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_schedule.fee_paid, '\001',"已偿还费用");                  
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_schedule.late_charge_paid, '\001',"已偿还滞纳金");        
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_schedule.adv_pmt_fee_paid, '\001',"已偿还提前还款手续费");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_schedule.paid_out_date, '\001',"还清日期");                 

            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_schedule.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_schedule.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_SCHEDULE", SD_ICPS_WBC_TM_SCHEDULE, NUMELE(SD_ICPS_WBC_TM_SCHEDULE),
                    &sdb_icps_wbc_tm_schedule, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tm_schedule.schedule_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
} 

/**
 * 自定义额度信息表-授权
 */
int ffunc_parse_wbankcar_file_to_db_tm_cust_limit_o(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_CUST_LIMIT_O WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_cust_limit_o, 0x00, sizeof(sdb_icps_wbc_tm_cust_limit_o));
            pstrcopy(sdb_icps_wbc_tm_cust_limit_o.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_cust_limit_o.busi_date)); /*业务日期*/           
            sdb_icps_wbc_tm_cust_limit_o.file_order = rcdCnt;
            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_cust_limit_o.org, '\001',"机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_cust_limit_o.cust_limit_id, '\001',"客户额度ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_cust_limit_o.limit_category, '\001',"额度种类");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_cust_limit_o.limit_type, '\001',"额度类型");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_cust_limit_o.credit_limit, '\001',"信用额度");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_cust_limit_o.jpa_version, '\001',"乐观锁版本号");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_cust_limit_o.last_modified_datetime, '\001',"修改时间");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_cust_limit_o.created_datetime, '\001',"创建时间");

       
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_cust_limit_o.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_cust_limit_o.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_CUST_LIMIT_O", SD_ICPS_WBC_TM_CUST_LIMIT_O, NUMELE(SD_ICPS_WBC_TM_CUST_LIMIT_O),
                    &sdb_icps_wbc_tm_cust_limit_o, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tm_cust_limit_o.cust_limit_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
} 
/*
*授权交易历史
*/
int ffunc_parse_wbankcar_file_to_db_tm_auth_hst(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_AUTH_HST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        LOG(LM_STD, Fmtmsg("fp_check[%p]", fp_check), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("errno[%s]",strerror(errno)), "INFO");
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_auth_hst, 0x00, sizeof(sdb_icps_wbc_tm_auth_hst));
            pstrcopy(sdb_icps_wbc_tm_auth_hst.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wbc_tm_auth_hst.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_auth_hst.file_order = rcdCnt;   
            
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_auth_hst.org, '\001',"机构号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_auth_hst.log_kv, '\001',"LOG的键值");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_auth_hst.acct_no, '\001',"账户编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_auth_hst.acct_type, '\001',"账户类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_auth_hst.logical_card_no, '\001',"逻辑卡号");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_auth_hst.acq_ref_no, '\001',"受理机构交易编码");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_auth_hst.txn_amt, '\001',"交易金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_auth_hst.txn_curr_cd, '\001',"交易币种代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_auth_hst.auth_code, '\001',"授权码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_auth_hst.acq_name_addr, '\001',"受理机构名称地址");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_auth_hst.chb_txn_amt, '\001',"持卡人账户币种金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_auth_hst.chb_curr_cd, '\001',"持卡人账户币种");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_auth_hst.channel, '\001',"交易渠道");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_auth_hst.mcc, '\001',"商户类别代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_auth_hst.acq_branch_id, '\001',"受理分行代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_auth_hst.fwd_inst_id, '\001',"转发机构号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_auth_hst.transmission_timestamp, '\001',"传送日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_auth_hst.settle_date, '\001',"清算日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_auth_hst.txn_direction, '\001',"交易方向");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_auth_hst.txn_terminal, '\001',"交易终端");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_auth_hst.txn_status, '\001',"交易状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_auth_hst.txn_type, '\001',"交易类型");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_auth_hst.log_ol_time, '\001',"LOG联机时间");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_auth_hst.log_biz_date, '\001',"联机业务日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_auth_hst.mti, '\001',"交易类型标识");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_auth_hst.orig_txn_type, '\001',"原交易类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_auth_hst.orig_fwd_inst_id, '\001',"原始转发机构号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_auth_hst.orig_acq_inst_id, '\001',"原始受理机构号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_auth_hst.orig_mti, '\001',"原交易MTI");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_auth_hst.orig_trans_date, '\001',"原始交易日期");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_auth_hst.orig_trace_no, '\001',"原始系统跟踪号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_auth_hst.orig_txn_proc, '\001',"原交易处理码");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_auth_hst.orig_txn_amt, '\001',"原始交易币种金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_auth_hst.orig_log_kv, '\001',"原交易LOG键值");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_auth_hst.orig_txn_val_1, '\001',"原交易键值1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_auth_hst.orig_txn_val_2, '\001',"原交易键值2");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_auth_hst.orig_chb_txn_amt, '\001',"原始入账币种金额");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_auth_hst.orig_biz_date, '\001',"原交易的联机业务处理日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_auth_hst.last_reversal_date, '\001',"最后一次冲撤时间");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_auth_hst.void_count, '\001',"撤销次数");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_auth_hst.manual_auth_flag, '\001',"人工授权标志");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_auth_hst.opera_id, '\001',"操作员ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_auth_hst.brand, '\001',"品牌");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_auth_hst.product_cd, '\001',"产品代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_auth_hst.mcc_type, '\001',"商户类型分组");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_auth_hst.final_reason, '\001',"授权原因");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_auth_hst.final_action, '\001',"最终行动");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_auth_hst.comp_amt, '\001',"最终授权金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_auth_hst.final_upd_direction, '\001',"最终更新方向");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_tm_auth_hst.final_upd_amt, '\001',"最终更新金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_tm_auth_hst.ic_ind, '\001',"是否IC卡");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_tm_auth_hst.the_3dsecure_type, '\001',"是否3D电子安全交易");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_tm_auth_hst.vip_status, '\001',"VIP状态");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_wbc_tm_auth_hst.curr_bal, '\001',"当前余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_wbc_tm_auth_hst.cash_amt, '\001',"取现金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wbc_tm_auth_hst.otb, '\001',"可用额度");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_wbc_tm_auth_hst.cash_otb, '\001',"取现可用额度");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 58, sdb_icps_wbc_tm_auth_hst.cust_otb, '\001',"客户可用额度");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wbc_tm_auth_hst.card_black_flag, '\001',"是否账户黑名单");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wbc_tm_auth_hst.merchant_black_flag, '\001',"是否商户黑名单");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_wbc_tm_auth_hst.expire_date, '\001',"有效日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 62, sdb_icps_wbc_tm_auth_hst.track_one_result, '\001',"一磁道完整性结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 63, sdb_icps_wbc_tm_auth_hst.track_two_result, '\001',"二磁道完整性结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wbc_tm_auth_hst.track_three_result, '\001',"三磁道完整性结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_wbc_tm_auth_hst.pwd_type, '\001',"密码种类");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wbc_tm_auth_hst.check_pwd_result, '\001',"验证密码结果");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 67, sdb_icps_wbc_tm_auth_hst.pay_pwd_err_num, '\001',"支付密码错误次数");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_wbc_tm_auth_hst.check_cvv_result, '\001',"CVV验证结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wbc_tm_auth_hst.check_cvv2_result, '\001',"CVV2验证结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_wbc_tm_auth_hst.check_icvn_result, '\001',"ICVN验证结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wbc_tm_auth_hst.check_arqc_result, '\001',"ARQC验证结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 72, sdb_icps_wbc_tm_auth_hst.check_atc_result, '\001',"ATC验证结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wbc_tm_auth_hst.check_cvr_result, '\001',"CVR验证结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 74, sdb_icps_wbc_tm_auth_hst.check_tvr_result, '\001',"TVR验证结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wbc_tm_auth_hst.rej_reason, '\001',"拒绝原因");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 76, sdb_icps_wbc_tm_auth_hst.unmatch_cr, '\001',"未匹配贷记金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 77, sdb_icps_wbc_tm_auth_hst.unmatch_db, '\001',"未匹配借记金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 78, sdb_icps_wbc_tm_auth_hst.b002, '\001',"介质卡号-B002");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 79, sdb_icps_wbc_tm_auth_hst.b003, '\001',"交易处理码-B003");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 80, sdb_icps_wbc_tm_auth_hst.b007, '\001',"交易传输时间-B007");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 81, sdb_icps_wbc_tm_auth_hst.b011, '\001',"系统跟踪号-B011");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 82, sdb_icps_wbc_tm_auth_hst.b022, '\001',"服务点PIN获取码-B022");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 83, sdb_icps_wbc_tm_auth_hst.b025, '\001',"服务点条件码-B025");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 84, sdb_icps_wbc_tm_auth_hst.b032, '\001',"受理机构标识码-B032");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 85, sdb_icps_wbc_tm_auth_hst.b033, '\001',"受理机构名称地址-B033");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 86, sdb_icps_wbc_tm_auth_hst.b039, '\001',"返回码-B039");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 87, sdb_icps_wbc_tm_auth_hst.b042, '\001',"受卡方(商户)标识码-B042");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 88, sdb_icps_wbc_tm_auth_hst.b060, '\001',"自定义域-B060");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 89, sdb_icps_wbc_tm_auth_hst.b061, '\001',"持卡人身份认证信息-B061");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 90, sdb_icps_wbc_tm_auth_hst.b090, '\001',"原始数据元");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 91, sdb_icps_wbc_tm_auth_hst.opera_term_id, '\001',"操作用户终端编号");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 92, sdb_icps_wbc_tm_auth_hst.jpa_version, '\001',"乐观锁版本号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 93, sdb_icps_wbc_tm_auth_hst.b004, '\001',"交易货币金额-B004");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 94, sdb_icps_wbc_tm_auth_hst.b006, '\001',"账户货币金额-B006");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 95, sdb_icps_wbc_tm_auth_hst.b049, '\001',"交易货币代码-B049");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 96, sdb_icps_wbc_tm_auth_hst.b051, '\001',"账户货币代码-B051");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 97, sdb_icps_wbc_tm_auth_hst.b037, '\001',"检索参考号-B037");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 98, sdb_icps_wbc_tm_auth_hst.b028, '\001',"手续费-B028");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 99, sdb_icps_wbc_tm_auth_hst.b048, '\001',"附加数据-B048");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 100, sdb_icps_wbc_tm_auth_hst.b054, '\001',"返回余额数组-B054");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 101, sdb_icps_wbc_tm_auth_hst.card_block_code, '\001',"卡片锁定码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 102, sdb_icps_wbc_tm_auth_hst.account_block_code, '\001',"帐户锁定码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 103, sdb_icps_wbc_tm_auth_hst.medium_block_code, '\001',"介质锁定码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 104, sdb_icps_wbc_tm_auth_hst.consumer_trans_id, '\001',"业务流水号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 105, sdb_icps_wbc_tm_auth_hst.sys_trans_id, '\001',"系统调用流水号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 106, sdb_icps_wbc_tm_auth_hst.qchannel_id, '\001',"渠道编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 107, sdb_icps_wbc_tm_auth_hst.sub_terminal_type, '\001',"终端类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 108, sdb_icps_wbc_tm_auth_hst.sub_merch_id, '\001',"二级商户编码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 109, sdb_icps_wbc_tm_auth_hst.sub_merch_name, '\001',"二级商户名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 110, sdb_icps_wbc_tm_auth_hst.wares_desc, '\001',"商品信息");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 111, sdb_icps_wbc_tm_auth_hst.last_modified_datetime, '\001',"修改时间");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 112, sdb_icps_wbc_tm_auth_hst.part_month, '\001',"分区用的月份");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 113, sdb_icps_wbc_tm_auth_hst.paid_stmt_date, '\001',"还款账单日");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 114, sdb_icps_wbc_tm_auth_hst.repay_amt, '\001',"应还款额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 115, sdb_icps_wbc_tm_auth_hst.transfer_type, '\001',"转账类型");


       
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_auth_hst.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_auth_hst.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AUTH_HST", SD_ICPS_WBC_TM_AUTH_HST, NUMELE(SD_ICPS_WBC_TM_AUTH_HST),
                    &sdb_icps_wbc_tm_auth_hst, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tm_auth_hst.log_kv), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    return 0;
} 

/**
 *授权流水银团拆分表
 */
int ffunc_parse_wbankcar_file_to_db_tm_auth_bank_cost(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_tm_auth_bank_cost WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_auth_bank_cost, 0x00, sizeof(sdb_icps_wbc_tm_auth_bank_cost));
            pstrcopy(sdb_icps_wbc_tm_auth_bank_cost.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_auth_bank_cost.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_auth_bank_cost.file_order = rcdCnt;     
            
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_auth_bank_cost.consumer_trans_id, '\001',"业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_auth_bank_cost.bank_group_id, '\001',"银团编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_auth_bank_cost.bank_no, '\001',"银行号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_auth_bank_cost.reg_type, '\001',"登记类型");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_auth_bank_cost.reg_amt, '\001',"登记金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_auth_bank_cost.reg_status, '\001',"登记状态");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_auth_bank_cost.biz_date, '\001',"业务日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_auth_bank_cost.reg_sys_id, '\001',"记账流水号");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_auth_bank_cost.reg_date, '\001',"记账日期");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_auth_bank_cost.reg_time, '\001',"记账请求时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_auth_bank_cost.recon_code, '\001',"对账码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_auth_bank_cost.ori_sys_id, '\001',"原记账流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_auth_bank_cost.cust_id, '\001',"客户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_auth_bank_cost.acct_no, '\001',"账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_auth_bank_cost.acct_type, '\001',"账户类型");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_auth_bank_cost.retry, '\001',"尝试次数");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_auth_bank_cost.created_datetime, '\001',"创建时间");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_auth_bank_cost.last_modified_datetime, '\001',"时间戳");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_auth_bank_cost.jpa_version, '\001',"乐观锁版本号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_auth_bank_cost.card_no, '\001',"卡号");            
        

            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_auth_bank_cost.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_auth_bank_cost.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AUTH_BANK_COST", SD_ICPS_WBC_TM_AUTH_BANK_COST, NUMELE(SD_ICPS_WBC_TM_AUTH_BANK_COST),
                    &sdb_icps_wbc_tm_auth_bank_cost, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_auth_bank_cost.consumer_trans_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}

/**
 *授权流水银团拆分明细表 
 */
int ffunc_parse_wbankcar_file_to_db_tm_auth_bank_cost_dtl(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_AUTH_BANK_COST_DTL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_auth_bank_cost_dtl, 0x00, sizeof(sdb_icps_wbc_tm_auth_bank_cost_dtl));
            pstrcopy(sdb_icps_wbc_tm_auth_bank_cost_dtl.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_auth_bank_cost_dtl.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_auth_bank_cost_dtl.file_order = rcdCnt;
            
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_auth_bank_cost_dtl.consumer_trans_id, '\001',"业务流水号");     
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_auth_bank_cost_dtl.bank_group_id, '\001',"银团编号");           
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_auth_bank_cost_dtl.bank_no, '\001',"银行号");                   
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_auth_bank_cost_dtl.loan_receipt_nbr, '\001',"借据号");          
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_auth_bank_cost_dtl.reg_type, '\001',"登记类型");                
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_auth_bank_cost_dtl.reg_amt, '\001',"登记金额");                 
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_auth_bank_cost_dtl.biz_date, '\001',"业务日期");                  
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_auth_bank_cost_dtl.cust_id, '\001',"客户编号");                
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_auth_bank_cost_dtl.acct_no, '\001',"账户编号");                
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_auth_bank_cost_dtl.acct_type, '\001',"账户类型");              
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_auth_bank_cost_dtl.created_datetime, '\001',"创建时间");    
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_auth_bank_cost_dtl.last_modified_datetime, '\001',"时间戳");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_auth_bank_cost_dtl.card_no, '\001',"卡号");                    
            
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_auth_bank_cost_dtl.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_auth_bank_cost_dtl.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AUTH_BANK_COST_DTL", SD_ICPS_WBC_TM_AUTH_BANK_COST_DTL, NUMELE(SD_ICPS_WBC_TM_AUTH_BANK_COST_DTL),
                    &sdb_icps_wbc_tm_auth_bank_cost_dtl, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_auth_bank_cost_dtl.consumer_trans_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*交易码定义表*/


int ffunc_parse_wbankcar_file_to_db_tm_txn_cd(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_TXN_CD WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_txn_cd, 0x00, sizeof(sdb_icps_wbc_tm_txn_cd));
            pstrcopy(sdb_icps_wbc_tm_txn_cd.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_txn_cd.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_txn_cd.file_order = rcdCnt;   
            
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_txn_cd.flow_no, '\001',"FLOW_NO");   
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_txn_cd.org, '\001',"机构号");         
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_txn_cd.txn_code, '\001',"交易码");    
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_txn_cd.txn_desc, '\001',"交易描述");  
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_txn_cd.txn_class, '\001',"TXN_CLASS");
          ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_txn_cd.bnp, '\001',"余额成分");       
          
          
                        
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_txn_cd.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_txn_cd.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_TXN_CD", SD_ICPS_WBC_TM_TXN_CD, NUMELE(SD_ICPS_WBC_TM_TXN_CD),
                    &sdb_icps_wbc_tm_txn_cd, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tm_txn_cd.flow_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*还款借据清单表*/

int ffunc_parse_wbankcar_file_to_db_tm_loan_receipt_list(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_LOAN_RECEIPT_LIST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_loan_receipt_list, 0x00, sizeof(sdb_icps_wbc_tm_loan_receipt_list));
            pstrcopy(sdb_icps_wbc_tm_loan_receipt_list.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_loan_receipt_list.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_loan_receipt_list.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_loan_receipt_list.consumer_trans_id, '\001',"业务流水号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_loan_receipt_list.sys_trans_id, '\001',"系统调用流水号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_loan_receipt_list.loan_receipt_nbr, '\001',"借据号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_loan_receipt_list.acct_no, '\001',"账户编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_loan_receipt_list.acct_type, '\001',"账户类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_loan_receipt_list.card_no, '\001',"卡号");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_loan_receipt_list.post_date, '\001',"入账日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_loan_receipt_list.last_modified_datetime, '\001',"时间戳");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_loan_receipt_list.pay_amt, '\001',"还款金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_loan_receipt_list.bank_group_id, '\001',"银团编号");

           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_loan_receipt_list.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_loan_receipt_list.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_LOAN_RECEIPT_LIST", SD_ICPS_WBC_TM_LOAN_RECEIPT_LIST, NUMELE(SD_ICPS_WBC_TM_LOAN_RECEIPT_LIST),
                    &sdb_icps_wbc_tm_loan_receipt_list, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_loan_receipt_list.consumer_trans_id), "ERROR");
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
    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*总账会计科目表*/

int ffunc_parse_wbankcar_file_to_db_tm_gl_bal(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_GL_BAL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_gl_bal, 0x00, sizeof(sdb_icps_wbc_tm_gl_bal));
            pstrcopy(sdb_icps_wbc_tm_gl_bal.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_gl_bal.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_gl_bal.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/    
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_gl_bal.org, '\001',"机构号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_gl_bal.subject, '\001',"科目");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_gl_bal.branch_id, '\001',"分支行号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_gl_bal.db_bal, '\001',"借方余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_gl_bal.cr_bal, '\001',"贷方余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_gl_bal.db_amt, '\001',"借方发生额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_gl_bal.db_count, '\001',"借方笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_gl_bal.cr_amt, '\001',"贷方发生额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_gl_bal.cr_count, '\001',"贷方笔数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_gl_bal.last_db_bal, '\001',"昨日借方余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_gl_bal.last_cr_bal, '\001',"昨日贷方余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_gl_bal.last_mth_db_bal, '\001',"上月末借方余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_gl_bal.last_mth_cr_bal, '\001',"上月末贷方余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_gl_bal.last_qtr_db_bal, '\001',"上季末借方余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_gl_bal.last_qtr_cr_bal, '\001',"上季末贷方余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_gl_bal.last_yr_db_bal, '\001',"上年末借方余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_gl_bal.last_yr_cr_bal, '\001',"上年末贷方余额");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_gl_bal.jpa_version, '\001',"乐观锁版本号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_gl_bal.product_cd, '\001',"产品编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_gl_bal.bal_id, '\001',"顺序号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_gl_bal.bank_no, '\001',"银行代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_gl_bal.bank_group_id, '\001',"银团代码");

           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_gl_bal.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_gl_bal.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_GL_BAL", SD_ICPS_WBC_TM_GL_BAL, NUMELE(SD_ICPS_WBC_TM_GL_BAL),
                    &sdb_icps_wbc_tm_gl_bal, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_gl_bal.subject), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*会计分录日报表*/

int ffunc_parse_wbankcar_file_to_db_tm_accounting_flow(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_ACCOUNTING_FLOW WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_accounting_flow, 0x00, sizeof(sdb_icps_wbc_tm_accounting_flow));
            pstrcopy(sdb_icps_wbc_tm_accounting_flow.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_accounting_flow.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_accounting_flow.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_accounting_flow.org, '\001',"内部机构号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_accounting_flow.cps_txn_seq, '\001',"核心交易流水");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_accounting_flow.card_no, '\001',"卡号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_accounting_flow.curr_cd, '\001',"币种");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_accounting_flow.txn_code, '\001',"交易码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_accounting_flow.txn_desc, '\001',"交易描述");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_accounting_flow.db_cr_ind, '\001',"借贷标记");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_accounting_flow.post_amt, '\001',"入账金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_accounting_flow.post_gl_ind, '\001',"入账方式");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_accounting_flow.owning_branch, '\001',"支行");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_accounting_flow.subject, '\001',"科目");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_accounting_flow.red_flag, '\001',"红蓝字标识");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_accounting_flow.queue, '\001',"排序");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_accounting_flow.product_cd, '\001',"产品号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_accounting_flow.ref_nbr, '\001',"借据号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_accounting_flow.age_group, '\001',"账龄组");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_accounting_flow.plan_nbr, '\001',"信用计划号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_accounting_flow.bnp_group, '\001',"余额成分组");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_accounting_flow.bank_group_id, '\001',"银团代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_accounting_flow.bank_no, '\001',"银行代码");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_accounting_flow.term, '\001',"期数");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_accounting_flow.batchdate, '\001',"批量");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_accounting_flow.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_accounting_flow.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_ACCOUNTING_FLOW", SD_ICPS_WBC_TM_ACCOUNTING_FLOW, NUMELE(SD_ICPS_WBC_TM_ACCOUNTING_FLOW),
                    &sdb_icps_wbc_tm_accounting_flow, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR");
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_accounting_flow.card_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*营改增信息表*/

int ffunc_parse_wbankcar_file_to_db_tm_loan_vms(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_LOAN_VMS WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG")
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO")
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR")
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_loan_vms, 0x00, sizeof(sdb_icps_wbc_tm_loan_vms));
            pstrcopy(sdb_icps_wbc_tm_loan_vms.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_loan_vms.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_loan_vms.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_loan_vms.id, '\001',"纳税借据ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_loan_vms.org, '\001',"机构号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_loan_vms.card_no, '\001',"介质卡号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_loan_vms.ref_nbr, '\001',"交易参考号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_loan_vms.bank_group_id, '\001',"银团编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_loan_vms.bank_no, '\001',"银行编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_loan_vms.product_cd, '\001',"产品号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_loan_vms.biz_tax_interest, '\001',"营业税下的应计和应收息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_loan_vms.vat_int_bal, '\001',"90天内的应纳税息余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_loan_vms.norevoke_vat_int_bal, '\001',"不冲抵算法下应纳税息（含90天内+90天外还款补记部分）");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_loan_vms.vat_tax, '\001',"记账增值税");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_loan_vms.loan_init_term, '\001',"贷款总期数");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_loan_vms.last_modified_time, '\001',"上次修改时间");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_loan_vms.paid_out_date, '\001',"结清日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_loan_vms.age_cd, '\001',"账龄");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_loan_vms.batch_date, '\001',"批量日期");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_loan_vms.jpa_version, '\001',"乐观锁版本号");

           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_loan_vms.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_loan_vms.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_LOAN_VMS", SD_ICPS_WBC_TM_LOAN_VMS, NUMELE(SD_ICPS_WBC_TM_LOAN_VMS),
                    &sdb_icps_wbc_tm_loan_vms, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_loan_vms.id), "ERROR")
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*nbs客户表*/

int ffunc_parse_wbankcar_file_to_db_tm_nbs_cust(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR")
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_NBS_CUST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO")
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR")
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_nbs_cust, 0x00, sizeof(sdb_icps_wbc_tm_nbs_cust));
            pstrcopy(sdb_icps_wbc_tm_nbs_cust.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_nbs_cust.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_nbs_cust.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_nbs_cust.nbs_cust_id, '\001',"NBS客户ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_nbs_cust.name, '\001',"姓名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_nbs_cust.id_type, '\001',"证件类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_nbs_cust.id_no, '\001',"证件号码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_nbs_cust.ecif_no, '\001',"ecif客户号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_nbs_cust.reserve1, '\001',"保留字段1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_nbs_cust.reserve2, '\001',"身份证有效期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_nbs_cust.reserve3, '\001',"保留字段3");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_nbs_cust.biz_date, '\001',"业务日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_nbs_cust.created_datetime, '\001',"创建时间日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_nbs_cust.last_modified_datetime, '\001',"更新时间日期");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_nbs_cust.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_nbs_cust.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_NBS_CUST", SD_ICPS_WBC_TM_NBS_CUST, NUMELE(SD_ICPS_WBC_TM_NBS_CUST),
                    &sdb_icps_wbc_tm_nbs_cust, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_nbs_cust.nbs_cust_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*平台客户信息表*/

int ffunc_parse_wbankcar_file_to_db_tm_merchant_cust(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_MERCHANT_CUST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_merchant_cust, 0x00, sizeof(sdb_icps_wbc_tm_merchant_cust));
            pstrcopy(sdb_icps_wbc_tm_merchant_cust.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_merchant_cust.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_merchant_cust.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_merchant_cust.user_id, '\001',"平台的客户ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_merchant_cust.merchant_id, '\001',"平台ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_merchant_cust.nbs_cust_id, '\001',"NBS客户ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_merchant_cust.user_name, '\001',"平台注册的客户名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_merchant_cust.user_mobile, '\001',"平台登记的用户手机号");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_merchant_cust.apply_datetime, '\001',"平台ID申请时间");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_merchant_cust.reg_mobile, '\001',"注册手机号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_merchant_cust.qq_openid, '\001',"QQ_OPENID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_merchant_cust.wx_openid, '\001',"WX_OPENID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_merchant_cust.login_id, '\001',"微众WEB登录ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_merchant_cust.company_name, '\001',"单位名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_merchant_cust.company_phone, '\001',"单位电话");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_merchant_cust.address, '\001',"居住地址");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_merchant_cust.contact_name, '\001',"联系人名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_merchant_cust.contact_phone, '\001',"联系人手机号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_merchant_cust.contact_relation, '\001',"联系人关系");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_merchant_cust.reserve1, '\001',"保留字段1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_merchant_cust.reserve2, '\001',"保留字段2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_merchant_cust.reserve3, '\001',"保留字段3");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_merchant_cust.biz_date, '\001',"业务日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_merchant_cust.created_datetime, '\001',"创建时间日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_merchant_cust.last_modified_datetime, '\001',"更新时间日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_merchant_cust.contact_addr, '\001',"联系人地址");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_merchant_cust.contact_id_no, '\001',"联系人身份证号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_merchant_cust.co_licenses, '\001',"营业执照号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_merchant_cust.driver_license, '\001',"驾驶证号码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_merchant_cust.company_addr, '\001',"公司地址");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_merchant_cust.home_phone, '\001',"家庭固话号码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_merchant_cust.occupation, '\001',"职业");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_merchant_cust.ss_ave_amt_mtly, '\001',"每月社保平均缴交金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_merchant_cust.salary_ave_mtly, '\001',"每月平均工资进账流水");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_merchant_cust.is_home_visited, '\001',"有无家访");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_merchant_cust.house_info, '\001',"房产信息");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_merchant_cust.mer_apply_result, '\001',"审批结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_merchant_cust.mer_apply_view, '\001',"审批意见");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_merchant_cust.mer_refuse_reason, '\001',"拒绝原因分类");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_merchant_cust.cust_value, '\001',"客户信息（大字段）");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_merchant_cust.is_guarantor, '\001',"有无担保人");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_merchant_cust.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_merchant_cust.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_MERCHANT_CUST", SD_ICPS_WBC_TM_MERCHANT_CUST, NUMELE(SD_ICPS_WBC_TM_MERCHANT_CUST),
                    &sdb_icps_wbc_tm_merchant_cust, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_merchant_cust.user_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*平台客户产品信息表*/

int ffunc_parse_wbankcar_file_to_db_tm_merchant_product_cust(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_MERCHANT_PRODUCT_CUST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_merchant_product_cust, 0x00, sizeof(sdb_icps_wbc_tm_merchant_product_cust));
            pstrcopy(sdb_icps_wbc_tm_merchant_product_cust.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_merchant_product_cust.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_merchant_product_cust.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_merchant_product_cust.user_id, '\001',"平台的客户ID");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_merchant_product_cust.merchant_id, '\001',"平台ID");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_merchant_product_cust.product_cd, '\001',"产品CD");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_merchant_product_cust.cnc_card_no, '\001',"贷款卡号");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_merchant_product_cust.debit_card_no, '\001',"他行借记卡号");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_merchant_product_cust.wb_debit_card_no, '\001',"本行借记卡号");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_merchant_product_cust.nbs_cust_id, '\001',"NBS客户ID");
			ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_merchant_product_cust.aps_app_time, '\001',"APS开户申请时间");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_merchant_product_cust.aps_app_no, '\001',"APS开户申请号");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_merchant_product_cust.aps_app_no_status, '\001',"APS申请号状态");
			ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_merchant_product_cust.aps_app_count, '\001',"单日申请次数");
			ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_merchant_product_cust.aps_approval_date, '\001',"APS审批通过日期");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_merchant_product_cust.aps_result_level, '\001',"APS审批结果等级");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_merchant_product_cust.aps_rej_code, '\001',"APS审批拒绝码");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_merchant_product_cust.aps_rej_date, '\001',"APS审批拒绝时间");
			ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_merchant_product_cust.cnc_setup_date, '\001',"开贷款户日期");
			ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_merchant_product_cust.aps_credit_limit, '\001',"开户时授信额度");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_merchant_product_cust.gid, '\001',"操作源GID");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_merchant_product_cust.oper_ip, '\001',"操作源IP");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_merchant_product_cust.os_type, '\001',"操作系统");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_merchant_product_cust.lbs, '\001',"LBS");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_merchant_product_cust.ios_idfa, '\001',"IOS标示符");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_merchant_product_cust.android_imei, '\001',"ANDROID蓝牙地址");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_merchant_product_cust.submitted_entry, '\001',"提交入口");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_merchant_product_cust.submitted_city, '\001',"申请城市");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_merchant_product_cust.reserve1, '\001',"保留字段1");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_merchant_product_cust.reserve2, '\001',"保留字段2");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_merchant_product_cust.reserve3, '\001',"保留字段3");
			ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_merchant_product_cust.biz_date, '\001',"业务日期");
			ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_merchant_product_cust.created_datetime, '\001',"创建时间日期");
			ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_merchant_product_cust.last_modified_datetime, '\001',"更新时间日期");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_merchant_product_cust.app_biz_seq_no, '\001',"申请业务流水号");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_merchant_product_cust.aps_rej_reason, '\001',"申请拒绝原因");
			ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_merchant_product_cust.app_expiry_date, '\001',"申请失效日期");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_merchant_product_cust.agent_id, '\001',"代理人身份id");
			ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_merchant_product_cust.agent_name, '\001',"代理人姓名");

           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_merchant_product_cust.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_merchant_product_cust.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_MERCHANT_PRODUCT_CUST", SD_ICPS_WBC_TM_MERCHANT_PRODUCT_CUST, NUMELE(SD_ICPS_WBC_TM_MERCHANT_PRODUCT_CUST),
                    &sdb_icps_wbc_tm_merchant_product_cust, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_merchant_product_cust.merchant_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*协议表*/

int ffunc_parse_wbankcar_file_to_db_tm_agreement(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_AGREEMENT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_agreement, 0x00, sizeof(sdb_icps_wbc_tm_agreement));
            pstrcopy(sdb_icps_wbc_tm_agreement.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_agreement.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_agreement.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_agreement.agreement_no, '\001',"平台订单号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_agreement.merchant_id, '\001',"平台ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_agreement.product_cd, '\001',"产品CD");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_agreement.product_stcode, '\001',"产品结构代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_agreement.nbs_cust_id, '\001',"NBS客户ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_agreement.user_id, '\001',"平台的客户ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_agreement.cnc_card_no, '\001',"贷款卡号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_agreement.debit_card_no, '\001',"他行借记卡号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_agreement.wb_debit_card_no, '\001',"本行借记卡号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_agreement.last_txn_status, '\001',"上一个业务状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_agreement.txn_status, '\001',"当前业务状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_agreement.last_native_staus, '\001',"上一处理状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_agreement.native_staus, '\001',"当前处理状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_agreement.billing_cycle, '\001',"账单周期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_agreement.first_stmt_date, '\001',"首个账单日");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_agreement.agreement_amt, '\001',"协议金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_agreement.pct_id, '\001',"定价控制编号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_agreement.fee_rate, '\001',"费用利率");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_agreement.interest_rate, '\001',"利息利率");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_agreement.penalty_rate, '\001',"罚息利率");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_agreement.liquidated_damages, '\001',"违约金");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_agreement.curr_term, '\001',"当期期数");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_agreement.curr_deduct_stage, '\001',"当前扣款阶段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_agreement.deduct_stage_hst, '\001',"扣款阶段历史记录");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_agreement.credit_interest_rate, '\001',"信用贷利率");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_agreement.credit_penalty_rate, '\001',"信用贷罚息利率");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_agreement.credit_curr_deduct_stage, '\001',"信用贷当前扣款阶段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_agreement.credit_deduct_stage_hst, '\001',"信用贷扣款阶段历史记录");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_agreement.master_card_flag, '\001',"主还款卡标识");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_agreement.reserve1, '\001',"保留字段1");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_agreement.reserve2, '\001',"保留字段2");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_agreement.reserve3, '\001',"保留字段3");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_agreement.biz_date, '\001',"业务日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_agreement.created_datetime, '\001',"创建时间日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_agreement.last_modified_datetime, '\001',"更新时间日期");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_agreement.loan_init_term, '\001',"总期数");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_agreement.order_type, '\001',"订单类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_agreement.fund_status, '\001',"资金占压状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_agreement.fee_curr_deduct_stage, '\001',"费用贷当前扣款阶段");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_agreement.profit_ratio, '\001',"分润比例");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_agreement.product_category, '\001',"产品大类");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_agreement.fee_deduct_stage_hst, '\001',"费用贷扣款阶段历史记录");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_agreement.reserve4, '\001',"保留字段4");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_agreement.reserve5, '\001',"保留字段5");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_agreement.reserve6, '\001',"保留字段6");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_agreement.reserve7, '\001',"保留字段7");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_agreement.reserve8, '\001',"保留字段8");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_agreement.reserve9, '\001',"保留字段9");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_tm_agreement.reserve10, '\001',"保留字段10");

           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_agreement.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_agreement.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AGREEMENT", SD_ICPS_WBC_TM_AGREEMENT, NUMELE(SD_ICPS_WBC_TM_AGREEMENT),
                    &sdb_icps_wbc_tm_agreement, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_agreement.agreement_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*协议附加表(车)*/

int ffunc_parse_wbankcar_file_to_db_tm_agreement_car(HXMLTREE lXmlhandle,WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_AGREEMENT_CAR WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_agreement_car, 0x00, sizeof(sdb_icps_wbc_tm_agreement_car));
            pstrcopy(sdb_icps_wbc_tm_agreement_car.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_agreement_car.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_agreement_car.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_agreement_car.agreement_no, '\001',"平台订单号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_agreement_car.merchant_id, '\001',"平台ID号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_agreement_car.product_cd, '\001',"产品号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_agreement_car.mer_order_no, '\001',"平台协议号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_agreement_car.is_new_car, '\001',"是否新车");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_agreement_car.car_id, '\001',"车辆ID");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_agreement_car.car_price, '\001',"车辆销售价");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_agreement_car.car_inquiry_price, '\001',"外部数据源查询价");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_agreement_car.assess_amount, '\001',"车辆估值");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_agreement_car.assess_time, '\001',"车辆评估时间");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_agreement_car.assess_class, '\001',"车辆检测级别");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_agreement_car.registrate_time, '\001',"上牌日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_agreement_car.vehicle_id, '\001',"机动车架号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_agreement_car.engine_no, '\001',"发动机号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_agreement_car.mileage, '\001',"行驶里程");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_agreement_car.xfr_times, '\001',"过户次数");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_agreement_car.coty, '\001',"车龄");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_agreement_car.motorcycle_type, '\001',"车型描述");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_agreement_car.ins_expire_date, '\001',"保险到期日");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_agreement_car.dealer_id, '\001',"车商ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_agreement_car.dealer_name, '\001',"车商");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_agreement_car.is_stage_guarantee_dealer, '\001',"是否阶段性担保车商");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_agreement_car.car_name, '\001',"车辆名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_agreement_car.is_second_hand_car, '\001',"是否二手车");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_agreement_car.car_actual_price, '\001',"车辆实际成交价");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_agreement_car.down_payment, '\001',"首付总金额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_agreement_car.car_context, '\001',"补充信息");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_agreement_car.driver_license, '\001',"驾驶证号码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_agreement_car.home_phone, '\001',"家庭固话号码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_agreement_car.occupation, '\001',"职业");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_agreement_car.ss_ave_amt_mtly, '\001',"每月社保平均缴交金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_agreement_car.salary_ave_mtly, '\001',"每月平均工资进账流水");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_agreement_car.is_home_visited, '\001',"有无家访");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_agreement_car.house_info, '\001',"房产信息");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_agreement_car.mer_apply_result, '\001',"审批结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_agreement_car.mer_apply_view, '\001',"审批意见");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_agreement_car.mer_refuse_reason, '\001',"拒绝原因分类");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_agreement_car.biz_date, '\001',"业务日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_agreement_car.created_datetime, '\001',"创建时间");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_agreement_car.last_modified_datetime, '\001',"更新时间");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_agreement_car.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_agreement_car.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AGREEMENT_CAR", SD_ICPS_WBC_TM_AGREEMENT_CAR, NUMELE(SD_ICPS_WBC_TM_AGREEMENT_CAR),
                    &sdb_icps_wbc_tm_agreement_car, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_agreement_car.agreement_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*订单号映射表*/

int ffunc_parse_wbankcar_file_to_db_tm_agreement_no_map(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_AGREEMENT_NO_MAP WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_agreement_no_map, 0x00, sizeof(sdb_icps_wbc_tm_agreement_no_map));
            pstrcopy(sdb_icps_wbc_tm_agreement_no_map.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_agreement_no_map.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_agreement_no_map.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_agreement_no_map.agreement_no, '\001',"NBS订单号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_agreement_no_map.merchant_id, '\001',"平台ID号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_agreement_no_map.mer_order_no, '\001',"平台订单号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_agreement_no_map.txn_status, '\001',"平台协议状态");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_agreement_no_map.biz_data, '\001',"业务日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_agreement_no_map.created_datetime, '\001',"创建时间");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_agreement_no_map.last_modified_datetime, '\001',"修改时间");
          
		  


            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_agreement_no_map.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_agreement_no_map.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_AGREEMENT_NO_MAP", SD_ICPS_WBC_TM_AGREEMENT_NO_MAP, NUMELE(SD_ICPS_WBC_TM_AGREEMENT_NO_MAP),
                    &sdb_icps_wbc_tm_agreement_no_map, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_agreement_no_map.agreement_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}

/*订单号与借据号映射*/
int ffunc_parse_wbankcar_file_to_db_tm_loan_yx(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_LOAN_YX WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_loan_yx, 0x00, sizeof(sdb_icps_wbc_tm_loan_yx));
            pstrcopy(sdb_icps_wbc_tm_loan_yx.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_loan_yx.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_loan_yx.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_loan_yx.loan_receipt_nbr, '\001',"借据号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_loan_yx.merchant_id, '\001',"平台ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_loan_yx.product_cd, '\001',"产品CD");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_loan_yx.agreement_no, '\001',"平台协议号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_loan_yx.cnc_card_no, '\001',"贷款卡号");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_loan_yx.loan_init_term, '\001',"总期数");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_loan_yx.curr_term, '\001',"当期期数");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_loan_yx.remain_term, '\001',"剩余期数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_loan_yx.interest_rate, '\001',"利息利率");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_loan_yx.loan_status, '\001',"状态");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_loan_yx.loan_prin, '\001',"总本金");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_loan_yx.loan_paid, '\001',"已还本金");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_loan_yx.loan_init_interest, '\001',"总利息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_loan_yx.int_paid, '\001',"已还利息");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_loan_yx.loan_expire_date , '\001',"到期日期");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_loan_yx.grace_date, '\001',"宽限日");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_loan_yx.due_days, '\001',"逾期天数");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_loan_yx.loan_paidout_flg, '\001',"结清标识");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_loan_yx.loan_paidout_date, '\001',"结清日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_loan_yx.terminate_reason_cd, '\001',"终止原因代码");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_loan_yx.batch_date, '\001',"批量同步日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_loan_yx.batch_no, '\001',"批次号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_loan_yx.loan_bal_late_charge, '\001',"欠款总滞纳金");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_loan_yx.loan_bal_adv_pmt_fee, '\001',"欠款总提前还款手续费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_loan_yx.loan_bal_fee, '\001',"欠款总费用");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_loan_yx.late_charge_paid, '\001',"已还滞纳金");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_loan_yx.adv_pmt_fee_paid, '\001',"已还提前还款手续费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_loan_yx.fee_paid, '\001',"已还费用");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_loan_yx.next_prin, '\001',"下期本金");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_loan_yx.next_fee, '\001',"下期手续费");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_loan_yx.register_date, '\001',"借据注册日期");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_loan_yx.prin_bal, '\001',"欠款总本金");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_loan_yx.int_bal, '\001',"欠款总利息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_loan_yx.penalty_bal, '\001',"欠款总罚息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_tm_loan_yx.penalty_paid, '\001',"已还罚息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_tm_loan_yx.penalty_rate, '\001',"罚息利率");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_tm_loan_yx.biz_date, '\001',"业务日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_tm_loan_yx.created_datetime, '\001',"创建时间日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_tm_loan_yx.last_modified_datetime, '\001',"更新时间日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_tm_loan_yx.loan_type, '\001',"借据类型");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_tm_loan_yx.unearned_prin, '\001',"未到期本金");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_tm_loan_yx.inst_return_flag, '\001',"是否已退息");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_tm_loan_yx.paid_out_return_status, '\001',"结清退保退息状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_tm_loan_yx.ref_nbr, '\001',"交易检索号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_tm_loan_yx.loan_merge_type, '\001',"借据合并类型");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_tm_loan_yx.bef_init_interest, '\001',"原贷款总利息");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_tm_loan_yx.orig_init_term, '\001',"原始贷款期数");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_tm_loan_yx.gl_term, '\001',"总账期数，会计账期数。需要乘以还款间隔以加工");

           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_loan_yx.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_loan_yx.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_LOAN_YX", SD_ICPS_WBC_TM_LOAN_YX, NUMELE(SD_ICPS_WBC_TM_LOAN_YX),
                    &sdb_icps_wbc_tm_loan_yx, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_loan_yx.loan_receipt_nbr), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}

/*nbs客户延展表*/

int ffunc_parse_wbankcar_file_to_db_tm_nbs_cust_ext_info(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_NBS_CUST_EXT_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_nbs_cust_ext_info, 0x00, sizeof(sdb_icps_wbc_tm_nbs_cust_ext_info));
            pstrcopy(sdb_icps_wbc_tm_nbs_cust_ext_info.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_nbs_cust_ext_info.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_nbs_cust_ext_info.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_nbs_cust_ext_info.nbs_cust_id, '\001',"NBS客户ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_nbs_cust_ext_info.product_cd, '\001',"产品号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_nbs_cust_ext_info.merchant_id, '\001',"平台ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_nbs_cust_ext_info.name, '\001',"姓名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_nbs_cust_ext_info.id_type, '\001',"证件类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_nbs_cust_ext_info.id_no, '\001',"证件号码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_nbs_cust_ext_info.id_no_expiry, '\001',"身份证有效期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_nbs_cust_ext_info.residential_address, '\001',"地址");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_nbs_cust_ext_info.gender, '\001',"性别");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_nbs_cust_ext_info.nationality, '\001',"国籍");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_nbs_cust_ext_info.marriage, '\001',"婚姻状况");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_nbs_cust_ext_info.education, '\001',"学历");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf1, '\001',"民族");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf2, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf3, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf4, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf5, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf6, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf7, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf8, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf9, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf10, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf11, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf12, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf13, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf14, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf15, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf16, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf17, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf18, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf19, '\001',"保留字段");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_nbs_cust_ext_info.cust_ext_inf20, '\001',"保留字段");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_nbs_cust_ext_info.created_datetime, '\001',"创建时间日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_tm_nbs_cust_ext_info.last_modified_datetime, '\001',"更新时间日期");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_nbs_cust_ext_info.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_nbs_cust_ext_info.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_NBS_CUST_EXT_INFO", SD_ICPS_WBC_TM_NBS_CUST_EXT_INFO, NUMELE(SD_ICPS_WBC_TM_NBS_CUST_EXT_INFO),
                    &sdb_icps_wbc_tm_nbs_cust_ext_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_nbs_cust_ext_info.nbs_cust_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*按照合作方的账号，该账号下面的所有存款交易明细表*/

int ffunc_parse_wbankcar_file_to_db_kdpl_zhminx(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_KDPL_ZHMINX WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_kdpl_zhminx, 0x00, sizeof(sdb_icps_wbc_kdpl_zhminx));
            pstrcopy(sdb_icps_wbc_kdpl_zhminx.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_kdpl_zhminx.busi_date)); /*业务日期*/
            sdb_icps_wbc_kdpl_zhminx.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_kdpl_zhminx.zhanghao, '\001',"负债账号");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_kdpl_zhminx.mxixuhao, '\001',"明细序号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_kdpl_zhminx.jiaoyirq, '\001',"交易日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_kdpl_zhminx.khjymxlb, '\001',"客户交易明细类别");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_kdpl_zhminx.jyyyjigo, '\001',"交易营业机构");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_kdpl_zhminx.kaihjigo, '\001',"账户开户机构");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_kdpl_zhminx.zhhuzwmc, '\001',"账户名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_kdpl_zhminx.jiedaibz, '\001',"借贷标志");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_kdpl_zhminx.jiaoybiz, '\001',"交易币种");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_kdpl_zhminx.chaohubz, '\001',"账户钞汇标志");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_kdpl_zhminx.jiaoyije, '\001',"交易金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_kdpl_zhminx.zhanghye, '\001',"账户余额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_kdpl_zhminx.kahaoooo, '\001',"卡号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_kdpl_zhminx.kehuzhao, '\001',"客户账号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_kdpl_zhminx.zhhaoxuh, '\001',"子账户序号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_kdpl_zhminx.pngzzlei, '\001',"凭证种类");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_kdpl_zhminx.pngzxhao, '\001',"凭证号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_kdpl_zhminx.zhaiyodm, '\001',"摘要代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_kdpl_zhminx.zhaiyoms, '\001',"摘要描述");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_kdpl_zhminx.duifjgdm, '\001',"对方金融机构");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_kdpl_zhminx.duifjgmc, '\001',"对方金融机构名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_kdpl_zhminx.duifkhzh, '\001',"对方客户账号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_kdpl_zhminx.duifminc, '\001',"对方户名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_kdpl_zhminx.duifbezh, '\001',"对方备注");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_kdpl_zhminx.beizhuuu, '\001',"备注");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_kdpl_zhminx.qixiriqi, '\001',"起息日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_kdpl_zhminx.qdaoleix, '\001',"交易渠道");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_kdpl_zhminx.waibclma, '\001',"对账代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_kdpl_zhminx.nbjoyima, '\001',"内部交易码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_kdpl_zhminx.xianzzbz, '\001',"现转标志");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_kdpl_zhminx.guiylius, '\001',"柜员流水(即交易流水)");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_kdpl_zhminx.caozguiy, '\001',"操作柜员");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_kdpl_zhminx.zhujriqi, '\001',"主机日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wbc_kdpl_zhminx.zjyilush, '\001',"主交易流水");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wbc_kdpl_zhminx.yewulush, '\001',"业务流水");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wbc_kdpl_zhminx.jiaoyisj, '\001',"交易时间");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wbc_kdpl_zhminx.bchongbz, '\001',"交易明细状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wbc_kdpl_zhminx.cuozriqi, '\001',"原错账日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wbc_kdpl_zhminx.cuozlius, '\001',"原错账交易流水");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wbc_kdpl_zhminx.yszjylsh, '\001',"原始主交易流水");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wbc_kdpl_zhminx.ysyewush, '\001',"原始业务流水");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wbc_kdpl_zhminx.czczflei, '\001',"冲正冲账分类");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wbc_kdpl_zhminx.mozhanbz, '\001',"抹账标志");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wbc_kdpl_zhminx.tokennnn, '\001',"token");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wbc_kdpl_zhminx.dsftoken, '\001',"对手方token");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 46, sdb_icps_wbc_kdpl_zhminx.lilvlilv, '\001',"利率");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wbc_kdpl_zhminx.jioyshij, '\001',"交易事件");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wbc_kdpl_zhminx.huidxhao, '\001',"回单序号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wbc_kdpl_zhminx.farendma, '\001',"法人代码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wbc_kdpl_zhminx.weihguiy, '\001',"维护柜员");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wbc_kdpl_zhminx.weihjigo, '\001',"维护机构");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wbc_kdpl_zhminx.weihriqi, '\001',"维护日期");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 53, sdb_icps_wbc_kdpl_zhminx.shijchuo, '\001',"时间戳");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_kdpl_zhminx.is_check_flag, "1", sizeof(sdb_icps_wbc_kdpl_zhminx.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_KDPL_ZHMINX", SD_ICPS_WBC_KDPL_ZHMINX, NUMELE(SD_ICPS_WBC_KDPL_ZHMINX),
                    &sdb_icps_wbc_kdpl_zhminx, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_kdpl_zhminx.zhanghao), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}

/*公安核查结果信息表*/

int ffunc_parse_wbankcar_file_to_db_tm_psb_check_info(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_PSB_CHECK_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_psb_check_info, 0x00, sizeof(sdb_icps_wbc_tm_psb_check_info));
            pstrcopy(sdb_icps_wbc_tm_psb_check_info.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_psb_check_info.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_psb_check_info.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_psb_check_info.seq_no, '\001',"查询流水号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_psb_check_info.org, '\001',"机构号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_psb_check_info.app_no, '\001',"申请件编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_psb_check_info.id_type, '\001',"证件类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_psb_check_info.id_no, '\001',"证件号码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_psb_check_info.name, '\001',"姓名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_psb_check_info.gender, '\001',"性别");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_psb_check_info.result_person_id, '\001',"证件号码核查结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_psb_check_info.result_person_name, '\001',"姓名核查结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_psb_check_info.photo_id, '\001',"照片文件id");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_psb_check_info.nation, '\001',"民族");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_psb_check_info.photo_md5, '\001',"照片md5值");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_psb_check_info.old_name, '\001',"曾用名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_psb_check_info.birth, '\001',"出生日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_psb_check_info.native_place, '\001',"籍贯省市县（区）");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_psb_check_info.address, '\001',"住址");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_psb_check_info.work_place, '\001',"服务处所");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_psb_check_info.marital_status, '\001',"婚姻状况");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_psb_check_info.degree_of_education, '\001',"文化程度");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_psb_check_info.issued_authority, '\001',"签发机关");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_psb_check_info.birth_place, '\001',"出生地");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_psb_check_info.occupation, '\001',"职业");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_psb_check_info.bl0, '\001',"在逃状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_psb_check_info.bl1, '\001',"违法状态");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_psb_check_info.created_datetime, '\001',"创建时间");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_psb_check_info.last_modified_datetime, '\001',"最后修改时间");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_psb_check_info.jpa_version, '\001',"乐观锁");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_psb_check_info.product_cd, '\001',"产品编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_psb_check_info.msg_serv_error, '\001',"服务异常描述");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_psb_check_info.msg_id_error, '\001',"查询结果描述");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_psb_check_info.flag, '\001',"结果获取渠道");

           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_psb_check_info.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_psb_check_info.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_PSB_CHECK_INFO", SD_ICPS_WBC_TM_PSB_CHECK_INFO, NUMELE(SD_ICPS_WBC_TM_PSB_CHECK_INFO),
                    &sdb_icps_wbc_tm_psb_check_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_psb_check_info.seq_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*身份信息*/

int ffunc_parse_wbankcar_file_to_db_tm_psb_personal_info(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_PSB_PERSONAL_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_psb_personal_info, 0x00, sizeof(sdb_icps_wbc_tm_psb_personal_info));
            pstrcopy(sdb_icps_wbc_tm_psb_personal_info.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_psb_personal_info.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_psb_personal_info.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_psb_personal_info.id, '\001',"ID");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_psb_personal_info.app_no, '\001',"申请件编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_psb_personal_info.certi_type, '\001',"证件类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_psb_personal_info.certi_no, '\001',"身份证号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_psb_personal_info.name, '\001',"姓名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_psb_personal_info.sex, '\001',"性别");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_psb_personal_info.birth_date, '\001',"出生日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_psb_personal_info.marrystate, '\001',"婚姻状况");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_psb_personal_info.mobile, '\001',"手机号码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_psb_personal_info.homephone, '\001',"家庭电话");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_psb_personal_info.compphone, '\001',"单位电话");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_psb_personal_info.qualification, '\001',"学历");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_psb_personal_info.degree, '\001',"学位");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_psb_personal_info.address, '\001',"通讯地址");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_psb_personal_info.reside_addr, '\001',"户籍地址");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_psb_personal_info.mate_certp, '\001',"配偶证件类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_psb_personal_info.mate_cerno, '\001',"配偶证件号码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_psb_personal_info.mate_name, '\001',"配偶姓名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_psb_personal_info.mate_corp, '\001',"配偶工作单位");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wbc_tm_psb_personal_info.mate_phone, '\001',"配偶联系电话");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wbc_tm_psb_personal_info.addr, '\001',"居住地址");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wbc_tm_psb_personal_info.reside_state, '\001',"居住状况");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wbc_tm_psb_personal_info.comp_nm, '\001',"工作单位");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wbc_tm_psb_personal_info.comp_addr, '\001',"单位地址");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wbc_tm_psb_personal_info.profess, '\001',"职业");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wbc_tm_psb_personal_info.comp_trade, '\001',"行业");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wbc_tm_psb_personal_info.business, '\001',"职务");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wbc_tm_psb_personal_info.teach_pose, '\001',"职称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wbc_tm_psb_personal_info.work_date, '\001',"本单位工作起始年份");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 30, sdb_icps_wbc_tm_psb_personal_info.infodate, '\001',"信息更新日期");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 31, sdb_icps_wbc_tm_psb_personal_info.create_time, '\001',"创建时间");
           ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 32, sdb_icps_wbc_tm_psb_personal_info.psb_query_date, '\001',"人行报告查询时间");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wbc_tm_psb_personal_info.reportsn, '\001',"人行报告编号");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_psb_personal_info.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_psb_personal_info.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_PSB_PERSONAL_INFO", SD_ICPS_WBC_TM_PSB_PERSONAL_INFO, NUMELE(SD_ICPS_WBC_TM_PSB_PERSONAL_INFO),
                    &sdb_icps_wbc_tm_psb_personal_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tm_psb_personal_info.id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*银行决策结果表*/

int ffunc_parse_wbankcar_file_to_db_tm_bank_credit_result(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_BANK_CREDIT_RESULT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_bank_credit_result, 0x00, sizeof(sdb_icps_wbc_tm_bank_credit_result));
            pstrcopy(sdb_icps_wbc_tm_bank_credit_result.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_bank_credit_result.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_bank_credit_result.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_bank_credit_result.seq_no, '\001',"决策流水");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_bank_credit_result.bank_no, '\001',"银行编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_bank_credit_result.bank_name, '\001',"银行名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_bank_credit_result.id_no, '\001',"证件号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_bank_credit_result.id_type, '\001',"证件类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_bank_credit_result.name, '\001',"姓名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_tm_bank_credit_result.nbs_order_no, '\001',"订单号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_tm_bank_credit_result.credit_info, '\001',"征信信息");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_tm_bank_credit_result.rule_action_type, '\001',"征信规则命中状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_tm_bank_credit_result.rule_code, '\001',"征信规则规则拒绝码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_tm_bank_credit_result.ruile_desc, '\001',"规则规则决策拒绝描述");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_tm_bank_credit_result.is_bl_rej, '\001',"黑名单命中状态");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wbc_tm_bank_credit_result.bl_rej_code, '\001',"黑名单拒绝编码");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wbc_tm_bank_credit_result.bl_rej_desc, '\001',"黑名单拒绝描述");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 15, sdb_icps_wbc_tm_bank_credit_result.credit_datetime, '\001',"风险判定时间");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wbc_tm_bank_credit_result.result_code, '\001',"决策结果");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wbc_tm_bank_credit_result.result_desc, '\001',"决策结果描述");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 18, sdb_icps_wbc_tm_bank_credit_result.created_datetime, '\001',"创建时间");
           ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 19, sdb_icps_wbc_tm_bank_credit_result.last_modified_datetime, '\001',"更新时间");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_bank_credit_result.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_bank_credit_result.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_BANK_CREDIT_RESULT", SD_ICPS_WBC_TM_BANK_CREDIT_RESULT, NUMELE(SD_ICPS_WBC_TM_BANK_CREDIT_RESULT),
                    &sdb_icps_wbc_tm_bank_credit_result, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_bank_credit_result.seq_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*银行表*/

int ffunc_parse_wbankcar_file_to_db_tm_bank(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_BANK WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_bank, 0x00, sizeof(sdb_icps_wbc_tm_bank));
            pstrcopy(sdb_icps_wbc_tm_bank.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_bank.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_bank.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_bank.bank_no, '\001',"银行号");          
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_bank.bank_name, '\001',"银行名称");      
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_bank.paying_acct, '\001',"备付金账户号"); /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_bank.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_bank.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_BANK", SD_ICPS_WBC_TM_BANK, NUMELE(SD_ICPS_WBC_TM_BANK),
                    &sdb_icps_wbc_tm_bank, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_tm_bank.bank_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*银团配置表*/

int ffunc_parse_wbankcar_file_to_db_tm_bank_group_member(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_TM_BANK_GROUP_MEMBER WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_tm_bank_group_member, 0x00, sizeof(sdb_icps_wbc_tm_bank_group_member));
            pstrcopy(sdb_icps_wbc_tm_bank_group_member.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_tm_bank_group_member.busi_date)); /*业务日期*/
            sdb_icps_wbc_tm_bank_group_member.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_tm_bank_group_member.member_id, '\001',"顺序号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_tm_bank_group_member.bank_group_id, '\001',"银团编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_tm_bank_group_member.bank_no, '\001',"银行号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_tm_bank_group_member.bank_proportion, '\001',"银行出资比例");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_tm_bank_group_member.product_category, '\001',"产品大类");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_tm_bank_group_member.priority, '\001',"出资优先级");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_tm_bank_group_member.is_check_flag, "1", sizeof(sdb_icps_wbc_tm_bank_group_member.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_TM_BANK_GROUP_MEMBER", SD_ICPS_WBC_TM_BANK_GROUP_MEMBER, NUMELE(SD_ICPS_WBC_TM_BANK_GROUP_MEMBER),
                    &sdb_icps_wbc_tm_bank_group_member, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_tm_bank_group_member.member_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*备付金资金清算汇总*/

int ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_tot(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_rrs_bdm_udf_clear_tot, 0x00, sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_tot));
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_tot.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_tot.busi_date)); /*业务日期*/
            sdb_icps_wbc_rrs_bdm_udf_clear_tot.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_rrs_bdm_udf_clear_tot.data_dt, '\001',"数据日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_rrs_bdm_udf_clear_tot.acct_no, '\001',"备付金帐号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_rrs_bdm_udf_clear_tot.ccy, '\001',"币种");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_rrs_bdm_udf_clear_tot.acct_name, '\001',"户名");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_rrs_bdm_udf_clear_tot.last_balance, '\001',"上日账户余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_rrs_bdm_udf_clear_tot.balance, '\001',"本日账户余额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_rrs_bdm_udf_clear_tot.payment_amt, '\001',"当日放款总金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_rrs_bdm_udf_clear_tot.repayment_amt, '\001',"当日还款总金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_rrs_bdm_udf_clear_tot.other_credit_amt, '\001',"当日其他划入款项");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_rrs_bdm_udf_clear_tot.other_debit_amt, '\001',"当日其他划出款项");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_rrs_bdm_udf_clear_tot.ds, '\001',"日期分区");

           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_tot.is_check_flag, "1", sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_tot.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT", SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT, NUMELE(SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_TOT),
                    &sdb_icps_wbc_rrs_bdm_udf_clear_tot, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_rrs_bdm_udf_clear_tot.acct_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*备付金资金清算明细*/

int ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_detail(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_rrs_bdm_udf_clear_detail, 0x00, sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_detail));
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_detail.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_detail.busi_date)); /*业务日期*/
            sdb_icps_wbc_rrs_bdm_udf_clear_detail.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_rrs_bdm_udf_clear_detail.data_dt, '\001',"数据日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_rrs_bdm_udf_clear_detail.acct_no, '\001',"备付金帐号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_rrs_bdm_udf_clear_detail.ccy, '\001',"币种");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_rrs_bdm_udf_clear_detail.bank_group_code, '\001',"银团编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_rrs_bdm_udf_clear_detail.data_type, '\001',"数据类型");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_rrs_bdm_udf_clear_detail.amount, '\001',"发生额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_rrs_bdm_udf_clear_detail.ds, '\001',"日期分区");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_detail.is_check_flag, "1", sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_detail.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL", SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL, NUMELE(SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_DETAIL),
                    &sdb_icps_wbc_rrs_bdm_udf_clear_detail, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_rrs_bdm_udf_clear_detail.acct_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*备付金其他款项资金明细*/

int ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_other_detail(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_rrs_bdm_udf_clear_other_detail, 0x00, sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_other_detail));
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.busi_date)); /*业务日期*/
            sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.data_dt, '\001',"数据日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.acct_no, '\001',"备付金帐号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.ccy, '\001',"币种");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.bank_group_code, '\001',"银团编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.data_type, '\001',"数据类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.ser_no, '\001',"明细序号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.amount, '\001',"发生额");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.memo, '\001',"备注");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.ds, '\001',"日期分区");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.is_check_flag, "1", sizeof(sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL", SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL, NUMELE(SD_ICPS_WBC_RRS_BDM_UDF_CLEAR_OTHER_DETAIL),
                    &sdb_icps_wbc_rrs_bdm_udf_clear_other_detail, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%d']", rcdCnt, sdb_icps_wbc_rrs_bdm_udf_clear_other_detail.acct_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*尾差调整表*/

int ffunc_parse_wbankcar_file_to_db_bank_group_dfq_split_diff(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_bank_group_dfq_split_diff, 0x00, sizeof(sdb_icps_wbc_bank_group_dfq_split_diff));
            pstrcopy(sdb_icps_wbc_bank_group_dfq_split_diff.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_bank_group_dfq_split_diff.busi_date)); /*业务日期*/
            sdb_icps_wbc_bank_group_dfq_split_diff.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_bank_group_dfq_split_diff.partition_date, '\001',"批量日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_bank_group_dfq_split_diff.product_cd , '\001',"产品编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_bank_group_dfq_split_diff.error_type, '\001',"异常类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_bank_group_dfq_split_diff.bank_group_id, '\001',"银团编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_bank_group_dfq_split_diff.bank_no, '\001',"银行编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_bank_group_dfq_split_diff.consumer_trans_id, '\001',"业务流水号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_bank_group_dfq_split_diff.reg_type, '\001',"交易类型");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_bank_group_dfq_split_diff.name, '\001',"姓名");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_bank_group_dfq_split_diff.logical_card_no, '\001',"逻辑卡号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_bank_group_dfq_split_diff.bf_amt, '\001',"备付金清算金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_bank_group_dfq_split_diff.account_amt, '\001',"CNC记账金额");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_bank_group_dfq_split_diff.error_amt, '\001',"应调整差额");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_bank_group_dfq_split_diff.is_check_flag, "1", sizeof(sdb_icps_wbc_bank_group_dfq_split_diff.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF", SD_ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF, NUMELE(SD_ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF),
                    &sdb_icps_wbc_bank_group_dfq_split_diff, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_bank_group_dfq_split_diff.partition_date), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*CBS清结算明细报表*/

int ffunc_parse_wbankcar_file_to_db_report_cbs_ptjr_car_data_paid_detail_day_coop(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop, 0x00, sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop));
            pstrcopy(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.busi_date)); /*业务日期*/
            sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/ 
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.partition_date, '\001',"批量日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.bank_group_id, '\001',"银团编号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.org_no, '\001',"合作机构名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.fee_name, '\001',"费用名称");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.loan_receipt_nbr, '\001',"借据号");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.txn_date, '\001',"交易发生批量日期");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.clearing_calc_day_amt, '\001',"实收利息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.clearing_day_amt, '\001',"平台费");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.clearing_day_no_vat_amt, '\001',"扣收平台费（不含税）");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.clearing_day_vat_amt, '\001',"扣收平台费（税）");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.interest_rate, '\001',"利率");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.fund_ratio, '\001',"资金定价");

           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.is_check_flag, "1", sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP", SD_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP, NUMELE(SD_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_DETAIL_DAY_COOP),
                    &sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_detail_day_coop.partition_date), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
    fclose(fp_list);
    fclose(fp_check);
    return 0;
}
/*CBS清结算汇总报表*/

int ffunc_parse_wbankcar_file_to_db_report_cbs_ptjr_car_data_paid_sum_day_coop(HXMLTREE lXmlhandle, WBC_PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[3072];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        LOG(LM_STD, Fmtmsg("ERRORMSG[%s]", strerror(errno)), "ERROR")
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop, 0x00, sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop));
            pstrcopy(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.busi_date)); /*业务日期*/
            sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.file_order = rcdCnt;
           /*********************************************************************************
           **********************************************************************************/
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.partition_date, '\001',"批量日期");
           ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.bank_group_id, '\001',"银团编号");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 3, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.clearing_calc_day_amt, '\001',"实收利息");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.clearing_day_no_vat_amt, '\001',"扣收平台费（不含税）");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.clearing_day_vat_amt, '\001',"扣收平台费（税）");
           ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.txn_num , '\001',"交易数");
           ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.clearing_day_amt, '\001',"平台费");
           
            /*参与对账标志*/
            pstrcopy(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.is_check_flag, "1", sizeof(sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP", SD_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP, NUMELE(SD_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP),
                    &sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wbc_report_cbs_ptjr_car_data_paid_sum_day_coop.partition_date), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")
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
        /*申请主表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_app_main(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_app_prim_applicant_info"))
    {
        /*申请人主卡信息表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_app_prim_applicant_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_account"))
    {
        /*账户信息表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_account(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_customer"))
    {
        /*客户信息表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_customer(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_plan"))
    {
        /*信用计划表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_plan(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tt_txn_post"))
    {
        /*当日入账交易表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tt_txn_post(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan"))
    {
        /*分期信息表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_loan(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_schedule"))
    {
        /*贷款分配表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_schedule(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_cust_limit_o"))
    {
        /*自定义额度信息表-授权*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_cust_limit_o(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_auth_hst"))
    {
        /*授权交易历史*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_auth_hst(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_auth_bank_cost"))
    {
        /*授权流水银团拆分表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_auth_bank_cost(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_auth_bank_cost_dtl"))
    {
        /*授权流水银团拆分明细表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_auth_bank_cost_dtl(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_txn_cd"))
    {
        /*交易码定义表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_txn_cd(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_receipt_list"))
    {
        /*还款借据清单表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_loan_receipt_list(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_gl_bal"))
    {
        /*总账会计科目表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_gl_bal(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_accounting_flow"))
    {
        /*会计分录日报表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_accounting_flow(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_vms"))
    {
        /*营改增信息表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_loan_vms(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_nbs_cust"))
    {
        /*nbs客户表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_nbs_cust(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_merchant_cust"))
    {
        /*平台客户信息表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_merchant_cust(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_merchant_product_cust"))
    {
        /*平台客户产品信息表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_merchant_product_cust(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_agreement"))
    {
        /*协议表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_agreement(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_agreement_car"))
    {
        /*协议附加表(车) */
        iRet = ffunc_parse_wbankcar_file_to_db_tm_agreement_car(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_agreement_no_map"))
    {
        /*订单号映射表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_agreement_no_map(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_yx"))
    {
        /*订单号与借据号映射*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_loan_yx(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_nbs_cust_ext_info"))
    {
        /*nbs客户延展表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_nbs_cust_ext_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "kdpl_zhminx"))
    {
        /*按照合作方的账号，该账号下面的所有存款交易明细表*/
        iRet = ffunc_parse_wbankcar_file_to_db_kdpl_zhminx(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_psb_check_info"))
    {
        /*公安核查结果信息表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_psb_check_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_psb_personal_info"))
    {
        /*身份信息*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_psb_personal_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_bank_credit_result"))
    {
        /*银行决策结果表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_bank_credit_result(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_bank"))
    {
        /*银行表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_bank(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_bank_group_member"))
    {
        /*银团配置表*/
        iRet = ffunc_parse_wbankcar_file_to_db_tm_bank_group_member(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_tot"))
    {
        /*备付金资金清算汇总*/
        iRet = ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_tot(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_detail"))
    {
        /*备付金资金清算明细*/
        iRet = ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_detail(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_other_detail"))
    {
        /*备付金其他款项资金明细*/
        iRet = ffunc_parse_wbankcar_file_to_db_rrs_bdm_udf_clear_other_detail(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "bank_group_dfq_split_diff"))
    {
        /*尾差调整表*/
        iRet = ffunc_parse_wbankcar_file_to_db_bank_group_dfq_split_diff(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "report_cbs_ptjr_car_data_paid_detail_day_coop"))
    {
        /*CBS清结算明细报表*/
        iRet = ffunc_parse_wbankcar_file_to_db_report_cbs_ptjr_car_data_paid_detail_day_coop(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "report_cbs_ptjr_car_data_paid_sum_day_coop"))
    {
        /*CBS清结算汇总报表*/
        iRet = ffunc_parse_wbankcar_file_to_db_report_cbs_ptjr_car_data_paid_sum_day_coop(lXmlhandle, st_para_chkfileins);
    }
    
    else
    {
        LOG(LM_STD, Fmtmsg("文件类型错误！"), "ERROR");
        return -2;
    }

    COMP_SOFTGETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, sBuf);
    fileins_status = atoi(trim(sBuf));
    LOG(LM_STD, Fmtmsg("目前文件入库状态[%d]", fileins_status), "INFO")

    if (9 == fileins_status) /*初始*/
    {
        if (0 == iRet) /*成功*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "0") /*成功*/
        else if (-404 == iRet) /*无文件*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "9") /*初始*/
        else
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "2") /*失败*/
    }
    else if (0 == fileins_status) /*成功*/
    {
        if (0 == iRet) /*成功*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "0") /*成功*/
        else
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "1") /*部分成功*/
    }
    else if (2 == fileins_status) /*失败*/
    {
        if (0 == iRet || -404 == iRet)
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "1") /*部分成功*/
    }
    COMP_SOFTGETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, sBuf);
    fileins_status = atoi(trim(sBuf));
    LOG(LM_STD, Fmtmsg("本文件入库后状态[%d]", fileins_status), "INFO")
    iRet = ffunc_upd_file_info(st_para_chkfileins.busi_date, st_para_chkfileins.busi_no, st_para_chkfileins.file_type, iRet);

    return iRet;
}

int ffunc_init_wbankcar_file_info(HXMLTREE lXmlhandle, PARA_FILEINFOINIT st_para_fileinfoinit)
{
    int iRet;

    /*申请主表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_app_main");
    /*申请人主卡信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_app_prim_applicant_info");
    /*账户信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_account");
    /*客户信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_customer");
    /*信用计划表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_plan");
    /*当日入账交易表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tt_txn_post");
    /*分期信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan");
    /*贷款分配表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_schedule");
    /*自定义额度信息表-授权*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_cust_limit_o");
    /*授权交易历史*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_auth_hst");
    /*授权流水银团拆分表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_auth_bank_cost");
    /*授权流水银团拆分明细表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_auth_bank_cost_dtl");
    /*交易码定义表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_txn_cd");
    /*还款借据清单表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_receipt_list");
    /*总账会计科目表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_gl_bal");
    /*会计分录日报表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_accounting_flow");
    /*营改增信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_vms");
    /*nbs客户表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_nbs_cust");
    /*平台客户信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_merchant_cust");
    /*平台客户产品信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_merchant_product_cust");
    /*协议表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_agreement");
    /*协议附加表(车)*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_agreement_car");
    /*订单号映射表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_agreement_no_map");
    /*订单号与借据号映射*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_yx");
    /*nbs客户延展表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_nbs_cust_ext_info");
    /*按照合作方的账号，该账号下面的所有存款交易明细表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "kdpl_zhminx");
    /*公安核查结果信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_psb_check_info");
    /*身份信息*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_psb_personal_info");
    /*银行决策结果表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_bank_credit_result");
    /*银行表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_bank");
    /*银团配置表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_bank_group_member");
    /*备付金资金清算汇总*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_tot");    
     /* 备付金资金清算明细 */
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_detail");
      /*备付金其他款项资金明细*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_other_detail");
     /* 尾差调整表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "bank_group_dfq_split_diff");            
     /* CBS清结算明细报表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "report_cbs_ptjr_car_data_paid_detail_day_coop");   
     /*CBS清结算汇总报表 */
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "report_cbs_ptjr_car_data_paid_sum_day_coop");
    return 0;
}
