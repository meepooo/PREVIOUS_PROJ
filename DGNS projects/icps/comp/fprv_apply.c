#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include "../incl/cJSON.h"

void zm_cJSON_to_CreditScore(HXMLTREE lXmlhandle, cJSON *json, char *respnode)
{
    char sXmlnode[256];
    cJSON *object = cJSON_GetObjectItem(json, "CreditScore");
    cJSON *item;
    if (object == NULL)
    {
        LOG(LM_DEBUG, Fmtmsg("Error before: [%s]", cJSON_GetErrorPtr()), "DEBUG");
        LOG(LM_DEBUG, Fmtmsg("111"), "DEBUG");
        cJSON_Delete(json);
    }
    LOG(LM_DEBUG, Fmtmsg("cJSON_GetObjectItem: type=%d, key is %s", object->type, object->string), "DEBUG");
    if (object != NULL)
    {
        LOG(LM_DEBUG, Fmtmsg("222"), "DEBUG");
        item = cJSON_GetObjectItem(object, "success");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valueint=%d", item->type, item->string, item->valueint),
                    "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/CreditScore/success", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valueint);
        }

        item = cJSON_GetObjectItem(object, "biz_no");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s", item->type, item->string,
                            item->valuestring), "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/CreditScore/biz_no", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valuestring);
        }

        item = cJSON_GetObjectItem(object, "zm_score");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s", item->type, item->string,
                            item->valuestring), "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/CreditScore/zm_score", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valuestring);
        }
    }
}

void zm_cJSON_to_DAS(HXMLTREE lXmlhandle, cJSON *json, char *respnode)
{
    char sXmlnode[256];
    cJSON *object, *arrayItem, *arrayObject, *item;
    object = cJSON_GetObjectItem(json, "DAS");
    int i;
    if (object == NULL)
    {
        LOG(LM_DEBUG, Fmtmsg("Error before: [%s]", cJSON_GetErrorPtr()), "DEBUG");
        cJSON_Delete(json);
    }
    LOG(LM_DEBUG, Fmtmsg("cJSON_GetObjectItem: type=%d, key is %s", object->type, object->string), "DEBUG");
    if (object != NULL)
    {
        item = cJSON_GetObjectItem(object, "success");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valueint=%d", item->type, item->string, item->valueint),
                    "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/DAS/success", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valueint);
        }

        item = cJSON_GetObjectItem(object, "biz_no");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s", item->type, item->string,
                            item->valuestring), "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/DAS/biz_no", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valuestring);
        }
        arrayItem = cJSON_GetObjectItem(object, "vars");
        if (arrayItem != NULL)
        {
            int size = cJSON_GetArraySize(arrayItem);
            LOG(LM_DEBUG, Fmtmsg("cJSON_GetArraySize: size=%d", size), "DEBUG");

            for (i = 0; i < size; i++)
            {
                //printf("i=%d\n",i);
                LOG(LM_DEBUG, Fmtmsg("i=%d", i), "DEBUG");
                arrayObject = cJSON_GetArrayItem(arrayItem, i);

                item = cJSON_GetObjectItem(object, "key");
                if (item != NULL)
                {
                    LOG(LM_DEBUG,
                            Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s", item->type, item->string,
                                    item->valuestring), "DEBUG");
                    /* 节点路径 */
                    memset(sXmlnode, 0, sizeof(sXmlnode));
                    sprintf(sXmlnode, "%s/ZmInfo/DAS/vars/key", respnode);
                    xml_SetElement(lXmlhandle, sXmlnode, item->valuestring);
                }

                item = cJSON_GetObjectItem(object, "value");
                if (item != NULL)
                {
                    LOG(LM_DEBUG,
                            Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s", item->type, item->string,
                                    item->valuestring), "DEBUG");
                    /* 节点路径 */
                    memset(sXmlnode, 0, sizeof(sXmlnode));
                    sprintf(sXmlnode, "%s/ZmInfo/DAS/vars/value", respnode);
                    xml_SetElement(lXmlhandle, sXmlnode, item->valuestring);
                }
            }
        }
    }
}

