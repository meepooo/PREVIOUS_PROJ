drop table ICPS_WB_TM_ACCOUNT;

drop table ICPS_WB_TM_AUTH_BANK_COST;

drop table ICPS_WB_TM_CARD;

drop table ICPS_WB_TM_GL_BAL;

drop table ICPS_WB_TM_PLAN;

drop table ICPS_WB_TM_APP_MAIN;

drop table ICPS_WB_TM_APP_INFO;

drop table ICPS_WB_TM_CUSTOMER;

drop table ICPS_WB_TT_TXN_POST;

drop table ICPS_WB_TM_TXN_REJECT;

drop table ICPS_WB_TM_LOAN;

drop table ICPS_WB_TM_SCHEDULE;

drop table ICPS_WB_DS_ACCOUNTING_FLOW;

drop table ICPS_WB_TM_CUST_LIMIT_O;

drop table ICPS_WB_TM_AUTH_HST;

drop table ICPS_WB_TM_IM_INFO;

drop table ICPS_WB_TM_LOAN_RECEIPT_LIST;

drop table ICPS_WB_TM_RE_HST;

drop table ICPS_WB_TM_PSB_PERSONAL_INFO;

drop table ICPS_WB_RRS_BDM_UDF_CLEAR_TOT;

drop table ICPS_WB_RRS_CLEAR_DETAIL;

drop table ICPS_WB_RSS_OTHER_DETAIL;

drop table ICPS_WB_TM_COLL_REC;

drop table ICPS_WB_TM_LOAN_VMS;

drop table ICPS_WB_TM_FREE_COUPONS_INFO;

drop table ICPS_WB_DS_SPLIT_DIFF;

drop table ICPS_WB_DS_DCA_COMMISSION;

drop table ICPS_WB_DS_DIFF_LIST;

drop table ICPS_WB_DS_SUCC_LIST;



