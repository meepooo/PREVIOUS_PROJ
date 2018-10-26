drop table ICPS_JB_TOTAL;

drop table ICPS_JB_LENDING_DETAIL;

drop table ICPS_JB_LOAN_DETAIL;

drop table ICPS_JB_REPAY_PLAN;

drop table ICPS_JB_REPAY_LOAN_DETAIL;

drop table ICPS_JB_REPAY_INSTMNT_DETAIL;

drop table ICPS_JB_XPT_LOAN_DETAIL;

drop table ICPS_JB_XPT_INSTMNT_DETAIL;

drop table ICPS_JB_LOAN_INIT;

drop table ICPS_JB_INSTMNT_INIT;

drop table ICPS_JB_LOAN_CALC;

drop table ICPS_JB_ARG_STATUS_CHANGE;

drop table ICPS_JB_FUND_DETAIL;


/*==============================================================*/
/* Table: ICPS_JB_TOTAL                                         */
/*==============================================================*/
create table ICPS_JB_TOTAL 
(
   busi_date            CHAR(8)              not null,
   encash_amt           DECIMAL(16,2),
   withhold_amt         DECIMAL(16,2),
   refund_amt           DECIMAL(16,2),
   accrued_int_amt      DECIMAL(16,2),
   non_accrued_int_amt  DECIMAL(16,2),
   accrued_ovd_prin_pnlt_amt DECIMAL(16,2),
   non_accrued_ovd_prin_pnlt_amt DECIMAL(16,2),
   accrued_ovd_int_pnlt_amt DECIMAL(16,2),
   non_accrued_ovd_int_pnlt_amt DECIMAL(16,2),
   prin_to_ovd_prin_amt DECIMAL(16,2),
   int_to_ovd_int_amt   DECIMAL(16,2),
   accrued_to_non_prin_amt DECIMAL(16,2),
   accrued_to_non_ovd_prin_amt DECIMAL(16,2),
   in_to_out_int_amt    DECIMAL(16,2),
   in_to_out_ovd_int_amt DECIMAL(16,2),
   in_to_out_ovd_prin_pnlt_amt DECIMAL(16,2),
   in_to_out_ovd_int_pnlt_amt DECIMAL(16,2),
   non_to_accrued_prin_amt DECIMAL(16,2),
   non_to_accrued_ovd_prin_amt DECIMAL(16,2),
   out_to_in_int_amt    DECIMAL(16,2),
   out_to_in_ovd_int_amt DECIMAL(16,2),
   out_to_in_ovd_prin_pnlt_amt DECIMAL(16,2),
   out_to_in_ovd_int_pnlt_amt DECIMAL(16,2),
   paid_prin_amt        DECIMAL(16,2),
   paid_non_accrued_prin_amt DECIMAL(16,2),
   paid_accrued_ovd_prin_amt DECIMAL(16,2),
   paid_non_accrued_ovd_prin_amt DECIMAL(16,2),
   paid_int_amt         DECIMAL(16,2),
   paid_out_int_amt     DECIMAL(16,2),
   paid_in_ovd_int_amt  DECIMAL(16,2),
   paid_out_ovd_int_amt DECIMAL(16,2),
   paid_in_ovd_prin_pnlt_int_amt DECIMAL(16,2),
   paid_out_ovd_prin_pnlt_int_amt DECIMAL(16,2),
   paid_in_ovd_int_pnlt_int_amt DECIMAL(16,2),
   paid_out_ovd_int_pnlt_int_amt DECIMAL(16,2),
   xpt_in_int_amt       DECIMAL(16,2),
   xpt_out_int_amt      DECIMAL(16,2),
   xpt_in_ovd_int_amt   DECIMAL(16,2),
   xpt_out_ovd_int_amt  DECIMAL(16,2),
   xpt_in_ovd_prin_pnlt_int_amt DECIMAL(16,2),
   xpt_out_ovd_prin_pnlt_int_amt DECIMAL(16,2),
   xpt_in_ovd_int_pnlt_int_amt DECIMAL(16,2),
   xpt_out_ovd_int_pnlt_int_amt DECIMAL(16,2),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_TOTAL primary key (busi_date)
);

comment on table ICPS_JB_TOTAL is
'汇总记账文件表';

comment on column ICPS_JB_TOTAL.busi_date is
'业务日期';

comment on column ICPS_JB_TOTAL.encash_amt is
'当天贷款发放金额';

comment on column ICPS_JB_TOTAL.withhold_amt is
'当天网商备付金代扣金额';

comment on column ICPS_JB_TOTAL.refund_amt is
'当天退回网商备付金金额';

comment on column ICPS_JB_TOTAL.accrued_int_amt is
'短期正常/逾期90天以内（含）贷款计提每日利息';

comment on column ICPS_JB_TOTAL.non_accrued_int_amt is
'短期逾期90天以上贷款计提每日利息';

comment on column ICPS_JB_TOTAL.accrued_ovd_prin_pnlt_amt is
'短期逾期90天以内（含）贷款计提每日逾期本金罚息';

comment on column ICPS_JB_TOTAL.non_accrued_ovd_prin_pnlt_amt is
'短期逾期90天以上贷款计提每日逾期本金罚息';

comment on column ICPS_JB_TOTAL.accrued_ovd_int_pnlt_amt is
'短期逾期90天以内（含）贷款计提每日逾期利息罚息';

