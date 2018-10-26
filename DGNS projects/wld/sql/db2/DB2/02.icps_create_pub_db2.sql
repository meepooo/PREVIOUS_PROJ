drop table ICPS_SERIAL;

drop table ICPS_BUSI_INF;

drop table ICPS_DAILY_STATUS;

drop table ICPS_FILE_INFO;



/*==============================================================*/
/* Table: ICPS_SERIAL                                           */
/*==============================================================*/
create table ICPS_SERIAL 
(
   plt_date             CHAR(8)              not null,
   plt_time             CHAR(6)              not null,
   plt_serial           VARCHAR(16)          not null,
   busi_date            VARCHAR(8)           not null,
   busi_no              VARCHAR(16)          not null,
   channel              VARCHAR(16),
   local_id             VARCHAR(32),
   trans_code           VARCHAR(8),
   send_recv_flag       CHAR(1),
   apply_no             VARCHAR(64),
   version              VARCHAR(8),
   send_time_zone       VARCHAR(32),
   send_dttm            VARCHAR(16),
   msg_id               VARCHAR(64),
   third_id             VARCHAR(32),
   third_trans_code     VARCHAR(64),
   third_respcode       VARCHAR(16),
   third_respmsg        VARCHAR(255),
   third_trans_status   VARCHAR(1),
   retry                CHAR(1),
   send_host_serial     VARCHAR(64),
   send_host_date       CHAR(8),
   host_serial          VARCHAR(64),
   host_date            CHAR(8),
   host_trans_code      VARCHAR(16),
   host_respcode        VARCHAR(16),
   host_respmsg         VARCHAR(250),
   host_status          VARCHAR(2),
   in_channel_date      VARCHAR(64),
   in_channel_serial    VARCHAR(8),
   respcode             VARCHAR(8),
   respmsg              VARCHAR(250),
   trans_status         VARCHAR(1),
   branch               VARCHAR(16),
   teller               VARCHAR(16),
   grant_branch         VARCHAR(16),
   grant_teller         VARCHAR(16),
   extend_param1        VARCHAR(10),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   extend_param4        VARCHAR(60),
   extend_param5        VARCHAR(250),
   constraint PK_ICPS_SERIAL primary key (plt_date, plt_serial)
);

comment on table ICPS_SERIAL is
'当日流水表';

comment on column ICPS_SERIAL.plt_date is
'平台日期YYYYMMDD';

comment on column ICPS_SERIAL.plt_time is
'平台时间HHMMSS';

comment on column ICPS_SERIAL.plt_serial is
'平台流水号';

comment on column ICPS_SERIAL.busi_date is
'业务日期';

comment on column ICPS_SERIAL.busi_no is
'业务编号 jiebei-借呗 jintiao-金条 wbank-微粒贷';

comment on column ICPS_SERIAL.channel is
'渠道代码 311-借呗 312-京东金条 313-微粒贷';

comment on column ICPS_SERIAL.local_id is
'本行机构标识';

comment on column ICPS_SERIAL.trans_code is
'平台交易代码';

comment on column ICPS_SERIAL.send_recv_flag is
'往来账标志 0-来账 1-往账';

comment on column ICPS_SERIAL.apply_no is
'申请单号';

comment on column ICPS_SERIAL.version is
'版本号 接口版本';

comment on column ICPS_SERIAL.send_time_zone is
'发送方所在时区 UTC+8';

comment on column ICPS_SERIAL.send_dttm is
'报文发起时间 YYYYMMDDHHMMSS';

comment on column ICPS_SERIAL.msg_id is
'请求报文标示号';

comment on column ICPS_SERIAL.third_id is
'第三方机构标识';

comment on column ICPS_SERIAL.third_trans_code is
'第三方交易代码';

comment on column ICPS_SERIAL.third_respcode is
'第三方响应码';

comment on column ICPS_SERIAL.third_respmsg is
'第三方响应信息';

comment on column ICPS_SERIAL.third_trans_status is
'第三方交易状态';

comment on column ICPS_SERIAL.retry is
'是否需要重试标记 Y-需要 N-不需要';

comment on column ICPS_SERIAL.send_host_serial is
'上送主机流水号';

comment on column ICPS_SERIAL.send_host_date is
'上送主机日期';

comment on column ICPS_SERIAL.host_serial is
'主机流水号';

comment on column ICPS_SERIAL.host_date is
'主机日期';

comment on column ICPS_SERIAL.host_trans_code is
'主机交易代码';

comment on column ICPS_SERIAL.host_respcode is
'主机响应码';