/*==============================================================*/
/* Table: ICPS_WB_TM_ACCOUNT                                    */
/*==============================================================*/
create table ICPS_WB_TM_ACCOUNT 
(
   busi_date            CHAR(8)             not null,
   file_order           INTEGER             not null,
   org                  CHAR(12),
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   cust_id              VARCHAR(20),
   cust_limit_id        VARCHAR(20),
   product_code         CHAR(6),
   default_logical_card_no VARCHAR(19),
   currency             CHAR(3),
   credit_limit         DECIMAL(13),
   temp_limit           DECIMAL(13),
   temp_limit_begin_date VARCHAR(8),
   temp_limit_end_date  VARCHAR(8),
   user_field1          DECIMAL(5,2),
   user_field2          DECIMAL(5,2),
   user_field3          DECIMAL(5,2),
   curr_balance         DECIMAL(15,2),
   user_field4          DECIMAL(15,2),
   principal_bal        DECIMAL(15,2),
   user_field5          DECIMAL(15,2),
   user_field6          DECIMAL(15,2),
   begin_bal            DECIMAL(15,2),
   pmt_due_day_bal      DECIMAL(15,2),
   user_field7          DECIMAL(15,2),
   user_field8          CHAR(1),
   user_field9          DECIMAL(13),
   user_field10         DECIMAL(13),
   user_field11         DECIMAL(13),
   user_field12         DECIMAL(13),
   user_field13         DECIMAL(13),
   user_field14         VARCHAR(8),
   user_field15         VARCHAR(8),
   user_field16         VARCHAR(8),
   user_field17         VARCHAR(8),
   user_field18         INTEGER,
   name                 VARCHAR(80),
   gender               CHAR(1),
   user_field19         VARCHAR(9),
   mobile_no            VARCHAR(20),
   user_field20         VARCHAR(200),
   billint_cycle        CHAR(2),
   user_field21         CHAR(1),
   user_field22         CHAR(1),
   user_field23         CHAR(1),
   user_field24         CHAR(3),
   user_field25         VARCHAR(40),
   user_field26         VARCHAR(40),
   user_field27         VARCHAR(40),
   user_field28         VARCHAR(200),
   user_field29         VARCHAR(10),
   user_field30         VARCHAR(80),
   user_field31         VARCHAR(27),
   AGE_CD               CHAR(1),
   user_field32         CHAR(1),
   UNMATCH_DB           DECIMAL(15,2),
   user_field33         DECIMAL(15,2),
   unmatch_cr           DECIMAL(15,2),
   dd_ind               CHAR(1),
   dd_bank_name         VARCHAR(80),
   dd_bank_branch       VARCHAR(14),
   dd_bank_acct_no      VARCHAR(40),
   dd_bank_acct_name    VARCHAR(80),
   last_dd_amt          DECIMAL(15,2),
   last_dd_date         VARCHAR(14),
   user_field34         CHAR(1),
   last_pmt_amt         DECIMAL(15,2),
   last_pmt_date        VARCHAR(14),
   last_stmt_date       VARCHAR(14),
   last_pmt_due_date    VARCHAR(14),
   last_agint_date      VARCHAR(14),
   collect_date         VARCHAR(14),
   collect_out_date     VARCHAR(14),
   next_stmt_date       VARCHAR(14),
   pmt_due_date         VARCHAR(14),
   dd_date              VARCHAR(14),
   grace_date           VARCHAR(14),
   user_field35         VARCHAR(14),
   closed_date          VARCHAR(14),
   first_stmt_date      VARCHAR(14),
   cancel_date          VARCHAR(14),
   charge_off_date      VARCHAR(14),
   user_field36         VARCHAR(14),
   usesr_field37        DECIMAL(15,2),
   usesr_field38        DECIMAL(15,2),
   usesr_field39        DECIMAL(15,2),
   usesr_field40        DECIMAL(15,2),
   usesr_field41        DECIMAL(15,2),
   usesr_field42        DECIMAL(15,2),
   usesr_field43        DECIMAL(15,2),
   usesr_field44        DECIMAL(15,2),
   usesr_field45        DECIMAL(15,2),
   usesr_field46        DECIMAL(15,2),
   usesr_field47        DECIMAL(15,2),
   usesr_field48        DECIMAL(15,2),
   usesr_field49        INTEGER,
   ctd_retail_amt       DECIMAL(15,2),
   ctd_retail_cnt       INTEGER,
   ctd_payment_amt      DECIMAL(15,2),
   ctd_payment_cnt      INTEGER,
   ctd_db_adj_amt       DECIMAL(15,2),
   ctd_db_adj_cnt       INTEGER,
   ctd_cr_adj_cnt       INTEGER,
   ctd_cr_adj_amt       DECIMAL(15,2),
   ctd_fee_amt          DECIMAL(15,2),
   ctd_fee_cnt          INTEGER,
   ctd_interest_amt     DECIMAL(15,2),
   ctd_interest_cnt     INTEGER,
   user_field50         DECIMAL(15,2),
   user_field51         INTEGER,
   user_field52         DECIMAL(15,2),
   mtd_retail_amt       DECIMAL(15,2),
   mtd_retail_cnt       INTEGER,
   user_field53         DECIMAL(15,2),
   user_field54         INTEGER,
   user_field55         DECIMAL(15,2),
   user_field56         INTEGER,
   ytd_retail_amt       DECIMAL(15,2),
   ytd_retail_cnt       INTEGER,
   user_field57         DECIMAL(15,2),
   user_field58         INTEGER,
   user_field59         DECIMAL(15,2),
   user_field60         INTEGER,
   user_field61         DECIMAL(15,2),
   user_field62         INTEGER,
   user_field63         DECIMAL(15,2),
   user_field64         INTEGER,
   user_field65         DECIMAL(15,2),
   user_field66         INTEGER,
   user_field67         DECIMAL(15,2),
   user_field68         INTEGER,
   user_field69         DECIMAL(15,2),
   user_field70         INTEGER,
   user_field71         DECIMAL(15,2),
   user_field72         DECIMAL(15,2),
   user_field73         DECIMAL(15,2),
   user_field74         DECIMAL(15,2),
   user_field75         VARCHAR(8),
   user_field76         CHAR(2),
   user_field77         VARCHAR(24),
   user_field78         VARCHAR(24),
   user_field79         CHAR(1),
   user_field80         CHAR(1),
   user_field81         CHAR(1),
   waive_svcfee_ind     CHAR(1),
   user_field82         VARCHAR(4),
   user_field83         VARCHAR(4),
   user_field84         VARCHAR(4),
   user_field85         VARCHAR(4),
   user_field86         VARCHAR(4),
   user_field87         VARCHAR(4),
   user_field88         VARCHAR(14),
   user_date2           VARCHAR(14),
   user_field89         VARCHAR(14),
   user_field90         VARCHAR(14),
   user_field91         VARCHAR(14),
   user_field92         VARCHAR(14),
   user_field93         INTEGER,
   user_field94         INTEGER,
   user_field95         INTEGER,
   user_field96         INTEGER,
   user_field97         INTEGER,
   user_field98         INTEGER,
   user_field99         VARCHAR(40),
   user_field100        VARCHAR(40),
   user_field101        VARCHAR(40),
   user_field102        VARCHAR(40),
   user_field103        VARCHAR(40),
   user_field104        VARCHAR(40),
   user_field105        DECIMAL(15,2),
   user_field106        DECIMAL(15,2),
   user_field107        DECIMAL(15,2),
   user_field108        DECIMAL(15,2),
   user_field109        DECIMAL(15,2),
   user_field110        DECIMAL(15,2),
   jpa_version          INTEGER,
   mtd_payment_amt      DECIMAL(15,2),
   mtd_payment_cnt      INTEGER,
   ytd_payment_amt      DECIMAL(15,2),
   ytd_payment_cnt      INTEGER,
   ltd_payment_amt      DECIMAL(15,2),
   ltd_payment_cnt      INTEGER,
   user_field111        CHAR(1),
   user_field112        DECIMAL(15,2),
   user_field113        INTEGER,
   last_post_date       VARCHAR(8),
   last_modified_datetime VARCHAR(14),
   user_field114        VARCHAR(8),
   last_sync_date       VARCHAR(8),
   user_field115        VARCHAR(14),
   user_field116        DECIMAL(15,2),
   user_field117        VARCHAR(16),
   bank_group_id        VARCHAR(5),
   bank_proportion      DECIMAL(5,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_ACCOUNT primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_ACCOUNT is
'账户信息表-核心批量';

comment on column ICPS_WB_TM_ACCOUNT.busi_date is
'业务日期';

comment on column ICPS_WB_TM_ACCOUNT.file_order is
'文件序号';

comment on column ICPS_WB_TM_ACCOUNT.org is
'机构号';

comment on column ICPS_WB_TM_ACCOUNT.acct_no is
'账户编号';

comment on column ICPS_WB_TM_ACCOUNT.acct_type is
'账户类型';

comment on column ICPS_WB_TM_ACCOUNT.cust_id is
'客户编号';

comment on column ICPS_WB_TM_ACCOUNT.cust_limit_id is
'客户额度ID';

comment on column ICPS_WB_TM_ACCOUNT.product_code is
'产品代码';

comment on column ICPS_WB_TM_ACCOUNT.default_logical_card_no is
'默认逻辑卡号';

comment on column ICPS_WB_TM_ACCOUNT.currency is
'币种';

comment on column ICPS_WB_TM_ACCOUNT.credit_limit is
'授信额度';

comment on column ICPS_WB_TM_ACCOUNT.temp_limit is
'临时额度';

comment on column ICPS_WB_TM_ACCOUNT.temp_limit_begin_date is
'临时额度开始日期';

comment on column ICPS_WB_TM_ACCOUNT.temp_limit_end_date is
'临时额度结束日期';

comment on column ICPS_WB_TM_ACCOUNT.user_field1 is
'备用字段1';

comment on column ICPS_WB_TM_ACCOUNT.user_field2 is
'备用字段2';

comment on column ICPS_WB_TM_ACCOUNT.user_field3 is
'备用字段3';

comment on column ICPS_WB_TM_ACCOUNT.curr_balance is
'当前余额';

comment on column ICPS_WB_TM_ACCOUNT.user_field4 is
'备用字段4';

comment on column ICPS_WB_TM_ACCOUNT.principal_bal is
'本金余额';

comment on column ICPS_WB_TM_ACCOUNT.user_field5 is
'备用字段5';

comment on column ICPS_WB_TM_ACCOUNT.user_field6 is
'备用字段6';

comment on column ICPS_WB_TM_ACCOUNT.begin_bal is
'上一到期日余额';

comment on column ICPS_WB_TM_ACCOUNT.pmt_due_day_bal is
'到期还款日余额';

comment on column ICPS_WB_TM_ACCOUNT.user_field7 is
'备用字段7';

comment on column ICPS_WB_TM_ACCOUNT.user_field8 is
'备用字段8';

comment on column ICPS_WB_TM_ACCOUNT.user_field9 is
'备用字段9';

comment on column ICPS_WB_TM_ACCOUNT.user_field10 is
'备用字段10';

comment on column ICPS_WB_TM_ACCOUNT.user_field11 is
'备用字段11';

comment on column ICPS_WB_TM_ACCOUNT.user_field12 is
'备用字段12';

comment on column ICPS_WB_TM_ACCOUNT.user_field13 is
'备用字段13';

comment on column ICPS_WB_TM_ACCOUNT.user_field14 is
'备用字段14';

comment on column ICPS_WB_TM_ACCOUNT.user_field15 is
'备用字段15';

comment on column ICPS_WB_TM_ACCOUNT.user_field16 is
'备用字段16';

comment on column ICPS_WB_TM_ACCOUNT.user_field17 is
'备用字段17';

comment on column ICPS_WB_TM_ACCOUNT.user_field18 is
'备用字段18';

comment on column ICPS_WB_TM_ACCOUNT.name is
'姓名';

comment on column ICPS_WB_TM_ACCOUNT.gender is
'性别';

comment on column ICPS_WB_TM_ACCOUNT.user_field19 is
'备用字段19';

comment on column ICPS_WB_TM_ACCOUNT.mobile_no is
'移动电话';

comment on column ICPS_WB_TM_ACCOUNT.user_field20 is
'备用字段20';

comment on column ICPS_WB_TM_ACCOUNT.billint_cycle is
'还款日';

comment on column ICPS_WB_TM_ACCOUNT.user_field21 is
'备用字段21';

comment on column ICPS_WB_TM_ACCOUNT.user_field22 is
'备用字段22';

comment on column ICPS_WB_TM_ACCOUNT.user_field23 is
'备用字段23';

comment on column ICPS_WB_TM_ACCOUNT.user_field24 is
'备用字段24';

comment on column ICPS_WB_TM_ACCOUNT.user_field25 is
'备用字段25';

comment on column ICPS_WB_TM_ACCOUNT.user_field26 is
'备用字段26';

comment on column ICPS_WB_TM_ACCOUNT.user_field27 is
'备用字段27';

comment on column ICPS_WB_TM_ACCOUNT.user_field28 is
'备用字段28';

comment on column ICPS_WB_TM_ACCOUNT.user_field29 is
'备用字段29';

comment on column ICPS_WB_TM_ACCOUNT.user_field30 is
'备用字段30';

comment on column ICPS_WB_TM_ACCOUNT.user_field31 is
'备用字段31';

comment on column ICPS_WB_TM_ACCOUNT.AGE_CD is
'拖欠月数';

comment on column ICPS_WB_TM_ACCOUNT.user_field32 is
'备用字段32';

comment on column ICPS_WB_TM_ACCOUNT.UNMATCH_DB is
'未入账借记金额';

comment on column ICPS_WB_TM_ACCOUNT.user_field33 is
'备用字段33';

comment on column ICPS_WB_TM_ACCOUNT.unmatch_cr is
'未入账贷记金额';

comment on column ICPS_WB_TM_ACCOUNT.dd_ind is
'约定还款类型';

comment on column ICPS_WB_TM_ACCOUNT.dd_bank_name is
'约定还款银行名称';

comment on column ICPS_WB_TM_ACCOUNT.dd_bank_branch is
'约定还款开户行号';

comment on column ICPS_WB_TM_ACCOUNT.dd_bank_acct_no is
'约定还款扣款账号';

comment on column ICPS_WB_TM_ACCOUNT.dd_bank_acct_name is
'约定还款扣款账户姓名';

comment on column ICPS_WB_TM_ACCOUNT.last_dd_amt is
'上期约定还款金额';

comment on column ICPS_WB_TM_ACCOUNT.last_dd_date is
'上期约定还款日期';

comment on column ICPS_WB_TM_ACCOUNT.user_field34 is
'备用字段34';

comment on column ICPS_WB_TM_ACCOUNT.last_pmt_amt is
'上期还款金额';

comment on column ICPS_WB_TM_ACCOUNT.last_pmt_date is
'上个还款日期';

comment on column ICPS_WB_TM_ACCOUNT.last_stmt_date is
'上个到期还款日期';

comment on column ICPS_WB_TM_ACCOUNT.last_pmt_due_date is
'上个到期还款日期1';

comment on column ICPS_WB_TM_ACCOUNT.last_agint_date is
'上课逾期月数提升日期';

comment on column ICPS_WB_TM_ACCOUNT.collect_date is
'入催日期';

comment on column ICPS_WB_TM_ACCOUNT.collect_out_date is
'出催收队列日期';

comment on column ICPS_WB_TM_ACCOUNT.next_stmt_date is
'下个到期还款日期';

comment on column ICPS_WB_TM_ACCOUNT.pmt_due_date is
'到期还款日期';

comment on column ICPS_WB_TM_ACCOUNT.dd_date is
'约定还款日期';

comment on column ICPS_WB_TM_ACCOUNT.grace_date is
'宽限日期';

comment on column ICPS_WB_TM_ACCOUNT.user_field35 is
'备用字段35';

comment on column ICPS_WB_TM_ACCOUNT.closed_date is
'最终销户日期';

comment on column ICPS_WB_TM_ACCOUNT.first_stmt_date is
'首个到期还款日期';

comment on column ICPS_WB_TM_ACCOUNT.cancel_date is
'销户日期';

comment on column ICPS_WB_TM_ACCOUNT.charge_off_date is
'转呆账日期';

comment on column ICPS_WB_TM_ACCOUNT.user_field36 is
'备用字段36';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field37 is
'备用字段37';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field38 is
'备用字段38';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field39 is
'备用字段39';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field40 is
'备用字段40';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field41 is
'备用字段41';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field42 is
'备用字段42';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field43 is
'备用字段43';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field44 is
'备用字段44';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field45 is
'备用字段45';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field46 is
'备用字段46';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field47 is
'备用字段47';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field48 is
'备用字段48';

comment on column ICPS_WB_TM_ACCOUNT.usesr_field49 is
'备用字段49';

comment on column ICPS_WB_TM_ACCOUNT.ctd_retail_amt is
'当期消费金额';

comment on column ICPS_WB_TM_ACCOUNT.ctd_retail_cnt is
'当期消费笔数';

comment on column ICPS_WB_TM_ACCOUNT.ctd_payment_amt is
'当期还款金额';

comment on column ICPS_WB_TM_ACCOUNT.ctd_payment_cnt is
'当期还款笔数';

comment on column ICPS_WB_TM_ACCOUNT.ctd_db_adj_amt is
'当期借记调整金额';

comment on column ICPS_WB_TM_ACCOUNT.ctd_db_adj_cnt is
'当期借记调整笔数';

comment on column ICPS_WB_TM_ACCOUNT.ctd_cr_adj_cnt is
'当期贷记调整笔数';

comment on column ICPS_WB_TM_ACCOUNT.ctd_cr_adj_amt is
'当期贷记调整金额';

comment on column ICPS_WB_TM_ACCOUNT.ctd_fee_amt is
'当期贷记调整金额';

comment on column ICPS_WB_TM_ACCOUNT.ctd_fee_cnt is
'当期费用笔数';

comment on column ICPS_WB_TM_ACCOUNT.ctd_interest_amt is
'当期利息金额';

comment on column ICPS_WB_TM_ACCOUNT.ctd_interest_cnt is
'当期利息笔数';

comment on column ICPS_WB_TM_ACCOUNT.user_field50 is
'备用字段50';

comment on column ICPS_WB_TM_ACCOUNT.user_field51 is
'备用字段51';

comment on column ICPS_WB_TM_ACCOUNT.user_field52 is
'备用字段52';

comment on column ICPS_WB_TM_ACCOUNT.mtd_retail_amt is
'本月消费金额';

comment on column ICPS_WB_TM_ACCOUNT.mtd_retail_cnt is
'本月消费笔数';

comment on column ICPS_WB_TM_ACCOUNT.user_field53 is
'备用字段53';

comment on column ICPS_WB_TM_ACCOUNT.user_field54 is
'备用字段54';

comment on column ICPS_WB_TM_ACCOUNT.user_field55 is
'备用字段55';

comment on column ICPS_WB_TM_ACCOUNT.user_field56 is
'备用字段56';

comment on column ICPS_WB_TM_ACCOUNT.ytd_retail_amt is
'本年消费金额';

comment on column ICPS_WB_TM_ACCOUNT.ytd_retail_cnt is
'本年消费笔数';

comment on column ICPS_WB_TM_ACCOUNT.user_field57 is
'备用字段57';

comment on column ICPS_WB_TM_ACCOUNT.user_field58 is
'备用字段58';

comment on column ICPS_WB_TM_ACCOUNT.user_field59 is
'备用字段59';

comment on column ICPS_WB_TM_ACCOUNT.user_field60 is
'备用字段60';

comment on column ICPS_WB_TM_ACCOUNT.user_field61 is
'备用字段61';

comment on column ICPS_WB_TM_ACCOUNT.user_field62 is
'备用字段62';

comment on column ICPS_WB_TM_ACCOUNT.user_field63 is
'备用字段63';

comment on column ICPS_WB_TM_ACCOUNT.user_field64 is
'备用字段64';

comment on column ICPS_WB_TM_ACCOUNT.user_field65 is
'备用字段64';

comment on column ICPS_WB_TM_ACCOUNT.user_field66 is
'备用字段66';

comment on column ICPS_WB_TM_ACCOUNT.user_field67 is
'备用字段67';

comment on column ICPS_WB_TM_ACCOUNT.user_field68 is
'备用字段68';

comment on column ICPS_WB_TM_ACCOUNT.user_field69 is
'备用字段69';

comment on column ICPS_WB_TM_ACCOUNT.user_field70 is
'备用字段70';

comment on column ICPS_WB_TM_ACCOUNT.user_field71 is
'备用字段71';

comment on column ICPS_WB_TM_ACCOUNT.user_field72 is
'备用字段72';

comment on column ICPS_WB_TM_ACCOUNT.user_field73 is
'备用字段73';

comment on column ICPS_WB_TM_ACCOUNT.user_field74 is
'备用字段74';

comment on column ICPS_WB_TM_ACCOUNT.user_field75 is
'备用字段75';

comment on column ICPS_WB_TM_ACCOUNT.user_field76 is
'备用字段76';

comment on column ICPS_WB_TM_ACCOUNT.user_field77 is
'备用字段77';

comment on column ICPS_WB_TM_ACCOUNT.user_field78 is
'备用字段78';

comment on column ICPS_WB_TM_ACCOUNT.user_field79 is
'备用字段79';

comment on column ICPS_WB_TM_ACCOUNT.user_field80 is
'备用字段80';

comment on column ICPS_WB_TM_ACCOUNT.user_field81 is
'备用字段81';

comment on column ICPS_WB_TM_ACCOUNT.waive_svcfee_ind is
'是否免除服务费';

comment on column ICPS_WB_TM_ACCOUNT.user_field82 is
'备用字段82';

comment on column ICPS_WB_TM_ACCOUNT.user_field83 is
'备用字段83';

comment on column ICPS_WB_TM_ACCOUNT.user_field84 is
'备用字段84';

comment on column ICPS_WB_TM_ACCOUNT.user_field85 is
'备用字段85';

comment on column ICPS_WB_TM_ACCOUNT.user_field86 is
'备用字段86';

comment on column ICPS_WB_TM_ACCOUNT.user_field87 is
'备用字段87';

comment on column ICPS_WB_TM_ACCOUNT.user_field88 is
'备用字段88';

comment on column ICPS_WB_TM_ACCOUNT.user_date2 is
'上期调额日期';

comment on column ICPS_WB_TM_ACCOUNT.user_field89 is
'备用字段89';

comment on column ICPS_WB_TM_ACCOUNT.user_field90 is
'备用字段90';

comment on column ICPS_WB_TM_ACCOUNT.user_field91 is
'备用字段91';

comment on column ICPS_WB_TM_ACCOUNT.user_field92 is
'备用字段92';

comment on column ICPS_WB_TM_ACCOUNT.user_field93 is
'备用字段93';

comment on column ICPS_WB_TM_ACCOUNT.user_field94 is
'备用字段94';

comment on column ICPS_WB_TM_ACCOUNT.user_field95 is
'备用字段95';

comment on column ICPS_WB_TM_ACCOUNT.user_field96 is
'备用字段96';

comment on column ICPS_WB_TM_ACCOUNT.user_field97 is
'备用字段97';

comment on column ICPS_WB_TM_ACCOUNT.user_field98 is
'备用字段98';

comment on column ICPS_WB_TM_ACCOUNT.user_field99 is
'备用字段99';

comment on column ICPS_WB_TM_ACCOUNT.user_field100 is
'备用字段100';

comment on column ICPS_WB_TM_ACCOUNT.user_field101 is
'备用字段101';

comment on column ICPS_WB_TM_ACCOUNT.user_field102 is
'备用字段102';

comment on column ICPS_WB_TM_ACCOUNT.user_field103 is
'备用字段103';

comment on column ICPS_WB_TM_ACCOUNT.user_field104 is
'备用字段104';

comment on column ICPS_WB_TM_ACCOUNT.user_field105 is
'备用字段105';

comment on column ICPS_WB_TM_ACCOUNT.user_field106 is
'备用字段106';

comment on column ICPS_WB_TM_ACCOUNT.user_field107 is
'备用字段107';

comment on column ICPS_WB_TM_ACCOUNT.user_field108 is
'备用字段108';

comment on column ICPS_WB_TM_ACCOUNT.user_field109 is
'备用字段109';

comment on column ICPS_WB_TM_ACCOUNT.user_field110 is
'备用字段110';

comment on column ICPS_WB_TM_ACCOUNT.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_ACCOUNT.mtd_payment_amt is
'当月还款金额';

comment on column ICPS_WB_TM_ACCOUNT.mtd_payment_cnt is
'当月还款笔数';

comment on column ICPS_WB_TM_ACCOUNT.ytd_payment_amt is
'当年还款金额';

comment on column ICPS_WB_TM_ACCOUNT.ytd_payment_cnt is
'当年还款笔数';

comment on column ICPS_WB_TM_ACCOUNT.ltd_payment_amt is
'历史还款金额';

comment on column ICPS_WB_TM_ACCOUNT.ltd_payment_cnt is
'历史还款笔数';

comment on column ICPS_WB_TM_ACCOUNT.user_field111 is
'备用字段111';

comment on column ICPS_WB_TM_ACCOUNT.user_field112 is
'备用字段112';

comment on column ICPS_WB_TM_ACCOUNT.user_field113 is
'备用字段113';

comment on column ICPS_WB_TM_ACCOUNT.last_post_date is
'上个批量处理时间';

comment on column ICPS_WB_TM_ACCOUNT.last_modified_datetime is
'修改时间';

comment on column ICPS_WB_TM_ACCOUNT.user_field114 is
'备用字段114';

comment on column ICPS_WB_TM_ACCOUNT.last_sync_date is
'上一次入账的批量日期';

comment on column ICPS_WB_TM_ACCOUNT.user_field115 is
'备用字段115';

comment on column ICPS_WB_TM_ACCOUNT.user_field116 is
'备用字段116';

comment on column ICPS_WB_TM_ACCOUNT.user_field117 is
'备用字段117';

comment on column ICPS_WB_TM_ACCOUNT.bank_group_id is
'银团编号';

comment on column ICPS_WB_TM_ACCOUNT.bank_proportion is
'银行出资比例';

comment on column ICPS_WB_TM_ACCOUNT.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_ACCOUNT.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_ACCOUNT.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_ACCOUNT.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_AUTH_BANK_COST                             */
/*==============================================================*/
create table ICPS_WB_TM_AUTH_BANK_COST 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   busi_serial          VARCHAR(32),
   bank_group_id        VARCHAR(5),
   bank_no              VARCHAR(10),
   reg_type             VARCHAR(50),
   reg_amt              DECIMAL(15,2),
   reg_status           VARCHAR(10),
   reg_sys_id           VARCHAR(32),
   reg_date             VARCHAR(14),
   reg_time             VARCHAR(14),
   recon_code           VARCHAR(20),
   ori_sys_id           VARCHAR(32),
   cust_id              VARCHAR(20),
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   retry                INTEGER,
   created_datetime     VARCHAR(14),
   last_modified_datetime VARCHAR(14),
   user_field268        INTEGER,
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_AUTH_BANK_COST primary key (file_order, busi_date)
);

comment on table ICPS_WB_TM_AUTH_BANK_COST is
'授权流水银团拆分表';

comment on column ICPS_WB_TM_AUTH_BANK_COST.busi_date is
'业务日期';

comment on column ICPS_WB_TM_AUTH_BANK_COST.file_order is
'文件序号';

comment on column ICPS_WB_TM_AUTH_BANK_COST.busi_serial is
'业务流水号';

comment on column ICPS_WB_TM_AUTH_BANK_COST.bank_group_id is
'银团编号';

comment on column ICPS_WB_TM_AUTH_BANK_COST.bank_no is
'银行号';

comment on column ICPS_WB_TM_AUTH_BANK_COST.reg_type is
'登记类型';

comment on column ICPS_WB_TM_AUTH_BANK_COST.reg_amt is
'登记金额';

comment on column ICPS_WB_TM_AUTH_BANK_COST.reg_status is
'登记状态';

comment on column ICPS_WB_TM_AUTH_BANK_COST.reg_sys_id is
'记账流水号';

comment on column ICPS_WB_TM_AUTH_BANK_COST.reg_date is
'记账日期';

comment on column ICPS_WB_TM_AUTH_BANK_COST.reg_time is
'记账请求时间';

comment on column ICPS_WB_TM_AUTH_BANK_COST.recon_code is
'对账码';

comment on column ICPS_WB_TM_AUTH_BANK_COST.ori_sys_id is
'原记账流水号';

comment on column ICPS_WB_TM_AUTH_BANK_COST.cust_id is
'客户编号';

comment on column ICPS_WB_TM_AUTH_BANK_COST.acct_no is
'账户编号';

comment on column ICPS_WB_TM_AUTH_BANK_COST.acct_type is
'账户类型';

comment on column ICPS_WB_TM_AUTH_BANK_COST.retry is
'尝试次数';

comment on column ICPS_WB_TM_AUTH_BANK_COST.created_datetime is
'创建时间';

comment on column ICPS_WB_TM_AUTH_BANK_COST.last_modified_datetime is
'时间戳';

comment on column ICPS_WB_TM_AUTH_BANK_COST.user_field268 is
'备用字段268';

comment on column ICPS_WB_TM_AUTH_BANK_COST.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_AUTH_BANK_COST.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_AUTH_BANK_COST.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_AUTH_BANK_COST.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_CARD                                       */
/*==============================================================*/
create table ICPS_WB_TM_CARD 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   logical_card_no      VARCHAR(19),
   acct_no              VARCHAR(20),
   cust_id              VARCHAR(20),
   user_field118        VARCHAR(15),
   product_cd           CHAR(6),
   app_no               VARCHAR(20),
   user_field119        VARCHAR(40),
   user_field120        CHAR(1),
   bsc_logiccard_no     VARCHAR(19),
   user_field121        VARCHAR(9),
   user_field122        VARCHAR(15),
   user_field123        VARCHAR(80),
   user_field124        VARCHAR(19),
   user_field125        VARCHAR(14),
   user_field126        VARCHAR(27),
   activate_ind         CHAR(1),
   cancel_date          VARCHAR(14),
   latest_card_no       VARCHAR(19),
   user_field127        CHAR(1),
   user_field128        VARCHAR(20),
   user_field129        VARCHAR(80),
   user_field130        CHAR(1),
   user_field131        CHAR(1),
   card_expire_date     VARCHAR(14),
   user_field132        DECIMAL(5,2),
   user_field133        CHAR(1),
   user_field134        CHAR(3),
   user_field135        VARCHAR(14),
   user_field136        VARCHAR(14),
   user_field137        CHAR(1),
   user_field138        VARCHAR(14),
   user_field139        CHAR(1),
   user_field140        CHAR(1),
   user_field141        CHAR(1),
   jpa_version          INTEGER,
   user_field142        VARCHAR(14),
   user_field143        VARCHAR(14),
   user_field144        VARCHAR(14),
   user_field145        VARCHAR(14),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_CARD primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_CARD is
'逻辑卡表';

comment on column ICPS_WB_TM_CARD.busi_date is
'业务日期';

comment on column ICPS_WB_TM_CARD.file_order is
'文件序号';

comment on column ICPS_WB_TM_CARD.org is
'机构号';

comment on column ICPS_WB_TM_CARD.logical_card_no is
'逻辑卡号';

comment on column ICPS_WB_TM_CARD.acct_no is
'账户编号';

comment on column ICPS_WB_TM_CARD.cust_id is
'客户编号';

comment on column ICPS_WB_TM_CARD.user_field118 is
'备用字段118';

comment on column ICPS_WB_TM_CARD.product_cd is
'产品代码';

comment on column ICPS_WB_TM_CARD.app_no is
'申请件编号';

comment on column ICPS_WB_TM_CARD.user_field119 is
'备用字段119';

comment on column ICPS_WB_TM_CARD.user_field120 is
'备用字段120';

comment on column ICPS_WB_TM_CARD.bsc_logiccard_no is
'逻辑卡主卡卡号';

comment on column ICPS_WB_TM_CARD.user_field121 is
'备用字段121';

comment on column ICPS_WB_TM_CARD.user_field122 is
'备用字段122';

comment on column ICPS_WB_TM_CARD.user_field123 is
'备用字段123';

comment on column ICPS_WB_TM_CARD.user_field124 is
'备用字段124';

comment on column ICPS_WB_TM_CARD.user_field125 is
'备用字段125';

comment on column ICPS_WB_TM_CARD.user_field126 is
'备用字段126';

comment on column ICPS_WB_TM_CARD.activate_ind is
'是否已激活';

comment on column ICPS_WB_TM_CARD.cancel_date is
'销卡销户日期';

comment on column ICPS_WB_TM_CARD.latest_card_no is
'最新介质卡号';

comment on column ICPS_WB_TM_CARD.user_field127 is
'备用字段127';

comment on column ICPS_WB_TM_CARD.user_field128 is
'备用字段128';

comment on column ICPS_WB_TM_CARD.user_field129 is
'备用字段129';

comment on column ICPS_WB_TM_CARD.user_field130 is
'备用字段130';

comment on column ICPS_WB_TM_CARD.user_field131 is
'备用字段131';

comment on column ICPS_WB_TM_CARD.card_expire_date is
'卡片有效日期';

comment on column ICPS_WB_TM_CARD.user_field132 is
'备用字段132';

comment on column ICPS_WB_TM_CARD.user_field133 is
'备用字段133';

comment on column ICPS_WB_TM_CARD.user_field134 is
'备用字段134';

comment on column ICPS_WB_TM_CARD.user_field135 is
'备用字段135';

comment on column ICPS_WB_TM_CARD.user_field136 is
'备用字段136';

comment on column ICPS_WB_TM_CARD.user_field137 is
'备用字段137';

comment on column ICPS_WB_TM_CARD.user_field138 is
'备用字段138';

comment on column ICPS_WB_TM_CARD.user_field139 is
'备用字段139';

comment on column ICPS_WB_TM_CARD.user_field140 is
'备用字段140';

comment on column ICPS_WB_TM_CARD.user_field141 is
'备用字段141';

comment on column ICPS_WB_TM_CARD.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_CARD.user_field142 is
'备用字段142';

comment on column ICPS_WB_TM_CARD.user_field143 is
'备用字段143';

comment on column ICPS_WB_TM_CARD.user_field144 is
'备用字段144';

comment on column ICPS_WB_TM_CARD.user_field145 is
'备用字段145';

comment on column ICPS_WB_TM_CARD.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_CARD.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_CARD.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_CARD.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_GL_BAL                                     */
/*==============================================================*/
create table ICPS_WB_TM_GL_BAL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   subject              VARCHAR(40),
   branch_id            VARCHAR(9),
   db_bal               DECIMAL(15,2),
   cr_bal               DECIMAL(15,2),
   db_amt               DECIMAL(15,2),
   db_count             INTEGER,
   cr_amt               DECIMAL(15,2),
   cr_count             INTEGER,
   last_db_bal          DECIMAL(15,2),
   last_cr_bal          DECIMAL(15,2),
   last_mth_db_bal      DECIMAL(15,2),
   last_mth_cr_bal      DECIMAL(15,2),
   last_qtr_db_bal      DECIMAL(15,2),
   last_qtr_cr_bal      DECIMAL(15,2),
   last_yr_db_ba        DECIMAL(15,2),
   last_yr_cr_ba        DECIMAL(15,2),
   jpa_version          INTEGER,
   product_cd           VARCHAR(6),
   bal_id               INTEGER,
   bank_no              VARCHAR(10),
   bank_group_id        VARCHAR(5),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_GL_BAL primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_GL_BAL is
'总账会计科目表';

comment on column ICPS_WB_TM_GL_BAL.busi_date is
'业务日期';

comment on column ICPS_WB_TM_GL_BAL.file_order is
'文件序号';

comment on column ICPS_WB_TM_GL_BAL.org is
'机构号';

comment on column ICPS_WB_TM_GL_BAL.subject is
'科目';

comment on column ICPS_WB_TM_GL_BAL.branch_id is
'分支行号';

comment on column ICPS_WB_TM_GL_BAL.db_bal is
'借方余额';

comment on column ICPS_WB_TM_GL_BAL.cr_bal is
'贷方余额';

comment on column ICPS_WB_TM_GL_BAL.db_amt is
'借方发生额';

comment on column ICPS_WB_TM_GL_BAL.db_count is
'借方笔数';

comment on column ICPS_WB_TM_GL_BAL.cr_amt is
'贷方发生额';

comment on column ICPS_WB_TM_GL_BAL.cr_count is
'贷方笔数';

comment on column ICPS_WB_TM_GL_BAL.last_db_bal is
'昨日借方余额';

comment on column ICPS_WB_TM_GL_BAL.last_cr_bal is
'昨日贷方余额';

comment on column ICPS_WB_TM_GL_BAL.last_mth_db_bal is
'上月末借方余额';

comment on column ICPS_WB_TM_GL_BAL.last_mth_cr_bal is
'上月末贷方余额';

comment on column ICPS_WB_TM_GL_BAL.last_qtr_db_bal is
'上季末借方余额';

comment on column ICPS_WB_TM_GL_BAL.last_qtr_cr_bal is
'上季末贷方余额';

comment on column ICPS_WB_TM_GL_BAL.last_yr_db_ba is
'上年末借方余额';

comment on column ICPS_WB_TM_GL_BAL.last_yr_cr_ba is
'上年末贷方余额';

comment on column ICPS_WB_TM_GL_BAL.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_GL_BAL.product_cd is
'产品编号';

comment on column ICPS_WB_TM_GL_BAL.bal_id is
'顺序号';

comment on column ICPS_WB_TM_GL_BAL.bank_no is
'银行代码';

comment on column ICPS_WB_TM_GL_BAL.bank_group_id is
'银团代码';

comment on column ICPS_WB_TM_GL_BAL.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_GL_BAL.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_GL_BAL.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_GL_BAL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_PLAN                                       */
/*==============================================================*/
create table ICPS_WB_TM_PLAN 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   plan_id              VARCHAR(20),
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   logical_card_no      VARCHAR(19),
   plan_nbr             CHAR(6),
   plan_type            CHAR(1),
   product_code         CHAR(6),
   ref_nbr              VARCHAR(23),
   curr_balance         DECIMAL(15,2),
   begin_bal            DECIMAL(15,2),
   dispute_amt          DECIMAL(15,2),
   tot_due_amt          DECIMAL(15,2),
   plan_add_date        VARCHAR(14),
   paid_out_date        VARCHAR(14),
   past_principal       DECIMAL(15,2),
   past_interest        DECIMAL(15,2),
   past_card_fee        DECIMAL(15,2),
   past_ovrlmt_fee      DECIMAL(15,2),
   past_lpc             DECIMAL(15,2),
   past_nsf_fee         DECIMAL(15,2),
   past_txn_fee         DECIMAL(15,2),
   past_svc_fee         DECIMAL(15,2),
   past_ins             DECIMAL(15,2),
   past_user_fee1       DECIMAL(15,2),
   past_user_fee2       DECIMAL(15,2),
   past_user_fee3       DECIMAL(15,2),
   past_user_fee4       DECIMAL(15,2),
   past_user_fee5       DECIMAL(15,2),
   past_user_fee6       DECIMAL(15,2),
   CTD_PRINCIPAL        DECIMAL(15,2),
   ctd_interest         DECIMAL(15,2),
   ctd_card_fee         DECIMAL(15,2),
   ctd_ovrlmt_fee       DECIMAL(15,2),
   ctd_lpc              DECIMAL(15,2),
   ctd_nsf_fee          DECIMAL(15,2),
   ctd_svc_fee          DECIMAL(15,2),
   ctd_txn_fee          DECIMAL(15,2),
   ctd_ins              DECIMAL(15,2),
   ctd_user_fee1        DECIMAL(15,2),
   ctd_user_fee2        DECIMAL(15,2),
   ctd_user_fee3        DECIMAL(15,2),
   ctd_user_fee4        DECIMAL(15,2),
   ctd_user_fee5        DECIMAL(15,2),
   ctd_user_fee6        DECIMAL(15,2),
   ctd_amt_db           DECIMAL(15,2),
   ctd_amt_cr           DECIMAL(15,2),
   ctd_nbr_db           INTEGER,
   ctd_nbr_cr           INTEGER,
   nodefbnp_int_acru    DECIMAL(15,4),
   beg_defbnp_int_acru  DECIMAL(15,4),
   ctd_defbnp_int_acru  DECIMAL(15,4),
   user_field146        VARCHAR(4),
   user_field147        VARCHAR(4),
   user_field148        VARCHAR(4),
   user_field149        VARCHAR(4),
   user_field150        VARCHAR(4),
   user_field151        VARCHAR(4),
   user_field152        INTEGER,
   user_field153        INTEGER,
   user_field154        INTEGER,
   user_field155        INTEGER,
   user_field156        INTEGER,
   user_field157        INTEGER,
   user_field158        VARCHAR(40),
   user_field159        VARCHAR(40),
   user_field160        VARCHAR(40),
   user_field161        VARCHAR(40),
   user_field162        VARCHAR(40),
   user_field163        VARCHAR(40),
   user_field164        VARCHAR(14),
   user_field165        VARCHAR(14),
   user_field166        VARCHAR(14),
   user_field167        VARCHAR(14),
   user_field168        VARCHAR(14),
   user_field169        VARCHAR(14),
   user_field170        DECIMAL(15,2),
   user_field171        DECIMAL(15,2),
   user_field172        DECIMAL(15,2),
   user_field173        DECIMAL(15,2),
   user_field174        DECIMAL(15,2),
   user_field175        DECIMAL(15,2),
   jpa_version          INTEGER,
   past_penalty         DECIMAL(15,2),
   ctd_penalty          DECIMAL(15,2),
   past_compound        DECIMAL(15,2),
   ctd_compound         DECIMAL(15,2),
   penalty_acru         DECIMAL(15,4),
   compound_acru        DECIMAL(15,4),
   interest_rate        DECIMAL(12,4),
   penalty_rate         DECIMAL(12,4),
   compound_rate        DECIMAL(12,4),
   use_plan_rate        CHAR(1),
   last_pmt_date        VARCHAR(14),
   term                 INTEGER,
   calc_type            CHAR(1),
   calc_cycle           INTEGER,
   fee_rate             DECIMAL(15,4),
   last_fee_date        VARCHAR(14),
   next_fee_date        VARCHAR(14),
   trans_serial         VARCHAR(20),
   first_dd_date        VARCHAR(14),
   busi_serial          VARCHAR(32),
   sys_trans_id         VARCHAR(32),
   user_field176        VARCHAR(15),
   sub_terminal_type    VARCHAR(15),
   sub_merch_id         VARCHAR(40),
   sub_merch_name       VARCHAR(60),
   wares_desc           VARCHAR(60),
   last_modified_datetime VARCHAR(14),
   original_amt         DECIMAL(15,4),
   interest_calc_base   CHAR(1),
   created_datetime     VARCHAR(14),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_PLAN primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_PLAN is
'信用计划表';

comment on column ICPS_WB_TM_PLAN.busi_date is
'业务日期';

comment on column ICPS_WB_TM_PLAN.file_order is
'文件序号';

comment on column ICPS_WB_TM_PLAN.org is
'机构号';

comment on column ICPS_WB_TM_PLAN.plan_id is
'流水号';

comment on column ICPS_WB_TM_PLAN.acct_no is
'账户编号';

comment on column ICPS_WB_TM_PLAN.acct_type is
'账户类型';

comment on column ICPS_WB_TM_PLAN.logical_card_no is
'逻辑卡号';

comment on column ICPS_WB_TM_PLAN.plan_nbr is
'信用计划号';

comment on column ICPS_WB_TM_PLAN.plan_type is
'信用计划类型';

comment on column ICPS_WB_TM_PLAN.product_code is
'产品代码';

comment on column ICPS_WB_TM_PLAN.ref_nbr is
'交易参考号';

comment on column ICPS_WB_TM_PLAN.curr_balance is
'当前余额';

comment on column ICPS_WB_TM_PLAN.begin_bal is
'期初余额';

comment on column ICPS_WB_TM_PLAN.dispute_amt is
'争议金额';

comment on column ICPS_WB_TM_PLAN.tot_due_amt is
'最小还款额';

comment on column ICPS_WB_TM_PLAN.plan_add_date is
'纪录建立日期';

comment on column ICPS_WB_TM_PLAN.paid_out_date is
'还清日期';

comment on column ICPS_WB_TM_PLAN.past_principal is
'上期本金';

comment on column ICPS_WB_TM_PLAN.past_interest is
'上期利息';

comment on column ICPS_WB_TM_PLAN.past_card_fee is
'上期年费';

comment on column ICPS_WB_TM_PLAN.past_ovrlmt_fee is
'上期超限费';

comment on column ICPS_WB_TM_PLAN.past_lpc is
'上期滞纳金';

comment on column ICPS_WB_TM_PLAN.past_nsf_fee is
'上期资金不足费';

comment on column ICPS_WB_TM_PLAN.past_txn_fee is
'上期交易费';

comment on column ICPS_WB_TM_PLAN.past_svc_fee is
'上期服务费';

comment on column ICPS_WB_TM_PLAN.past_ins is
'上期保险金额';

comment on column ICPS_WB_TM_PLAN.past_user_fee1 is
'上期自定义费用1';

comment on column ICPS_WB_TM_PLAN.past_user_fee2 is
'上期自定义费用2';

comment on column ICPS_WB_TM_PLAN.past_user_fee3 is
'上期自定义费用3';

comment on column ICPS_WB_TM_PLAN.past_user_fee4 is
'上期自定义费用4';

comment on column ICPS_WB_TM_PLAN.past_user_fee5 is
'上期自定义费用5';

comment on column ICPS_WB_TM_PLAN.past_user_fee6 is
'上期自定义费用6';

comment on column ICPS_WB_TM_PLAN.CTD_PRINCIPAL is
'当前本金';

comment on column ICPS_WB_TM_PLAN.ctd_interest is
'当期利息';

comment on column ICPS_WB_TM_PLAN.ctd_card_fee is
'当期年费';

comment on column ICPS_WB_TM_PLAN.ctd_ovrlmt_fee is
'当期超限费';

comment on column ICPS_WB_TM_PLAN.ctd_lpc is
'当期滞纳金';

comment on column ICPS_WB_TM_PLAN.ctd_nsf_fee is
'当期资金不足费';

comment on column ICPS_WB_TM_PLAN.ctd_svc_fee is
'当期服务费';

comment on column ICPS_WB_TM_PLAN.ctd_txn_fee is
'当期交易费';

comment on column ICPS_WB_TM_PLAN.ctd_ins is
'当期保险金额';

comment on column ICPS_WB_TM_PLAN.ctd_user_fee1 is
'当期新增自定义费用1';

comment on column ICPS_WB_TM_PLAN.ctd_user_fee2 is
'当期新增自定义费用2';

comment on column ICPS_WB_TM_PLAN.ctd_user_fee3 is
'当期新增自定义费用3';

comment on column ICPS_WB_TM_PLAN.ctd_user_fee4 is
'当期新增自定义费用4';

comment on column ICPS_WB_TM_PLAN.ctd_user_fee5 is
'当期新增自定义费用5';

comment on column ICPS_WB_TM_PLAN.ctd_user_fee6 is
'当期新增自定义费用6';

comment on column ICPS_WB_TM_PLAN.ctd_amt_db is
'当期借记金额';

comment on column ICPS_WB_TM_PLAN.ctd_amt_cr is
'当期贷记金额';

comment on column ICPS_WB_TM_PLAN.ctd_nbr_db is
'当期借记交易笔数';

comment on column ICPS_WB_TM_PLAN.ctd_nbr_cr is
'当期贷记交易笔数';

comment on column ICPS_WB_TM_PLAN.nodefbnp_int_acru is
'非延迟利息';

comment on column ICPS_WB_TM_PLAN.beg_defbnp_int_acru is
'往期累积延时利息';

comment on column ICPS_WB_TM_PLAN.ctd_defbnp_int_acru is
'当期累积延时利息';

comment on column ICPS_WB_TM_PLAN.user_field146 is
'备用字段146';

comment on column ICPS_WB_TM_PLAN.user_field147 is
'备用字段147';

comment on column ICPS_WB_TM_PLAN.user_field148 is
'备用字段148';

comment on column ICPS_WB_TM_PLAN.user_field149 is
'备用字段149';

comment on column ICPS_WB_TM_PLAN.user_field150 is
'备用字段150';

comment on column ICPS_WB_TM_PLAN.user_field151 is
'备用字段151';

comment on column ICPS_WB_TM_PLAN.user_field152 is
'备用字段152';

comment on column ICPS_WB_TM_PLAN.user_field153 is
'备用字段153';

comment on column ICPS_WB_TM_PLAN.user_field154 is
'备用字段154';

comment on column ICPS_WB_TM_PLAN.user_field155 is
'备用字段155';

comment on column ICPS_WB_TM_PLAN.user_field156 is
'备用字段156';

comment on column ICPS_WB_TM_PLAN.user_field157 is
'备用字段157';

comment on column ICPS_WB_TM_PLAN.user_field158 is
'备用字段158';

comment on column ICPS_WB_TM_PLAN.user_field159 is
'备用字段159';

comment on column ICPS_WB_TM_PLAN.user_field160 is
'备用字段160';

comment on column ICPS_WB_TM_PLAN.user_field161 is
'备用字段161';

comment on column ICPS_WB_TM_PLAN.user_field162 is
'备用字段162';

comment on column ICPS_WB_TM_PLAN.user_field163 is
'备用字段163';

comment on column ICPS_WB_TM_PLAN.user_field164 is
'备用字段164';

comment on column ICPS_WB_TM_PLAN.user_field165 is
'备用字段165';

comment on column ICPS_WB_TM_PLAN.user_field166 is
'备用字段166';

comment on column ICPS_WB_TM_PLAN.user_field167 is
'备用字段167';

comment on column ICPS_WB_TM_PLAN.user_field168 is
'备用字段168';

comment on column ICPS_WB_TM_PLAN.user_field169 is
'备用字段169';

comment on column ICPS_WB_TM_PLAN.user_field170 is
'备用字段170';

comment on column ICPS_WB_TM_PLAN.user_field171 is
'备用字段171';

comment on column ICPS_WB_TM_PLAN.user_field172 is
'备用字段172';

comment on column ICPS_WB_TM_PLAN.user_field173 is
'备用字段173';

comment on column ICPS_WB_TM_PLAN.user_field174 is
'备用字段174';

comment on column ICPS_WB_TM_PLAN.user_field175 is
'备用字段175';

comment on column ICPS_WB_TM_PLAN.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_PLAN.past_penalty is
'往期罚息';

comment on column ICPS_WB_TM_PLAN.ctd_penalty is
'当期罚息';

comment on column ICPS_WB_TM_PLAN.past_compound is
'往期复利';

comment on column ICPS_WB_TM_PLAN.ctd_compound is
'当期复利';

comment on column ICPS_WB_TM_PLAN.penalty_acru is
'罚息累计';

comment on column ICPS_WB_TM_PLAN.compound_acru is
'复利累计';

comment on column ICPS_WB_TM_PLAN.interest_rate is
'基础利率';

comment on column ICPS_WB_TM_PLAN.penalty_rate is
'罚息利率';

comment on column ICPS_WB_TM_PLAN.compound_rate is
'复利利率';

comment on column ICPS_WB_TM_PLAN.use_plan_rate is
'是否使用plan的利率';

comment on column ICPS_WB_TM_PLAN.last_pmt_date is
'上一还款日期';

comment on column ICPS_WB_TM_PLAN.term is
'所在贷款期数';

comment on column ICPS_WB_TM_PLAN.calc_type is
'计费类型';

comment on column ICPS_WB_TM_PLAN.calc_cycle is
'计费周期';

comment on column ICPS_WB_TM_PLAN.fee_rate is
'费率';

comment on column ICPS_WB_TM_PLAN.last_fee_date is
'上一收费日';

comment on column ICPS_WB_TM_PLAN.next_fee_date is
'下一收费日';

comment on column ICPS_WB_TM_PLAN.trans_serial is
'交易流水号';

comment on column ICPS_WB_TM_PLAN.first_dd_date is
'交易流水号';

comment on column ICPS_WB_TM_PLAN.busi_serial is
'业务流水号';

comment on column ICPS_WB_TM_PLAN.sys_trans_id is
'系统调用流水号';

comment on column ICPS_WB_TM_PLAN.user_field176 is
'备用字段176';

comment on column ICPS_WB_TM_PLAN.sub_terminal_type is
'终端类型';

comment on column ICPS_WB_TM_PLAN.sub_merch_id is
'二级商户编码';

comment on column ICPS_WB_TM_PLAN.sub_merch_name is
'二级商户名称';

comment on column ICPS_WB_TM_PLAN.wares_desc is
'商品信息';

comment on column ICPS_WB_TM_PLAN.last_modified_datetime is
'修改时间';

comment on column ICPS_WB_TM_PLAN.original_amt is
'原始交易本金';

comment on column ICPS_WB_TM_PLAN.interest_calc_base is
'计息基数';

comment on column ICPS_WB_TM_PLAN.created_datetime is
'创建时间';

comment on column ICPS_WB_TM_PLAN.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_PLAN.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_PLAN.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_PLAN.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_APP_MAIN                                   */
/*==============================================================*/
create table ICPS_WB_TM_APP_MAIN 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   app_no               VARCHAR(20),
   user_field1          CHAR(1),
   user_field2          DECIMAL(13),
   user_field3          DECIMAL(13),
   acc_lmt              DECIMAL(13),
   product_cd           VARCHAR(6),
   user_field4          DECIMAL(13),
   user_field5          DECIMAL(13),
   user_field6          DECIMAL(13),
   user_field7          DECIMAL(13),
   user_field8          DECIMAL(13),
   user_field9          DECIMAL(13),
   user_field10         DECIMAL(13),
   user_field11         DECIMAL(13),
   user_field12         CHAR(1),
   user_field13         CHAR(3),
   user_field14         CHAR(1),
   user_field15         VARCHAR(20),
   user_field16         CHAR(3),
   user_field17         INTEGER,
   user_field18         DECIMAL(5,2),
   user_field19         VARCHAR(20),
   user_field20         VARCHAR(400),
   user_field21         VARCHAR(1000),
   user_field22         INTEGER,
   user_field23         CHAR(1),
   user_field24         VARCHAR(20),
   user_field25         VARCHAR(20),
   user_field26         VARCHAR(9),
   user_field27         VARCHAR(20),
   user_field28         CHAR(1),
   user_field29         VARCHAR(80),
   user_field30         VARCHAR(20),
   user_field31         VARCHAR(20),
   user_field32         CHAR(1),
   user_field33         VARCHAR(9),
   user_field34         VARCHAR(15),
   user_field35         VARCHAR(20),
   user_field36         VARCHAR(32),
   user_field37         CHAR(1),
   user_field38         VARCHAR(40),
   user_field39         CHAR(1),
   user_field40         CHAR(1),
   user_field41         CHAR(1),
   user_field42         VARCHAR(20),
   user_field43         VARCHAR(20),
   user_field44         VARCHAR(400),
   user_field45         VARCHAR(40),
   user_field46         VARCHAR(40),
   user_field47         VARCHAR(32),
   user_field48         VARCHAR(32),
   user_field49         VARCHAR(32),
   user_field50         VARCHAR(10),
   user_field51         VARCHAR(14),
   last_modified_datetime VARCHAR(14),
   jpa_Vversion         INTEGER,
   uesr_field52         CHAR(1),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_APP_MAIN primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_APP_MAIN is
'申请主表';

comment on column ICPS_WB_TM_APP_MAIN.busi_date is
'业务日期';

comment on column ICPS_WB_TM_APP_MAIN.file_order is
'文件序号';

comment on column ICPS_WB_TM_APP_MAIN.org is
'机构号';

comment on column ICPS_WB_TM_APP_MAIN.app_no is
'申请件编号';

comment on column ICPS_WB_TM_APP_MAIN.user_field1 is
'备用字段';

comment on column ICPS_WB_TM_APP_MAIN.user_field2 is
'备用字段2';

comment on column ICPS_WB_TM_APP_MAIN.user_field3 is
'备用字段3';

comment on column ICPS_WB_TM_APP_MAIN.acc_lmt is
'核准额度';

comment on column ICPS_WB_TM_APP_MAIN.product_cd is
'卡产品代码';

comment on column ICPS_WB_TM_APP_MAIN.user_field4 is
'备用字段4';

comment on column ICPS_WB_TM_APP_MAIN.user_field5 is
'备用字段5';

comment on column ICPS_WB_TM_APP_MAIN.user_field6 is
'备用字段6';

comment on column ICPS_WB_TM_APP_MAIN.user_field7 is
'备用字段7';

comment on column ICPS_WB_TM_APP_MAIN.user_field8 is
'备用字段8';

comment on column ICPS_WB_TM_APP_MAIN.user_field9 is
'备用字段9';

comment on column ICPS_WB_TM_APP_MAIN.user_field10 is
'备用字段10';

comment on column ICPS_WB_TM_APP_MAIN.user_field11 is
'备用字段11';

comment on column ICPS_WB_TM_APP_MAIN.user_field12 is
'备用字段12';

comment on column ICPS_WB_TM_APP_MAIN.user_field13 is
'备用字段13';

comment on column ICPS_WB_TM_APP_MAIN.user_field14 is
'备用字段14';

comment on column ICPS_WB_TM_APP_MAIN.user_field15 is
'备用字段15';

comment on column ICPS_WB_TM_APP_MAIN.user_field16 is
'备用字段16';

comment on column ICPS_WB_TM_APP_MAIN.user_field17 is
'备用字段17';

comment on column ICPS_WB_TM_APP_MAIN.user_field18 is
'备用字段18';

comment on column ICPS_WB_TM_APP_MAIN.user_field19 is
'备用字段19';

comment on column ICPS_WB_TM_APP_MAIN.user_field20 is
'备用字段20';

comment on column ICPS_WB_TM_APP_MAIN.user_field21 is
'备用字段21';

comment on column ICPS_WB_TM_APP_MAIN.user_field22 is
'备用字段22';

comment on column ICPS_WB_TM_APP_MAIN.user_field23 is
'备用字段23';

comment on column ICPS_WB_TM_APP_MAIN.user_field24 is
'备用字段24';

comment on column ICPS_WB_TM_APP_MAIN.user_field25 is
'备用字段25';

comment on column ICPS_WB_TM_APP_MAIN.user_field26 is
'备用字段26';

comment on column ICPS_WB_TM_APP_MAIN.user_field27 is
'备用字段27';

comment on column ICPS_WB_TM_APP_MAIN.user_field28 is
'备用字段28';

comment on column ICPS_WB_TM_APP_MAIN.user_field29 is
'备用字段29';

comment on column ICPS_WB_TM_APP_MAIN.user_field30 is
'备用字段30';

comment on column ICPS_WB_TM_APP_MAIN.user_field31 is
'备用字段31';

comment on column ICPS_WB_TM_APP_MAIN.user_field32 is
'备用字段32';

comment on column ICPS_WB_TM_APP_MAIN.user_field33 is
'备用字段33';

comment on column ICPS_WB_TM_APP_MAIN.user_field34 is
'备用字段34';

comment on column ICPS_WB_TM_APP_MAIN.user_field35 is
'备用字段35';

comment on column ICPS_WB_TM_APP_MAIN.user_field36 is
'备用字段36';

comment on column ICPS_WB_TM_APP_MAIN.user_field37 is
'备用字段37';

comment on column ICPS_WB_TM_APP_MAIN.user_field38 is
'备用字段38';

comment on column ICPS_WB_TM_APP_MAIN.user_field39 is
'备用字段39';

comment on column ICPS_WB_TM_APP_MAIN.user_field40 is
'备用字段40';

comment on column ICPS_WB_TM_APP_MAIN.user_field41 is
'备用字段41';

comment on column ICPS_WB_TM_APP_MAIN.user_field42 is
'备用字段42';

comment on column ICPS_WB_TM_APP_MAIN.user_field43 is
'备用字段43';

comment on column ICPS_WB_TM_APP_MAIN.user_field44 is
'备用字段44';

comment on column ICPS_WB_TM_APP_MAIN.user_field45 is
'备用字段45';

comment on column ICPS_WB_TM_APP_MAIN.user_field46 is
'备用字段46';

comment on column ICPS_WB_TM_APP_MAIN.user_field47 is
'备用字段47';

comment on column ICPS_WB_TM_APP_MAIN.user_field48 is
'备用字段48';

comment on column ICPS_WB_TM_APP_MAIN.user_field49 is
'备用字段49';

comment on column ICPS_WB_TM_APP_MAIN.user_field50 is
'备用字段50';

comment on column ICPS_WB_TM_APP_MAIN.user_field51 is
'备用字段51';

comment on column ICPS_WB_TM_APP_MAIN.last_modified_datetime is
'最后修改时间';

comment on column ICPS_WB_TM_APP_MAIN.jpa_Vversion is
'乐观锁';

comment on column ICPS_WB_TM_APP_MAIN.uesr_field52 is
'备用字段52';

comment on column ICPS_WB_TM_APP_MAIN.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_APP_MAIN.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_APP_MAIN.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_APP_MAIN.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_APP_INFO                                   */
/*==============================================================*/
create table ICPS_WB_TM_APP_INFO 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   id                   VARCHAR(20),
   org                  CHAR(12),
   app_no               VARCHAR(20),
   user_field53         CHAR(1),
   user_field54         VARCHAR(19),
   name                 VARCHAR(80),
   emb_logo             VARCHAR(30),
   gender               VARCHAR(2),
   nationality          VARCHAR(3),
   residency_country_cd CHAR(3),
   id_type              CHAR(1),
   id_no                VARCHAR(30),
   user_field55         VARCHAR(14),
   user_field56         VARCHAR(200),
   birthday             VARCHAR(14),
   user_field57         CHAR(1),
   user_field58         DECIMAL(15,2),
   user_field59         CHAR(1),
   user_field60         CHAR(1),
   user_field61         VARCHAR(3),
   user_field62         VARCHAR(40),
   user_field63         VARCHAR(40),
   user_field64         VARCHAR(40),
   user_field65         CHAR(1),
   user_field66         VARCHAR(200),
   user_field67         VARCHAR(10),
   user_field68         VARCHAR(20),
   user_field69         VARCHAR(14),
   cellphone            VARCHAR(20),
   user_field70         VARCHAR(80),
   user_field71         VARCHAR(40),
   user_field72         VARCHAR(40),
   user_field73         CHAR(1),
   user_field74         VARCHAR(2),
   user_field75         DECIMAL(15,2),
   user_field76         CHAR(1),
   user_field77         VARCHAR(20),
   user_field78         VARCHAR(200),
   user_field79         VARCHAR(3),
   user_field80         VARCHAR(40),
   user_field81         VARCHAR(40),
   user_field82         VARCHAR(40),
   user_field83         VARCHAR(200),
   user_field84         VARCHAR(10),
   user_field85         VARCHAR(20),
   user_field86         VARCHAR(80),
   user_field87         CHAR(1),
   user_field88         CHAR(1),
   user_field89         CHAR(1),
   user_field90         DECIMAL(2),
   user_field91         VARCHAR(20),
   user_field92         CHAR(1),
   user_field93         CHAR(1),
   user_field94         VARCHAR(14),
   user_field95         CHAR(1),
   user_field96         CHAR(1),
   user_field97         VARCHAR(10),
   user_field98         CHAR(1),
   user_field99         CHAR(1),
   pr_of_country        CHAR(1),
   user_field100        VARCHAR(80),
   user_field101        VARCHAR(80),
   user_field102        VARCHAR(80),
   user_field103        VARCHAR(19),
   user_field104        VARCHAR(20),
   user_field105        VARCHAR(32),
   user_field106        VARCHAR(40),
   user_field107        CHAR(1),
   user_field108        VARCHAR(2),
   user_field109        VARCHAR(40),
   user_field110        VARCHAR(40),
   user_field111        VARCHAR(14),
   user_field112        VARCHAR(14),
   jpa_version          INTEGER,
   cust_no              VARCHAR(20),
   acct_no              VARCHAR(20),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_APP_INFO primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_APP_INFO is
'主卡申请人信息表';

comment on column ICPS_WB_TM_APP_INFO.busi_date is
'业务日期';

comment on column ICPS_WB_TM_APP_INFO.file_order is
'文件序号';

comment on column ICPS_WB_TM_APP_INFO.id is
'标识';

comment on column ICPS_WB_TM_APP_INFO.org is
'机构号';

comment on column ICPS_WB_TM_APP_INFO.app_no is
'申请件编号';

comment on column ICPS_WB_TM_APP_INFO.user_field53 is
'备用字段53';

comment on column ICPS_WB_TM_APP_INFO.user_field54 is
'备用字段54';

comment on column ICPS_WB_TM_APP_INFO.name is
'姓名';

comment on column ICPS_WB_TM_APP_INFO.emb_logo is
'凸印名称';

comment on column ICPS_WB_TM_APP_INFO.gender is
'性别';

comment on column ICPS_WB_TM_APP_INFO.nationality is
'国籍';

comment on column ICPS_WB_TM_APP_INFO.residency_country_cd is
'永久居住地国家代码';

comment on column ICPS_WB_TM_APP_INFO.id_type is
'证件类型';

comment on column ICPS_WB_TM_APP_INFO.id_no is
'证件号码';

comment on column ICPS_WB_TM_APP_INFO.user_field55 is
'备用字段55';

comment on column ICPS_WB_TM_APP_INFO.user_field56 is
'备用字段56';

comment on column ICPS_WB_TM_APP_INFO.birthday is
'生日';

comment on column ICPS_WB_TM_APP_INFO.user_field57 is
'备用字段57';

comment on column ICPS_WB_TM_APP_INFO.user_field58 is
'备用字段58';

comment on column ICPS_WB_TM_APP_INFO.user_field59 is
'备用字段59';

comment on column ICPS_WB_TM_APP_INFO.user_field60 is
'备用字段60';

comment on column ICPS_WB_TM_APP_INFO.user_field61 is
'备用字段61';

comment on column ICPS_WB_TM_APP_INFO.user_field62 is
'备用字段62';

comment on column ICPS_WB_TM_APP_INFO.user_field63 is
'备用字段63';

comment on column ICPS_WB_TM_APP_INFO.user_field64 is
'备用字段64';

comment on column ICPS_WB_TM_APP_INFO.user_field65 is
'备用字段65';

comment on column ICPS_WB_TM_APP_INFO.user_field66 is
'备用字段66';

comment on column ICPS_WB_TM_APP_INFO.user_field67 is
'备用字段67';

comment on column ICPS_WB_TM_APP_INFO.user_field68 is
'备用字段68';

comment on column ICPS_WB_TM_APP_INFO.user_field69 is
'备用字段69';

comment on column ICPS_WB_TM_APP_INFO.cellphone is
'移动电话';

comment on column ICPS_WB_TM_APP_INFO.user_field70 is
'备用字段70';

comment on column ICPS_WB_TM_APP_INFO.user_field71 is
'备用字段71';

comment on column ICPS_WB_TM_APP_INFO.user_field72 is
'备用字段72';

comment on column ICPS_WB_TM_APP_INFO.user_field73 is
'备用字段73';

comment on column ICPS_WB_TM_APP_INFO.user_field74 is
'备用字段74';

comment on column ICPS_WB_TM_APP_INFO.user_field75 is
'备用字段75';

comment on column ICPS_WB_TM_APP_INFO.user_field76 is
'备用字段76';

comment on column ICPS_WB_TM_APP_INFO.user_field77 is
'备用字段77';

comment on column ICPS_WB_TM_APP_INFO.user_field78 is
'备用字段78';

comment on column ICPS_WB_TM_APP_INFO.user_field79 is
'备用字段79';

comment on column ICPS_WB_TM_APP_INFO.user_field80 is
'备用字段80';

comment on column ICPS_WB_TM_APP_INFO.user_field81 is
'备用字段81';

comment on column ICPS_WB_TM_APP_INFO.user_field82 is
'备用字段82';

comment on column ICPS_WB_TM_APP_INFO.user_field83 is
'备用字段83';

comment on column ICPS_WB_TM_APP_INFO.user_field84 is
'备用字段84';

comment on column ICPS_WB_TM_APP_INFO.user_field85 is
'备用字段85';

comment on column ICPS_WB_TM_APP_INFO.user_field86 is
'备用字段86';

comment on column ICPS_WB_TM_APP_INFO.user_field87 is
'备用字段87';

comment on column ICPS_WB_TM_APP_INFO.user_field88 is
'备用字段88';

comment on column ICPS_WB_TM_APP_INFO.user_field89 is
'备用字段89';

comment on column ICPS_WB_TM_APP_INFO.user_field90 is
'备用字段90';

comment on column ICPS_WB_TM_APP_INFO.user_field91 is
'备用字段91';

comment on column ICPS_WB_TM_APP_INFO.user_field92 is
'备用字段92';

comment on column ICPS_WB_TM_APP_INFO.user_field93 is
'备用字段93';

comment on column ICPS_WB_TM_APP_INFO.user_field94 is
'备用字段94';

comment on column ICPS_WB_TM_APP_INFO.user_field95 is
'备用字段95';

comment on column ICPS_WB_TM_APP_INFO.user_field96 is
'备用字段96';

comment on column ICPS_WB_TM_APP_INFO.user_field97 is
'备用字段97';

comment on column ICPS_WB_TM_APP_INFO.user_field98 is
'备用字段98';

comment on column ICPS_WB_TM_APP_INFO.user_field99 is
'备用字段99';

comment on column ICPS_WB_TM_APP_INFO.pr_of_country is
'是否永久居住';

comment on column ICPS_WB_TM_APP_INFO.user_field100 is
'备用字段100';

comment on column ICPS_WB_TM_APP_INFO.user_field101 is
'备用字段101';

comment on column ICPS_WB_TM_APP_INFO.user_field102 is
'备用字段102';

comment on column ICPS_WB_TM_APP_INFO.user_field103 is
'备用字段103';

comment on column ICPS_WB_TM_APP_INFO.user_field104 is
'备用字段104';

comment on column ICPS_WB_TM_APP_INFO.user_field105 is
'备用字段105';

comment on column ICPS_WB_TM_APP_INFO.user_field106 is
'备用字段106';

comment on column ICPS_WB_TM_APP_INFO.user_field107 is
'备用字段107';

comment on column ICPS_WB_TM_APP_INFO.user_field108 is
'备用字段108';

comment on column ICPS_WB_TM_APP_INFO.user_field109 is
'备用字段109';

comment on column ICPS_WB_TM_APP_INFO.user_field110 is
'备用字段110';

comment on column ICPS_WB_TM_APP_INFO.user_field111 is
'备用字段111';

comment on column ICPS_WB_TM_APP_INFO.user_field112 is
'备用字段112';

comment on column ICPS_WB_TM_APP_INFO.jpa_version is
'乐观锁';

comment on column ICPS_WB_TM_APP_INFO.cust_no is
'客户号';

comment on column ICPS_WB_TM_APP_INFO.acct_no is
'账户号';

comment on column ICPS_WB_TM_APP_INFO.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_APP_INFO.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_APP_INFO.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_APP_INFO.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_CUSTOMER                                   */
/*==============================================================*/
create table ICPS_WB_TM_CUSTOMER 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   cust_id              VARCHAR(20),
   id_num               VARCHAR(30),
   id_type              CHAR(1),
   title                CHAR(1),
   name                 VARCHAR(80),
   gender               CHAR(1),
   brith_date           VARCHAR(8) ,
   user_field177        CHAR(1),
   user_field178        VARCHAR(20),
   nationality          CHAR(3),
   pr_of_country        CHAR(1),
   residency_country_cd CHAR(3),
   user_field179        CHAR(1),
   user_field180        CHAR(1),
   user_field181        CHAR(1),
   user_field182        VARCHAR(200),
   user_field183        VARCHAR(20),
   user_field184        CHAR(1),
   user_field185        CHAR(1),
   user_field186        VARCHAR(14),
   user_field187        CHAR(1),
   mobile_no            VARCHAR(20),
   user_field188        VARCHAR(80),
   user_field189        CHAR(1),
   user_field190        INTEGER,
   language_ind         VARCHAR(4),
   user_field191        VARCHAR(14),
   user_field192        DECIMAL(15,2),
   user_field193        VARCHAR(20),
   user_field194        VARCHAR(14),
   user_field195        VARCHAR(80),
   user_field196        VARCHAR(80),
   user_field197        CHAR(1),
   user_field198        VARCHAR(200),
   user_field199        VARCHAR(4),
   user_field200        VARCHAR(4),
   user_field201        VARCHAR(4),
   user_field202        VARCHAR(4),
   user_field203        VARCHAR(4),
   user_field204        VARCHAR(4),
   user_field205        VARCHAR(14),
   user_field206        VARCHAR(14),
   user_field207        VARCHAR(14),
   user_field208        VARCHAR(14),
   user_field209        VARCHAR(14),
   user_field210        VARCHAR(14),
   user_field211        INTEGER,
   user_field212        INTEGER,
   user_field213        INTEGER,
   user_field214        INTEGER,
   user_field215        INTEGER,
   user_field216        INTEGER,
   user_field217        VARCHAR(40),
   user_field218        VARCHAR(40),
   user_field219        VARCHAR(40),
   user_field220        VARCHAR(40),
   user_field221        VARCHAR(40),
   user_field222        VARCHAR(40),
   user_field223        DECIMAL(15,2),
   user_field224        DECIMAL(15,2),
   user_field225        DECIMAL(15,2),
   user_field226        DECIMAL(15,2),
   user_field227        DECIMAL(15,2),
   user_field228        DECIMAL(15,2),
   user_field229        VARCHAR(20),
   emb_name             VARCHAR(26),
   jpa_version          INTEGER,
   cust_limit_id        VARCHAR(20),
   last_modified_datetime VARCHAR(14),
   user_field230        VARCHAR(10),
   user_field231        VARCHAR(2),
   surname              VARCHAR(20),
   user_field232        VARCHAR(14),
   user_field233        VARCHAR(3),
   user_field234        CHAR(53),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_CUSTOMER primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_CUSTOMER is
'客户信息表';

comment on column ICPS_WB_TM_CUSTOMER.busi_date is
'业务日期';

comment on column ICPS_WB_TM_CUSTOMER.file_order is
'文件序号';

comment on column ICPS_WB_TM_CUSTOMER.org is
'机构号';

comment on column ICPS_WB_TM_CUSTOMER.cust_id is
'客户编号';

comment on column ICPS_WB_TM_CUSTOMER.id_num is
'证件号码';

comment on column ICPS_WB_TM_CUSTOMER.id_type is
'证件类型';

comment on column ICPS_WB_TM_CUSTOMER.title is
'称谓';

comment on column ICPS_WB_TM_CUSTOMER.name is
'姓名';

comment on column ICPS_WB_TM_CUSTOMER.gender is
'性别';

comment on column ICPS_WB_TM_CUSTOMER.brith_date is
'生日';

comment on column ICPS_WB_TM_CUSTOMER.user_field177 is
'备用字段177';

comment on column ICPS_WB_TM_CUSTOMER.user_field178 is
'备用字段178';

comment on column ICPS_WB_TM_CUSTOMER.nationality is
'国籍';

comment on column ICPS_WB_TM_CUSTOMER.pr_of_country is
'是否永久居住';

comment on column ICPS_WB_TM_CUSTOMER.residency_country_cd is
'永久居住地国家代码';

comment on column ICPS_WB_TM_CUSTOMER.user_field179 is
'备用字段179';

comment on column ICPS_WB_TM_CUSTOMER.user_field180 is
'备用字段180';

comment on column ICPS_WB_TM_CUSTOMER.user_field181 is
'备用字段181';

comment on column ICPS_WB_TM_CUSTOMER.user_field182 is
'备用字段182';

comment on column ICPS_WB_TM_CUSTOMER.user_field183 is
'备用字段183';

comment on column ICPS_WB_TM_CUSTOMER.user_field184 is
'备用字段184';

comment on column ICPS_WB_TM_CUSTOMER.user_field185 is
'备用字段185';

comment on column ICPS_WB_TM_CUSTOMER.user_field186 is
'备用字段186';

comment on column ICPS_WB_TM_CUSTOMER.user_field187 is
'备用字段187';

comment on column ICPS_WB_TM_CUSTOMER.mobile_no is
'移动电话';

comment on column ICPS_WB_TM_CUSTOMER.user_field188 is
'备用字段188';

comment on column ICPS_WB_TM_CUSTOMER.user_field189 is
'备用字段189';

comment on column ICPS_WB_TM_CUSTOMER.user_field190 is
'备用字段190';

comment on column ICPS_WB_TM_CUSTOMER.language_ind is
'语言代码';

comment on column ICPS_WB_TM_CUSTOMER.user_field191 is
'备用字段191';

comment on column ICPS_WB_TM_CUSTOMER.user_field192 is
'备用字段192';

comment on column ICPS_WB_TM_CUSTOMER.user_field193 is
'备用字段193';

comment on column ICPS_WB_TM_CUSTOMER.user_field194 is
'备用字段194';

comment on column ICPS_WB_TM_CUSTOMER.user_field195 is
'备用字段195';

comment on column ICPS_WB_TM_CUSTOMER.user_field196 is
'备用字段196';

comment on column ICPS_WB_TM_CUSTOMER.user_field197 is
'备用字段197';

comment on column ICPS_WB_TM_CUSTOMER.user_field198 is
'备用字段198';

comment on column ICPS_WB_TM_CUSTOMER.user_field199 is
'备用字段199';

comment on column ICPS_WB_TM_CUSTOMER.user_field200 is
'备用字段200';

comment on column ICPS_WB_TM_CUSTOMER.user_field201 is
'备用字段201';

comment on column ICPS_WB_TM_CUSTOMER.user_field202 is
'备用字段202';

comment on column ICPS_WB_TM_CUSTOMER.user_field203 is
'备用字段203';

comment on column ICPS_WB_TM_CUSTOMER.user_field204 is
'备用字段204';

comment on column ICPS_WB_TM_CUSTOMER.user_field205 is
'备用字段205';

comment on column ICPS_WB_TM_CUSTOMER.user_field206 is
'备用字段206';

comment on column ICPS_WB_TM_CUSTOMER.user_field207 is
'备用字段207';

comment on column ICPS_WB_TM_CUSTOMER.user_field208 is
'备用字段208';

comment on column ICPS_WB_TM_CUSTOMER.user_field209 is
'备用字段209';

comment on column ICPS_WB_TM_CUSTOMER.user_field210 is
'备用字段210';

comment on column ICPS_WB_TM_CUSTOMER.user_field211 is
'备用字段211';

comment on column ICPS_WB_TM_CUSTOMER.user_field212 is
'备用字段212';

comment on column ICPS_WB_TM_CUSTOMER.user_field213 is
'备用字段213';

comment on column ICPS_WB_TM_CUSTOMER.user_field214 is
'备用字段214';

comment on column ICPS_WB_TM_CUSTOMER.user_field215 is
'备用字段215';

comment on column ICPS_WB_TM_CUSTOMER.user_field216 is
'备用字段216';

comment on column ICPS_WB_TM_CUSTOMER.user_field217 is
'备用字段217';

comment on column ICPS_WB_TM_CUSTOMER.user_field218 is
'备用字段218';

comment on column ICPS_WB_TM_CUSTOMER.user_field219 is
'备用字段219';

comment on column ICPS_WB_TM_CUSTOMER.user_field220 is
'备用字段220';

comment on column ICPS_WB_TM_CUSTOMER.user_field221 is
'备用字段221';

comment on column ICPS_WB_TM_CUSTOMER.user_field222 is
'备用字段222';

comment on column ICPS_WB_TM_CUSTOMER.user_field223 is
'备用字段223';

comment on column ICPS_WB_TM_CUSTOMER.user_field224 is
'备用字段224';

comment on column ICPS_WB_TM_CUSTOMER.user_field225 is
'备用字段225';

comment on column ICPS_WB_TM_CUSTOMER.user_field226 is
'备用字段226';

comment on column ICPS_WB_TM_CUSTOMER.user_field227 is
'备用字段227';

comment on column ICPS_WB_TM_CUSTOMER.user_field228 is
'备用字段228';

comment on column ICPS_WB_TM_CUSTOMER.user_field229 is
'备用字段229';

comment on column ICPS_WB_TM_CUSTOMER.emb_name is
'拼音名';

comment on column ICPS_WB_TM_CUSTOMER.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_CUSTOMER.cust_limit_id is
'客户额度ID';

comment on column ICPS_WB_TM_CUSTOMER.last_modified_datetime is
'修改时间';

comment on column ICPS_WB_TM_CUSTOMER.user_field230 is
'备用字段230';

comment on column ICPS_WB_TM_CUSTOMER.user_field231 is
'备用字段231';

comment on column ICPS_WB_TM_CUSTOMER.surname is
'姓氏';

comment on column ICPS_WB_TM_CUSTOMER.user_field232 is
'备用字段232';

comment on column ICPS_WB_TM_CUSTOMER.user_field233 is
'备用字段233';

comment on column ICPS_WB_TM_CUSTOMER.user_field234 is
'备用字段234';

comment on column ICPS_WB_TM_CUSTOMER.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_CUSTOMER.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_CUSTOMER.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_CUSTOMER.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TT_TXN_POST                                   */
/*==============================================================*/
create table ICPS_WB_TT_TXN_POST 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   trans_serial         VARCHAR(20),
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   card_no              VARCHAR(19),
   logical_card_no      VARCHAR(19),
   bsc_logiccard_no     VARCHAR(19),
   product_code         CHAR(6),
   trans_date           VARCHAR(14),
   trans_time           VARCHAR(14),
   post_txn_type        CHAR(1),
   txn_code             CHAR(4),
   loan_flag            CHAR(1),
   trans_amt            DECIMAL(15,2),
   post_amt             DECIMAL(15,2),
   transfer_in_date     VARCHAR(14),
   user_field235        CHAR(6),
   user_field236        VARCHAR(27),
   txn_curr_cd          CHAR(3),
   post_curr_cd         CHAR(3),
   orig_trans_date      VARCHAR(14),
   plan_nbr             CHAR(6),
   ref_nbr              VARCHAR(23),
   txn_desc             VARCHAR(80),
   txn_short_desc       VARCHAR(80),
   user_field237        DECIMAL(13)  ,
   posting_flag         CHAR(3),
   pre_posting_flag     CHAR(3),
   user_field238        DECIMAL(15,2),
   orig_pmt_amt         DECIMAL(15,2),
   user_field239        CHAR(9),
   user_field240        VARCHAR(8) ,
   user_field241        VARCHAR(15),
   user_field242        VARCHAR(15),
   mcc                  CHAR(4),
   input_txn_code       CHAR(4),
   input_txn_amt        DECIMAL(15,2),
   input_sett_amt       DECIMAL(15,2),
   user_field246        DECIMAL(15,2),
   stmt_date            VARCHAR(14),
   user_field247        VARCHAR(7),
   jpa_version          INTEGER,
   term                 INTEGER,
   busi_serial          VARCHAR(32),
   sys_trans_id         VARCHAR(32),
   user_field248        VARCHAR(15),
   sub_terminal_type    VARCHAR(15),
   last_modified_datetime VARCHAR(14),
   paid_stmt_date       VARCHAR(14),
   repay_amt            DECIMAL(15,2),
   bank_proportion      DECIMAL(5,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TT_TXN_POST primary key (busi_date, file_order)
);

comment on table ICPS_WB_TT_TXN_POST is
'当日入账交易表';

comment on column ICPS_WB_TT_TXN_POST.busi_date is
'业务日期';

comment on column ICPS_WB_TT_TXN_POST.file_order is
'文件序号';

comment on column ICPS_WB_TT_TXN_POST.org is
'机构号';

comment on column ICPS_WB_TT_TXN_POST.trans_serial is
'交易流水号';

comment on column ICPS_WB_TT_TXN_POST.acct_no is
'账户编号';

comment on column ICPS_WB_TT_TXN_POST.acct_type is
'账户类型';

comment on column ICPS_WB_TT_TXN_POST.card_no is
'卡号';

comment on column ICPS_WB_TT_TXN_POST.logical_card_no is
'逻辑卡号';

comment on column ICPS_WB_TT_TXN_POST.bsc_logiccard_no is
'逻辑卡主卡卡号';

comment on column ICPS_WB_TT_TXN_POST.product_code is
'产品代码';

comment on column ICPS_WB_TT_TXN_POST.trans_date is
'交易日期';

comment on column ICPS_WB_TT_TXN_POST.trans_time is
'交易时间';

comment on column ICPS_WB_TT_TXN_POST.post_txn_type is
'入账交易类型';

comment on column ICPS_WB_TT_TXN_POST.txn_code is
'交易码';

comment on column ICPS_WB_TT_TXN_POST.loan_flag is
'借贷标志';

comment on column ICPS_WB_TT_TXN_POST.trans_amt is
'交易金额';

comment on column ICPS_WB_TT_TXN_POST.post_amt is
'入账币种金额';

comment on column ICPS_WB_TT_TXN_POST.transfer_in_date is
'入账日期';

comment on column ICPS_WB_TT_TXN_POST.user_field235 is
'备用字段235';

comment on column ICPS_WB_TT_TXN_POST.user_field236 is
'备用字段236';

comment on column ICPS_WB_TT_TXN_POST.txn_curr_cd is
'交易币种代码';

comment on column ICPS_WB_TT_TXN_POST.post_curr_cd is
'入账币种代码';

comment on column ICPS_WB_TT_TXN_POST.orig_trans_date is
'原始交易日期';

comment on column ICPS_WB_TT_TXN_POST.plan_nbr is
'信用计划号';

comment on column ICPS_WB_TT_TXN_POST.ref_nbr is
'交易参考号';

comment on column ICPS_WB_TT_TXN_POST.txn_desc is
'交易描述';

comment on column ICPS_WB_TT_TXN_POST.txn_short_desc is
'账单交易描述';

comment on column ICPS_WB_TT_TXN_POST.user_field237 is
'备用字段237';

comment on column ICPS_WB_TT_TXN_POST.posting_flag is
'入账结果标示码';

comment on column ICPS_WB_TT_TXN_POST.pre_posting_flag is
'往日入账结果标示码';

comment on column ICPS_WB_TT_TXN_POST.user_field238 is
'备用字段238';

comment on column ICPS_WB_TT_TXN_POST.orig_pmt_amt is
'还款交易原始金额';

comment on column ICPS_WB_TT_TXN_POST.user_field239 is
'备用字段239';

comment on column ICPS_WB_TT_TXN_POST.user_field240 is
'备用字段240';

comment on column ICPS_WB_TT_TXN_POST.user_field241 is
'备用字段241';

comment on column ICPS_WB_TT_TXN_POST.user_field242 is
'备用字段242';

comment on column ICPS_WB_TT_TXN_POST.mcc is
'商户类别代码';

comment on column ICPS_WB_TT_TXN_POST.input_txn_code is
'原交易交易码';

comment on column ICPS_WB_TT_TXN_POST.input_txn_amt is
'原交易交易金额';

comment on column ICPS_WB_TT_TXN_POST.input_sett_amt is
'原交易清算金额';

comment on column ICPS_WB_TT_TXN_POST.user_field246 is
'备用字段246';

comment on column ICPS_WB_TT_TXN_POST.stmt_date is
'下一到期还款日';

comment on column ICPS_WB_TT_TXN_POST.user_field247 is
'备用字段247';

comment on column ICPS_WB_TT_TXN_POST.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TT_TXN_POST.term is
'所在贷款期数';

comment on column ICPS_WB_TT_TXN_POST.busi_serial is
'业务流水号';

comment on column ICPS_WB_TT_TXN_POST.sys_trans_id is
'系统调用流水号';

comment on column ICPS_WB_TT_TXN_POST.user_field248 is
'备用字段248';

comment on column ICPS_WB_TT_TXN_POST.sub_terminal_type is
'终端类型';

comment on column ICPS_WB_TT_TXN_POST.last_modified_datetime is
'修改时间';

comment on column ICPS_WB_TT_TXN_POST.paid_stmt_date is
'还款对应出单日（没用）';

comment on column ICPS_WB_TT_TXN_POST.repay_amt is
'应还款额';

comment on column ICPS_WB_TT_TXN_POST.bank_proportion is
'银行出资比例';

comment on column ICPS_WB_TT_TXN_POST.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TT_TXN_POST.extend_param1 is
'扩展1';

comment on column ICPS_WB_TT_TXN_POST.extend_param2 is
'扩展2';

comment on column ICPS_WB_TT_TXN_POST.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_TXN_REJECT                                 */
/*==============================================================*/
create table ICPS_WB_TM_TXN_REJECT 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   trans_serial         VARCHAR(20),
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   card_no              VARCHAR(19),
   logical_card_no      VARCHAR(19),
   bsc_logiccard_no     VARCHAR(19),
   product_code         CHAR(6),
   trans_date           VARCHAR(14),
   trans_time           VARCHAR(14),
   post_txn_type        CHAR(1),
   txn_code             CHAR(4),
   loan_flag            CHAR(1),
   trans_amt            DECIMAL(15,2),
   post_amt             DECIMAL(15,2),
   transfer_in_date     VARCHAR(14),
   user_field252        CHAR(6),
   user_field253        VARCHAR(27),
   txn_curr_cd          CHAR(3),
   post_curr_cd         CHAR(3),
   orig_trans_date      VARCHAR(14),
   plan_nbr             CHAR(6),
   ref_nbr              VARCHAR(23),
   txn_desc             VARCHAR(80),
   txn_short_desc       VARCHAR(80),
   user_field254        DECIMAL(13),
   posting_flag         CHAR(3),
   pre_posting_flag     CHAR(3),
   user_field255        DECIMAL(15,2),
   orig_pmt_amt         DECIMAL(15,2),
   user_field256        CHAR(9),
   user_field257        VARCHAR(8) ,
   user_field258        VARCHAR(15),
   user_field259        VARCHAR(40),
   mcc                  CHAR(4),
   input_txn_code       CHAR(4),
   input_txn_amt        DECIMAL(15,2),
   input_sett_amt       DECIMAL(15,2),
   user_field260        DECIMAL(15,2),
   user_field261        DECIMAL(15,2),
   user_field262        DECIMAL(15,2),
   user_field263        DECIMAL(15,2),
   stmt_date            VARCHAR(14),
   voucher_no           VARCHAR(7),
   jpa_version          INTEGER,
   term                 INTEGER,
   busi_serial          VARCHAR(32),
   sys_trans_id         VARCHAR(32),
   user_field265        VARCHAR(40),
   user_field264        VARCHAR(15),
   sub_terminal_type    VARCHAR(15),
   user_field266        VARCHAR(60),
   user_field267        VARCHAR(60),
   last_modified_datetime VARCHAR(14),
   paid_stmt_date       VARCHAR(14),
   repay_amt            DECIMAL(15,2),
   bank_proportion      DECIMAL(5,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_TXN_REJECT primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_TXN_REJECT is
'挂账交易历史表';

comment on column ICPS_WB_TM_TXN_REJECT.busi_date is
'业务日期';

comment on column ICPS_WB_TM_TXN_REJECT.file_order is
'文件序号';

comment on column ICPS_WB_TM_TXN_REJECT.org is
'机构号';

comment on column ICPS_WB_TM_TXN_REJECT.trans_serial is
'交易流水号';

comment on column ICPS_WB_TM_TXN_REJECT.acct_no is
'账户编号';

comment on column ICPS_WB_TM_TXN_REJECT.acct_type is
'账户类型';

comment on column ICPS_WB_TM_TXN_REJECT.card_no is
'卡号';

comment on column ICPS_WB_TM_TXN_REJECT.logical_card_no is
'逻辑卡号';

comment on column ICPS_WB_TM_TXN_REJECT.bsc_logiccard_no is
'逻辑卡主卡卡号';

comment on column ICPS_WB_TM_TXN_REJECT.product_code is
'产品代码';

comment on column ICPS_WB_TM_TXN_REJECT.trans_date is
'交易日期';

comment on column ICPS_WB_TM_TXN_REJECT.trans_time is
'交易时间';

comment on column ICPS_WB_TM_TXN_REJECT.post_txn_type is
'入账交易类型';

comment on column ICPS_WB_TM_TXN_REJECT.txn_code is
'交易码';

comment on column ICPS_WB_TM_TXN_REJECT.loan_flag is
'借贷标志';

comment on column ICPS_WB_TM_TXN_REJECT.trans_amt is
'交易金额';

comment on column ICPS_WB_TM_TXN_REJECT.post_amt is
'入账币种金额
';

comment on column ICPS_WB_TM_TXN_REJECT.transfer_in_date is
'入账日期';

comment on column ICPS_WB_TM_TXN_REJECT.user_field252 is
'备用字段252';

comment on column ICPS_WB_TM_TXN_REJECT.user_field253 is
'备用字段253';

comment on column ICPS_WB_TM_TXN_REJECT.txn_curr_cd is
'交易币种代码';

comment on column ICPS_WB_TM_TXN_REJECT.post_curr_cd is
'入账币种代码';

comment on column ICPS_WB_TM_TXN_REJECT.orig_trans_date is
'原始交易日期';

comment on column ICPS_WB_TM_TXN_REJECT.plan_nbr is
'信用计划号';

comment on column ICPS_WB_TM_TXN_REJECT.ref_nbr is
'交易参考号';

comment on column ICPS_WB_TM_TXN_REJECT.txn_desc is
'交易描述';

comment on column ICPS_WB_TM_TXN_REJECT.txn_short_desc is
'账单交易描述';

comment on column ICPS_WB_TM_TXN_REJECT.user_field254 is
'备用字段254';

comment on column ICPS_WB_TM_TXN_REJECT.posting_flag is
'入账结果标示码';

comment on column ICPS_WB_TM_TXN_REJECT.pre_posting_flag is
'往日入账结果标示码';

comment on column ICPS_WB_TM_TXN_REJECT.user_field255 is
'备用字段255';

comment on column ICPS_WB_TM_TXN_REJECT.orig_pmt_amt is
'还款交易原始金额';

comment on column ICPS_WB_TM_TXN_REJECT.user_field256 is
'备用字段256';

comment on column ICPS_WB_TM_TXN_REJECT.user_field257 is
'备用字段257';

comment on column ICPS_WB_TM_TXN_REJECT.user_field258 is
'备用字段258';

comment on column ICPS_WB_TM_TXN_REJECT.user_field259 is
'备用字段259';

comment on column ICPS_WB_TM_TXN_REJECT.mcc is
'商户类别代码';

comment on column ICPS_WB_TM_TXN_REJECT.input_txn_code is
'原交易交易码';

comment on column ICPS_WB_TM_TXN_REJECT.input_txn_amt is
'原交易交易金额';

comment on column ICPS_WB_TM_TXN_REJECT.input_sett_amt is
'原交易清算金额';

comment on column ICPS_WB_TM_TXN_REJECT.user_field260 is
'备用字段260';

comment on column ICPS_WB_TM_TXN_REJECT.user_field261 is
'备用字段261';

comment on column ICPS_WB_TM_TXN_REJECT.user_field262 is
'备用字段262';

comment on column ICPS_WB_TM_TXN_REJECT.user_field263 is
'备用字段263';

comment on column ICPS_WB_TM_TXN_REJECT.stmt_date is
'下一到期还款日';

comment on column ICPS_WB_TM_TXN_REJECT.voucher_no is
'销售单凭证号';

comment on column ICPS_WB_TM_TXN_REJECT.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_TXN_REJECT.term is
'所在贷款期数';

comment on column ICPS_WB_TM_TXN_REJECT.busi_serial is
'业务流水号';

comment on column ICPS_WB_TM_TXN_REJECT.sys_trans_id is
'系统调用流水号';

comment on column ICPS_WB_TM_TXN_REJECT.user_field265 is
'备用字段265';

comment on column ICPS_WB_TM_TXN_REJECT.user_field264 is
'备用字段264';

comment on column ICPS_WB_TM_TXN_REJECT.sub_terminal_type is
'终端类型';

comment on column ICPS_WB_TM_TXN_REJECT.user_field266 is
'备用字段266';

comment on column ICPS_WB_TM_TXN_REJECT.user_field267 is
'备用字段267';

comment on column ICPS_WB_TM_TXN_REJECT.last_modified_datetime is
'修改时间';

comment on column ICPS_WB_TM_TXN_REJECT.paid_stmt_date is
'还款所属出单日（无用）';

comment on column ICPS_WB_TM_TXN_REJECT.repay_amt is
'应还款额';

comment on column ICPS_WB_TM_TXN_REJECT.bank_proportion is
'银行出资比例';

comment on column ICPS_WB_TM_TXN_REJECT.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_TXN_REJECT.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_TXN_REJECT.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_TXN_REJECT.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_LOAN                                       */
/*==============================================================*/
create table ICPS_WB_TM_LOAN 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   loan_id              VARCHAR(20),
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   ref_nbr              VARCHAR(23),
   logical_card_no      VARCHAR(19),
   card_no              VARCHAR(19),
   register_date        VARCHAR(14),
   request_time         VARCHAR(14),
   loan_type            VARCHAR(5),
   loan_status          CHAR(1),
   last_loan_status     CHAR(1),
   loan_init_term       INTEGER,
   curr_term            INTEGER,
   remain_term          INTEGER,
   loan_init_prin       DECIMAL(15,2),
   loan_fixed_pmt_prin  DECIMAL(15,2),
   loan_first_term_prin DECIMAL(15,2),
   loan_final_term_prin DECIMAL(15,2),
   loan_init_fee1       DECIMAL(15,2),
   loan_fixed_fee1      DECIMAL(15,2),
   loan_first_term_fee1 DECIMAL(15,2),
   loan_final_term_fee1 DECIMAL(15,2),
   unearned_prin        DECIMAL(15,2),
   unearned_fee1        DECIMAL(15,2),
   paid_out_date        VARCHAR(14),
   terminate_date       VARCHAR(14),
   terminate_reason_cd  CHAR(1),
   prin_paid            DECIMAL(15,2),
   int_paid             DECIMAL(15,2),
   fee_paid             DECIMAL(15,2),
   loan_curr_bal        DECIMAL(15,2),
   loan_bal_xfrout      DECIMAL(15,2),
   loan_bal_xfrin       DECIMAL(15,2),
   loan_bal_principal   DECIMAL(15,2),
   loan_bal_interest    DECIMAL(15,2),
   loan_bal_penalty     DECIMAL(15,2),
   loan_prin_xfrout     DECIMAL(15,2),
   loan_prin_xfrin      DECIMAL(15,2),
   loan_fee1_xfrout     DECIMAL(15,2),
   loan_fee1_xfrin      DECIMAL(15,2),
   orig_txn_amt         DECIMAL(15,2),
   orig_trans_date      VARCHAR(14),
   orig_auth_code       CHAR(6),
   jpa_version          INTEGER,
   loan_code            VARCHAR(4),
   register_id          VARCHAR(20),
   resch_init_prin      DECIMAL(15,2),
   resch_date           VARCHAR(14),
   bef_resch_fixed_pmt_prin DECIMAL(15,2),
   bef_resch_init_term  INTEGER,
   bef_resch_first_term_prin DECIMAL(15,2),
   bef_resch_final_term_prin DECIMAL(15,2),
   bef_resch_init_fee1  DECIMAL(15,2),
   bef_resch_fixed_fee1 DECIMAL(15,2),
   bef_resch_first_term_fee1 DECIMAL(15,2),
   bef_resch_final_term_fee1 DECIMAL(15,2),
   resch_first_term_fee1 DECIMAL(15,2),
   loan_fee_method      CHAR(1),
   interest_rate        DECIMAL(12,4),
   penalty_rate         DECIMAL(12,4),
   compound_rate        DECIMAL(12,4),
   float_rate           DECIMAL(5,2),
   loan_receipt_nbr     VARCHAR(20),
   loan_expire_date     VARCHAR(14),
   loan_cd              VARCHAR(2),
   payment_hist         VARCHAR(24),
   ctd_payment_amt      DECIMAL(15,2),
   past_resch_cnt       INTEGER,
   past_shorted_cnt     INTEGER,
   adv_pmt_amt          DECIMAL(15,2),
   last_action_date     VARCHAR(14),
   last_action_type     CHAR(1),
   last_modified_datetime VARCHAR(14),
   activate_date        VARCHAR(14),
   interest_calc_base   VARCHAR(14),
   first_bill_date      VARCHAR(14),
   age_cd               CHAR(1),
   recalc_ind           CHAR(1),
   recalc_date          VARCHAR(14),
   grace_date           VARCHAR(14),
   cancel_date          VARCHAR(14),
   cancel_reason        VARCHAR(100),
   bank_group_id        VARCHAR(5),
   due_days             INTEGER,
   contract_ver         VARCHAR(200),
   loan_init_interest   DECIMAL(15,2),
   bef_init_interest    DECIMAL(15,2),
   bank_proportion      DECIMAL(5,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_LOAN primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_LOAN is
'分期信息表';

comment on column ICPS_WB_TM_LOAN.busi_date is
'业务日期';

comment on column ICPS_WB_TM_LOAN.file_order is
'文件序号';

comment on column ICPS_WB_TM_LOAN.org is
'机构号';

comment on column ICPS_WB_TM_LOAN.loan_id is
'借据ID';

comment on column ICPS_WB_TM_LOAN.acct_no is
'账户编号';

comment on column ICPS_WB_TM_LOAN.acct_type is
'账户类型';

comment on column ICPS_WB_TM_LOAN.ref_nbr is
'交易参考号';

comment on column ICPS_WB_TM_LOAN.logical_card_no is
'逻辑卡号';

comment on column ICPS_WB_TM_LOAN.card_no is
'卡号';

comment on column ICPS_WB_TM_LOAN.register_date is
'贷款注册日期';

comment on column ICPS_WB_TM_LOAN.request_time is
'请求日期时间';

comment on column ICPS_WB_TM_LOAN.loan_type is
'贷款类型';

comment on column ICPS_WB_TM_LOAN.loan_status is
'贷款状态';

comment on column ICPS_WB_TM_LOAN.last_loan_status is
'贷款上次状态';

comment on column ICPS_WB_TM_LOAN.loan_init_term is
'贷款总期数';

comment on column ICPS_WB_TM_LOAN.curr_term is
'当前期数';

comment on column ICPS_WB_TM_LOAN.remain_term is
'剩余期数';

comment on column ICPS_WB_TM_LOAN.loan_init_prin is
'贷款总本金';

comment on column ICPS_WB_TM_LOAN.loan_fixed_pmt_prin is
'贷款每期应还本金';

comment on column ICPS_WB_TM_LOAN.loan_first_term_prin is
'贷款首期应还本金';

comment on column ICPS_WB_TM_LOAN.loan_final_term_prin is
'贷款末期应还本金';

comment on column ICPS_WB_TM_LOAN.loan_init_fee1 is
'贷款总手续费';

comment on column ICPS_WB_TM_LOAN.loan_fixed_fee1 is
'贷款每期手续费';

comment on column ICPS_WB_TM_LOAN.loan_first_term_fee1 is
'贷款首期手续费';

comment on column ICPS_WB_TM_LOAN.loan_final_term_fee1 is
'贷款末期手续费';

comment on column ICPS_WB_TM_LOAN.unearned_prin is
'贷款账单的本金';

comment on column ICPS_WB_TM_LOAN.unearned_fee1 is
'贷款账单手续费';

comment on column ICPS_WB_TM_LOAN.paid_out_date is
'还清日期';

comment on column ICPS_WB_TM_LOAN.terminate_date is
'提前终止日期';

comment on column ICPS_WB_TM_LOAN.terminate_reason_cd is
'贷款终止原因代码';

comment on column ICPS_WB_TM_LOAN.prin_paid is
'已偿还本金';

comment on column ICPS_WB_TM_LOAN.int_paid is
'已偿还利息';

comment on column ICPS_WB_TM_LOAN.fee_paid is
'已偿还费用';

comment on column ICPS_WB_TM_LOAN.loan_curr_bal is
'贷款当前总余额';

comment on column ICPS_WB_TM_LOAN.loan_bal_xfrout is
'贷款未到期余额';

comment on column ICPS_WB_TM_LOAN.loan_bal_xfrin is
'贷款已到期余额';

comment on column ICPS_WB_TM_LOAN.loan_bal_principal is
'欠款总本金';

comment on column ICPS_WB_TM_LOAN.loan_bal_interest is
'欠款总利息';

comment on column ICPS_WB_TM_LOAN.loan_bal_penalty is
'欠款总罚息';

comment on column ICPS_WB_TM_LOAN.loan_prin_xfrout is
'贷款未到期本金';

comment on column ICPS_WB_TM_LOAN.loan_prin_xfrin is
'贷款已到期本金';

comment on column ICPS_WB_TM_LOAN.loan_fee1_xfrout is
'贷款未到期手续费';

comment on column ICPS_WB_TM_LOAN.loan_fee1_xfrin is
'贷款已到期手续费';

comment on column ICPS_WB_TM_LOAN.orig_txn_amt is
'原始交易币种金额';

comment on column ICPS_WB_TM_LOAN.orig_trans_date is
'原始交易日期';

comment on column ICPS_WB_TM_LOAN.orig_auth_code is
'原始交易授权码';

comment on column ICPS_WB_TM_LOAN.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_LOAN.loan_code is
'贷款产品号';

comment on column ICPS_WB_TM_LOAN.register_id is
'贷款申请顺序号';

comment on column ICPS_WB_TM_LOAN.resch_init_prin is
'展期本金金额';

comment on column ICPS_WB_TM_LOAN.resch_date is
'展期生效日期';

comment on column ICPS_WB_TM_LOAN.bef_resch_fixed_pmt_prin is
'展期前每期应还本金';

comment on column ICPS_WB_TM_LOAN.bef_resch_init_term is
'展期前总期数';

comment on column ICPS_WB_TM_LOAN.bef_resch_first_term_prin is
'展期前贷款首期应还本金';

comment on column ICPS_WB_TM_LOAN.bef_resch_final_term_prin is
'展期前贷款末期应还本金';

comment on column ICPS_WB_TM_LOAN.bef_resch_init_fee1 is
'展期前贷款总手续费';

comment on column ICPS_WB_TM_LOAN.bef_resch_fixed_fee1 is
'BEF_贷款每期手续费';

comment on column ICPS_WB_TM_LOAN.bef_resch_first_term_fee1 is
'展期前贷款首期手续费';

comment on column ICPS_WB_TM_LOAN.bef_resch_final_term_fee1 is
'展期前贷款末期手续费';

comment on column ICPS_WB_TM_LOAN.resch_first_term_fee1 is
'展期后首期手续费';

comment on column ICPS_WB_TM_LOAN.loan_fee_method is
'贷款手续费收取方式';

comment on column ICPS_WB_TM_LOAN.interest_rate is
'基础利率';

comment on column ICPS_WB_TM_LOAN.penalty_rate is
'罚息利率';

comment on column ICPS_WB_TM_LOAN.compound_rate is
'复利利率';

comment on column ICPS_WB_TM_LOAN.float_rate is
'浮动比例';

comment on column ICPS_WB_TM_LOAN.loan_receipt_nbr is
'借据号';

comment on column ICPS_WB_TM_LOAN.loan_expire_date is
'贷款到期日期';

comment on column ICPS_WB_TM_LOAN.loan_cd is
'贷款逾期最大期数';

comment on column ICPS_WB_TM_LOAN.payment_hist is
'24个月还款状态';

comment on column ICPS_WB_TM_LOAN.ctd_payment_amt is
'当期还款额';

comment on column ICPS_WB_TM_LOAN.past_resch_cnt is
'已展期次数';

comment on column ICPS_WB_TM_LOAN.past_shorted_cnt is
'已缩期次数';

comment on column ICPS_WB_TM_LOAN.adv_pmt_amt is
'提前还款金额';

comment on column ICPS_WB_TM_LOAN.last_action_date is
'上次行动日期';

comment on column ICPS_WB_TM_LOAN.last_action_type is
'上次行动类型';

comment on column ICPS_WB_TM_LOAN.last_modified_datetime is
'修改时间';

comment on column ICPS_WB_TM_LOAN.activate_date is
'激活日期';

comment on column ICPS_WB_TM_LOAN.interest_calc_base is
'计息基数';

comment on column ICPS_WB_TM_LOAN.first_bill_date is
'首个到期还款日';

comment on column ICPS_WB_TM_LOAN.age_cd is
'账龄';

comment on column ICPS_WB_TM_LOAN.recalc_ind is
'利率重算标志';

comment on column ICPS_WB_TM_LOAN.recalc_date is
'利率重算日';

comment on column ICPS_WB_TM_LOAN.grace_date is
'宽限日期';

comment on column ICPS_WB_TM_LOAN.cancel_date is
'撤销日期';

comment on column ICPS_WB_TM_LOAN.cancel_reason is
'贷款撤销原因';

comment on column ICPS_WB_TM_LOAN.bank_group_id is
'银团编号';

comment on column ICPS_WB_TM_LOAN.due_days is
'当前逾期天数';

comment on column ICPS_WB_TM_LOAN.contract_ver is
'合同版本号';

comment on column ICPS_WB_TM_LOAN.loan_init_interest is
'贷款总利息';

comment on column ICPS_WB_TM_LOAN.bef_init_interest is
'原贷款总利息';

comment on column ICPS_WB_TM_LOAN.bank_proportion is
'银行出资比例';

comment on column ICPS_WB_TM_LOAN.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_LOAN.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_LOAN.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_LOAN.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_SCHEDULE                                   */
/*==============================================================*/
create table ICPS_WB_TM_SCHEDULE 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   schedule_id          VARCHAR(20),
   loan_id              VARCHAR(20),
   org                  CHAR(12)    ,
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   logical_card_no      VARCHAR(19),
   card_no              VARCHAR(19),
   loan_init_prin       DECIMAL(15,2),
   loan_init_term       INTEGER,
   curr_term            INTEGER,
   loan_term_prin       DECIMAL(15,2),
   loan_term_fee1       DECIMAL(15,2),
   loan_term_interest   DECIMAL(15,2),
   loan_pmt_due_date    VARCHAR(14),
   loan_grace_date      VARCHAR(14),
   last_modified_datetime VARCHAR(14),
   start_date           VARCHAR(14),
   schedule_action      CHAR(1),
   prin_paid            DECIMAL(15,2),
   int_paid             DECIMAL(15,2),
   penalty_paid         DECIMAL(15,2),
   compound_paid        DECIMAL(15,2),
   fee_paid             DECIMAL(15,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_SCHEDULE primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_SCHEDULE is
'贷款分配表';

comment on column ICPS_WB_TM_SCHEDULE.busi_date is
'业务日期';

comment on column ICPS_WB_TM_SCHEDULE.file_order is
'文件序号';

comment on column ICPS_WB_TM_SCHEDULE.schedule_id is
'分配表ID';

comment on column ICPS_WB_TM_SCHEDULE.loan_id is
'贷款计划ID';

comment on column ICPS_WB_TM_SCHEDULE.org is
'机构号';

comment on column ICPS_WB_TM_SCHEDULE.acct_no is
'账户编号';

comment on column ICPS_WB_TM_SCHEDULE.acct_type is
'账户类型';

comment on column ICPS_WB_TM_SCHEDULE.logical_card_no is
'逻辑卡号';

comment on column ICPS_WB_TM_SCHEDULE.card_no is
'卡号';

comment on column ICPS_WB_TM_SCHEDULE.loan_init_prin is
'贷款总本金';

comment on column ICPS_WB_TM_SCHEDULE.loan_init_term is
'贷款总期数';

comment on column ICPS_WB_TM_SCHEDULE.curr_term is
'当前期数';

comment on column ICPS_WB_TM_SCHEDULE.loan_term_prin is
'应还本金';

comment on column ICPS_WB_TM_SCHEDULE.loan_term_fee1 is
'应还费用';

comment on column ICPS_WB_TM_SCHEDULE.loan_term_interest is
'应还利息';

comment on column ICPS_WB_TM_SCHEDULE.loan_pmt_due_date is
'到款到期还款日期';

comment on column ICPS_WB_TM_SCHEDULE.loan_grace_date is
'宽限日';

comment on column ICPS_WB_TM_SCHEDULE.last_modified_datetime is
'修改时间';

comment on column ICPS_WB_TM_SCHEDULE.start_date is
'起息日';

comment on column ICPS_WB_TM_SCHEDULE.schedule_action is
'还款计划操作动作';

comment on column ICPS_WB_TM_SCHEDULE.prin_paid is
'已偿还本金';

comment on column ICPS_WB_TM_SCHEDULE.int_paid is
'已偿还利息';

comment on column ICPS_WB_TM_SCHEDULE.penalty_paid is
'已偿还罚息';

comment on column ICPS_WB_TM_SCHEDULE.compound_paid is
'已偿还复利';

comment on column ICPS_WB_TM_SCHEDULE.fee_paid is
'已偿还费用';

comment on column ICPS_WB_TM_SCHEDULE.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_SCHEDULE.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_SCHEDULE.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_SCHEDULE.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_DS_ACCOUNTING_FLOW                            */
/*==============================================================*/
create table ICPS_WB_DS_ACCOUNTING_FLOW 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   host_trans_serial    VARCHAR(36),
   card_no              VARCHAR(19),
   currency             CHAR(3),
   txn_code             CHAR(4),
   txn_desc             VARCHAR(80),
   db_cr_ind            CHAR(1),
   post_amt             DECIMAL(15,2),
   post_gl_ind          CHAR(1),
   owning_branch        VARCHAR(9),
   subject              VARCHAR(40),
   red_flag             CHAR(1),
   queue                INTEGER,
   product_cd           VARCHAR(10),
   ref_nbr              VARCHAR(25),
   age_group            VARCHAR(5),
   plan_nbr             VARCHAR(10),
   bnp_group            VARCHAR(5),
   bank_group_id        VARCHAR(10),
   bank_no              VARCHAR(15),
   term                 INTEGER,
   batchDate            VARCHAR(14),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_DS_ACCOUNTING_FLOW primary key (busi_date, file_order)
);

comment on table ICPS_WB_DS_ACCOUNTING_FLOW is
'会计分录日报表';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.busi_date is
'业务日期';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.file_order is
'文件序号';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.org is
'内部机构号';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.host_trans_serial is
'核心交易流水';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.card_no is
'卡号';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.currency is
'币种';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.txn_code is
'交易码';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.txn_desc is
'交易描述';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.db_cr_ind is
'借贷标记';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.post_amt is
'入账金额';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.post_gl_ind is
'入账方式';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.owning_branch is
'支行';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.subject is
'科目';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.red_flag is
'红蓝字标识';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.queue is
'排序';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.product_cd is
'产品号';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.ref_nbr is
'借据号';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.age_group is
'账龄组';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.plan_nbr is
'信用计划号';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.bnp_group is
'余额成分组';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.bank_group_id is
'银团代码';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.bank_no is
'银行代码';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.term is
'期数';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.batchDate is
'批量';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.extend_param1 is
'扩展1';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.extend_param2 is
'扩展2';

comment on column ICPS_WB_DS_ACCOUNTING_FLOW.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_CUST_LIMIT_O                               */
/*==============================================================*/
create table ICPS_WB_TM_CUST_LIMIT_O 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   cust_limit_id        VARCHAR(20),
   limit_category       VARCHAR(20),
   limit_type           CHAR(1),
   credit_limit         DECIMAL(13,0),
   jpa_version          INTEGER,
   last_modified_datetime VARCHAR(14),
   created_datetime     VARCHAR(14),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_CUST_LIMIT_O primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_CUST_LIMIT_O is
'自定义额度信息表-授权';

comment on column ICPS_WB_TM_CUST_LIMIT_O.busi_date is
'业务日期';

comment on column ICPS_WB_TM_CUST_LIMIT_O.file_order is
'文件序号';

comment on column ICPS_WB_TM_CUST_LIMIT_O.org is
'机构号';

comment on column ICPS_WB_TM_CUST_LIMIT_O.cust_limit_id is
'客户额度ID';

comment on column ICPS_WB_TM_CUST_LIMIT_O.limit_category is
'额度种类';

comment on column ICPS_WB_TM_CUST_LIMIT_O.limit_type is
'额度类型';

comment on column ICPS_WB_TM_CUST_LIMIT_O.credit_limit is
'信用额度';

comment on column ICPS_WB_TM_CUST_LIMIT_O.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_CUST_LIMIT_O.last_modified_datetime is
'修改时间';

comment on column ICPS_WB_TM_CUST_LIMIT_O.created_datetime is
'创建时间';

comment on column ICPS_WB_TM_CUST_LIMIT_O.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_CUST_LIMIT_O.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_CUST_LIMIT_O.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_CUST_LIMIT_O.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_AUTH_HST                                   */
/*==============================================================*/
create table ICPS_WB_TM_AUTH_HST 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   log_kv               VARCHAR(20),
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   logical_card_no      VARCHAR(19),
   acq_ref_no           INTEGER,
   trans_amt            DECIMAL(15,2),
   txn_curr_cd          CHAR(3),
   user_field269        CHAR(6),
   acq_name_addr        VARCHAR(40),
   chb_txn_amt          DECIMAL(15,2),
   chb_curr_cd          CHAR(3),
   user_field270        VARCHAR(15),
   mcc                  CHAR(4),
   acq_branch_id        CHAR(9),
   fwd_inst_id          VARCHAR(11),
   transmission_timestamp VARCHAR(10),
   settle_date          CHAR(4),
   txn_direction        VARCHAR(20),
   txn_terminal         VARCHAR(40),
   trans_status         CHAR(1),
   trans_type           VARCHAR(20),
   log_ol_time          VARCHAR(14),
   log_biz_date         VARCHAR(14),
   mti                  CHAR(4),
   orig_txn_type        VARCHAR(20),
   orig_fwd_inst_id     VARCHAR(11),
   orig_acq_inst_id     VARCHAR(11),
   orig_mti             VARCHAR(4),
   orig_trans_date      VARCHAR(14),
   orig_trace_no        INTEGER,
   orig_txn_proc        CHAR(6),
   orig_txn_amt         DECIMAL(15,2),
   orig_log_kv          VARCHAR(20),
   orig_txn_val_1       VARCHAR(38),
   orig_txn_val_2       VARCHAR(40),
   orig_chb_txn_amt     DECIMAL(15,2),
   orig_biz_date        VARCHAR(14),
   last_reversal_date   VARCHAR(14),
   void_count           INTEGER,
   manual_auth_flag     CHAR(1),
   opera_id             VARCHAR(40),
   brand                VARCHAR(2),
   product_code         CHAR(6),
   mcc_type             CHAR(2),
   user_field271        CHAR(4),
   user_field272        CHAR(1),
   comp_amt             DECIMAL(15,2),
   final_upd_direction  CHAR(1),
   final_upd_amt        DECIMAL(15,2),
   ic_ind               CHAR(1),
   the_3dsecure_type    CHAR(1),
   vip_status           CHAR(1),
   curr_balance         DECIMAL(15,2),
   cash_amt             DECIMAL(15,2),
   otb                  DECIMAL(15,2),
   cash_otb             DECIMAL(15,2),
   cust_otb             DECIMAL(15,2),
   user_field273        VARCHAR(20),
   user_field274        VARCHAR(20),
   expire_date          VARCHAR(4),
   track_one_result     VARCHAR(20),
   track_two_result     VARCHAR(20),
   track_three_result   VARCHAR(20),
   pwd_type             CHAR(1),
   check_pwd_result     VARCHAR(20),
   pay_pwd_err_num      INTEGER,
   check_cvv_result     VARCHAR(20),
   check_cvv2_result    VARCHAR(20),
   check_icvn_result    VARCHAR(20),
   check_arqc_result    VARCHAR(20),
   check_atc_result     VARCHAR(20),
   check_cvr_result     VARCHAR(20),
   check_tvr_result     VARCHAR(20),
   user_field275        VARCHAR(40),
   unmatch_cr           DECIMAL(15,2),
   unmatch_db           DECIMAL(15,2),
   b002                 VARCHAR(20),
   b003                 VARCHAR(6),
   b007                 VARCHAR(10),
   b011                 CHAR(6),
   b022                 VARCHAR(3),
   b025                 VARCHAR(4),
   b032                 VARCHAR(15),
   b033                 VARCHAR(40),
   b039                 VARCHAR(2),
   b042                 VARCHAR(15),
   user_field277        VARCHAR(103),
   user_field278        VARCHAR(400),
   b090                 VARCHAR(42),
   opera_term_id        VARCHAR(20),
   jpa_version          INTEGER,
   b004                 DECIMAL(13),
   b006                 DECIMAL(13),
   b049                 CHAR(3),
   b051                 CHAR(3),
   b037                 CHAR(23),
   b028                 DECIMAL(13),
   b048                 VARCHAR(999),
   b054                 VARCHAR(60),
   user_field279        VARCHAR(27),
   user_field280        VARCHAR(27),
   user_field281        VARCHAR(27),
   busi_serial          VARCHAR(32),
   sys_trans_id         VARCHAR(32),
   user_field282        VARCHAR(15),
   sub_terminal_type    VARCHAR(15),
   sub_merch_id         VARCHAR(40),
   sub_merch_name       VARCHAR(60),
   wares_desc           VARCHAR(60),
   last_modified_datetime VARCHAR(14),
   part_month           INTEGER,
   paid_stmt_date       VARCHAR(14),
   repay_amt            DECIMAL(15,2),
   bank_proportion      DECIMAL(5,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_AUTH_HST primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_AUTH_HST is
'授权交易历史表';

comment on column ICPS_WB_TM_AUTH_HST.busi_date is
'业务日期';

comment on column ICPS_WB_TM_AUTH_HST.file_order is
'文件序号';

comment on column ICPS_WB_TM_AUTH_HST.org is
'机构号';

comment on column ICPS_WB_TM_AUTH_HST.log_kv is
'LOG的键值';

comment on column ICPS_WB_TM_AUTH_HST.acct_no is
'账户编号';

comment on column ICPS_WB_TM_AUTH_HST.acct_type is
'账户类型';

comment on column ICPS_WB_TM_AUTH_HST.logical_card_no is
'逻辑卡号';

comment on column ICPS_WB_TM_AUTH_HST.acq_ref_no is
'受理机构交易编码';

comment on column ICPS_WB_TM_AUTH_HST.trans_amt is
'交易金额';

comment on column ICPS_WB_TM_AUTH_HST.txn_curr_cd is
'交易币种代码';

comment on column ICPS_WB_TM_AUTH_HST.user_field269 is
'备用字段269';

comment on column ICPS_WB_TM_AUTH_HST.acq_name_addr is
'受理机构名称地址';

comment on column ICPS_WB_TM_AUTH_HST.chb_txn_amt is
'持卡人账户币种金额';

comment on column ICPS_WB_TM_AUTH_HST.chb_curr_cd is
'持卡人账户币种';

comment on column ICPS_WB_TM_AUTH_HST.user_field270 is
'备用字段270';

comment on column ICPS_WB_TM_AUTH_HST.mcc is
'商户类别代码';

comment on column ICPS_WB_TM_AUTH_HST.acq_branch_id is
'受理分行代码';

comment on column ICPS_WB_TM_AUTH_HST.fwd_inst_id is
'转发机构号';

comment on column ICPS_WB_TM_AUTH_HST.transmission_timestamp is
'传送日期';

comment on column ICPS_WB_TM_AUTH_HST.settle_date is
'清算日期';

comment on column ICPS_WB_TM_AUTH_HST.txn_direction is
'交易方向';

comment on column ICPS_WB_TM_AUTH_HST.txn_terminal is
'交易终端';

comment on column ICPS_WB_TM_AUTH_HST.trans_status is
'交易状态';

comment on column ICPS_WB_TM_AUTH_HST.trans_type is
'交易类型';

comment on column ICPS_WB_TM_AUTH_HST.log_ol_time is
'LOG联机时间';

comment on column ICPS_WB_TM_AUTH_HST.log_biz_date is
'联机业务日期';

comment on column ICPS_WB_TM_AUTH_HST.mti is
'交易类型标识';

comment on column ICPS_WB_TM_AUTH_HST.orig_txn_type is
'原交易类型';

comment on column ICPS_WB_TM_AUTH_HST.orig_fwd_inst_id is
'原始转发机构号';

comment on column ICPS_WB_TM_AUTH_HST.orig_acq_inst_id is
'原始受理机构号';

comment on column ICPS_WB_TM_AUTH_HST.orig_mti is
'原交易MTI';

comment on column ICPS_WB_TM_AUTH_HST.orig_trans_date is
'原始交易日期';

comment on column ICPS_WB_TM_AUTH_HST.orig_trace_no is
'原始系统跟踪号';

comment on column ICPS_WB_TM_AUTH_HST.orig_txn_proc is
'原交易处理码';

comment on column ICPS_WB_TM_AUTH_HST.orig_txn_amt is
'原始交易币种金额';

comment on column ICPS_WB_TM_AUTH_HST.orig_log_kv is
'原交易LOG键值';

comment on column ICPS_WB_TM_AUTH_HST.orig_txn_val_1 is
'原交易键值1';

comment on column ICPS_WB_TM_AUTH_HST.orig_txn_val_2 is
'原交易键值2';

comment on column ICPS_WB_TM_AUTH_HST.orig_chb_txn_amt is
'原始入账币种金额';

comment on column ICPS_WB_TM_AUTH_HST.orig_biz_date is
'原交易的联机业务处理日期';

comment on column ICPS_WB_TM_AUTH_HST.last_reversal_date is
'最后一次冲撤时间';

comment on column ICPS_WB_TM_AUTH_HST.void_count is
'撤销次数';

comment on column ICPS_WB_TM_AUTH_HST.manual_auth_flag is
'人工授权标志';

comment on column ICPS_WB_TM_AUTH_HST.opera_id is
'操作员ID';

comment on column ICPS_WB_TM_AUTH_HST.brand is
'品牌';

comment on column ICPS_WB_TM_AUTH_HST.product_code is
'产品代码';

comment on column ICPS_WB_TM_AUTH_HST.mcc_type is
'商户类型分组';

comment on column ICPS_WB_TM_AUTH_HST.user_field271 is
'备用字段271';

comment on column ICPS_WB_TM_AUTH_HST.user_field272 is
'备用字段272';

comment on column ICPS_WB_TM_AUTH_HST.comp_amt is
'最终授权金额';

comment on column ICPS_WB_TM_AUTH_HST.final_upd_direction is
'最终更新方向';

comment on column ICPS_WB_TM_AUTH_HST.final_upd_amt is
'最终更新金额';

comment on column ICPS_WB_TM_AUTH_HST.ic_ind is
'是否IC卡';

comment on column ICPS_WB_TM_AUTH_HST.the_3dsecure_type is
'是否3D电子安全交易';

comment on column ICPS_WB_TM_AUTH_HST.vip_status is
'VIP状态';

comment on column ICPS_WB_TM_AUTH_HST.curr_balance is
'当前余额';

comment on column ICPS_WB_TM_AUTH_HST.cash_amt is
'取现金额';

comment on column ICPS_WB_TM_AUTH_HST.otb is
'可用额度';

comment on column ICPS_WB_TM_AUTH_HST.cash_otb is
'取现可用额度';

comment on column ICPS_WB_TM_AUTH_HST.cust_otb is
'客户可用额度';

comment on column ICPS_WB_TM_AUTH_HST.user_field273 is
'备用字段273';

comment on column ICPS_WB_TM_AUTH_HST.user_field274 is
'备用字段274';

comment on column ICPS_WB_TM_AUTH_HST.expire_date is
'有效日期';

comment on column ICPS_WB_TM_AUTH_HST.track_one_result is
'一磁道完整性结果';

comment on column ICPS_WB_TM_AUTH_HST.track_two_result is
'二磁道完整性结果';

comment on column ICPS_WB_TM_AUTH_HST.track_three_result is
'三磁道完整性结果';

comment on column ICPS_WB_TM_AUTH_HST.pwd_type is
'密码种类';

comment on column ICPS_WB_TM_AUTH_HST.check_pwd_result is
'验证密码结果';

comment on column ICPS_WB_TM_AUTH_HST.pay_pwd_err_num is
'支付密码错误次数';

comment on column ICPS_WB_TM_AUTH_HST.check_cvv_result is
'CVV验证结果';

comment on column ICPS_WB_TM_AUTH_HST.check_cvv2_result is
'CVV2验证结果';

comment on column ICPS_WB_TM_AUTH_HST.check_icvn_result is
'ICVN验证结果';

comment on column ICPS_WB_TM_AUTH_HST.check_arqc_result is
'ARQC验证结果';

comment on column ICPS_WB_TM_AUTH_HST.check_atc_result is
'ATC验证结果';

comment on column ICPS_WB_TM_AUTH_HST.check_cvr_result is
'CVR验证结果';

comment on column ICPS_WB_TM_AUTH_HST.check_tvr_result is
'TVR验证结果';

comment on column ICPS_WB_TM_AUTH_HST.user_field275 is
'备用字段275';

comment on column ICPS_WB_TM_AUTH_HST.unmatch_cr is
'未匹配贷记金额';

comment on column ICPS_WB_TM_AUTH_HST.unmatch_db is
'未匹配借记金额';

comment on column ICPS_WB_TM_AUTH_HST.b002 is
'介质卡号-B002';

comment on column ICPS_WB_TM_AUTH_HST.b003 is
'交易处理码-B003';

comment on column ICPS_WB_TM_AUTH_HST.b007 is
'交易传输时间-B007';

comment on column ICPS_WB_TM_AUTH_HST.b011 is
'系统跟踪号-B011';

comment on column ICPS_WB_TM_AUTH_HST.b022 is
'服务点PIN获取码-B022';

comment on column ICPS_WB_TM_AUTH_HST.b025 is
'服务点条件码-B025';

comment on column ICPS_WB_TM_AUTH_HST.b032 is
'受理机构标识码-B032';

comment on column ICPS_WB_TM_AUTH_HST.b033 is
'受理机构名称地址-B033';

comment on column ICPS_WB_TM_AUTH_HST.b039 is
'返回码-B039';

comment on column ICPS_WB_TM_AUTH_HST.b042 is
'受卡方(商户)标识码-B042';

comment on column ICPS_WB_TM_AUTH_HST.user_field277 is
'备用字段276';

comment on column ICPS_WB_TM_AUTH_HST.user_field278 is
'备用字段277';

comment on column ICPS_WB_TM_AUTH_HST.b090 is
'原始数据元';

comment on column ICPS_WB_TM_AUTH_HST.opera_term_id is
'操作用户终端编号';

comment on column ICPS_WB_TM_AUTH_HST.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_AUTH_HST.b004 is
'交易货币金额-B004';

comment on column ICPS_WB_TM_AUTH_HST.b006 is
'账户货币金额-B006';

comment on column ICPS_WB_TM_AUTH_HST.b049 is
'交易货币代码-B049';

comment on column ICPS_WB_TM_AUTH_HST.b051 is
'账户货币代码-B051';

comment on column ICPS_WB_TM_AUTH_HST.b037 is
'检索参考号-B037';

comment on column ICPS_WB_TM_AUTH_HST.b028 is
'手续费-B028';

comment on column ICPS_WB_TM_AUTH_HST.b048 is
'附加数据-B048';

comment on column ICPS_WB_TM_AUTH_HST.b054 is
'返回余额数组-B054';

comment on column ICPS_WB_TM_AUTH_HST.user_field279 is
'备用字段278';

comment on column ICPS_WB_TM_AUTH_HST.user_field280 is
'备用字段279';

comment on column ICPS_WB_TM_AUTH_HST.user_field281 is
'备用字段280';

comment on column ICPS_WB_TM_AUTH_HST.busi_serial is
'业务流水号';

comment on column ICPS_WB_TM_AUTH_HST.sys_trans_id is
'系统调用流水号';

comment on column ICPS_WB_TM_AUTH_HST.user_field282 is
'备用字段281';

comment on column ICPS_WB_TM_AUTH_HST.sub_terminal_type is
'终端类型';

comment on column ICPS_WB_TM_AUTH_HST.sub_merch_id is
'二级商户编码';

comment on column ICPS_WB_TM_AUTH_HST.sub_merch_name is
'二级商户名称';

comment on column ICPS_WB_TM_AUTH_HST.wares_desc is
'商品信息';

comment on column ICPS_WB_TM_AUTH_HST.last_modified_datetime is
'修改时间';

comment on column ICPS_WB_TM_AUTH_HST.part_month is
'分区用的月份';

comment on column ICPS_WB_TM_AUTH_HST.paid_stmt_date is
'还款账单日';

comment on column ICPS_WB_TM_AUTH_HST.repay_amt is
'应还款额';

comment on column ICPS_WB_TM_AUTH_HST.bank_proportion is
'银行出资比例';

comment on column ICPS_WB_TM_AUTH_HST.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_AUTH_HST.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_AUTH_HST.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_AUTH_HST.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_IM_INFO                                    */
/*==============================================================*/
create table ICPS_WB_TM_IM_INFO 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   seq_no               VARCHAR(20),
   org                  CHAR(12),
   product_code         CHAR(6),
   cust_id              VARCHAR(20),
   acct_no              VARCHAR(20),
   app_type             VARCHAR(3),
   app_acct_no          VARCHAR(40),
   user_field282        VARCHAR(255),
   created_datetime     VARCHAR(14),
   update_time          VARCHAR(14),
   jpa_version          INTEGER,
   last_update_biz_date VARCHAR(14),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_IM_INFO primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_IM_INFO is
'客户即时通讯信息表';

comment on column ICPS_WB_TM_IM_INFO.busi_date is
'业务日期';

comment on column ICPS_WB_TM_IM_INFO.file_order is
'文件序号';

comment on column ICPS_WB_TM_IM_INFO.seq_no is
'序号';

comment on column ICPS_WB_TM_IM_INFO.org is
'机构号';

comment on column ICPS_WB_TM_IM_INFO.product_code is
'产品代码';

comment on column ICPS_WB_TM_IM_INFO.cust_id is
'客户编号';

comment on column ICPS_WB_TM_IM_INFO.acct_no is
'账户编号';

comment on column ICPS_WB_TM_IM_INFO.app_type is
'应用类型';

comment on column ICPS_WB_TM_IM_INFO.app_acct_no is
'应用账号';

comment on column ICPS_WB_TM_IM_INFO.user_field282 is
'备用字段282';

comment on column ICPS_WB_TM_IM_INFO.created_datetime is
'创建时间';

comment on column ICPS_WB_TM_IM_INFO.update_time is
'更新时间';

comment on column ICPS_WB_TM_IM_INFO.jpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_IM_INFO.last_update_biz_date is
'上次联机更新业务日期';

comment on column ICPS_WB_TM_IM_INFO.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_IM_INFO.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_IM_INFO.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_IM_INFO.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_LOAN_RECEIPT_LIST                          */
/*==============================================================*/
create table ICPS_WB_TM_LOAN_RECEIPT_LIST 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   busi_serial          VARCHAR(32),
   sys_trans_id         VARCHAR(32),
   loan_receipt_nbr     VARCHAR(20),
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   card_no              VARCHAR(19),
   transfer_in_date     VARCHAR(14),
   last_modified_datetime VARCHAR(14),
   pay_amt              DECIMAL(15,2),
   bank_group_id        VARCHAR(5),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_LOAN_RECEIPT_LIS primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_LOAN_RECEIPT_LIST is
'还款借据清单表';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.busi_date is
'业务日期';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.file_order is
'文件序号';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.busi_serial is
'业务流水号';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.sys_trans_id is
'系统调用流水号';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.loan_receipt_nbr is
'借据号';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.acct_no is
'账户编号';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.acct_type is
'账户类型';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.card_no is
'卡号';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.transfer_in_date is
'入账日期';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.last_modified_datetime is
'时间戳';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.pay_amt is
'还款金额';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.bank_group_id is
'银团编号';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_LOAN_RECEIPT_LIST.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_RE_HST                                     */
/*==============================================================*/
create table ICPS_WB_TM_RE_HST 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   busi_serial          VARCHAR(32),
   sys_trans_id         VARCHAR(32),
   loan_receipt_nbr     VARCHAR(20),
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   card_no              VARCHAR(19),
   transfer_in_date     VARCHAR(14),
   last_modified_datetime VARCHAR(14),
   move_date            VARCHAR(14),
   part_month           INTEGER,
   pay_amt              DECIMAL(15,2),
   bank_group_id        VARCHAR(5),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_RE_HST primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_RE_HST is
'还款借据清单表历史';

comment on column ICPS_WB_TM_RE_HST.busi_date is
'业务日期';

comment on column ICPS_WB_TM_RE_HST.file_order is
'文件序号';

comment on column ICPS_WB_TM_RE_HST.busi_serial is
'业务流水号';

comment on column ICPS_WB_TM_RE_HST.sys_trans_id is
'系统调用流水号';

comment on column ICPS_WB_TM_RE_HST.loan_receipt_nbr is
'借据号';

comment on column ICPS_WB_TM_RE_HST.acct_no is
'账户编号';

comment on column ICPS_WB_TM_RE_HST.acct_type is
'账户类型';

comment on column ICPS_WB_TM_RE_HST.card_no is
'卡号';

comment on column ICPS_WB_TM_RE_HST.transfer_in_date is
'入账日期';

comment on column ICPS_WB_TM_RE_HST.last_modified_datetime is
'时间戳';

comment on column ICPS_WB_TM_RE_HST.move_date is
'转移日期(大数据提取用)';

comment on column ICPS_WB_TM_RE_HST.part_month is
'分区用的月份';

comment on column ICPS_WB_TM_RE_HST.pay_amt is
'还款金额';

comment on column ICPS_WB_TM_RE_HST.bank_group_id is
'银团编号';

comment on column ICPS_WB_TM_RE_HST.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_RE_HST.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_RE_HST.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_RE_HST.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_PSB_PERSONAL_INFO                          */
/*==============================================================*/
create table ICPS_WB_TM_PSB_PERSONAL_INFO 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   id                   INTEGER,
   app_no               VARCHAR(20),
   id_type              CHAR(1),
   certi_no             VARCHAR(18),
   name                 VARCHAR(90),
   gender               CHAR(1),
   birth_date           VARCHAR(14),
   marital_status       VARCHAR(2),
   mobile_no            VARCHAR(20),
   home_phone           VARCHAR(30),
   unit_phone           VARCHAR(30),
   qualification        VARCHAR(2),
   degree               VARCHAR(2),
   address              VARCHAR(700),
   reside_addr          VARCHAR(700),
   mate_certp           CHAR(1),
   mate_cerno           VARCHAR(18),
   mate_name            VARCHAR(30),
   mate_corp            VARCHAR(500),
   mate_phone           VARCHAR(30),
   addr                 VARCHAR(700),
   reside_state         VARCHAR(2),
   comp_nm              VARCHAR(700),
   unit_addr            VARCHAR(700),
   profession           VARCHAR(2),
   comp_trade           VARCHAR(2),
   position             VARCHAR(2),
   teach_pose           VARCHAR(2),
   work_date            VARCHAR(4),
   infodate             VARCHAR(14),
   create_time          VARCHAR(14),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_PSB_PERSONAL_INF primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_PSB_PERSONAL_INFO is
'F_WBANK身份信息表';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.busi_date is
'业务日期';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.file_order is
'文件序号';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.id is
'ID';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.app_no is
'申请件编号';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.id_type is
'证件类型';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.certi_no is
'身份证号';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.name is
'姓名';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.gender is
'性别';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.birth_date is
'出生日期';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.marital_status is
'婚姻状况';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.mobile_no is
'手机号码';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.home_phone is
'家庭电话';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.unit_phone is
'单位电话';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.qualification is
'学历';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.degree is
'学位';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.address is
'通讯地址';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.reside_addr is
'户籍地址';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.mate_certp is
'配偶证件类型';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.mate_cerno is
'配偶证件号码';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.mate_name is
'配偶姓名';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.mate_corp is
'配偶工作单位';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.mate_phone is
'配偶联系电话';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.addr is
'居住地址';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.reside_state is
'居住状况';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.comp_nm is
'工作单位';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.unit_addr is
'单位地址';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.profession is
'职业';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.comp_trade is
'行业';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.position is
'职务';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.teach_pose is
'职称';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.work_date is
'本单位工作起始年份';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.infodate is
'信息更新日期';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.create_time is
'创建时间';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_PSB_PERSONAL_INFO.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_RRS_BDM_UDF_CLEAR_TOT                         */
/*==============================================================*/
create table ICPS_WB_RRS_BDM_UDF_CLEAR_TOT 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   data_dt              VARCHAR(10),
   acct_no              VARCHAR(40),
   currency             VARCHAR(23),
   acct_name            VARCHAR(100),
   last_balance         DECIMAL(20,4),
   balance              DECIMAL(20,4),
   payment_amt          DECIMAL(20,4),
   repayment_amt        DECIMAL(20,4),
   other_credit_amt     DECIMAL(20,4),
   other_debit_amt      DECIMAL(20,4),
   ds                   VARCHAR(10),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_RRS_BDM_UDF_CLEAR_T primary key (busi_date, file_order)
);

comment on table ICPS_WB_RRS_BDM_UDF_CLEAR_TOT is
'备付金资金清算汇总表';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.busi_date is
'业务日期';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.file_order is
'文件序号';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.data_dt is
'数据日期';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.acct_no is
'备付金帐号';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.currency is
'币种';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.acct_name is
'户名';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.last_balance is
'上日账户余额';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.balance is
'本日账户余额';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.payment_amt is
'当日放款总金额';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.repayment_amt is
'当日还款总金额';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.other_credit_amt is
'当日其他划入款项';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.other_debit_amt is
'当日其他划出款项';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.ds is
'日期分区';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.extend_param1 is
'扩展1';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.extend_param2 is
'扩展2';

comment on column ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.extend_param3 is
'扩展3';



/*==============================================================*/
/* Table: ICPS_WB_RRS_CLEAR_DETAIL                              */
/*==============================================================*/
create table ICPS_WB_RRS_CLEAR_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   data_dt              VARCHAR(10),
   acct_no              VARCHAR(40),
   currency             VARCHAR(3),
   bank_group_code      VARCHAR(5),
   data_type            VARCHAR(6),
   amount               DECIMAL(20,4),
   ds                   VARCHAR(10),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_RRS_CLEAR_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_WB_RRS_CLEAR_DETAIL is
'备付金资金清算明细';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.busi_date is
'业务日期';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.file_order is
'文件序号';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.data_dt is
'数据日期:YYYYMMDD';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.acct_no is
'备付金帐号';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.currency is
'币种:CNY-人民币';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.bank_group_code is
'银团编号:除1、3类型外，其他数据类型的均为为ZZZZZ';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.data_type is
'数据类型：
1：放款
2：放款撤销
3：还款
4：还款撤销
5：其他划入款项
6：其他划出款项"
';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.amount is
'发生额';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.ds is
'日期分区';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_WB_RRS_CLEAR_DETAIL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_RSS_OTHER_DETAIL                              */
/*==============================================================*/
create table ICPS_WB_RSS_OTHER_DETAIL 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   data_dt              VARCHAR(10),
   acct_no              VARCHAR(40),
   currency             VARCHAR(3),
   bank_group_code      VARCHAR(5),
   data_type            VARCHAR(6),
   ser_no               INTEGER,
   amount               DECIMAL(20,4),
   memo                 VARCHAR(20),
   ds                   VARCHAR(10),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_RSS_OTHER_DETAIL primary key (busi_date, file_order)
);

comment on table ICPS_WB_RSS_OTHER_DETAIL is
'备付金其他款项资金明细';

comment on column ICPS_WB_RSS_OTHER_DETAIL.busi_date is
'业务日期';

comment on column ICPS_WB_RSS_OTHER_DETAIL.file_order is
'文件序号';

comment on column ICPS_WB_RSS_OTHER_DETAIL.data_dt is
'数据日期';

comment on column ICPS_WB_RSS_OTHER_DETAIL.acct_no is
'备付金账号';

comment on column ICPS_WB_RSS_OTHER_DETAIL.currency is
'币种:CNY-人民币';

comment on column ICPS_WB_RSS_OTHER_DETAIL.bank_group_code is
'银团编号';

comment on column ICPS_WB_RSS_OTHER_DETAIL.data_type is
'数据类型：
1：其他划入款项
2：其他划出款项"
';

comment on column ICPS_WB_RSS_OTHER_DETAIL.ser_no is
'明细序号';

comment on column ICPS_WB_RSS_OTHER_DETAIL.amount is
'发生额';

comment on column ICPS_WB_RSS_OTHER_DETAIL.memo is
'备注';

comment on column ICPS_WB_RSS_OTHER_DETAIL.ds is
'日期分区';

comment on column ICPS_WB_RSS_OTHER_DETAIL.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_RSS_OTHER_DETAIL.extend_param1 is
'扩展1';

comment on column ICPS_WB_RSS_OTHER_DETAIL.extend_param2 is
'扩展2';

comment on column ICPS_WB_RSS_OTHER_DETAIL.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_COLL_REC                                   */
/*==============================================================*/
create table ICPS_WB_TM_COLL_REC 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   coll_rec_id          INTEGER,
   case_no              VARCHAR(32),
   cust_id              VARCHAR(20),
   coll_rec_type        VARCHAR(10),
   action_code          VARCHAR(32),
   user_field1          CHAR(1),
   user_field2          VARCHAR(4),
   coll_time            VARCHAR(14),
   coll_conseq          VARCHAR(10),
   prom_amt             DECIMAL(15,2),
   prom_date            VARCHAR(14),
   user_field3          VARCHAR(400),
   user_field4          DECIMAL(15,2),
   user_field5          VARCHAR(10),
   user_field6          VARCHAR(10),
   user_field7          VARCHAR(10),
   user_field8          VARCHAR(10),
   user_field9          VARCHAR(10),
   user_field10         VARCHAR(10),
   user_field11         VARCHAR(20),
   user_field12         VARCHAR(50),
   user_field13         VARCHAR(50),
   user_field14         VARCHAR(10),
   user_field15         VARCHAR(10),
   user_field16         VARCHAR(50),
   user_field17         VARCHAR(50),
   user_field18         VARCHAR(14),
   user_field19         VARCHAR(14),
   user_field20         INTEGER,
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_COLL_REC primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_COLL_REC is
'催收记录表';

comment on column ICPS_WB_TM_COLL_REC.busi_date is
'业务日期';

comment on column ICPS_WB_TM_COLL_REC.file_order is
'文件序号';

comment on column ICPS_WB_TM_COLL_REC.org is
'机构号';

comment on column ICPS_WB_TM_COLL_REC.coll_rec_id is
'催记流水号';

comment on column ICPS_WB_TM_COLL_REC.case_no is
'案件编号';

comment on column ICPS_WB_TM_COLL_REC.cust_id is
'客户编号';

comment on column ICPS_WB_TM_COLL_REC.coll_rec_type is
'催记类型';

comment on column ICPS_WB_TM_COLL_REC.action_code is
'催收动作';

comment on column ICPS_WB_TM_COLL_REC.user_field1 is
'备用字段';

comment on column ICPS_WB_TM_COLL_REC.user_field2 is
'备用字段2';

comment on column ICPS_WB_TM_COLL_REC.coll_time is
'催收时间';

comment on column ICPS_WB_TM_COLL_REC.coll_conseq is
'催收结果';

comment on column ICPS_WB_TM_COLL_REC.prom_amt is
'承诺金额';

comment on column ICPS_WB_TM_COLL_REC.prom_date is
'承诺日期';

comment on column ICPS_WB_TM_COLL_REC.user_field3 is
'备用字段3';

comment on column ICPS_WB_TM_COLL_REC.user_field4 is
'备用字段4';

comment on column ICPS_WB_TM_COLL_REC.user_field5 is
'备用字段5';

comment on column ICPS_WB_TM_COLL_REC.user_field6 is
'备用字段6';

comment on column ICPS_WB_TM_COLL_REC.user_field7 is
'备用字段7';

comment on column ICPS_WB_TM_COLL_REC.user_field8 is
'备用字段8';

comment on column ICPS_WB_TM_COLL_REC.user_field9 is
'备用字段9';

comment on column ICPS_WB_TM_COLL_REC.user_field10 is
'备用字段10';

comment on column ICPS_WB_TM_COLL_REC.user_field11 is
'备用字段11';

comment on column ICPS_WB_TM_COLL_REC.user_field12 is
'备用字段12';

comment on column ICPS_WB_TM_COLL_REC.user_field13 is
'备用字段13';

comment on column ICPS_WB_TM_COLL_REC.user_field14 is
'备用字段14';

comment on column ICPS_WB_TM_COLL_REC.user_field15 is
'备用字段15';

comment on column ICPS_WB_TM_COLL_REC.user_field16 is
'备用字段16';

comment on column ICPS_WB_TM_COLL_REC.user_field17 is
'备用字段17';

comment on column ICPS_WB_TM_COLL_REC.user_field18 is
'备用字段18';

comment on column ICPS_WB_TM_COLL_REC.user_field19 is
'备用字段19';

comment on column ICPS_WB_TM_COLL_REC.user_field20 is
'备用字段20';

comment on column ICPS_WB_TM_COLL_REC.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_COLL_REC.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_COLL_REC.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_COLL_REC.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_LOAN_VMS                                   */
/*==============================================================*/
create table ICPS_WB_TM_LOAN_VMS 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   id                   VARCHAR(20),
   org                  VARCHAR(12),
   card_no              VARCHAR(19),
   ref_nbr              VARCHAR(23),
   bank_group_id        VARCHAR(5),
   bank_no              VARCHAR(10),
   product_cd           VARCHAR(6),
   biz_tax_interes      DECIMAL(15,2),
   vat_int_bal          DECIMAL(15,2),
   norevoke_vat_int_bal DECIMAL(15,2),
   vat_tax              DECIMAL(15,2),
   loan_int_term        INTEGER,
   last_modified_time   VARCHAR(14),
   paid_out_date        VARCHAR(14),
   age_no               CHAR(1),
   batch_date           VARCHAR(14),
   lpa_version          INTEGER,
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_LOAN_VMS primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_LOAN_VMS is
'借据纳税加工表';

comment on column ICPS_WB_TM_LOAN_VMS.busi_date is
'业务日期';

comment on column ICPS_WB_TM_LOAN_VMS.file_order is
'文件序号';

comment on column ICPS_WB_TM_LOAN_VMS.id is
'纳税借据ID';

comment on column ICPS_WB_TM_LOAN_VMS.org is
'机构号';

comment on column ICPS_WB_TM_LOAN_VMS.card_no is
'介质卡号';

comment on column ICPS_WB_TM_LOAN_VMS.ref_nbr is
'交易参考号';

comment on column ICPS_WB_TM_LOAN_VMS.bank_group_id is
'银团编号';

comment on column ICPS_WB_TM_LOAN_VMS.bank_no is
'银行编号';

comment on column ICPS_WB_TM_LOAN_VMS.product_cd is
'产品号';

comment on column ICPS_WB_TM_LOAN_VMS.biz_tax_interes is
'营业税下的应计和应收息';

comment on column ICPS_WB_TM_LOAN_VMS.vat_int_bal is
'90天内的应纳税息余额';

comment on column ICPS_WB_TM_LOAN_VMS.norevoke_vat_int_bal is
'不冲抵算法下应纳税息（含90天内+90天外还款补记部分）';

comment on column ICPS_WB_TM_LOAN_VMS.vat_tax is
'记账增值税';

comment on column ICPS_WB_TM_LOAN_VMS.loan_int_term is
'贷款总期数';

comment on column ICPS_WB_TM_LOAN_VMS.last_modified_time is
'上次修改时间';

comment on column ICPS_WB_TM_LOAN_VMS.paid_out_date is
'结清日期';

comment on column ICPS_WB_TM_LOAN_VMS.age_no is
'账龄';

comment on column ICPS_WB_TM_LOAN_VMS.batch_date is
'批量日期';

comment on column ICPS_WB_TM_LOAN_VMS.lpa_version is
'乐观锁版本号';

comment on column ICPS_WB_TM_LOAN_VMS.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_LOAN_VMS.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_LOAN_VMS.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_LOAN_VMS.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_TM_FREE_COUPONS_INFO                          */
/*==============================================================*/
create table ICPS_WB_TM_FREE_COUPONS_INFO 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   org                  CHAR(12),
   list_no              VARCHAR(21),
   act_no               CHAR(11),
   equity_no            CHAR(8),
   equity_type          VARCHAR(10),
   equity_value         INTEGER,
   loan_receipt_nbr     VARCHAR(20),
   card_no              VARCHAR(19),
   ref_nbr              VARCHAR(23),
   bank_group_id        VARCHAR(5),
   bank_no              VARCHAR(10),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_TM_FREE_COUPONS_INF primary key (busi_date, file_order)
);

comment on table ICPS_WB_TM_FREE_COUPONS_INFO is
'免息信息卷';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.busi_date is
'业务日期';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.file_order is
'文件序号';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.org is
'机构号';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.list_no is
'资格编号';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.act_no is
'活动编号';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.equity_no is
'权益编号';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.equity_type is
'权益类型';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.equity_value is
'权益值';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.loan_receipt_nbr is
'借据号';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.card_no is
'介质卡号';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.ref_nbr is
'交易参考';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.bank_group_id is
'银团编号';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.bank_no is
'银行编号';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.extend_param1 is
'扩展1';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.extend_param2 is
'扩展2';

comment on column ICPS_WB_TM_FREE_COUPONS_INFO.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_DS_SPLIT_DIFF                                 */
/*==============================================================*/
create table ICPS_WB_DS_SPLIT_DIFF 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   partition_date       CHAR(8),
   error_type           VARCHAR(40),
   bank_group_id        VARCHAR(5),
   bank_no              VARCHAR(10),
   busi_serial          VARCHAR(40),
   trans_type           VARCHAR(10),
   name                 VARCHAR(80),
   logical_card_no      VARCHAR(19),
   bf_amt               DECIMAL(15,2),
   account_amt          DECIMAL(15,2),
   error_amt            DECIMAL(15,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_DS_SPLIT_DIFF primary key (busi_date, file_order)
);

comment on table ICPS_WB_DS_SPLIT_DIFF is
'F_银团尾差调整表';

comment on column ICPS_WB_DS_SPLIT_DIFF.busi_date is
'业务日期';

comment on column ICPS_WB_DS_SPLIT_DIFF.file_order is
'文件序号';

comment on column ICPS_WB_DS_SPLIT_DIFF.partition_date is
'批量日期';

comment on column ICPS_WB_DS_SPLIT_DIFF.error_type is
'异常类型';

comment on column ICPS_WB_DS_SPLIT_DIFF.bank_group_id is
'银团编号';

comment on column ICPS_WB_DS_SPLIT_DIFF.bank_no is
'银行编号';

comment on column ICPS_WB_DS_SPLIT_DIFF.busi_serial is
'业务流水号';

comment on column ICPS_WB_DS_SPLIT_DIFF.trans_type is
'交易类型';

comment on column ICPS_WB_DS_SPLIT_DIFF.name is
'姓名';

comment on column ICPS_WB_DS_SPLIT_DIFF.logical_card_no is
'逻辑卡号';

comment on column ICPS_WB_DS_SPLIT_DIFF.bf_amt is
'备付金清算金额';

comment on column ICPS_WB_DS_SPLIT_DIFF.account_amt is
'CNC记账金额';

comment on column ICPS_WB_DS_SPLIT_DIFF.error_amt is
'应调整差额';

comment on column ICPS_WB_DS_SPLIT_DIFF.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_DS_SPLIT_DIFF.extend_param1 is
'扩展1';

comment on column ICPS_WB_DS_SPLIT_DIFF.extend_param2 is
'扩展2';

comment on column ICPS_WB_DS_SPLIT_DIFF.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_DS_DCA_COMMISSION                             */
/*==============================================================*/
create table ICPS_WB_DS_DCA_COMMISSION 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   out_amt              DECIMAL(15,2),
   out_prin             DECIMAL(15,2),
   out_interest         DECIMAL(15,2),
   out_penatly          DECIMAL(15,2),
   out_due_days         INTEGER,
   out_age_cd           CHAR(6),
   repay_amt            DECIMAL(15,2),
   commision_ratio      DECIMAL(7,2),
   bank_group_id        VARCHAR(5),
   bank_proportion      DECIMAL(7,2),
   out_expense          DECIMAL(15,2),
   name                 VARCHAR(80),
   logical_card_no      VARCHAR(19),
   cust_id              VARCHAR(20),
   acct_no              VARCHAR(20),
   loan_receipt_nbr     VARCHAR(20),
   bn                   VARCHAR(20),
   partition_date       VARCHAR(10),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_DS_DCA_COMMISSION primary key (busi_date, file_order)
);