comment on column ICPS_JB_TOTAL.non_accrued_ovd_int_pnlt_amt is
'短期逾期90天以上贷款计提每日逾期利息罚息';

comment on column ICPS_JB_TOTAL.prin_to_ovd_prin_amt is
'正常本金转逾期本金';

comment on column ICPS_JB_TOTAL.int_to_ovd_int_amt is
'正常利息转逾期利息';

comment on column ICPS_JB_TOTAL.accrued_to_non_prin_amt is
'正常本金（应计）转正常本金（非应计）';

comment on column ICPS_JB_TOTAL.accrued_to_non_ovd_prin_amt is
'逾期本金（应计）转逾期本金（非应计）';

comment on column ICPS_JB_TOTAL.in_to_out_int_amt is
'正常利息（表内）转正常利息（表外）';

comment on column ICPS_JB_TOTAL.in_to_out_ovd_int_amt is
'逾期利息（表内）转逾期利息（表外）';

comment on column ICPS_JB_TOTAL.in_to_out_ovd_prin_pnlt_amt is
'逾期本金罚息（表内）转逾期本金罚息（表外）';

comment on column ICPS_JB_TOTAL.in_to_out_ovd_int_pnlt_amt is
'逾期利息罚息（表内）转逾期利息罚息（表外）';

comment on column ICPS_JB_TOTAL.non_to_accrued_prin_amt is
'正常本金（非应计）转正常本金（应计）';

comment on column ICPS_JB_TOTAL.non_to_accrued_ovd_prin_amt is
'逾期本金（非应计）转逾期本金（应计）';

comment on column ICPS_JB_TOTAL.out_to_in_int_amt is
'正常利息（表外）转正常利息（表内）';

comment on column ICPS_JB_TOTAL.out_to_in_ovd_int_amt is
'逾期利息（表外）转逾期利息（表内）';

comment on column ICPS_JB_TOTAL.out_to_in_ovd_prin_pnlt_amt is
'逾期本金罚息（表外）转逾本金罚息（表内）';

comment on column ICPS_JB_TOTAL.out_to_in_ovd_int_pnlt_amt is
'逾期利息罚息（表外）转逾期利息罚息（表内）';

comment on column ICPS_JB_TOTAL.paid_prin_amt is
'实还正常本金（应计）';

comment on column ICPS_JB_TOTAL.paid_non_accrued_prin_amt is
'实还正常本金（非应计）';

comment on column ICPS_JB_TOTAL.paid_accrued_ovd_prin_amt is
'实还逾期本金（应计）';

comment on column ICPS_JB_TOTAL.paid_non_accrued_ovd_prin_amt is
'实还逾期本金（非应计）';

comment on column ICPS_JB_TOTAL.paid_int_amt is
'实还正常利息（表内）';

comment on column ICPS_JB_TOTAL.paid_out_int_amt is
'实还正常利息（表外）';

comment on column ICPS_JB_TOTAL.paid_in_ovd_int_amt is
'实还逾期利息（表内）';

comment on column ICPS_JB_TOTAL.paid_out_ovd_int_amt is
'实还逾期利息（表外）';

comment on column ICPS_JB_TOTAL.paid_in_ovd_prin_pnlt_int_amt is
'实还逾期本金罚息（表内）';

comment on column ICPS_JB_TOTAL.paid_out_ovd_prin_pnlt_int_amt is
'实还逾期本金罚息（表外）';

comment on column ICPS_JB_TOTAL.paid_in_ovd_int_pnlt_int_amt is
'实还逾期利息罚息（表内）';

comment on column ICPS_JB_TOTAL.paid_out_ovd_int_pnlt_int_amt is
'实还逾期利息罚息（表外）';

comment on column ICPS_JB_TOTAL.xpt_in_int_amt is
'减免正常利息（表内）';

comment on column ICPS_JB_TOTAL.xpt_out_int_amt is
'减免正常利息（表外）';

comment on column ICPS_JB_TOTAL.xpt_in_ovd_int_amt is
'减免逾期利息（表内）';

comment on column ICPS_JB_TOTAL.xpt_out_ovd_int_amt is
'减免逾期利息（表外）';

comment on column ICPS_JB_TOTAL.xpt_in_ovd_prin_pnlt_int_amt is
'减免逾期本金罚息（表内）';

comment on column ICPS_JB_TOTAL.xpt_out_ovd_prin_pnlt_int_amt is
'减免逾期本金罚息（表外）';

comment on column ICPS_JB_TOTAL.xpt_in_ovd_int_pnlt_int_amt is
'减免逾期利息罚息（表内）';

comment on column ICPS_JB_TOTAL.xpt_out_ovd_int_pnlt_int_amt is
'减免逾期利息罚息（表外）';

comment on column ICPS_JB_TOTAL.extend_param1 is
'扩展1';

comment on column ICPS_JB_TOTAL.extend_param2 is
'扩展2';