comment on column ICPS_SERIAL.host_respmsg is
'主机响应信息';

comment on column ICPS_SERIAL.host_status is
'主机交易状态';

comment on column ICPS_SERIAL.in_channel_date is
'行内渠道日期';

comment on column ICPS_SERIAL.in_channel_serial is
'行内渠道流水号';

comment on column ICPS_SERIAL.respcode is
'交易响应码';

comment on column ICPS_SERIAL.respmsg is
'交易响应信息';

comment on column ICPS_SERIAL.trans_status is
'交易状态';

comment on column ICPS_SERIAL.branch is
'交易机构';

comment on column ICPS_SERIAL.teller is
'交易柜员';

comment on column ICPS_SERIAL.grant_branch is
'授权机构';

comment on column ICPS_SERIAL.grant_teller is
'授权柜员';

comment on column ICPS_SERIAL.extend_param1 is
'扩展1';

comment on column ICPS_SERIAL.extend_param2 is
'扩展2';

comment on column ICPS_SERIAL.extend_param3 is
'扩展3';

comment on column ICPS_SERIAL.extend_param4 is
'扩展4';

comment on column ICPS_SERIAL.extend_param5 is
'扩展5';


/*==============================================================*/
/* Table: ICPS_BUSI_INF                                         */
/*==============================================================*/
create table ICPS_BUSI_INF 
(
   busi_no              VARCHAR(16)         not null,
   busi_nm              VARCHAR(64),
   local_id             VARCHAR(16),
   time_zone            VARCHAR(32),
   sign_type            VARCHAR(16),
   message_charset      VARCHAR(16),
   version              VARCHAR(8)          not null,
   clear_acct_id        VARCHAR(64),
   clear_acct_nm        VARCHAR(128),
   position_acct_id     VARCHAR(64),
   position_acct_nm     VARCHAR(128),
   fee_out_acct_id      VARCHAR(64),
   fee_out_acct_nm      VARCHAR(128),
   fee_in_acct_id       VARCHAR(64),
   fee_in_acct_nm       VARCHAR(128),
   provisions_acct_id   VARCHAR(64),
   provisions_acct_nm   VARCHAR(128),
   open_flag            CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_BUSI_INF primary key (busi_no)
);

comment on table ICPS_BUSI_INF is
'业务信息表';

comment on column ICPS_BUSI_INF.busi_no is
'业务编号 jiebei-借呗 jintiao-金条 wbank-微粒贷';

comment on column ICPS_BUSI_INF.busi_nm is
'业务名称';

comment on column ICPS_BUSI_INF.local_id is
'本机构代码';

comment on column ICPS_BUSI_INF.time_zone is
'本机构时区';

comment on column ICPS_BUSI_INF.sign_type is
'签名算法类型 RSA';

comment on column ICPS_BUSI_INF.message_charset is
'报文字符编码';

comment on column ICPS_BUSI_INF.version is
'版本号';

comment on column ICPS_BUSI_INF.clear_acct_id is
'内部清算账号';

comment on column ICPS_BUSI_INF.clear_acct_nm is
'内部清算账号名称';

comment on column ICPS_BUSI_INF.position_acct_id is
'内部头寸账号';

comment on column ICPS_BUSI_INF.position_acct_nm is
'内部头寸账号名称';

comment on column ICPS_BUSI_INF.fee_out_acct_id is
'手续费支出账号';

comment on column ICPS_BUSI_INF.fee_out_acct_nm is
'手续费支出账号名称';

comment on column ICPS_BUSI_INF.fee_in_acct_id is
'手续费收入账号';

comment on column ICPS_BUSI_INF.fee_in_acct_nm is
'手续费收入账号名称';

comment on column ICPS_BUSI_INF.provisions_acct_id is
'第三方备付金账号';

comment on column ICPS_BUSI_INF.provisions_acct_nm is
'第三方备付金账号名称';

comment on column ICPS_BUSI_INF.open_flag is
'开通标识 0-未开通 1-开通';

comment on column ICPS_BUSI_INF.extend_param1 is
'扩展1';

comment on column ICPS_BUSI_INF.extend_param2 is
'扩展2';

