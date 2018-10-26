drop table ICPS_JT_LOAN_TOTAL;

drop table ICPS_JT_CUS;

drop table ICPS_JT_CUSCREDIT;

drop table ICPS_JT_QUOTAADJUST;

drop table ICPS_JT_LOAN;

drop table ICPS_JT_PLAN;

drop table ICPS_JT_FLOW;

drop table ICPS_JT_FUND_DETAIL;


/*==============================================================*/
/* Table: ICPS_JT_LOAN_TOTAL                                    */
/*==============================================================*/
create table ICPS_JT_LOAN_TOTAL 
(
   busi_date            CHAR(8)              not null,
   encash_amt           DECIMAL(16,2),
   prin_to_ovd_prin_amt DECIMAL(16,2),
   non_prin_to_ovd_prin_amt DECIMAL(16,2),
   accrued_to_non_ovd_prin_amt DECIMAL(16,2),
   in_int_to_ovd_int_amt DECIMAL(16,2),
   out_int_to_ovd_int_amt DECIMAL(16,2),
   in_to_out_ovd_int_amt DECIMAL(16,2),
   in_to_out_pnlt_int_amt DECIMAL(16,2),
   in_refund_ovd_int_amt DECIMAL(16,2),
   paid_prin_amt        DECIMAL(16,2),
   paid_accrued_ovd_prin_amt DECIMAL(16,2),
   paid_non_accrued_ovd_prin_amt DECIMAL(16,2),
   paid_int_amt         DECIMAL(16,2),
   paid_in_ovd_int_amt  DECIMAL(16,2),
   paid_out_ovd_int_amt DECIMAL(16,2),
   paid_in_pnlt_int_amt DECIMAL(16,2),
   paid_out_pnlt_int_amt DECIMAL(16,2),
   ahead_prin_amt       DECIMAL(16,2),
   ahead_int_amt        DECIMAL(16,2),
   refund_prin_amt      DECIMAL(16,2),
   refund_ovd_prin_amt  DECIMAL(16,2),
   refund_in_pnlt_int   DECIMAL(16,2),
   encash_amt2          DECIMAL(16,2),
   prin_to_ovd_prin_amt2 DECIMAL(16,2),
   non_prin_to_ovd_prin_amt2 DECIMAL(16,2),
   accrued_to_non_ovd_prin_amt2 DECIMAL(16,2),
   in_int_to_ovd_int_amt2 DECIMAL(16,2),
   out_int_to_ovd_int_amt2 DECIMAL(16,2),
   in_to_out_ovd_int_amt2 DECIMAL(16,2),
   in_to_out_pnlt_int_amt2 DECIMAL(16,2),
   in_refund_ovd_int_amt2 DECIMAL(16,2),
   paid_prin_amt2       DECIMAL(16,2),
   paid_accrued_ovd_prin_amt2 DECIMAL(16,2),
   paid_non_accrued_ovd_prin_amt2 DECIMAL(16,2),
   paid_int_amt2        DECIMAL(16,2),
   paid_in_ovd_int_amt2 DECIMAL(16,2),
   paid_out_ovd_int_amt2 DECIMAL(16,2),
   paid_in_pnlt_int_amt2 DECIMAL(16,2),
   paid_out_pnlt_int_amt2 DECIMAL(16,2),
   ahead_prin_amt2      DECIMAL(16,2),
   ahead_int_amt2       DECIMAL(16,2),
   refund_prin_amt2     DECIMAL(16,2),
   refund_ovd_prin_amt2 DECIMAL(16,2),
   refund_in_pnlt_int_amt2 DECIMAL(16,2),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_LOAN_TOTAL primary key (busi_date)
);

comment on table ICPS_JT_LOAN_TOTAL is
'汇总记账表';

comment on column ICPS_JT_LOAN_TOTAL.busi_date is
'业务日期';

comment on column ICPS_JT_LOAN_TOTAL.encash_amt is
'短期贷款放款资金';

comment on column ICPS_JT_LOAN_TOTAL.prin_to_ovd_prin_amt is
'短期贷款正常本金转逾期本金（应计）';

comment on column ICPS_JT_LOAN_TOTAL.non_prin_to_ovd_prin_amt is
'短期贷款正常本金转逾期本金（非应计）';

comment on column ICPS_JT_LOAN_TOTAL.accrued_to_non_ovd_prin_amt is
'短期贷款逾期本金（应计）转逾期本金（非应计）';