comment on table ICPS_WB_DS_DCA_COMMISSION is
'委外催收借据级费用分摊明细表';

comment on column ICPS_WB_DS_DCA_COMMISSION.busi_date is
'业务日期';

comment on column ICPS_WB_DS_DCA_COMMISSION.file_order is
'文件序号';

comment on column ICPS_WB_DS_DCA_COMMISSION.out_amt is
'委外金额';

comment on column ICPS_WB_DS_DCA_COMMISSION.out_prin is
'委外本金';

comment on column ICPS_WB_DS_DCA_COMMISSION.out_interest is
'委外利息';

comment on column ICPS_WB_DS_DCA_COMMISSION.out_penatly is
'委外罚息';

comment on column ICPS_WB_DS_DCA_COMMISSION.out_due_days is
'委外逾期天数';

comment on column ICPS_WB_DS_DCA_COMMISSION.out_age_cd is
'委外逾期时段';

comment on column ICPS_WB_DS_DCA_COMMISSION.repay_amt is
'还款金额';

comment on column ICPS_WB_DS_DCA_COMMISSION.commision_ratio is
'委外费率';

comment on column ICPS_WB_DS_DCA_COMMISSION.bank_group_id is
'银团编号';

comment on column ICPS_WB_DS_DCA_COMMISSION.bank_proportion is
'银团比例';

