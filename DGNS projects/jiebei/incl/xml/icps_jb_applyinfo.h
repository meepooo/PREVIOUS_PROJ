#ifndef  __ICPS_JB_APPLY_XML_H__
#define  __ICPS_JB_APPLY_XML_H__
		/* 蚂蚁借呗授信请求单信息 */
		#define XMLNM_ICPS_JB_APPLY_VERSION            "/jiebei_req/request/head/version"                /*版本号*/                
		#define XMLNM_ICPS_JB_APPLY_APPID              "/jiebei_req/request/head/appId"                  /*系统标识*/              
		#define XMLNM_ICPS_JB_APPLY_FUNCTION           "/jiebei_req/request/head/function"               /*交易编码*/              
		#define XMLNM_ICPS_JB_APPLY_REQTIMEZONE        "/jiebei_req/request/head/reqTimeZone"            /*发送方所在时区*/        
		#define XMLNM_ICPS_JB_APPLY_REQTIME            "/jiebei_req/request/head/reqTime"                /*报文发起时间*/          
		#define XMLNM_ICPS_JB_APPLY_REQMSGID           "/jiebei_req/request/head/reqMsgId"               /*请求报文唯一标示*/      
		#define XMLNM_ICPS_JB_APPLY_SIGNTYPE           "/jiebei_req/request/head/signType"               /*签名算法类型*/          
		#define XMLNM_ICPS_JB_APPLY_INPUTCHARSET       "/jiebei_req/request/head/inputCharset"           /*报文字符编码*/          
		#define XMLNM_ICPS_JB_APPLY_RESERVE            "/jiebei_req/request/head/reserve"                /*预留域*/                
		#define XMLNM_ICPS_JB_APPLY_APPLYNO            "/jiebei_req/request/body/applyNo"                /*申请单号*/              
		#define XMLNM_ICPS_JB_APPLY_CERTTYPE           "/jiebei_req/request/body/certType"               /*证件类型*/              
		#define XMLNM_ICPS_JB_APPLY_CERTNO             "/jiebei_req/request/body/certNo"                 /*证件号码*/              
		#define XMLNM_ICPS_JB_APPLY_CERTVALIDENDDATE   "/jiebei_req/request/body/certValidEndDate"       /*证件有效期*/            
		#define XMLNM_ICPS_JB_APPLY_NAME               "/jiebei_req/request/body/name"                   /*姓名*/                  
		#define XMLNM_ICPS_JB_APPLY_MOBILENO           "/jiebei_req/request/body/mobileNo"               /*手机号*/                
		#define XMLNM_ICPS_JB_APPLY_ZMAUTHFLAG         "/jiebei_req/request/body/zmAuthFlag"             /*芝麻授权成功表示*/      
		#define XMLNM_ICPS_JB_APPLY_HASJBADMIT         "/jiebei_req/request/body/hasJBAdmit"             /*是否之前就有借呗额度*/  
		#define XMLNM_ICPS_JB_APPLY_OCCUPATION            "/jiebei_req/request/body/pbocInfo/PersonalInfo/Professional/Occupation"        /*职业*/  
		#define XMLNM_ICPS_JB_APPLY_ADDRESS            "/jiebei_req/request/body/extInfo/address"        /*详细地址*/  
		#define XMLNM_ICPS_JB_APPLY_CITY         		"/jiebei_req/request/body/extInfo/city"           /*城市*/  
		#define XMLNM_ICPS_JB_APPLY_PROV         		"/jiebei_req/request/body/extInfo/prov"           /*省份*/  
		#define XMLNM_ICPS_JB_APPLY_AREA         		"/jiebei_req/request/body/extInfo/area"           /*地区*/  
		#define XMLNM_ICPS_JB_APPLY_CUSTOMERNO         		"/jiebei/drcbank/customerno"           /*客户编号*/  
        #define XMLNM_ICPS_JB_APPLY_REQTRACENO             "/icps/req/trans_no"                  /*向小微金融平台请求流水号*/
		/* 银行初审反馈结果  */
		#define XMLNM_ICPS_JB_APPLY_APPLYSTAT          "/jiebei/drcbank/applystat"                /*授信请求单状态 */
		#define XMLNM_ICPS_JB_APPLY_ISADMIT            "/jiebei/drcbank/isAdmit"                /*是否推荐准入*/          
		#define XMLNM_ICPS_JB_APPLY_CREDITNO           "/jiebei/drcbank/creditNo"               /*授信编号*/              
		#define XMLNM_ICPS_JB_APPLY_CREDITAMT          "/jiebei/drcbank/creditAmt"              /*推荐准入时，推荐的额度*/
		#define XMLNM_ICPS_JB_APPLY_CREDITRATE         "/jiebei/drcbank/creditRate"             /*推荐准入时，推荐的利率*/
		#define XMLNM_ICPS_JB_APPLY_REFUSECODE         "/jiebei/drcbank/refuseCode"             /*推荐拒绝时，拒绝码*/    
		#define XMLNM_ICPS_JB_APPLY_REFUSEMSG          "/jiebei/drcbank/refuseMsg"              /*推荐拒绝时，拒绝原因*/     
		#define XMLNM_ICPS_JB_APPLY_RESULTSTAT         "/jiebei/drcbank/resultstat"              /*初审返回状态码 */
        /*蚂蚁初审结果返回结果状态吗 */
		#define XMLNM_ICPS_JB_APPLY_RESPCODE         "/jiebei_resp/response/body/resultInfo/resultCode"             /*处理结果标记*/
		#define XMLNM_ICPS_JB_APPLY_RESPMSG          "/jiebei_resp/response/body/resultInfo/resultMsg"             /*处理结果描述*/
		#define XMLNM_ICPS_JB_APPLY_RETRY            "/jiebei_resp/response/body/resultInfo/retry"             /*是否需要重试*/

          
#endif