comment on column ICPS_JT_LOAN_TOTAL.in_int_to_ovd_int_amt is
'短期贷款正常利息转逾期利息（表内）';

comment on column ICPS_JT_LOAN_TOTAL.out_int_to_ovd_int_amt is
'短期贷款正常利息转逾期利息（表外）';

comment on column ICPS_JT_LOAN_TOTAL.in_to_out_ovd_int_amt is
'短期贷款逾期利息（表内）转逾期利息（表外）';

comment on column ICPS_JT_LOAN_TOTAL.in_to_out_pnlt_int_amt is
'短期贷款罚息（表内）转罚息（表外）';

comment on column ICPS_JT_LOAN_TOTAL.in_refund_ovd_int_amt is
'短期退货还款冲销的逾期利息（表内）';

comment on column ICPS_JT_LOAN_TOTAL.paid_prin_amt is
'实还短期正常贷款本金';

comment on column ICPS_JT_LOAN_TOTAL.paid_accrued_ovd_prin_amt is
'实还短期逾期贷款本金（应计）';

comment on column ICPS_JT_LOAN_TOTAL.paid_non_accrued_ovd_prin_amt is
'实还短期逾期贷款本金（非应计）';

comment on column ICPS_JT_LOAN_TOTAL.paid_int_amt is
'实还短期正常贷款利息';

comment on column ICPS_JT_LOAN_TOTAL.paid_in_ovd_int_amt is
'实还短期逾期贷款利息（表内）';

comment on column ICPS_JT_LOAN_TOTAL.paid_out_ovd_int_amt is
'实还短期逾期贷款利息（表外）';

comment on column ICPS_JT_LOAN_TOTAL.paid_in_pnlt_int_amt is
'实还短期贷款罚息（表内）';

comment on column ICPS_JT_LOAN_TOTAL.paid_out_pnlt_int_amt is
'实还短期贷款罚息（表外）';

comment on column ICPS_JT_LOAN_TOTAL.ahead_prin_amt is
'提前归还短期贷款正常本金';

comment on column ICPS_JT_LOAN_TOTAL.ahead_int_amt is
'提前归还短期贷款正常利息';

comment on column ICPS_JT_LOAN_TOTAL.refund_prin_amt is
'退货短期贷款本金';

comment on column ICPS_JT_LOAN_TOTAL.refund_ovd_prin_amt is
'退货短期贷款逾期本金（应计）';

comment on column ICPS_JT_LOAN_TOTAL.refund_in_pnlt_int is
'退货短期贷款罚息（表内）';

comment on column ICPS_JT_LOAN_TOTAL.encash_amt2 is
'中长期贷款放款资金';

comment on column ICPS_JT_LOAN_TOTAL.prin_to_ovd_prin_amt2 is
'中长期贷款正常本金转逾期本金（应计）';

comment on column ICPS_JT_LOAN_TOTAL.non_prin_to_ovd_prin_amt2 is
'中长期贷款正常本金转逾期本金（非应计）';

comment on column ICPS_JT_LOAN_TOTAL.accrued_to_non_ovd_prin_amt2 is
'中长期贷款逾期本金（应计）转逾期本金（非应计）';

comment on column ICPS_JT_LOAN_TOTAL.in_int_to_ovd_int_amt2 is
'中长期贷款正常利息转逾期利息（表内）';

comment on column ICPS_JT_LOAN_TOTAL.out_int_to_ovd_int_amt2 is
'中长期贷款正常利息转逾期利息（表外）';

comment on column ICPS_JT_LOAN_TOTAL.in_to_out_ovd_int_amt2 is
'中长期贷款逾期利息（表内）转逾期利息（表外）';

comment on column ICPS_JT_LOAN_TOTAL.in_to_out_pnlt_int_amt2 is
'中长期贷款罚息（表内）转罚息（表外）';

comment on column ICPS_JT_LOAN_TOTAL.in_refund_ovd_int_amt2 is
'中长期退货还款冲销的逾期利息（表内）';

comment on column ICPS_JT_LOAN_TOTAL.paid_prin_amt2 is
'实还中长期正常贷款本金';

comment on column ICPS_JT_LOAN_TOTAL.paid_accrued_ovd_prin_amt2 is
'实还中长期逾期贷款本金（应计）';

comment on column ICPS_JT_LOAN_TOTAL.paid_non_accrued_ovd_prin_amt2 is
'实还中长期逾期贷款本金（非应计）';