comment on column ICPS_JB_TOTAL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_LENDING_DETAIL                                */
/*==============================================================*/
create table ICPS_JB_LENDING_DETAIL 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   fund_seq_no          VARCHAR(64),
   third_product_code   VARCHAR(64),
   name                 VARCHAR(128),
   id_type              VARCHAR(2),
   id_num               VARCHAR(32),
   loan_status          VARCHAR(2),
   loan_use             VARCHAR(2),
   use_area             VARCHAR(2),
   apply_date           VARCHAR(20),
   encash_date          VARCHAR(20),
   currency             VARCHAR(3),
   encash_amt           DECIMAL(16,2),
   start_date           VARCHAR(8),
   end_date             VARCHAR(8),
   total_terms          INTEGER,
   repay_mode           VARCHAR(8),
   grace_day            INTEGER,
   rate_type            VARCHAR(2),
   day_rate             DECIMAL(16,6),
   prin_repay_frequency VARCHAR(2),
   int_repay_frequency  VARCHAR(2),
   guarantee_type       VARCHAR(3),
   credit_no            VARCHAR(64),
   encash_acct_type     VARCHAR(2),
   encash_acct          VARCHAR(32),
   repay_acct_type      VARCHAR(2),
   repay_acct           VARCHAR(32),
   loan_apply_no        VARCHAR(32),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_LENDING_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_LENDING_DETAIL is
'在途支用明细文件';

comment on column ICPS_JB_LENDING_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_LENDING_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_LENDING_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_LENDING_DETAIL.fund_seq_no is
'放款资金流水号';

comment on column ICPS_JB_LENDING_DETAIL.third_product_code is
'产品码';

comment on column ICPS_JB_LENDING_DETAIL.name is
'客户真实姓名';

comment on column ICPS_JB_LENDING_DETAIL.id_type is
'证件类型';

comment on column ICPS_JB_LENDING_DETAIL.id_num is
'客户证件号码';

comment on column ICPS_JB_LENDING_DETAIL.loan_status is
'贷款状态 1-成功 2-失败 3-在途';

comment on column ICPS_JB_LENDING_DETAIL.loan_use is
'贷款用途 1-消费 2-经营';

comment on column ICPS_JB_LENDING_DETAIL.use_area is
'贷款资金使用位置 0-境外 1-境内';

comment on column ICPS_JB_LENDING_DETAIL.apply_date is
'申请支用时间 YYYYMMDDHHMMSS';

comment on column ICPS_JB_LENDING_DETAIL.encash_date is
'放款日期 YYYYMMDDHHMMSS';

comment on column ICPS_JB_LENDING_DETAIL.currency is
'币种 CNY';

comment on column ICPS_JB_LENDING_DETAIL.encash_amt is
'放款金额';

comment on column ICPS_JB_LENDING_DETAIL.start_date is
'贷款起息日 YYYYMMDD';

comment on column ICPS_JB_LENDING_DETAIL.end_date is
'贷款到期日 YYYYMMDD';

comment on column ICPS_JB_LENDING_DETAIL.total_terms is
'贷款期次数';

comment on column ICPS_JB_LENDING_DETAIL.repay_mode is
'还款方式 1-等额本息 2-等额本金 6-按期付息到期一次还本';

comment on column ICPS_JB_LENDING_DETAIL.grace_day is
'宽限期天数';

comment on column ICPS_JB_LENDING_DETAIL.rate_type is
'利率类型 F-固定利率 L0-浮动利率-按日 L1-浮动利率-按周 L2-浮动利率-按月 L3-浮动利率-按季 L4-浮动利率-按半年 L5-浮动利率-按年 L9-浮动利率-其它';

comment on column ICPS_JB_LENDING_DETAIL.day_rate is
'贷款日利率';

comment on column ICPS_JB_LENDING_DETAIL.prin_repay_frequency is
'本金还款频率，该笔贷款连续两次还款时间的间隔。01:日02:周03:月04:季05:半年06:年07:一次性08:不定期（贷款期限内任意时间还款）99:其他';

comment on column ICPS_JB_LENDING_DETAIL.int_repay_frequency is
'本金还款频率，该笔贷款连续两次还款时间的间隔。01:日02:周03:月04:季05:半年06:年07:一次性08:不定期（贷款期限内任意时间还款）99:其他';

comment on column ICPS_JB_LENDING_DETAIL.guarantee_type is
'担保类型，A 质押贷款B 抵押贷款B01   房地产抵押贷款B99   其他抵押贷款C 保证贷款C01   联保贷款C99   其他保证贷款D 信用/免担保贷款E 组合担保Z 其他';

comment on column ICPS_JB_LENDING_DETAIL.credit_no is
'授信编号';

comment on column ICPS_JB_LENDING_DETAIL.encash_acct_type is
'放款帐号类型，01:银行借记卡02:支付宝';

comment on column ICPS_JB_LENDING_DETAIL.encash_acct is
'放款帐号';

comment on column ICPS_JB_LENDING_DETAIL.repay_acct_type is
'还款帐号类型，01:银行借记卡02:支付宝';

comment on column ICPS_JB_LENDING_DETAIL.repay_acct is
'还款帐号';

comment on column ICPS_JB_LENDING_DETAIL.loan_apply_no is
'贷款申请单号';

