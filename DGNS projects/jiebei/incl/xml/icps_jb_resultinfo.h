#ifndef  __ICPS_JB_RESULT_XML_H__
#define  __ICPS_JB_RESULT_XML_H__
		/* 蚂蚁借呗终审请求单信息 */
		#define XMLNM_ICPS_JB_RESULT_VERSION            			"/jiebei_req/request/head/version"                /*版本号*/
		#define XMLNM_ICPS_JB_RESULT_APPID              			"/jiebei_req/request/head/appId"                  /*系统标识*/
		#define XMLNM_ICPS_JB_RESULT_FUNCTION           			"/jiebei_req/request/head/function"               /*交易编码*/
		#define XMLNM_ICPS_JB_RESULT_REQTIMEZONE        			"/jiebei_req/request/head/reqTimeZone"            /*发送方所在时区*/
		#define XMLNM_ICPS_JB_RESULT_REQTIME            			"/jiebei_req/request/head/reqTime"                /*报文发起时间*/
		#define XMLNM_ICPS_JB_RESULT_REQMSGID           			"/jiebei_req/request/head/reqMsgId"               /*请求报文唯一标示*/
		#define XMLNM_ICPS_JB_RESULT_SIGNTYPE           			"/jiebei_req/request/head/signType"               /*签名算法类型*/
		#define XMLNM_ICPS_JB_RESULT_INPUTCHARSET       			"/jiebei_req/request/head/inputCharset"           /*报文字符编码*/
		#define XMLNM_ICPS_JB_RESULT_RESERVE            			"/jiebei_req/request/head/reserve"                /*预留域*/
		#define XMLNM_ICPS_JB_RESULT_APPLYNO                      "/jiebei_req/request/body/applyNo"                /*申请单号*/
		#define XMLNM_ICPS_JB_RESULT_CERTTYPE                     "/jiebei_req/request/body/certType"               /*证件类型*/
		#define XMLNM_ICPS_JB_RESULT_CERTNO                       "/jiebei_req/request/body/certNo"                 /*证件号码*/
		#define XMLNM_ICPS_JB_RESULT_NAME                         "/jiebei_req/request/body/name"                   /*姓名*/
		#define XMLNM_ICPS_JB_RESULT_PLATFORMACCESS               "/jiebei_req/request/body/platformAccess"         /*本次审批结果，是否通过*/
		#define XMLNM_ICPS_JB_RESULT_PLATFORMREFUSEREASON         "/jiebei_req/request/body/platformRefuseReason"   /*本次审批结果，是否通过*/
		#define XMLNM_ICPS_JB_RESULT_PLATFORMADMIT                "/jiebei_req/request/body/platformAdmit"          /*如果通过，则输出审批额度*/
		#define XMLNM_ICPS_JB_RESULT_PLATFORMRATE                 "/jiebei_req/request/body/platformRate"           /*如果通过，则输出审批基础利率*/
		#define XMLNM_ICPS_JB_RESULT_RISKRATING                   "/jiebei_req/request/body/riskRating"             /*风险评级*/
		#define XMLNM_ICPS_JB_RESULT_SOLVENCYRATINGS              "/jiebei_req/request/body/solvencyRatings"        /*偿债能力评级*/
        #define XMLNM_ICPS_JB_RESULT_CHANGERESULTREASON           "/jiebei_req/request/body/changeResultReason"     /*额度、定价变更原因*/
        /*银行反馈结果 */
        /*
        #define XMLNM_ICPS_JB_RESULT_RESULTCODE                   "/jiebei/drcbank/resultCode"                       / *响应码         * /
        #define XMLNM_ICPS_JB_RESULT_RESULTMSG                    "/jiebei/drcbank/resultMsg"                        / *响应描述       * /
        */
        #define XMLNM_ICPS_JB_RESULT_ISADMIT                      "/jiebei/drcbank/isAdmit"                          /*是否推荐准入   */
        #define XMLNM_ICPS_JB_RESULT_ADMITMSG                     "/jiebei/drcbank/admitMsg"                         /*准入原因       */
          
#endif