comment on column ICPS_JT_LOAN_TOTAL.paid_int_amt2 is
'实还中长期正常贷款利息';

comment on column ICPS_JT_LOAN_TOTAL.paid_in_ovd_int_amt2 is
'实还中长期逾期贷款利息（表内）';

comment on column ICPS_JT_LOAN_TOTAL.paid_out_ovd_int_amt2 is
'实还中长期逾期贷款利息（表外）';

comment on column ICPS_JT_LOAN_TOTAL.paid_in_pnlt_int_amt2 is
'实还中长期贷款罚息（表内）';

comment on column ICPS_JT_LOAN_TOTAL.paid_out_pnlt_int_amt2 is
'实还中长期贷款罚息（表外）';

comment on column ICPS_JT_LOAN_TOTAL.ahead_prin_amt2 is
'提前归还中长期贷款正常本金';

comment on column ICPS_JT_LOAN_TOTAL.ahead_int_amt2 is
'提前归还中长期贷款正常利息';

comment on column ICPS_JT_LOAN_TOTAL.refund_prin_amt2 is
'退货中长期贷款本金';

comment on column ICPS_JT_LOAN_TOTAL.refund_ovd_prin_amt2 is
'退货中长期贷款逾期本金（应计）';

comment on column ICPS_JT_LOAN_TOTAL.refund_in_pnlt_int_amt2 is
'退货中长期贷款罚息（表内）';

comment on column ICPS_JT_LOAN_TOTAL.extend_param1 is
'扩展1';

comment on column ICPS_JT_LOAN_TOTAL.extend_param2 is
'扩展2';

comment on column ICPS_JT_LOAN_TOTAL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JT_CUS                                           */
/*==============================================================*/
create table ICPS_JT_CUS 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   customer_code        VARCHAR(60),
   customer_name        VARCHAR(250),
   gender               CHAR(1),
   brith_date           VARCHAR(8),
   resident_flag        CHAR(1),
   customer_status      CHAR(1),
   border_in_out_flag   CHAR(1),
   id_type              CHAR(5),
   id_num               VARCHAR(60),
   mobile_no            VARCHAR(60),
   addr                 VARCHAR(250),
   bank_name            VARCHAR(100),
   bank_acct            VARCHAR(60),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_CUS primary key (busi_date, file_order)
);

comment on table ICPS_JT_CUS is
'客户信息文件';

comment on column ICPS_JT_CUS.busi_date is
'业务日期YYYYMMDD';

comment on column ICPS_JT_CUS.customer_code is
'客户编号';

comment on column ICPS_JT_CUS.customer_name is
'客户姓名';

comment on column ICPS_JT_CUS.gender is
'客户性别';

comment on column ICPS_JT_CUS.brith_date is
'出生日期YYYYMMDD';

comment on column ICPS_JT_CUS.resident_flag is
'居民标志';

comment on column ICPS_JT_CUS.customer_status is
'客户状态';

comment on column ICPS_JT_CUS.border_in_out_flag is
'境内境外标志';

comment on column ICPS_JT_CUS.id_type is
'证件类型';

comment on column ICPS_JT_CUS.id_num is
'证件号码';

comment on column ICPS_JT_CUS.mobile_no is
'手机号码';

comment on column ICPS_JT_CUS.addr is
'通讯地址';

comment on column ICPS_JT_CUS.bank_name is
'绑定银行卡行名';

comment on column ICPS_JT_CUS.bank_acct is
'绑定银行卡卡号';

comment on column ICPS_JT_CUS.is_check_flag is
'参与对账标识';

comment on column ICPS_JT_CUS.extend_param1 is
'扩展1';

comment on column ICPS_JT_CUS.extend_param2 is
'扩展2';

comment on column ICPS_JT_CUS.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JT_CUSCREDIT                                     */
/*==============================================================*/
create table ICPS_JT_CUSCREDIT 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   customer_code        VARCHAR(60),
   product_code         VARCHAR(4),
   quota_code           VARCHAR(60),
   currency             VARCHAR(3),
   cycle_quota_flag     CHAR(1),
   start_date           VARCHAR(8),
   end_date             VARCHAR(8),
   quota                DECIMAL(16,2),
   limit                INTEGER,
   nouse_quota          DECIMAL(16,2),
   tmp_quota_flag       VARCHAR(4),
   auth_status          VARCHAR(3),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_CUSCREDIT primary key (busi_date, file_order)
);