comment on column ICPS_JB_LENDING_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_LENDING_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_LENDING_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_LENDING_DETAIL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_LOAN_DETAIL                                   */
/*==============================================================*/
create table ICPS_JB_LOAN_DETAIL 
(
   busi_date            VARCHAR(8)          not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   fund_seq_no          VARCHAR(64),
   third_product_code   VARCHAR(64),
   name                 VARCHAR(128),
   id_type              VARCHAR(2),
   id_num               VARCHAR(32),
   loan_status          VARCHAR(2),
   loan_use             VARCHAR(2),
   use_area             VARCHAR(2),
   apply_date           VARCHAR(20),
   encash_date          VARCHAR(20),
   currency             VARCHAR(3),
   encash_amt           DECIMAL(16,2),
   start_date           VARCHAR(8),
   end_date             VARCHAR(8),
   total_terms          INTEGER,
   repay_mode           VARCHAR(8),
   grace_day            INTEGER,
   rate_type            VARCHAR(2),
   day_rate             DECIMAL(16,6),
   prin_repay_frequency VARCHAR(2),
   int_repay_frequency  VARCHAR(2),
   guarantee_type       VARCHAR(3),
   credit_no            VARCHAR(64),
   encash_acct_type     VARCHAR(2),
   encash_acct          VARCHAR(32),
   repay_acct_type      VARCHAR(2),
   repay_acct           VARCHAR(32),
   loan_apply_no        VARCHAR(64),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_LOAN_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_LOAN_DETAIL is
'放款（借据）明细文件';

comment on column ICPS_JB_LOAN_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_LOAN_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_LOAN_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_LOAN_DETAIL.fund_seq_no is
'放款资金流水号';

comment on column ICPS_JB_LOAN_DETAIL.third_product_code is
'产品码';

comment on column ICPS_JB_LOAN_DETAIL.name is
'客户真实姓名';

comment on column ICPS_JB_LOAN_DETAIL.id_type is
'证件类型';

comment on column ICPS_JB_LOAN_DETAIL.id_num is
'客户证件号码';

comment on column ICPS_JB_LOAN_DETAIL.loan_status is
'贷款状态 1-成功 2-失败 3-在途';

comment on column ICPS_JB_LOAN_DETAIL.loan_use is
'贷款用途 1-消费 2-经营';

comment on column ICPS_JB_LOAN_DETAIL.use_area is
'贷款资金使用位置 0-境外 1-境内';

comment on column ICPS_JB_LOAN_DETAIL.apply_date is
'申请支用时间 YYYYMMDDHHMMSS';

comment on column ICPS_JB_LOAN_DETAIL.encash_date is
'放款日期 YYYYMMDDHHMMSS';

comment on column ICPS_JB_LOAN_DETAIL.currency is
'币种 CNY-人民币';

comment on column ICPS_JB_LOAN_DETAIL.encash_amt is
'放款金额';

comment on column ICPS_JB_LOAN_DETAIL.start_date is
'贷款起息日 YYYYMMDD';

comment on column ICPS_JB_LOAN_DETAIL.end_date is
'贷款到期日 YYYYMMDD';

comment on column ICPS_JB_LOAN_DETAIL.total_terms is
'贷款期次数';

comment on column ICPS_JB_LOAN_DETAIL.repay_mode is
'还款方式 1-等额本息 2-等额本金 6-按期付息到期一次还本';

comment on column ICPS_JB_LOAN_DETAIL.grace_day is
'宽限期天数';

comment on column ICPS_JB_LOAN_DETAIL.rate_type is
'利率类型，F:固定利率L0:浮动利率-按日L1:浮动利率-按周L2:浮动利率-按月L3:浮动利率-按季L4:浮动利率-按半年L5:浮动利率-按年L9:浮动利率-其它';

comment on column ICPS_JB_LOAN_DETAIL.day_rate is
'贷款日利率';

comment on column ICPS_JB_LOAN_DETAIL.prin_repay_frequency is
'本金还款频率，该笔贷款连续两次还款时间的间隔。01:日02:周03:月04:季05:半年06:年07:一次性08:不定期（贷款期限内任意时间还款）99:其他';

comment on column ICPS_JB_LOAN_DETAIL.int_repay_frequency is
'本金还款频率，该笔贷款连续两次还款时间的间隔。01:日02:周03:月04:季05:半年06:年07:一次性08:不定期（贷款期限内任意时间还款）99:其他';

comment on column ICPS_JB_LOAN_DETAIL.guarantee_type is
'担保类型，A 质押贷款B 抵押贷款B01   房地产抵押贷款B99   其他抵押贷款C 保证贷款C01   联保贷款C99   其他保证贷款D 信用/免担保贷款E 组合担保Z 其他';

comment on column ICPS_JB_LOAN_DETAIL.credit_no is
'授信编号';

comment on column ICPS_JB_LOAN_DETAIL.encash_acct_type is
'放款帐号类型，01:银行借记卡02:支付宝';

comment on column ICPS_JB_LOAN_DETAIL.encash_acct is
'放款帐号';

comment on column ICPS_JB_LOAN_DETAIL.repay_acct_type is
'还款帐号类型，01:银行借记卡02:支付宝';

comment on column ICPS_JB_LOAN_DETAIL.repay_acct is
'还款帐号';

comment on column ICPS_JB_LOAN_DETAIL.loan_apply_no is
'贷款申请单号';

comment on column ICPS_JB_LOAN_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_LOAN_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_LOAN_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_LOAN_DETAIL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_REPAY_PLAN                                    */
/*==============================================================*/
create table ICPS_JB_REPAY_PLAN 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   term_no              INTEGER,
   start_date           VARCHAR(8),
   end_date             VARCHAR(8),
   prin_amt             DECIMAL(16,2),
   int_amt              DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_REPAY_PLAN primary key (busi_date, file_order)
);

comment on table ICPS_JB_REPAY_PLAN is
'放款（分期）明细文件';

comment on column ICPS_JB_REPAY_PLAN.busi_date is
'业务日期';