void zm_cJSON_to_IVS(HXMLTREE lXmlhandle, cJSON *json, char *respnode)
{
    char sXmlnode[256];
    cJSON *object = cJSON_GetObjectItem(json, "IVS");
    cJSON *item;
    if (object == NULL)
    {
        LOG(LM_DEBUG, Fmtmsg("Error before: [%s]", cJSON_GetErrorPtr()), "DEBUG");
        cJSON_Delete(json);
    }
    LOG(LM_DEBUG, Fmtmsg("cJSON_GetObjectItem: type=%d, key is %s", object->type, object->string), "DEBUG");

    if (object != NULL)
    {
        item = cJSON_GetObjectItem(object, "success");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valueint=%d", item->type, item->string, item->valueint),
                    "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/IVS/success", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valueint);
        }

        item = cJSON_GetObjectItem(object, "biz_no");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s", item->type, item->string,
                            item->valuestring), "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/IVS/biz_no", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valuestring);
        }

        item = cJSON_GetObjectItem(object, "hit");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s", item->type, item->string,
                            item->valuestring), "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/IVS/biz_no", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valuestring);
        }
    }
}

void zm_cJSON_to_WatchListii(HXMLTREE lXmlhandle, cJSON *json, char *respnode)
{
    char sXmlnode[256];
    cJSON *object = cJSON_GetObjectItem(json, "WatchListii");
    cJSON *item;
    if (object == NULL)
    {
        LOG(LM_DEBUG, Fmtmsg("Error before: [%s]", cJSON_GetErrorPtr()), "DEBUG");
        cJSON_Delete(json);
    }
    LOG(LM_DEBUG, Fmtmsg("cJSON_GetObjectItem: type=%d, key is %s", object->type, object->string), "DEBUG");

    if (object != NULL)
    {
        item = cJSON_GetObjectItem(object, "success");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%d", item->type, item->string,
                            item->valuestring), "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/WatchListii/success", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valuestring);
        }

        item = cJSON_GetObjectItem(object, "biz_no");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s", item->type, item->string,
                            item->valuestring), "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/WatchListii/biz_no", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valuestring);
        }

        item = cJSON_GetObjectItem(object, "is_matched");
        if (item != NULL)
        {
            LOG(LM_DEBUG,
                    Fmtmsg("cJSON_GetObjectItem: type=%d, string is %s, valueint=%d", item->type, item->string, item->valueint),
                    "DEBUG");
            /* 节点路径 */
            memset(sXmlnode, 0, sizeof(sXmlnode));
            sprintf(sXmlnode, "%s/ZmInfo/WatchListii/is_matched", respnode);
            xml_SetElement(lXmlhandle, sXmlnode, item->valueint);
        }
    }
}

int cJSON_to_ZmInfo(HXMLTREE lXmlhandle, char *cZmInfo, char *respnode)
{
    cJSON *json;
    int i;
    char sXmlnode[256];
    json = cJSON_Parse(cZmInfo);
    if (NULL == json)
    {
        LOG(LM_DEBUG, Fmtmsg("Error before: [%s]", cJSON_GetErrorPtr()), "DEBUG");
        return COMPRET_FAIL;
    }
    else
    {
//        zm_cJSON_to_CreditScore(lXmlhandle, json, respnode);
        zm_cJSON_to_DAS(lXmlhandle, json, respnode);
//        zm_cJSON_to_IVS(lXmlhandle, json, respnode);
//        zm_cJSON_to_WatchListii(lXmlhandle, json, respnode);

        cJSON_Delete(json);
    }
    return 0;
}