comment on table ICPS_JT_CUSCREDIT is
'授信额度信息文件';

comment on column ICPS_JT_CUSCREDIT.busi_date is
'业务日期YYYYMMDD';

comment on column ICPS_JT_CUSCREDIT.customer_code is
'客户编号';

comment on column ICPS_JT_CUSCREDIT.product_code is
'产品编号';

comment on column ICPS_JT_CUSCREDIT.quota_code is
'额度编号';

comment on column ICPS_JT_CUSCREDIT.currency is
'币种';

comment on column ICPS_JT_CUSCREDIT.cycle_quota_flag is
'循环额度标志';

comment on column ICPS_JT_CUSCREDIT.start_date is
'授信生效起始日期';

comment on column ICPS_JT_CUSCREDIT.end_date is
'授信到期日';

comment on column ICPS_JT_CUSCREDIT.quota is
'授信额度';

comment on column ICPS_JT_CUSCREDIT.limit is
'授信期限';

comment on column ICPS_JT_CUSCREDIT.nouse_quota is
'未动拨授信额度';

comment on column ICPS_JT_CUSCREDIT.tmp_quota_flag is
'是否临时额度';

comment on column ICPS_JT_CUSCREDIT.auth_status is
'授信状态';

comment on column ICPS_JT_CUSCREDIT.is_check_flag is
'参与对账标识';

comment on column ICPS_JT_CUSCREDIT.extend_param1 is
'扩展1';

comment on column ICPS_JT_CUSCREDIT.extend_param2 is
'扩展2';

comment on column ICPS_JT_CUSCREDIT.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JT_QUOTAADJUST                                   */
/*==============================================================*/
create table ICPS_JT_QUOTAADJUST 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   customer_code        VARCHAR(60),
   product_code         VARCHAR(4),
   quota_code           VARCHAR(60),
   adjust_type          VARCHAR(2),
   adjust_mode          VARCHAR(2),
   adjust_quota         DECIMAL(26,8),
   before_adjust_quota  DECIMAL(26,8),
   after_adjust_quota   DECIMAL(26,8),
   adjust_cal_date      VARCHAR(8),
   adjust_effective_date VARCHAR(8),
   adjust_serial        VARCHAR(60),
   error_type           CHAR(1),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_QUOTAADJUST primary key (busi_date, file_order)
);

comment on table ICPS_JT_QUOTAADJUST is
'调额信息文件';

comment on column ICPS_JT_QUOTAADJUST.busi_date is
'业务日期YYYYMMDD';

comment on column ICPS_JT_QUOTAADJUST.customer_code is
'客户编号';

comment on column ICPS_JT_QUOTAADJUST.product_code is
'产品编号';

comment on column ICPS_JT_QUOTAADJUST.quota_code is
'额度编号';

comment on column ICPS_JT_QUOTAADJUST.adjust_type is
'币种';

comment on column ICPS_JT_QUOTAADJUST.adjust_mode is
'循环额度标志';

comment on column ICPS_JT_QUOTAADJUST.adjust_quota is
'授信生效起始日期';

comment on column ICPS_JT_QUOTAADJUST.before_adjust_quota is
'授信到期日';

comment on column ICPS_JT_QUOTAADJUST.after_adjust_quota is
'授信额度';

comment on column ICPS_JT_QUOTAADJUST.adjust_cal_date is
'授信期限';

comment on column ICPS_JT_QUOTAADJUST.adjust_effective_date is
'未动拨授信额度';

comment on column ICPS_JT_QUOTAADJUST.adjust_serial is
'是否临时额度';

comment on column ICPS_JT_QUOTAADJUST.error_type is
'授信状态';

comment on column ICPS_JT_QUOTAADJUST.is_check_flag is
'参与对账标识';

comment on column ICPS_JT_QUOTAADJUST.extend_param1 is
'扩展1';

comment on column ICPS_JT_QUOTAADJUST.extend_param2 is
'扩展2';