comment on column ICPS_WB_DS_DCA_COMMISSION.out_expense is
'委外费用';

comment on column ICPS_WB_DS_DCA_COMMISSION.name is
'名字';

comment on column ICPS_WB_DS_DCA_COMMISSION.logical_card_no is
'卡号';

comment on column ICPS_WB_DS_DCA_COMMISSION.cust_id is
'客户号';

comment on column ICPS_WB_DS_DCA_COMMISSION.acct_no is
'账户号';

comment on column ICPS_WB_DS_DCA_COMMISSION.loan_receipt_nbr is
'借据号';

comment on column ICPS_WB_DS_DCA_COMMISSION.bn is
'银行号';

comment on column ICPS_WB_DS_DCA_COMMISSION.partition_date is
'分区日期';

comment on column ICPS_WB_DS_DCA_COMMISSION.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_DS_DCA_COMMISSION.extend_param1 is
'扩展1';

comment on column ICPS_WB_DS_DCA_COMMISSION.extend_param2 is
'扩展2';

comment on column ICPS_WB_DS_DCA_COMMISSION.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_DS_DIFF_LIST                                  */
/*==============================================================*/
create table ICPS_WB_DS_DIFF_LIST 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   id_num               VARCHAR(30),
   id_type              CHAR(1),
   cust_id              VARCHAR(20),
   product_code         VARCHAR(6),
   acct_no              VARCHAR(20),
   acct_type            CHAR(1),
   logical_card_no      VARCHAR(19),
   ref_nbr              VARCHAR(23),
   loan_init_prin       DECIMAL(15,2),
   bank_group_id        VARCHAR(5),
   writeoff_proc_status VARCHAR(20),
   writeoff_proc_desc   VARCHAR(100),
   product_attr         VARCHAR(5),
   name                 VARCHAR(200),
   writeoff_date        VARCHAR(10),
   bank_no              VARCHAR(20),
   bank_proportion      DECIMAL(5,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_DS_DIFF_LIST primary key (busi_date, file_order)
);