comment on column ICPS_JB_REPAY_PLAN.file_order is
'文件序号';

comment on column ICPS_JB_REPAY_PLAN.contract_no is
'借呗平台贷款合约号';

comment on column ICPS_JB_REPAY_PLAN.term_no is
'期次号';

comment on column ICPS_JB_REPAY_PLAN.start_date is
'分期开始日期 YYYYMMDD';

comment on column ICPS_JB_REPAY_PLAN.end_date is
'分期结束日期 YYYYMMDD';

comment on column ICPS_JB_REPAY_PLAN.prin_amt is
'本金金额';

comment on column ICPS_JB_REPAY_PLAN.int_amt is
'初始利息匡算金额';

comment on column ICPS_JB_REPAY_PLAN.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_REPAY_PLAN.extend_param1 is
'扩展1';

comment on column ICPS_JB_REPAY_PLAN.extend_param2 is
'扩展2';

comment on column ICPS_JB_REPAY_PLAN.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_REPAY_LOAN_DETAIL                             */
/*==============================================================*/
create table ICPS_JB_REPAY_LOAN_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   repay_seq_no         VARCHAR(64),
   fee_no               VARCHAR(64),
   withdraw_no          VARCHAR(64),
   repay_type           VARCHAR(8),
   repay_date           VARCHAR(20),
   curr_prin_bal        DECIMAL(16,2),
   curr_ovd_prin_bal    DECIMAL(16,2),
   curr_int_bal         DECIMAL(16,2),
   curr_ovd_int_bal     DECIMAL(16,2),
   curr_ovd_prin_pnlt_bal DECIMAL(16,2),
   curr_ovd_int_pnlt_bal DECIMAL(16,2),
   repay_amt            DECIMAL(16,2),
   paid_prin_amt        DECIMAL(16,2),
   paid_ovd_prin_amt    DECIMAL(16,2),
   paid_int_amt         DECIMAL(16,2),
   paid_ovd_int_amt     DECIMAL(16,2),
   paid_ovd_prin_pnlt_amt DECIMAL(16,2),
   paid_ovd_int_pnlt_amt DECIMAL(16,2),
   fee_amt              DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_REPAY_LOAN_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_REPAY_LOAN_DETAIL is
'还款（借据）明细文件';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_seq_no is
'还款流水号';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.fee_no is
'收费单号';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.withdraw_no is
'还款提现单号';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_type is
'还款类型 01-主动还款 02-批量扣款 03-动账通知还款 04-线下还款';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_date is
'还款日期 YYYYMMDDHHMMSS';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_prin_bal is
'本次还款前的应收未收正常本金余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_prin_bal is
'本次还款前的应收未收逾期本金余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_int_bal is
'本次还款前的应收未收正常利息余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_int_bal is
'本次还款前的应收未收逾期利息余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_prin_pnlt_bal is
'本次还款前的应收未收逾期本金罚息余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.curr_ovd_int_pnlt_bal is
'本次还款前的应收未收逾期利息罚息余额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.repay_amt is
'总金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_prin_amt is
'本次实还正常本金金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_prin_amt is
'本次实还逾期本金金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_int_amt is
'本次实还正常利息金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_int_amt is
'本次实还逾期利息金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_prin_pnlt_amt is
'本次实还逾期本金罚息金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.paid_ovd_int_pnlt_amt is
'本次实还逾期利息罚息金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.fee_amt is
'本次还款对应的平台服务费金额';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_REPAY_LOAN_DETAIL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_REPAY_INSTMNT_DETAIL                          */
/*==============================================================*/
create table ICPS_JB_REPAY_INSTMNT_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32),
   repay_seq_no         VARCHAR(64),
   term_no              INTEGER,
   repay_amt_type       VARCHAR(8),
   repay_date           VARCHAR(8),
   curr_prin_bal        DECIMAL(16,2),
   curr_int_bal         DECIMAL(16,2),
   curr_ovd_prin_pnlt_bal DECIMAL(16,2),
   curr_ovd_int_pnlt_bal DECIMAL(16,2),
   repay_amt            DECIMAL(16,2),
   paid_prin_amt        DECIMAL(16,2),
   paid_int_amt         DECIMAL(16,2),
   paid_ovd_prin_pnlt_amt DECIMAL(16,2),
   paid_ovd_int_pnlt_amt DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_REPAY_INSTMNT_DETAI primary key (busi_date, file_order)
);

comment on table ICPS_JB_REPAY_INSTMNT_DETAIL is
'还款（分期）明细文件';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_seq_no is
'还款流水号';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.term_no is
'期次号';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_amt_type is
'还款金额类型 01-按期还款 02-提前还款 03-逾期还款';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_date is
'还款日期 YYYYMMDD';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_prin_bal is
'本次还款前的应收未收本金';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_int_bal is
'本次还款前的应收未收利息';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_ovd_prin_pnlt_bal is
'本次还款前的应收未收逾期本金罚息';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.curr_ovd_int_pnlt_bal is
'本次还款前的应收未收逾期利息罚息';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.repay_amt is
'本次实还总金额';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_prin_amt is
'本次实还本金金额';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_int_amt is
'本次实还利息金额';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_ovd_prin_pnlt_amt is
'本次实还逾期本金罚息金额';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.paid_ovd_int_pnlt_amt is
'本次实还逾期利息罚息金额';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_REPAY_INSTMNT_DETAIL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_XPT_LOAN_DETAIL                               */
/*==============================================================*/
create table ICPS_JB_XPT_LOAN_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32),
   xpt_seq_no           VARCHAR(64),
   xpt_date             VARCHAR(20),
   curr_int_bal         DECIMAL(16,2),
   curr_ovd_int_bal     DECIMAL(16,2),
   curr_ovd_prin_pnlt_bal DECIMAL(16,2),
   curr_ovd_int_pnlt_bal DECIMAL(16,2),
   xpt_amt              DECIMAL(16,2),
   xpt_int_amt          DECIMAL(16,2),
   xpt_ovd_int_amt      DECIMAL(16,2),
   xpt_ovd_prin_pnlt_amt DECIMAL(16,2),
   xpt_ovd_int_pnlt_amt DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_XPT_LOAN_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_XPT_LOAN_DETAIL is