comment on column ICPS_JT_QUOTAADJUST.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JT_LOAN                                          */
/*==============================================================*/
create table ICPS_JT_LOAN 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   customer_code        VARCHAR(60),
   product_code         VARCHAR(4),
   quota_code           VARCHAR(60),
   loan_code            VARCHAR(60),
   currency             CHAR(3),
   loan_status          CHAR(1),
   encash_date          VARCHAR(8),
   encash_amt           DECIMAL(16,8),
   end_date             VARCHAR(8),
   use_area             VARCHAR(6),
   prin_repay_frequency VARCHAR(6),
   int_repay_frequency  VARCHAR(6),
   self_pay_amt         DECIMAL(16,2),
   entrusted_pay_amt    DECIMAL(16,2),
   ovd_flag             CHAR(1),
   ovd_days             INTEGER,
   ovd_non_days         INTEGER,
   prin_ovd_days        VARCHAR(8),
   int_ovd_days         VARCHAR(8),
   next_int_date        VARCHAR(8),
   rate_type            VARCHAR(6),
   loan_bal             DECIMAL(16,2),
   ovd_loan_bal         DECIMAL(16,2),
   ovd_int              DECIMAL(16,2),
   out_int_bal          DECIMAL(16,2),
   int_flag             CHAR(1),
   accrued_int          DECIMAL(16,2),
   int_amt              DECIMAL(16,2),
   pnlt_amt             DECIMAL(16,2),
   encash_acct          VARCHAR(64),
   repay_acct           VARCHAR(64),
   guarantee_type       CHAR(3),
   repay_mode           CHAR(1),
   loan_rate            DECIMAL(16,8),
   penalty_rate         DECIMAL(16,8),
   loan_rate_type       CHAR(1),
   penalty_rate_type    CHAR(1),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_LOAN primary key (busi_date, file_order)
);

comment on table ICPS_JT_LOAN is
'贷款借据信息表文件';

comment on column ICPS_JT_LOAN.busi_date is
'业务日期YYYYMMDD';

comment on column ICPS_JT_LOAN.contract_no is
'客户签订的合同号码';

comment on column ICPS_JT_LOAN.customer_code is
'客户编号';

comment on column ICPS_JT_LOAN.product_code is
'产品编号';

comment on column ICPS_JT_LOAN.quota_code is
'额度编号';

comment on column ICPS_JT_LOAN.loan_code is
'贷款编号';

comment on column ICPS_JT_LOAN.currency is
'币种 默认CNY';

comment on column ICPS_JT_LOAN.loan_status is
'贷款状态 1正常 2逾期 3结清 9其它';

comment on column ICPS_JT_LOAN.encash_date is
'放款日期';

comment on column ICPS_JT_LOAN.encash_amt is
'放款金额';

comment on column ICPS_JT_LOAN.end_date is
'到期日期';

comment on column ICPS_JT_LOAN.use_area is
'贷款资金使用位置 I:境内（中国大陆）O:境外（含港澳台）';

comment on column ICPS_JT_LOAN.prin_repay_frequency is
'本金还款频率 连续两次还款时间的间隔 01:日 02:周 03:月 04:季 05:半年
06:年 07:一次性08:不定期（贷款期限内任意时间还款）99:其他';

comment on column ICPS_JT_LOAN.int_repay_frequency is
'利息还款频率 连续两次还款时间的间隔 01:日 02:周 03:月 04:季 05:半年
06:年 07:一次性08:不定期（贷款期限内任意时间还款）99:其他';

comment on column ICPS_JT_LOAN.self_pay_amt is
'自主支付金额';

comment on column ICPS_JT_LOAN.entrusted_pay_amt is
'受托支付金额';

comment on column ICPS_JT_LOAN.ovd_flag is
'逾期标志 1:逾期 0:正常';

comment on column ICPS_JT_LOAN.ovd_days is
'逾期天数';

comment on column ICPS_JT_LOAN.ovd_non_days is
'逾期宽限天数';

comment on column ICPS_JT_LOAN.prin_ovd_days is
'本金逾期日期';

comment on column ICPS_JT_LOAN.int_ovd_days is
'利息逾期日期';

comment on column ICPS_JT_LOAN.next_int_date is
'下一付息日';

comment on column ICPS_JT_LOAN.rate_type is
'利率类型 F:固定利率 L0:浮动利率-按日 L1:浮动利率-按周 L2:浮动利率-按月
L3:浮动利率-按季 L4:浮动利率-按半年 L5:浮动利率-按年 L9:浮动利率-其它';

comment on column ICPS_JT_LOAN.loan_bal is
'贷款余额';

comment on column ICPS_JT_LOAN.ovd_loan_bal is
'逾期贷款余额';

comment on column ICPS_JT_LOAN.ovd_int is
'逾期利息';

