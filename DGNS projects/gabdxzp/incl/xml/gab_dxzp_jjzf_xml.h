#ifndef __GAB_DXZP_JJZF_XML_H__
#define __GAB_DXZP_JJZF_XML_H__

    #define XMLNM_GAB_DXZP_ZCZHYH    "/Response/Body/TransferOutBankID"        /*转出账户所属银行机构编码            */
    #define XMLNM_GAB_DXZP_ZCZHYHMC  "/Response/Body/TransferOutBankName"      /*转出账户银行名称                    */
    #define XMLNM_GAB_DXZP_ZCZHM     "/Response/Body/TransferOutAccountName"   /*转出账户名                          */
    #define XMLNM_GAB_DXZP_ZCZH      "/Response/Body/TransferOutAccountNumber" /*转出账号                            */
    //#define XMLNM_GAB_DXZP_BZ        "/Response/Body/Currency"                 /*币种，默认为RMB                     */
    #define XMLNM_GAB_DXZP_ZCJE      "/Response/Body/TransferAmount"           /*转出金额，两位小数                  */
    #define XMLNM_GAB_DXZP_ZCSJ      "/Response/Body/TransferTime"             /*转出时间(yyyyMMddHHmmss)            */
    #define XMLNM_GAB_DXZP_KHYH      "/Response/Body/BankID"                   /*止付账户所属银行机构编码            */
    #define XMLNM_GAB_DXZP_KHYHMC    "/Response/Body/BankName"                 /*止付账户所属银行名称                */
    #define XMLNM_GAB_DXZP_ZHLB      "/Response/Body/AccountType"              /*止付账号类别（01-个人；02-对公）    */
    //#define XMLNM_GAB_DXZP_ZHMC      "/Response/Body/AccountName"              /*止付账户名                          */
    #define XMLNM_GAB_DXZP_ZH        "/Response/Body/AccountNumber"            /*止付账卡号                          */
    #define XMLNM_GAB_DXZP_DQR       "/Response/Body/ExpireTime"               /*止付截止时间(yyyymmddhhmmss)20160413   */
    #define XMLNM_GAB_DXZP_JGFKSJ    "/Response/Body/FeedbackLimit"            /*结果反馈限定时间（小时）            */
    #define XMLNM_GAB_DXZP_SFBLC     "/Response/Body/ApplicationType"          /*是否补流程                        */
    #define XMLNM_GAB_DXZP_YJBSQBH   "/Response/Body/OriginalApplicationID"    /*原举报申请编号                      */
    #define XMLNM_GAB_DXZP_ZFQSSJ    "/Response/Body/StartTime"                /*止付起始时间(yyyymmddhhmmss)         */
    #define XMLNM_GAB_DXZP_ZFJSSJ    "/Response/Body/ExpireTime"               /*止付截止时间(yyyymmddhhmmss)        */
    #define XMLNM_GAB_DXZP_ZFJCSXSJ  "/Response/Body/ApplicationTime"           /*止付解除时间(yyyyMMddHHmmss)       */
    #define XMLNM_GAB_DXZP_ZFYQQSSJ  "/Response/Body/PostponeStartTime"           /*止付解除时间(yyyyMMddHHmmss)       */

#endif