'减免（借据）明细文件';

comment on column ICPS_JB_XPT_LOAN_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_XPT_LOAN_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_XPT_LOAN_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_seq_no is
'减免流水号';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_date is
'减免时间 YYYYMMDDHHMMSS';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_int_bal is
'本次还款前的应收未收正常利息余额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_ovd_int_bal is
'本次还款前的应收未收逾期利息余额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_ovd_prin_pnlt_bal is
'本次还款前的应收未收逾期本金罚息余额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.curr_ovd_int_pnlt_bal is
'本次还款前的应收未收逾期利息罚息余额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_amt is
'减免总金额（单位分）';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_int_amt is
'本次减免正常利息金额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_ovd_int_amt is
'本次减免逾期利息金额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_ovd_prin_pnlt_amt is
'本次减免逾期本金罚息金额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.xpt_ovd_int_pnlt_amt is
'本次减免逾期利息罚息金额';

comment on column ICPS_JB_XPT_LOAN_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_XPT_LOAN_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_XPT_LOAN_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_XPT_LOAN_DETAIL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_XPT_INSTMNT_DETAIL                            */
/*==============================================================*/
create table ICPS_JB_XPT_INSTMNT_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32),
   xpt_seq_no           VARCHAR(64),
   term_no              INTEGER,
   settle_date          VARCHAR(8),
   curr_int_bal         DECIMAL(16,2),
   curr_ovd_prin_pnlt_bal DECIMAL(16,2),
   curr_ovd_int_pnlt_bal DECIMAL(16,2),
   xpt_amt              DECIMAL(16,2),
   xpt_int_amt          DECIMAL(16,2),
   xpt_ovd_prin_pnlt_amt DECIMAL(16,2),
   xpt_ovd_int_pnlt_amt DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_XPT_INSTMNT_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_XPT_INSTMNT_DETAIL is
'减免（分期）明细文件';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_seq_no is
'减免流水号';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.term_no is
'期次号';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.settle_date is
'减免会计日期 YYYYMMDD';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.curr_int_bal is
'本次还款前的应收未收利息';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.curr_ovd_prin_pnlt_bal is
'本次还款前的应收未收逾期本金罚息';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.curr_ovd_int_pnlt_bal is
'本次还款前的应收未收逾期利息罚息';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_amt is
'本次减免总金额';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_int_amt is
'本次减免利息金额';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_ovd_prin_pnlt_amt is
'本次减免逾期本金罚息金额';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.xpt_ovd_int_pnlt_amt is
'本次减免逾期利息罚息金额';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_XPT_INSTMNT_DETAIL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_LOAN_INIT                                     */
/*==============================================================*/
create table ICPS_JB_LOAN_INIT 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32),
   settle_date          VARCHAR(8),
   status               VARCHAR(10),
   clear_date           VARCHAR(8),
   asset_class          VARCHAR(2),
   accrued_status       VARCHAR(2),
   next_repay_date      VARCHAR(8),
   unclear_terms        INTEGER,
   ovd_terms            INTEGER,
   prin_ovd_days        INTEGER,
   int_ovd_days         INTEGER,
   prin_bal             DECIMAL(16,2),
   ovd_prin_bal         DECIMAL(16,2),
   int_bal              DECIMAL(16,2),
   ovd_int_bal          DECIMAL(16,2),
   ovd_prin_pnlt_bal    DECIMAL(16,2),
   ovd_int_pnlt_bal     DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_LOAN_INIT primary key (busi_date, file_order)
);

comment on table ICPS_JB_LOAN_INIT is
'日初（借据）信息文件';

comment on column ICPS_JB_LOAN_INIT.busi_date is
'业务日期';

comment on column ICPS_JB_LOAN_INIT.file_order is
'文件序号';

comment on column ICPS_JB_LOAN_INIT.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_LOAN_INIT.settle_date is
'会计日期，格式YYYYMMdd';

comment on column ICPS_JB_LOAN_INIT.status is
'借据状态，正常NORMAL,逾期OVD,结清CLEAR ';

comment on column ICPS_JB_LOAN_INIT.clear_date is
'结清日期，格式YYYYMMdd';

comment on column ICPS_JB_LOAN_INIT.asset_class is
'五级分类标识，正常1，关注2，次级3，可疑4，损失5';

comment on column ICPS_JB_LOAN_INIT.accrued_status is
'应计非应计标识，应计0，非应计1';

comment on column ICPS_JB_LOAN_INIT.next_repay_date is
'下一还款日期 YYYYMMDD';