comment on column ICPS_JT_LOAN.out_int_bal is
'表外欠息';

comment on column ICPS_JT_LOAN.int_flag is
'计息标志 Y:正常计息 N:停止计息';

comment on column ICPS_JT_LOAN.accrued_int is
'应计利息';

comment on column ICPS_JT_LOAN.int_amt is
'当日利息';

comment on column ICPS_JT_LOAN.pnlt_amt is
'当日罚息';

comment on column ICPS_JT_LOAN.encash_acct is
'贷款入帐账号';

comment on column ICPS_JT_LOAN.repay_acct is
'还款账号';

comment on column ICPS_JT_LOAN.guarantee_type is
'贷款担保方式 A质押贷款B抵押贷款B01房地产抵押贷款B99其他抵押贷款C保证贷款C01联保贷款C99其他保证贷款D信用/免担保贷款E组合担保Z 其他';

comment on column ICPS_JT_LOAN.repay_mode is
'还款方式 1-等额本金;2-分期还款';

comment on column ICPS_JT_LOAN.loan_rate is
'借款利率';

comment on column ICPS_JT_LOAN.penalty_rate is
'违约金利率';

comment on column ICPS_JT_LOAN.loan_rate_type is
'借款利率类型';

comment on column ICPS_JT_LOAN.penalty_rate_type is
'违约金利率类型';

comment on column ICPS_JT_LOAN.is_check_flag is
'参与对账标识';

comment on column ICPS_JT_LOAN.extend_param1 is
'扩展1';

comment on column ICPS_JT_LOAN.extend_param2 is
'扩展2';

comment on column ICPS_JT_LOAN.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JT_PLAN                                          */
/*==============================================================*/
create table ICPS_JT_PLAN 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   product_code         VARCHAR(4),
   quota_code           VARCHAR(60),
   loan_code            VARCHAR(60),
   term_no              VARCHAR(20),
   repay_order          INTEGER,
   prin_end_date        VARCHAR(10),
   prin_amt             DECIMAL(16,2),
   int_end_date         VARCHAR(10),
   int_amt              DECIMAL(16,2),
   repay_terms          INTEGER,
   pnlt_amt             DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_PLAN primary key (busi_date, file_order)
);

comment on table ICPS_JT_PLAN is
'贷款还款计划信息文件';

comment on column ICPS_JT_PLAN.busi_date is
'业务日期YYYYMMDD';

comment on column ICPS_JT_PLAN.contract_no is
'客户签订的合同号码';

comment on column ICPS_JT_PLAN.product_code is
'产品编号';

comment on column ICPS_JT_PLAN.quota_code is
'额度编号';

comment on column ICPS_JT_PLAN.loan_code is
'贷款编号';

comment on column ICPS_JT_PLAN.term_no is
'分期单号';

comment on column ICPS_JT_PLAN.repay_order is
'还款期数';

comment on column ICPS_JT_PLAN.prin_end_date is
'本金到期日YYYYMMDD';

comment on column ICPS_JT_PLAN.prin_amt is
'本金 本期应该偿还的本金数额';

comment on column ICPS_JT_PLAN.int_end_date is
'利息到期日YYYYMMDD';

comment on column ICPS_JT_PLAN.int_amt is
'利息 本期（截止利息到期日）应计利息，不含逾期利息和罚息';

comment on column ICPS_JT_PLAN.repay_terms is
'还款总期数';

comment on column ICPS_JT_PLAN.pnlt_amt is
'罚息';

comment on column ICPS_JT_PLAN.is_check_flag is
'参与对账标识';

comment on column ICPS_JT_PLAN.extend_param1 is
'扩展1';

comment on column ICPS_JT_PLAN.extend_param2 is
'扩展2';

comment on column ICPS_JT_PLAN.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JT_FLOW                                          */
/*==============================================================*/
create table ICPS_JT_FLOW 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   product_code         VARCHAR(4),
   quota_code           VARCHAR(60),
   loan_code            VARCHAR(60),
   term_no              VARCHAR(20),
   repay_date           VARCHAR(10),
   repay_serial         VARCHAR(40),
   repay_mode           VARCHAR(6),
   curr_prin_amt        DECIMAL(16,2),
   prin_amt             DECIMAL(16,2),
   curr_int_amt         DECIMAL(16,2),
   int_amt              DECIMAL(16,2),
   curr_other_amt       DECIMAL(16,2),
   pnlt_amt             DECIMAL(16,2),
   repay_order          INTEGER,
   unclear_terms        INTEGER,
   repay_amt_type       VARCHAR(6),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_FLOW primary key (busi_date, file_order)
);