comment on table ICPS_WB_DS_DIFF_LIST is
'待核销借据与已核销借据差异表';

comment on column ICPS_WB_DS_DIFF_LIST.busi_date is
'业务日期';

comment on column ICPS_WB_DS_DIFF_LIST.file_order is
'文件序号';

comment on column ICPS_WB_DS_DIFF_LIST.id_num is
'证件号';

comment on column ICPS_WB_DS_DIFF_LIST.id_type is
'证件类型';

comment on column ICPS_WB_DS_DIFF_LIST.cust_id is
'客户号';

comment on column ICPS_WB_DS_DIFF_LIST.product_code is
'产品号';

comment on column ICPS_WB_DS_DIFF_LIST.acct_no is
'账号';

comment on column ICPS_WB_DS_DIFF_LIST.acct_type is
'账户类型';

comment on column ICPS_WB_DS_DIFF_LIST.logical_card_no is
'卡号';

comment on column ICPS_WB_DS_DIFF_LIST.ref_nbr is
'参考号';

comment on column ICPS_WB_DS_DIFF_LIST.loan_init_prin is
'本金';

comment on column ICPS_WB_DS_DIFF_LIST.bank_group_id is
'银团号';

comment on column ICPS_WB_DS_DIFF_LIST.writeoff_proc_status is
'核销状态';