comment on column ICPS_BUSI_INF.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_DAILY_STATUS                                     */
/*==============================================================*/
create table ICPS_DAILY_STATUS 
(
   busi_date            CHAR(8)              not null,
   busi_no              VARCHAR(16)          not null,
   file_step            CHAR(2),
   third_total_check_status CHAR(1),
   third_detail_check_status CHAR(1),
   host_total_check_status CHAR(1),
   host_detail_check_status CHAR(1),
   third_pre_total_check_status CHAR(1),
   third_pre_detail_check_status CHAR(1),
   host_pre_total_check_status CHAR(1),
   host_pre_detail_check_status CHAR(1),
   plt_date             CHAR(8),
   plt_serial           VARCHAR(16),
   send_host_date       CHAR(8),
   host_serial          VARCHAR(64),
   host_date            CHAR(8),
   respcode             VARCHAR(8),
   respmsg              VARCHAR(250),
   trans_status         VARCHAR(1),
   branch               VARCHAR(16),
   teller               VARCHAR(16),
   extend_param1        VARCHAR(10),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_DAILY_STATUS primary key (busi_date, busi_no)
);

comment on table ICPS_DAILY_STATUS is
'日终状态表';

comment on column ICPS_DAILY_STATUS.busi_date is
'业务日期';

comment on column ICPS_DAILY_STATUS.busi_no is
'业务编号 jiebei-借呗 jintiao-金条 wbank-微粒贷';

comment on column ICPS_DAILY_STATUS.file_step is
'文件步点 00-获取中 01-获取成功 02-部分获取成功 03-获取失败 04-入库中 05-入库成功 06-部分入库成功 07-入库失败 99-初始';

comment on column ICPS_DAILY_STATUS.third_total_check_status is
'第三方对总账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中';

comment on column ICPS_DAILY_STATUS.third_detail_check_status is
'第三方明细对账状态  0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中';

comment on column ICPS_DAILY_STATUS.host_total_check_status is
'核心对总账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中';

comment on column ICPS_DAILY_STATUS.host_detail_check_status is
'核心明细对账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中';

comment on column ICPS_DAILY_STATUS.third_pre_total_check_status is
'第三方预对总账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中';

comment on column ICPS_DAILY_STATUS.third_pre_detail_check_status is
'第三方预明细对账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中';

comment on column ICPS_DAILY_STATUS.host_pre_total_check_status is
'核心预对总账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中';

comment on column ICPS_DAILY_STATUS.host_pre_detail_check_status is
'核心预明细对账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中';

comment on column ICPS_DAILY_STATUS.plt_date is
'平台日期YYYYMMDD';

comment on column ICPS_DAILY_STATUS.plt_serial is
'平台流水号';

comment on column ICPS_DAILY_STATUS.send_host_date is
'上送主机日期';

comment on column ICPS_DAILY_STATUS.host_serial is
'主机流水号';

comment on column ICPS_DAILY_STATUS.host_date is
'主机日期';

comment on column ICPS_DAILY_STATUS.respcode is
'交易响应码';

comment on column ICPS_DAILY_STATUS.respmsg is
'交易响应信息';

comment on column ICPS_DAILY_STATUS.trans_status is
'交易状态';

comment on column ICPS_DAILY_STATUS.branch is
'交易机构';

comment on column ICPS_DAILY_STATUS.teller is
'交易柜员';

comment on column ICPS_DAILY_STATUS.extend_param1 is
'扩展1';

comment on column ICPS_DAILY_STATUS.extend_param2 is
'扩展2';

comment on column ICPS_DAILY_STATUS.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_FILE_INFO                                        */
/*==============================================================*/
create table ICPS_FILE_INFO 
(
   busi_date            VARCHAR(8)          not null,
   busi_no              VARCHAR(16)         not null,
   file_type            VARCHAR(60)         not null,
   md5_code             VARCHAR(64),
   file_status          CHAR(1),
   plt_date             CHAR(8),
   plt_serial           VARCHAR(16),
   extend_param1        VARCHAR(10),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_FILE_INFO primary key (busi_date, busi_no, file_type)
);

comment on table ICPS_FILE_INFO is
'文件信息管理表';

comment on column ICPS_FILE_INFO.busi_date is
'业务日期';

comment on column ICPS_FILE_INFO.busi_no is
'业务编号 jiebei-借呗 jintiao-金条 wbank-微粒贷';

comment on column ICPS_FILE_INFO.file_type is
'文件类型';

comment on column ICPS_FILE_INFO.md5_code is
'MD5值 16进制字符串';

comment on column ICPS_FILE_INFO.file_status is
'文件状态';

comment on column ICPS_FILE_INFO.plt_date is
'平台日期YYYYMMDD';

comment on column ICPS_FILE_INFO.plt_serial is
'平台流水号';

comment on column ICPS_FILE_INFO.extend_param1 is
'扩展1';

comment on column ICPS_FILE_INFO.extend_param2 is
'扩展2';

comment on column ICPS_FILE_INFO.extend_param3 is
'扩展3';