#ifndef __ICPS_XMLMACRO_H__
#define __ICPS_XMLMACRO_H__



#define XMLNM_APP_JYXX_LSJLBZ                   "/app/jyxx/lsjlbz"                         /*流水记录标志 0 记录 1 不记录*/


/* 当日流水 登记 XML节点宏定义 ---BEGIN */
#define XMLNM_ICPS_REQ_PLT_DATE                 "/icps/req/plt_date"                       /*平台日期*/
#define XMLNM_ICPS_REQ_PLT_TIME                 "/icps/req/plt_time"                       /*平台时间*/
#define XMLNM_ICPS_REQ_PLT_SERIAL               "/icps/req/plt_serial"                     /*平台流水号*/
#define XMLNM_ICPS_REQ_BUSI_DATE                "/icps/req/busi_date"                      /*业务日期*/
#define XMLNM_ICPS_REQ_BUSI_NO                  "/icps/req/busi_no"                        /*业务编号*/
#define XMLNM_ICPS_REQ_CHANNEL                  "/icps/req/channel"                        /*渠道代码*/
#define XMLNM_ICPS_REQ_LOCAL_ID                 "/icps/req/local_id"                       /*本行机构标识*/
#define XMLNM_ICPS_REQ_TRANS_CODE               "/icps/req/trans_code"                     /*平台交易代码*/
#define XMLNM_ICPS_REQ_SEND_RECV_FLAG           "/icps/req/send_recv_flag"                 /*往来账标志*/
#define XMLNM_ICPS_REQ_APPLY_NO                 "/icps/req/apply_no"                       /*申请单号*/
#define XMLNM_ICPS_REQ_VERSION                  "/icps/req/version"                        /*版本号*/
#define XMLNM_ICPS_REQ_SEND_TIME_ZONE           "/icps/req/send_time_zone"                 /*发送方所在时区*/
#define XMLNM_ICPS_REQ_SEND_DTTM                "/icps/req/send_dttm"                      /*报文发起时间*/
#define XMLNM_ICPS_REQ_MSG_ID                   "/icps/req/msg_id"                         /*请求报文标示号*/
#define XMLNM_ICPS_REQ_THIRD_ID                 "/icps/req/third_id"                       /*第三方机构标识*/
#define XMLNM_ICPS_REQ_THIRD_TRANS_CODE         "/icps/req/third_trans_code"               /*第三方交易代码*/
#define XMLNM_ICPS_REQ_THIRD_RESPCODE           "/icps/req/third_respcode"                 /*第三方响应码*/
#define XMLNM_ICPS_REQ_THIRD_RESPMSG            "/icps/req/third_respmsg"                  /*第三方响应信息*/
#define XMLNM_ICPS_REQ_THIRD_TRANS_STATUS       "/icps/req/third_trans_status"             /*第三方交易状态*/
#define XMLNM_ICPS_REQ_RETRY                    "/icps/req/retry"                          /*是否需要重试标记*/
#define XMLNM_ICPS_REQ_SEND_HOST_SERIAL         "/icps/req/send_host_serial"               /*上送主机流水号*/
#define XMLNM_ICPS_REQ_SEND_HOST_DATE           "/icps/req/send_host_date"                 /*上送主机日期*/
#define XMLNM_ICPS_REQ_HOST_SERIAL              "/icps/req/host_serial"                    /*主机流水号*/
#define XMLNM_ICPS_REQ_HOST_DATE                "/icps/req/host_date"                      /*主机日期*/
#define XMLNM_ICPS_REQ_HOST_TRANS_CODE          "/icps/req/host_trans_code"                /*主机交易代码*/
#define XMLNM_ICPS_REQ_HOST_RESPCODE            "/icps/req/host_respcode"                  /*主机响应码*/
#define XMLNM_ICPS_REQ_HOST_RESPMSG             "/icps/req/host_respmsg"                   /*主机响应信息*/
#define XMLNM_ICPS_REQ_HOST_STATUS              "/icps/req/host_status"                    /*主机交易状态*/
#define XMLNM_ICPS_REQ_IN_CHANNEL_DATE          "/icps/req/in_channel_date"                /*行内渠道日期*/
#define XMLNM_ICPS_REQ_IN_CHANNEL_SERIAL        "/icps/req/in_channel_serial"              /*行内渠道流水号*/
#define XMLNM_ICPS_REQ_RESPCODE                 "/icps/req/respcode"                       /*交易响应码*/
#define XMLNM_ICPS_REQ_RESPMSG                  "/icps/req/respmsg"                        /*交易响应信息*/
#define XMLNM_ICPS_REQ_TRANS_STATUS             "/icps/req/trans_status"                   /*交易状态*/
#define XMLNM_ICPS_REQ_BRANCH                   "/icps/req/branch"                         /*交易机构*/
#define XMLNM_ICPS_REQ_TELLER                   "/icps/req/teller"                         /*交易柜员*/
#define XMLNM_ICPS_REQ_GRANT_BRANCH             "/icps/req/grant_branch"                   /*授权机构*/
#define XMLNM_ICPS_REQ_GRANT_TELLER             "/icps/req/grant_teller"                   /*授权柜员*/
#define XMLNM_ICPS_REQ_EXTEND_PARAM1            "/icps/req/extend_param1"                  /*扩展1*/
#define XMLNM_ICPS_REQ_EXTEND_PARAM2            "/icps/req/extend_param2"                  /*扩展2*/
#define XMLNM_ICPS_REQ_EXTEND_PARAM3            "/icps/req/extend_param3"                  /*扩展3*/
#define XMLNM_ICPS_REQ_EXTEND_PARAM4            "/icps/req/extend_param4"                  /*扩展4*/
#define XMLNM_ICPS_REQ_EXTEND_PARAM5            "/icps/req/extend_param5"                  /*扩展5*/
/* 当日流水 登记 XML节点宏定义 ---END */