comment on column ICPS_JB_LOAN_INIT.unclear_terms is
'未结清期数';

comment on column ICPS_JB_LOAN_INIT.ovd_terms is
'逾期期次数';

comment on column ICPS_JB_LOAN_INIT.prin_ovd_days is
'本金逾期天数';

comment on column ICPS_JB_LOAN_INIT.int_ovd_days is
'利息逾期天数';

comment on column ICPS_JB_LOAN_INIT.prin_bal is
'正常本金余额';

comment on column ICPS_JB_LOAN_INIT.ovd_prin_bal is
'逾期本金余额';

comment on column ICPS_JB_LOAN_INIT.int_bal is
'正常利息余额';

comment on column ICPS_JB_LOAN_INIT.ovd_int_bal is
'逾期利息余额';

comment on column ICPS_JB_LOAN_INIT.ovd_prin_pnlt_bal is
'逾期本金罚息余额';

comment on column ICPS_JB_LOAN_INIT.ovd_int_pnlt_bal is
'逾期利息罚息余额';

comment on column ICPS_JB_LOAN_INIT.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_LOAN_INIT.extend_param1 is
'扩展1';

comment on column ICPS_JB_LOAN_INIT.extend_param2 is
'扩展2';

comment on column ICPS_JB_LOAN_INIT.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_INSTMNT_INIT                                  */
/*==============================================================*/
create table ICPS_JB_INSTMNT_INIT 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32)         not null,
   settle_date          VARCHAR(8),
   term_no              INTEGER,
   start_date           VARCHAR(8),
   end_date             VARCHAR(8),
   status               VARCHAR(10),
   clear_date           VARCHAR(8),
   prin_ovd_date        VARCHAR(8),
   int_ovd_date         VARCHAR(8),
   prin_ovd_days        INTEGER,
   int_ovd_days         INTEGER,
   prin_bal             DECIMAL(16,2),
   int_bal              DECIMAL(16,2),
   ovd_prin_pnlt_bal    DECIMAL(16,2),
   ovd_int_pnlt_bal     DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_INSTMNT_INIT primary key (busi_date, file_order)
);

comment on table ICPS_JB_INSTMNT_INIT is
'日初（分期）信息文件';

comment on column ICPS_JB_INSTMNT_INIT.busi_date is
'业务日期';

comment on column ICPS_JB_INSTMNT_INIT.file_order is
'文件序号';

comment on column ICPS_JB_INSTMNT_INIT.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_INSTMNT_INIT.settle_date is
'会计日期 YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.term_no is
'期次号';

comment on column ICPS_JB_INSTMNT_INIT.start_date is
'分期开始日期 YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.end_date is
'分期结束日期（当期还款日） YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.status is
'分期状态，正常NORMAL,逾期OVD,结清CLEAR ';

comment on column ICPS_JB_INSTMNT_INIT.clear_date is
'结清日期 YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.prin_ovd_date is
'本金转逾期日期 YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.int_ovd_date is
'利息转逾期日期 YYYYMMDD';

comment on column ICPS_JB_INSTMNT_INIT.prin_ovd_days is
'本金逾期天数';

comment on column ICPS_JB_INSTMNT_INIT.int_ovd_days is
'利息逾期天数';

comment on column ICPS_JB_INSTMNT_INIT.prin_bal is
'本金余额';

comment on column ICPS_JB_INSTMNT_INIT.int_bal is
'利息余额';

comment on column ICPS_JB_INSTMNT_INIT.ovd_prin_pnlt_bal is
'逾期本金罚息余额';

comment on column ICPS_JB_INSTMNT_INIT.ovd_int_pnlt_bal is
'逾期利息罚息余额';

comment on column ICPS_JB_INSTMNT_INIT.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_INSTMNT_INIT.extend_param1 is
'扩展1';

comment on column ICPS_JB_INSTMNT_INIT.extend_param2 is
'扩展2';

comment on column ICPS_JB_INSTMNT_INIT.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_LOAN_CALC                                     */
/*==============================================================*/
create table ICPS_JB_LOAN_CALC 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(64),
   calc_date            VARCHAR(8),
   accrued_status       VARCHAR(2),
   prin_bal             DECIMAL(16,2),
   ovd_prin_bal         DECIMAL(16,2),
   ovd_int_bal          DECIMAL(16,2),
   real_rate            DECIMAL(16,6),
   pnlt_rate            DECIMAL(16,6),
   int_amt              DECIMAL(16,2),
   ovd_prin_pnlt_amt    DECIMAL(16,2),
   ovd_int_pnlt_amt     DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_LOAN_CALC primary key (busi_date, file_order)
);

comment on table ICPS_JB_LOAN_CALC is
'利息计提明细文件';

comment on column ICPS_JB_LOAN_CALC.busi_date is
'业务日期';

comment on column ICPS_JB_LOAN_CALC.file_order is
'文件序号';

comment on column ICPS_JB_LOAN_CALC.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_LOAN_CALC.calc_date is
'计息日期 YYYYMMDD';

comment on column ICPS_JB_LOAN_CALC.accrued_status is
'应计非应计标识 应计0，非应计1';

comment on column ICPS_JB_LOAN_CALC.prin_bal is
'正常本金余额';

comment on column ICPS_JB_LOAN_CALC.ovd_prin_bal is
'逾期本金余额';

comment on column ICPS_JB_LOAN_CALC.ovd_int_bal is
'逾期利息余额';