comment on column ICPS_WB_DS_DIFF_LIST.writeoff_proc_desc is
'未核销原因';

comment on column ICPS_WB_DS_DIFF_LIST.product_attr is
'产品属性';

comment on column ICPS_WB_DS_DIFF_LIST.name is
'姓名';

comment on column ICPS_WB_DS_DIFF_LIST.writeoff_date is
'核销日期';

comment on column ICPS_WB_DS_DIFF_LIST.bank_no is
'银行号';

comment on column ICPS_WB_DS_DIFF_LIST.bank_proportion is
'银团比例';

comment on column ICPS_WB_DS_DIFF_LIST.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_DS_DIFF_LIST.extend_param1 is
'扩展1';

comment on column ICPS_WB_DS_DIFF_LIST.extend_param2 is
'扩展2';

comment on column ICPS_WB_DS_DIFF_LIST.extend_param3 is
'扩展3';


/*==============================================================*/
/* Table: ICPS_WB_DS_SUCC_LIST                                  */
/*==============================================================*/
create table ICPS_WB_DS_SUCC_LIST 
(
   busi_date            CHAR(8)              not null,
   file_order           INTEGER              not null,
   writeoff_date        VARCHAR(10),
   name                 VARCHAR(200),
   cust_id              VARCHAR(20),
   bank_no              VARCHAR(20),
   bank_group_id        VARCHAR(5),
   product_cd           VARCHAR(6),
   logical_card_no      VARCHAR(19),
   ref_nbr              VARCHAR(23),
   writeoff_proc_status VARCHAR(20),
   loan_init_prin       DECIMAL(15,2),
   loan_intr_penalty    DECIMAL(15,2),
   bank_proportion      DECIMAL(5,2),
   is_check_flag        CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_WB_DS_SUCC_LIST primary key (busi_date, file_order)
);