/* 当日流水 更新 XML节点宏定义 ---BEGIN */
#define XMLNM_ICPS_RESP_PLT_DATE                "/icps/resp/plt_date"                      /*平台日期*/
#define XMLNM_ICPS_RESP_PLT_TIME                "/icps/resp/plt_time"                      /*平台时间*/
#define XMLNM_ICPS_RESP_PLT_SERIAL              "/icps/resp/plt_serial"                    /*平台流水号*/
#define XMLNM_ICPS_RESP_BUSI_DATE               "/icps/resp/busi_date"                     /*业务日期*/
#define XMLNM_ICPS_RESP_BUSI_NO                 "/icps/resp/busi_no"                       /*业务编号*/
#define XMLNM_ICPS_RESP_CHANNEL                 "/icps/resp/channel"                       /*渠道代码*/
#define XMLNM_ICPS_RESP_LOCAL_ID                "/icps/resp/local_id"                      /*本行机构标识*/
#define XMLNM_ICPS_RESP_TRANS_CODE              "/icps/resp/trans_code"                    /*平台交易代码*/
#define XMLNM_ICPS_RESP_SEND_RECV_FLAG          "/icps/resp/send_recv_flag"                /*往来账标志*/
#define XMLNM_ICPS_RESP_APPLY_NO                "/icps/resp/apply_no"                      /*申请单号*/
#define XMLNM_ICPS_RESP_VERSION                 "/icps/resp/version"                       /*版本号*/
#define XMLNM_ICPS_RESP_SEND_TIME_ZONE          "/icps/resp/send_time_zone"                /*发送方所在时区*/
#define XMLNM_ICPS_RESP_SEND_DTTM               "/icps/resp/send_dttm"                     /*报文发起时间*/
#define XMLNM_ICPS_RESP_MSG_ID                  "/icps/resp/msg_id"                        /*请求报文标示号*/
#define XMLNM_ICPS_RESP_THIRD_ID                "/icps/resp/third_id"                      /*第三方机构标识*/
#define XMLNM_ICPS_RESP_THIRD_TRANS_CODE        "/icps/resp/third_trans_code"              /*第三方交易代码*/
#define XMLNM_ICPS_RESP_THIRD_RESPCODE          "/icps/resp/third_respcode"                /*第三方响应码*/
#define XMLNM_ICPS_RESP_THIRD_RESPMSG           "/icps/resp/third_respmsg"                 /*第三方响应信息*/
#define XMLNM_ICPS_RESP_THIRD_TRANS_STATUS      "/icps/resp/third_trans_status"            /*第三方交易状态*/
#define XMLNM_ICPS_RESP_RETRY                   "/icps/resp/retry"                         /*是否需要重试标记*/
#define XMLNM_ICPS_RESP_SEND_HOST_SERIAL        "/icps/resp/send_host_serial"              /*上送主机流水号*/
#define XMLNM_ICPS_RESP_SEND_HOST_DATE          "/icps/resp/send_host_date"                /*上送主机日期*/
#define XMLNM_ICPS_RESP_HOST_SERIAL             "/icps/resp/host_serial"                   /*主机流水号*/
#define XMLNM_ICPS_RESP_HOST_DATE               "/icps/resp/host_date"                     /*主机日期*/
#define XMLNM_ICPS_RESP_HOST_TRANS_CODE         "/icps/resp/host_trans_code"               /*主机交易代码*/
#define XMLNM_ICPS_RESP_HOST_RESPCODE           "/icps/resp/host_respcode"                 /*主机响应码*/
#define XMLNM_ICPS_RESP_HOST_RESPMSG            "/icps/resp/host_respmsg"                  /*主机响应信息*/
#define XMLNM_ICPS_RESP_HOST_STATUS             "/icps/resp/host_status"                   /*主机交易状态*/
#define XMLNM_ICPS_RESP_RESPCODE                "/icps/resp/respcode"                      /*交易响应码*/
#define XMLNM_ICPS_RESP_RESPMSG                 "/icps/resp/respmsg"                       /*交易响应信息*/
#define XMLNM_ICPS_RESP_TRANS_STATUS            "/icps/resp/trans_status"                  /*交易状态*/
#define XMLNM_ICPS_RESP_BRANCH                  "/icps/resp/branch"                        /*交易机构*/
#define XMLNM_ICPS_RESP_TELLER                  "/icps/resp/teller"                        /*交易柜员*/
#define XMLNM_ICPS_RESP_GRANT_BRANCH            "/icps/resp/grant_branch"                  /*授权机构*/
#define XMLNM_ICPS_RESP_GRANT_TELLER            "/icps/resp/grant_teller"                  /*授权柜员*/
#define XMLNM_ICPS_RESP_EXTEND_PARAM1           "/icps/resp/extend_param1"                 /*扩展1*/
#define XMLNM_ICPS_RESP_EXTEND_PARAM2           "/icps/resp/extend_param2"                 /*扩展2*/
#define XMLNM_ICPS_RESP_EXTEND_PARAM3           "/icps/resp/extend_param3"                 /*扩展3*/
#define XMLNM_ICPS_RESP_EXTEND_PARAM4           "/icps/resp/extend_param4"                 /*扩展4*/
#define XMLNM_ICPS_RESP_EXTEND_PARAM5           "/icps/resp/extend_param5"                 /*扩展5*/
/* 当日流水 更新 XML节点宏定义 ---END */