int cBankInfo_to_Xml(HXMLTREE lXmlhandle, char *cBankInfo, char *respnode)
{
    char sXmlnode[256] =
    { 0 };
    char sElementPath[256];
    char sElementValue[40 + 1];
    cJSON *json = cJSON_CreateObject();

    XML2JSON(cBankInfo, "apply_no");
    cJSON_AddItemToObject(json, "applyNo", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "id_type");
    cJSON_AddItemToObject(json, "certType", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "id_num");
    cJSON_AddItemToObject(json, "certNo", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "is_exist_customer");
    cJSON_AddItemToObject(json, "isExistCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_exist_debt_customer");
    cJSON_AddItemToObject(json, "isExistDebtCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "balance");
    cJSON_AddItemToObject(json, "balance", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "avg_balance_last_3days");
    cJSON_AddItemToObject(json, "avgBalanceLast3days", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "avg_balance_last_6days");
    cJSON_AddItemToObject(json, "avgBalanceLast6days", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "income_last_3m");
    cJSON_AddItemToObject(json, "incomeLast3m", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "pay_last_3m");
    cJSON_AddItemToObject(json, "payLast3m", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "income_last_6m");
    cJSON_AddItemToObject(json, "incomeLast6m", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "pay_last_6m");
    cJSON_AddItemToObject(json, "payLast6m", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "is_exist_credit_customer");
    cJSON_AddItemToObject(json, "isExistCCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "curr_credit_card_amt");
    cJSON_AddItemToObject(json, "applyNo", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "curr_use_credit_card_amt");
    cJSON_AddItemToObject(json, "currDisburseCCAmt", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "is_exist_fin_customer");
    cJSON_AddItemToObject(json, "isExistFinCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "fin_balance");
    cJSON_AddItemToObject(json, "finBalance", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "avg_fin_bal_last_6m");
    cJSON_AddItemToObject(json, "avgFinBalanceLast6m", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "is_exist_insurance_customer");
    cJSON_AddItemToObject(json, "isExistInsuranceCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_exist_loan_customer");
    cJSON_AddItemToObject(json, "isExistLoanCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "operation_loan_bal");
    cJSON_AddItemToObject(json, "operationLoanBal", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "personal_credit_bal");
    cJSON_AddItemToObject(json, "personalCreditBal", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "car_loan_bal");
    cJSON_AddItemToObject(json, "autoLoanBal", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "car_asset");
    cJSON_AddItemToObject(json, "autoAsset", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "house_loan_bal");
    cJSON_AddItemToObject(json, "houseLoanBal", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "house_asset");
    cJSON_AddItemToObject(json, "houseAsset", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "is_stock_customer");
    cJSON_AddItemToObject(json, "isStockCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_third_depository");
    cJSON_AddItemToObject(json, "isThirdDepository", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_payroll_customer");
    cJSON_AddItemToObject(json, "isPayrollCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_social_security_customer");
    cJSON_AddItemToObject(json, "isSocialSecurityCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_life_payment_customer");
    cJSON_AddItemToObject(json, "isLifePaymentCUst", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "company_name");
    cJSON_AddItemToObject(json, "incorporation", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "company_origin");
    cJSON_AddItemToObject(json, "incOrigin", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "position");
    cJSON_AddItemToObject(json, "position", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "position_origin");
    cJSON_AddItemToObject(json, "positionOrigin", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "industry");
    cJSON_AddItemToObject(json, "industry", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "industry_origin");
    cJSON_AddItemToObject(json, "industryOrigin", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "work_years");
    cJSON_AddItemToObject(json, "workYears", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "work_years_origin");
    cJSON_AddItemToObject(json, "workYearsOrigin", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "income");
    cJSON_AddItemToObject(json, "income", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "income_origin");
    cJSON_AddItemToObject(json, "incomeOrigin", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "marriage_status");
    cJSON_AddItemToObject(json, "marriageStatus", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "marriage_origin");
    cJSON_AddItemToObject(json, "marriageOrigin", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_operation");
    cJSON_AddItemToObject(json, "isOperation", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "operation_origin");
    cJSON_AddItemToObject(json, "operationOrigin", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_inner_black_customer");
    cJSON_AddItemToObject(json, "isInnerBlackCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_police_certified");
    cJSON_AddItemToObject(json, "isPoliceCertified", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_court_exec_customer");
    cJSON_AddItemToObject(json, "isCourtExecCust", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_query_house_fund");
    cJSON_AddItemToObject(json, "isQueryHouseFund", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "fund_query_date");
    cJSON_AddItemToObject(json, "fundQueryDate", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "fund_month_amt");
    cJSON_AddItemToObject(json, "fundMonthAmt", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "fund_acct_date");
    cJSON_AddItemToObject(json, "fundAccountDate", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "fund_months_last_6m");
    cJSON_AddItemToObject(json, "fundMonthsLast6m", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "fund_amt_last_6m");
    cJSON_AddItemToObject(json, "fundAmtLast6m", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "fund_total_months");
    cJSON_AddItemToObject(json, "fundTotalMonths", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "fund_total_amt");
    cJSON_AddItemToObject(json, "fundTotalAmt", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "fund_max_amt");
    cJSON_AddItemToObject(json, "fundMaxAmt", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "is_query_social_security");
    cJSON_AddItemToObject(json, "isQuerySocialSecurity", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "social_query_date");
    cJSON_AddItemToObject(json, "socialQueryDate", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "pension_query_month_amt");
    cJSON_AddItemToObject(json, "pensionQueryMonthAmt", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "pension_acct_date");
    cJSON_AddItemToObject(json, "pensionAccountDate", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "pension_months_last_6m");
    cJSON_AddItemToObject(json, "pensionMonthsLast6m", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "pension_amt_last_6m");
    cJSON_AddItemToObject(json, "pensionAmtLast6m", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "pension_total_months");
    cJSON_AddItemToObject(json, "pensionTotalMonths", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "pension_total_amt");
    cJSON_AddItemToObject(json, "pensionTotalAmt", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "medicare_month_amt");
    cJSON_AddItemToObject(json, "medicareMonthAmt", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "medicare_acct_date");
    cJSON_AddItemToObject(json, "medicareAccountDate", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "medicare_months_last_6m");
    cJSON_AddItemToObject(json, "medicareMonthsLast6m", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "medicare_amt_last_6m");
    cJSON_AddItemToObject(json, "medicareAmtLast6m", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "medicare_total_months");
    cJSON_AddItemToObject(json, "medicareTotalMonths", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "medicare_total_amt");
    cJSON_AddItemToObject(json, "medicareTotalAmt", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "is_query_degree");
    cJSON_AddItemToObject(json, "isQueryDegree", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "school_name");
    cJSON_AddItemToObject(json, "schoolName", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "degree_level");
    cJSON_AddItemToObject(json, "degreeLevel", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "degree_type");
    cJSON_AddItemToObject(json, "degreeType", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "entrance_year");
    cJSON_AddItemToObject(json, "entranceYear", cJSON_CreateString(sElementValue));

    XML2JSON(cBankInfo, "is_query_communication");
    cJSON_AddItemToObject(json, "isQueryCommunication", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "communication");
    cJSON_AddItemToObject(json, "communication", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "online_days");
    cJSON_AddItemToObject(json, "onlineDays", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "total_tel_fare");
    cJSON_AddItemToObject(json, "medicareAmtLast6m", cJSON_CreateNumber(atof(sElementValue)));

    XML2JSON(cBankInfo, "total_call_hours");
    cJSON_AddItemToObject(json, "totalCalHours", cJSON_CreateNumber(atoi(sElementValue)));

    XML2JSON(cBankInfo, "is_out_black_customer");
    cJSON_AddItemToObject(json, "isOutBlackCust", cJSON_CreateNumber(atoi(sElementValue)));

    char *buf = cJSON_Print(json);

    memset(sXmlnode, 0, sizeof(sXmlnode));
    sprintf(sXmlnode, "%s", respnode);
    if (xml_AddElement(lXmlhandle, sXmlnode, buf) == FAIL)
    {
        return COMPRET_FAIL;
    }
    return COMPSTATUS_SUCC;
}