comment on table ICPS_WB_DS_SUCC_LIST is
'已核销借据清单表';

comment on column ICPS_WB_DS_SUCC_LIST.busi_date is
'业务日期';

comment on column ICPS_WB_DS_SUCC_LIST.file_order is
'文件序号';

comment on column ICPS_WB_DS_SUCC_LIST.writeoff_date is
'核销日期';

comment on column ICPS_WB_DS_SUCC_LIST.name is
'姓名';

comment on column ICPS_WB_DS_SUCC_LIST.cust_id is
'客户号';

comment on column ICPS_WB_DS_SUCC_LIST.bank_no is
'银行号';

comment on column ICPS_WB_DS_SUCC_LIST.bank_group_id is
'银团号';

comment on column ICPS_WB_DS_SUCC_LIST.product_cd is
'产品号';

comment on column ICPS_WB_DS_SUCC_LIST.logical_card_no is
'卡号';

comment on column ICPS_WB_DS_SUCC_LIST.ref_nbr is
'参考号';

comment on column ICPS_WB_DS_SUCC_LIST.writeoff_proc_status is
'核销状态';

comment on column ICPS_WB_DS_SUCC_LIST.loan_init_prin is
'本金';

comment on column ICPS_WB_DS_SUCC_LIST.loan_intr_penalty is
'利息罚息';

comment on column ICPS_WB_DS_SUCC_LIST.bank_proportion is
'银团比例';

comment on column ICPS_WB_DS_SUCC_LIST.is_check_flag is
'参与对账标识';

comment on column ICPS_WB_DS_SUCC_LIST.extend_param1 is
'扩展1';

comment on column ICPS_WB_DS_SUCC_LIST.extend_param2 is
'扩展2';

comment on column ICPS_WB_DS_SUCC_LIST.extend_param3 is
'扩展3';
