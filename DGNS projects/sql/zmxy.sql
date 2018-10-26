drop table zmxy_qzpfxx;
drop table zmxy_qzpfxx_verify_code;
drop table zmxy_qzpfxx_risk_code;
drop table zmxy_zmpfxx;
drop table zmxy_hygzmdxx;
drop table zmxy_hygzmdxx_details;
drop table zmxy_hygzmdxx_details_extend_info;
drop table zmxy_xtcsb;
drop table zmxy_sjfkhz;
drop table zmxy_sjfkmx;

--==============================================================
-- Table:  zmxy_qzpfxx 
--==============================================================
create table  zmxy_qzpfxx 
(
    transaction_id           VARCHAR(32)               not null,
    product_code             VARCHAR(32),
    cert_type                VARCHAR(32),
    cert_no                  VARCHAR(20),
    name                     VARCHAR(64),
    mobile                   VARCHAR(15),
    email                    VARCHAR(32),
    bank_card                VARCHAR(20),
    address                  VARCHAR(256),
    ip                       VARCHAR(40),
    mac                      VARCHAR(20),
    wifimac                  VARCHAR(20),
    imei                     VARCHAR(16),
    biz_no                   VARCHAR(40),
    score                    CHAR(3),
    hit_risk                 CHAR(5),
    whrq                     CHAR(8),
    cgbz                     CHAR(1),
   constraint  pk_zmxy_qzpfxx  primary key ( transaction_id )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_qzpfxx is
'欺诈评分信息表';

comment on column zmxy_qzpfxx.transaction_id is
'业务凭证流水号';

comment on column zmxy_qzpfxx.product_code is
'产品代码';

comment on column zmxy_qzpfxx.cert_type is
'证件类型';

comment on column zmxy_qzpfxx.cert_no is
'证件号码';

comment on column zmxy_qzpfxx.name is
'姓名';

comment on column zmxy_qzpfxx.mobile is
'手机号码';

comment on column zmxy_qzpfxx.email is
'邮箱';

comment on column zmxy_qzpfxx.bank_card is
'银行卡号码';

comment on column zmxy_qzpfxx.address is
'地址信息';

comment on column zmxy_qzpfxx.ip is
'IP地址';

comment on column zmxy_qzpfxx.mac is
'MAC地址';

comment on column zmxy_qzpfxx.wifimac is
'WIFIMAC地址';

comment on column zmxy_qzpfxx.imei is
'国际移动设备标志';

comment on column zmxy_qzpfxx.biz_no is
'业务号';

comment on column zmxy_qzpfxx.score is
'分数';

comment on column zmxy_qzpfxx.hit_risk is
'命中标志';

comment on column zmxy_qzpfxx.whrq is
'本地维护日期';

comment on column zmxy_qzpfxx.cgbz is
'成功标志，Y-成功，N-失败';


--==============================================================
-- Table:  zmxy_qzpfxx_verify_code 
--==============================================================
create table  zmxy_qzpfxx_verify_code 
(
    transaction_id           VARCHAR(32)               not null,
    verify_code             VARCHAR(20)                not null,
   constraint  pk_zmxy_qzpfxx_verify_code  primary key ( transaction_id, verify_code )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_qzpfxx_verify_code is
'欺诈评分信息匹配信息表';

comment on column zmxy_qzpfxx_verify_code.transaction_id is
'业务凭证流水号';

comment on column zmxy_qzpfxx_verify_code.verify_code is
'匹配信息验证码';


--==============================================================
-- Table:  zmxy_qzpfxx_risk_code 
--==============================================================
create table  zmxy_qzpfxx_risk_code 
(
    transaction_id           VARCHAR(32)               not null,
    risk_code                VARCHAR(20)               not null,
   constraint  pk_zmxy_qzpfxx_risk_code  primary key ( transaction_id, risk_code )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_qzpfxx_risk_code is
'欺诈评分信息风险信息表';

comment on column zmxy_qzpfxx_risk_code.transaction_id is
'业务凭证流水号';

comment on column zmxy_qzpfxx_risk_code.risk_code is
'风险信息验证码';


--==============================================================
-- Table:  zmxy_zmpfxx 
--==============================================================
create table  zmxy_zmpfxx 
(
    transaction_id           VARCHAR(32)               not null,
    product_code             VARCHAR(32)               not null,
    open_id                  VARCHAR(32)               not null,
    biz_no                   VARCHAR(40),               
    zm_score                 CHAR(3),
    whrq                     CHAR(8),
    cgbz                     CHAR(1),
   constraint  pk_zmxy_zmpfxx  primary key ( transaction_id )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_zmpfxx is
'芝麻信用评分信息表';

comment on column zmxy_zmpfxx.transaction_id is
'业务凭证流水号';

comment on column zmxy_zmpfxx.product_code is
'产品代码';

comment on column zmxy_zmpfxx.open_id is
'芝麻会员身份标识';

comment on column zmxy_zmpfxx.biz_no is
'业务号';

comment on column zmxy_zmpfxx.zm_score is
'分数';

comment on column zmxy_zmpfxx.whrq is
'本地维护日期';

comment on column zmxy_zmpfxx.cgbz is
'成功标志，Y-成功，N-失败';


--==============================================================
-- Table:  zmxy_hygzmdxx 
--==============================================================
create table  zmxy_hygzmdxx 
(
    transaction_id           VARCHAR(32)               not null,
    product_code             VARCHAR(32)               not null,
    open_id                  VARCHAR(32)               not null,
    biz_no                   VARCHAR(40),
    is_matched               CHAR(5),
    whrq                     CHAR(8),
    cgbz                     CHAR(1),
   constraint  pk_zmxy_hygzmdxx  primary key ( transaction_id )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_hygzmdxx is
'行业关注名单信息表';

comment on column zmxy_hygzmdxx.transaction_id is
'业务凭证流水号';

comment on column zmxy_hygzmdxx.product_code is
'产品代码';

comment on column zmxy_hygzmdxx.open_id is
'芝麻会员身份标识';

comment on column zmxy_hygzmdxx.biz_no is
'业务号';

comment on column zmxy_hygzmdxx.is_matched is
'命中标志';

comment on column zmxy_hygzmdxx.whrq is
'本地维护日期';

comment on column zmxy_hygzmdxx.cgbz is
'成功标志，Y-成功，N-失败';

--==============================================================
-- Table:  zmxy_hygzmdxx_details 
--==============================================================
create table  zmxy_hygzmdxx_details 
(
    transaction_id       VARCHAR(32)               not null,
    biz_code             VARCHAR(16),
    level                VARCHAR(16),
    type                 VARCHAR(16),
    code                 VARCHAR(16)               not null,
    refresh_time         VARCHAR(20),
    settlement           CHAR(5),
    status               VARCHAR(16),
    statement            VARCHAR(256),
   constraint  pk_zmxy_hygzmdxx_details  primary key ( transaction_id,code )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_hygzmdxx_details is
'行业关注名单信息细节列表';

comment on column zmxy_hygzmdxx_details.transaction_id is
'业务凭证流水号';

comment on column zmxy_hygzmdxx_details.biz_code is
'风险信息行业编码';

comment on column zmxy_hygzmdxx_details.level is
'风险等级';

comment on column zmxy_hygzmdxx_details.type is
'行业名单风险类型';

comment on column zmxy_hygzmdxx_details.code is
'风险编码';

comment on column zmxy_hygzmdxx_details.refresh_time is
'数据刷新时间';

comment on column zmxy_hygzmdxx_details.settlement is
'结算状态';

comment on column zmxy_hygzmdxx_details.status is
'异议处理流程状态';

comment on column zmxy_hygzmdxx_details.statement is
'异议声明';



--==============================================================
-- Table:  zmxy_hygzmdxx_details_extend_info 
--==============================================================
create table  zmxy_hygzmdxx_details_extend_info 
(
    transaction_id       VARCHAR(32)               not null,
    code                 VARCHAR(16)               not null,
    key                  VARCHAR(32)               not null,
    value                VARCHAR(256),
    description          VARCHAR(256),
   constraint  pk_zmxy_hygzmdxx_details_extend_info  primary key ( transaction_id,code,key )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_hygzmdxx_details_extend_info is
'行业关注名单信息细节扩展信息列表';

comment on column zmxy_hygzmdxx_details_extend_info.transaction_id is
'业务凭证流水号';

comment on column zmxy_hygzmdxx_details_extend_info.code is
'风险编码';

comment on column zmxy_hygzmdxx_details_extend_info.key is
'补充信息字段的英文编码';

comment on column zmxy_hygzmdxx_details_extend_info.value is
'补充信息字段的信息内容';

comment on column zmxy_hygzmdxx_details_extend_info.description is
'补充信息字段的中文描述';


--==============================================================
-- Table:  zmxy_xtcsb 
--==============================================================
create table  zmxy_xtcsb 
(
    app_id       VARCHAR(32)               not null,
    charset      VARCHAR(16),
    version      VARCHAR(8),               
    platform     VARCHAR(32),
    type_id      VARCHAR(32),
    columns      VARCHAR(200),
    primary_key_columns  VARCHAR(200),
    update_day   CHAR(2),
    by1          VARCHAR(32),
   constraint  pk_zmxy_xtcsb  primary key ( app_id )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_xtcsb is
'芝麻信用系统参数表';

comment on column zmxy_xtcsb.app_id is
'商户ID';

comment on column zmxy_xtcsb.charset is
'报文字符集';

comment on column zmxy_xtcsb.version is
'接口版本';

comment on column zmxy_xtcsb.platform is
'来源平台';

comment on column zmxy_xtcsb.type_id is
'数据反馈的typeid';

comment on column zmxy_xtcsb.columns is
'数据反馈的单条数据的数据列,以英文逗号分隔';

comment on column zmxy_xtcsb.primary_key_columns is
'数据反馈的明细的主键列,以英文逗号分隔';

comment on column zmxy_xtcsb.update_day is
'芝麻分更新日，06-每月6号更新';

comment on column zmxy_xtcsb.by1 is
'备用字段1';


--==============================================================
-- Table:  zmxy_sjfkhz 
--==============================================================
create table  zmxy_sjfkhz 
(
    zwrq       VARCHAR(8)               not null,
    zhqzlsh    VARCHAR(8)               not null,
    records      VARCHAR(10),
    file_description      VARCHAR(256),               
   constraint  pk_zmxy_sjfkhz  primary key ( zwrq,zhqzlsh )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_sjfkhz is
'芝麻信用数据反馈汇总表';

comment on column zmxy_sjfkhz.zwrq is
'账务日期';

comment on column zmxy_sjfkhz.zhqzlsh is
'综合前置流水号';

comment on column zmxy_sjfkhz.records is
'文件明细记录数';

comment on column zmxy_sjfkhz.file_description is
'文件描述';


--==============================================================
-- Table:  zmxy_sjfkmx 
--==============================================================
create table  zmxy_sjfkmx 
(
    zwrq                       VARCHAR(8)               not null,
    zhqzlsh                    VARCHAR(8)               not null,
    credentials_type           VARCHAR(2),
    credentials_no             VARCHAR(32),
    user_name                  VARCHAR(256),
    order_no                   VARCHAR(64),
    biz_type                   VARCHAR(2), 
    pay_month                  VARCHAR(16),
    gmt_ovd_date               VARCHAR(20),
    order_status               VARCHAR(3),
    create_amt                 VARCHAR(32),
    overdue_days               VARCHAR(10),
    overdue_amt                VARCHAR(32),
    gmt_pay                    VARCHAR(20),
    memo                       VARCHAR(256),
   constraint  pk_zmxy_sjfkmx  primary key ( zwrq,zhqzlsh )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_sjfkmx is
'芝麻信用数据反馈明细表';

comment on column zmxy_sjfkmx.zwrq is
'账务日期';

comment on column zmxy_sjfkmx.zhqzlsh is
'综合前置流水号';

comment on column zmxy_sjfkmx.credentials_type is
'证件类型';

comment on column zmxy_sjfkmx.credentials_no is
'证件号码';

comment on column zmxy_sjfkmx.user_name is
'用户姓名';

comment on column zmxy_sjfkmx.order_no is
'业务号';

comment on column zmxy_sjfkmx.biz_type is
'业务种类';

comment on column zmxy_sjfkmx.pay_month is
'还款月份';

comment on column zmxy_sjfkmx.gmt_ovd_date is
'各阶段日期';

comment on column zmxy_sjfkmx.order_status is
'业务状态';

comment on column zmxy_sjfkmx.create_amt is
'授信额度/放款金额';

comment on column zmxy_sjfkmx.overdue_days is
'当前逾期天数';

comment on column zmxy_sjfkmx.overdue_amt is
'当前逾期总额';

comment on column zmxy_sjfkmx.gmt_pay is
'结清日期';

comment on column zmxy_sjfkmx.memo is
'备注';






insert into zmxy_xtcsb (app_id,charset,version,platform,type_id,columns,primary_key_columns,update_day,by1) values ('300001971','GBK','1.0','zmop','typeid','明细数据列','主键列','06','');
insert into app_cpxx(cpdm,cpmc,yybs,zbjg,ywrqlx,qdkzbz,jgkzcs,sxfbz,sfqybz,qyms,xyxljz,kkfs,jzsx,dzms,lsblts,pdblts,jyfs,rzms,whjg,whgy,whsj,cpzt,sxftkbz)
values('0030021','芝麻信用系统','003','00000','1','1','0','1','0','1','K_DWBH','1','0','2',0,0,'5','0','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'),'0','0');
insert into app_dwxx values('003002110000','芝麻信用系统前置','','','','','','','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'),'','','0');
insert into app_dwcpxy values('003002110000','0030021','003002110000','芝麻信用系统前置','','','','','','','','','','','','','','','','','','',0.00,'00000','admin',to_char(current timestamp,'yyyymmddhh24miss'),'','','0','','','','','','','','','1','','','');
insert into app_txaqxx (ljbs,ljmc,ljlx,dwbh,qdkz,txms,txdz,txdk,whjg,whgy,whsj,txzt)values ('zmxy','芝麻信用','3','003002110000','1','1','10.8.208.140','50043','00000','admin','20180227081818','0');