comment on column ICPS_JB_LOAN_CALC.real_rate is
'贷款实际日利率';

comment on column ICPS_JB_LOAN_CALC.pnlt_rate is
'贷款罚息日利率';

comment on column ICPS_JB_LOAN_CALC.int_amt is
'正常利息';

comment on column ICPS_JB_LOAN_CALC.ovd_prin_pnlt_amt is
'逾期本金罚息';

comment on column ICPS_JB_LOAN_CALC.ovd_int_pnlt_amt is
'逾期利息罚息';

comment on column ICPS_JB_LOAN_CALC.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_LOAN_CALC.extend_param1 is
'扩展1';

comment on column ICPS_JB_LOAN_CALC.extend_param2 is
'扩展2';

comment on column ICPS_JB_LOAN_CALC.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_ARG_STATUS_CHANGE                             */
/*==============================================================*/
create table ICPS_JB_ARG_STATUS_CHANGE 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   contract_no          VARCHAR(32),
   settle_date          VARCHAR(8),
   status_seq_no        VARCHAR(64),
   event_code           VARCHAR(16),
   before_status        VARCHAR(10),
   after_status         VARCHAR(10),
   prin_amt             DECIMAL(16,2),
   int_amt              DECIMAL(16,2),
   ovd_prin_pnlt_amt    DECIMAL(16,2),
   ovd_int_pnlt_amt     DECIMAL(16,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_ARG_STATUS_CHANGE primary key (busi_date, file_order)
);

comment on table ICPS_JB_ARG_STATUS_CHANGE is
'借据形态转移流水文件';

comment on column ICPS_JB_ARG_STATUS_CHANGE.busi_date is
'业务日期';

comment on column ICPS_JB_ARG_STATUS_CHANGE.file_order is
'文件序号';

comment on column ICPS_JB_ARG_STATUS_CHANGE.contract_no is
'借呗平台贷款合同号';

comment on column ICPS_JB_ARG_STATUS_CHANGE.settle_date is
'会计日期';

comment on column ICPS_JB_ARG_STATUS_CHANGE.status_seq_no is
'状态变化流水号';

comment on column ICPS_JB_ARG_STATUS_CHANGE.event_code is
'事件码，转逾期11020007，转非应计11020014，转应计11020015';

comment on column ICPS_JB_ARG_STATUS_CHANGE.before_status is
'借据转移前状态（包括应计） ，取值为NORMAL（应计变更取值切0或1）';

comment on column ICPS_JB_ARG_STATUS_CHANGE.after_status is
'借据转移后状态（包括应计），取值为OVD（应计变更取值为0或1）';

comment on column ICPS_JB_ARG_STATUS_CHANGE.prin_amt is
'本金发生额';

comment on column ICPS_JB_ARG_STATUS_CHANGE.int_amt is
'利息发生额';

comment on column ICPS_JB_ARG_STATUS_CHANGE.ovd_prin_pnlt_amt is
'逾期本金罚息发生额';

comment on column ICPS_JB_ARG_STATUS_CHANGE.ovd_int_pnlt_amt is
'逾期利息罚息发生额';

comment on column ICPS_JB_ARG_STATUS_CHANGE.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_ARG_STATUS_CHANGE.extend_param1 is
'扩展1';

comment on column ICPS_JB_ARG_STATUS_CHANGE.extend_param2 is
'扩展2';

comment on column ICPS_JB_ARG_STATUS_CHANGE.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_JB_FUND_DETAIL                                   */
/*==============================================================*/
create table ICPS_JB_FUND_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   third_busi_serial    VARCHAR(64),
   third_busi_type      VARCHAR(32),
   trans_amt            DECIMAL(16,2),
   trans_refund_amt     DECIMAL(16,2),
   trans_dttm           VARCHAR(14),
   third_trans_name     VARCHAR(256),
   peer_org_name        VARCHAR(32),
   trans_sub_detail     VARCHAR(128),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_JB_FUND_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_JB_FUND_DETAIL is
'网商银行资金对账文件';

comment on column ICPS_JB_FUND_DETAIL.busi_date is
'业务日期';

comment on column ICPS_JB_FUND_DETAIL.file_order is
'文件序号';

comment on column ICPS_JB_FUND_DETAIL.third_busi_serial is
'网商银行交易流水号';

comment on column ICPS_JB_FUND_DETAIL.third_busi_type is
'业务操作，代收P_DLGATE，代扣P_WITHDRAW（如果收费账户是独立的，则P_FEE代表是收费）';

comment on column ICPS_JB_FUND_DETAIL.trans_amt is
'交易金额 代扣为负数，代收为正数';

comment on column ICPS_JB_FUND_DETAIL.trans_refund_amt is
'交易退款金额 如果此金额大于0则代表是代扣退款';

comment on column ICPS_JB_FUND_DETAIL.trans_dttm is
'交易时间 YYYYMMDDHHMMSS';

comment on column ICPS_JB_FUND_DETAIL.third_trans_name is
'交易名称 代收，代扣';

comment on column ICPS_JB_FUND_DETAIL.peer_org_name is
'对方机构名称';

comment on column ICPS_JB_FUND_DETAIL.trans_sub_detail is
'业务单号';

comment on column ICPS_JB_FUND_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_JB_FUND_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_JB_FUND_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_JB_FUND_DETAIL.extend_param3 is
'扩展3';