comment on table ICPS_JT_FLOW is
'贷款还款明细信息文件';

comment on column ICPS_JT_FLOW.busi_date is
'业务日期YYYYMMDD';

comment on column ICPS_JT_FLOW.contract_no is
'客户签订的合同号码';

comment on column ICPS_JT_FLOW.product_code is
'产品编号';

comment on column ICPS_JT_FLOW.quota_code is
'额度编号';

comment on column ICPS_JT_FLOW.loan_code is
'贷款编号';

comment on column ICPS_JT_FLOW.term_no is
'分期单号';

comment on column ICPS_JT_FLOW.repay_date is
'还款日期yyyy-MM-dd';

comment on column ICPS_JT_FLOW.repay_serial is
'流水号';

comment on column ICPS_JT_FLOW.repay_mode is
'还款方式 1-等额本金;2-分期还款';

comment on column ICPS_JT_FLOW.curr_prin_amt is
'本期应还本金';

comment on column ICPS_JT_FLOW.prin_amt is
'实际偿还本金金额';

comment on column ICPS_JT_FLOW.curr_int_amt is
'本期应还利息';

comment on column ICPS_JT_FLOW.int_amt is
'实际偿还利息金额';

comment on column ICPS_JT_FLOW.curr_other_amt is
'本期应还其他金额';

comment on column ICPS_JT_FLOW.pnlt_amt is
'罚息金额';

comment on column ICPS_JT_FLOW.repay_order is
'还款期数';

comment on column ICPS_JT_FLOW.unclear_terms is
'剩余还款期数';

comment on column ICPS_JT_FLOW.repay_amt_type is
'还款类型 01按期还款、02提前还款、03逾期还款、04退货、05冲销、06差额补足、07归还差额补足';

comment on column ICPS_JT_FLOW.is_check_flag is
'参与对账标识';

comment on column ICPS_JT_FLOW.extend_param1 is
'扩展1';

comment on column ICPS_JT_FLOW.extend_param2 is
'扩展2';

comment on column ICPS_JT_FLOW.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JT_FUND_DETAIL                                   */
/*==============================================================*/
create table ICPS_JT_FUND_DETAIL 
(
   trans_date           VARCHAR(8)          not null,
   file_type            CHAR(8)              not null,
   file_order           INTEGER              not null,
   trans_time           CHAR(6),
   sys_date             CHAR(8),
   acct_direction       CHAR(1),
   trans_amt            DECIMAL(16,2),
   summary_code         VARCHAR(10),
   summary              VARCHAR(250),
   acct_bal             DECIMAL(16,2),
   currency             CHAR(3),
   peer_acct            VARCHAR(36),
   peer_acct_name       VARCHAR(60),
   remarks              VARCHAR(250),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JT_FUND_DETAIL primary key (trans_date, file_type, file_order)
);

comment on table ICPS_JT_FUND_DETAIL is
'兴业资金流水文件';

comment on column ICPS_JT_FUND_DETAIL.trans_date is
'业务日期';

comment on column ICPS_JT_FUND_DETAIL.file_type is
'文件类型';

comment on column ICPS_JT_FUND_DETAIL.trans_time is
'交易时间';

comment on column ICPS_JT_FUND_DETAIL.sys_date is
'系统日期';

comment on column ICPS_JT_FUND_DETAIL.acct_direction is
'收支方向';

comment on column ICPS_JT_FUND_DETAIL.trans_amt is
'交易金额';

comment on column ICPS_JT_FUND_DETAIL.summary_code is
'摘要代码';

comment on column ICPS_JT_FUND_DETAIL.summary is
'中文摘要';

comment on column ICPS_JT_FUND_DETAIL.acct_bal is
'账户余额';

comment on column ICPS_JT_FUND_DETAIL.currency is
'货币号';

comment on column ICPS_JT_FUND_DETAIL.peer_acct is
'对方账户';

comment on column ICPS_JT_FUND_DETAIL.peer_acct_name is
'对方账户户名';

comment on column ICPS_JT_FUND_DETAIL.remarks is
'备注';

comment on column ICPS_JT_FUND_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JT_FUND_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JT_FUND_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JT_FUND_DETAIL.extend_param3 is
'扩展3';