/* 日终状态 XML节点宏定义 ---BEGIN */
#define XMLNM_ICPS_DAILY_STATUS_BUSI_DATE                     "/icps/daily_status/busi_date"                        /*业务日期*/
#define XMLNM_ICPS_DAILY_STATUS_BUSI_NO                       "/icps/daily_status/busi_no"                          /*业务编号*/
#define XMLNM_ICPS_DAILY_STATUS_FILE_STEP                     "/icps/daily_status/file_step"                        /*文件步点*/
#define XMLNM_ICPS_DAILY_STATUS_THIRD_PRE_CHECK_STATUS       "/icps/daily_status/third_pre_check_status"          /*第三方预对账状态  */
#define XMLNM_ICPS_DAILY_STATUS_THIRD_CHECK_STATUS           "/icps/daily_status/third_check_status"              /*第三方对账状态    */
#define XMLNM_ICPS_DAILY_STATUS_SUBJECT_ACCT_ENTER_STATUS    "/icps/daily_status/subject_acct_enter_status"         /*科目入账状态*/
#define XMLNM_ICPS_DAILY_STATUS_SUBJECT_CHECK_STATUS         "/icps/daily_status/subject_check_status"            /*科目对账状态  */
#define XMLNM_ICPS_DAILY_STATUS_BUSINESS_STATUS              "/icps/daily_status/business_status"                 /*业务对账状态      */
#define XMLNM_ICPS_DAILY_STATUS_HOST_TOTAL_CHECK_STATUS      "/icps/daily_status/host_total_check_status"         /*核心总账对账状态  */
#define XMLNM_ICPS_DAILY_STATUS_HOST_DETAIL_CHECK_STATUS     "/icps/daily_status/host_detail_check_status"        /*核心明细对账状态  */
#define XMLNM_ICPS_DAILY_STATUS_CLEAR_STATUS                 "/icps/daily_status/clear_status"                    /*清算状态          */
#define XMLNM_ICPS_DAILY_STATUS_PLT_DATE                      "/icps/daily_status/plt_date"                        /*平台日期*/
#define XMLNM_ICPS_DAILY_STATUS_PLT_SERIAL                    "/icps/daily_status/plt_serial"                      /*平台流水号*/
#define XMLNM_ICPS_DAILY_STATUS_SEND_HOST_DATE                "/icps/daily_status/send_host_date"                  /*上送主机日期*/
#define XMLNM_ICPS_DAILY_STATUS_HOST_SERIAL                   "/icps/daily_status/host_serial"                     /*主机流水号*/
#define XMLNM_ICPS_DAILY_STATUS_HOST_DATE                     "/icps/daily_status/host_date"                       /*主机日期*/
#define XMLNM_ICPS_DAILY_STATUS_RESPCODE                      "/icps/daily_status/respcode"                        /*交易响应码*/
#define XMLNM_ICPS_DAILY_STATUS_RESPMSG                       "/icps/daily_status/respmsg"                         /*交易响应信息*/
#define XMLNM_ICPS_DAILY_STATUS_TRANS_STATUS                  "/icps/daily_status/trans_status"                    /*交易状态*/
#define XMLNM_ICPS_DAILY_STATUS_BRANCH                        "/icps/daily_status/branch"                          /*交易机构*/
#define XMLNM_ICPS_DAILY_STATUS_TELLER                        "/icps/daily_status/teller"                          /*交易柜员*/
#define XMLNM_ICPS_DAILY_STATUS_EXTEND_PARAM1                 "/icps/daily_status/extend_param1"                   /*扩展1*/
#define XMLNM_ICPS_DAILY_STATUS_EXTEND_PARAM2                 "/icps/daily_status/extend_param2"                   /*扩展2*/
#define XMLNM_ICPS_DAILY_STATUS_EXTEND_PARAM3                 "/icps/daily_status/extend_param3"                   /*扩展3*/
/* 日终状态 XML节点宏定义 ---END */


#define XMLNM_ICPS_REQ_FILEINS_STATUS                         "/icps/req/fileins_status"                            /*文件入库状态 9-初始 0成功 1-部分成功 2-失败*/
#endif
