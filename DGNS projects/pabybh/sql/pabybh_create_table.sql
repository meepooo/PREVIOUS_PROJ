drop table PABYBH_ACCTO2N;

drop table PABYBH_ACCT_ENTRY_HIS;

drop table PABYBH_ACCT_ENTRY;

drop table PABYBH_CHECKCTL;

drop table PABYBH_COURSE_INFO;

drop table PABYBH_CUSTINFO;

drop index K_PABYBH_DEPCHKINFO_1;

drop table PABYBH_DEPCHKINFO;

drop index K_PABYBH_DEPCHKINFO_2;

drop table PABYBH_DEPCHKINFO_HIS;

drop index K_PABYBH_HOSCHKINFO_1;

drop table PABYBH_HOSCHKINFO;

drop index K_PABYBH_HOSCHKINFO_2;

drop table PABYBH_HOSCHKINFO_HIS;

drop index K_PABYBH_NOTBAL_1;

drop table PABYBH_NOTBAL;

drop index K_PABYBH_NOTBAL_2;

drop table PABYBH_NOTBAL_HIS;

drop table PABYBH_ORGCFG;

drop table PABYBH_PABTRANSCTL;

drop table PABYBH_SECKEY;

drop index K_PABYBH_SERIAL_3;

drop index K_PABYBH_SERIAL_2;

drop index K_PABYBH_SERIAL_1;

drop table PABYBH_SERIAL;

drop index K_PABYBH_SERIAL_6;

drop index K_PABYBH_SERIAL_5;

drop index K_PABYBH_SERIAL_4;

drop table PABYBH_SERIAL_HIS;

drop index K_PABYBH_SIGN_1;

drop table PABYBH_SIGN;

drop table PABYBH_SVRINFO;

drop table PABYBH_TRADER;

--==============================================================
-- Table: PABYBH_ACCTO2N
--==============================================================
create table PABYBH_ACCTO2N (
   COBANKNO             VARCHAR(12)            not null,
   OLDACCT              VARCHAR(32)            not null,
   OLDORG               VARCHAR(10),
   NEWACCT              VARCHAR(32)            not null,
   NEWORG               VARCHAR(10),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PK_PABYBH_ACCTO2N primary key (COBANKNO, OLDACCT)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_ACCTO2N is
'核心新老账号映射';

comment on column PABYBH_ACCTO2N.COBANKNO is
'合作行号';

comment on column PABYBH_ACCTO2N.OLDACCT is
'老账号';

comment on column PABYBH_ACCTO2N.OLDORG is
'老机构';

comment on column PABYBH_ACCTO2N.NEWACCT is
'新账号';

comment on column PABYBH_ACCTO2N.NEWORG is
'新机构';

comment on column PABYBH_ACCTO2N.EXTFLD1 is
'备用字段1';

comment on column PABYBH_ACCTO2N.EXTFLD2 is
'备用字段2';

comment on column PABYBH_ACCTO2N.EXTFLD3 is
'备用字段3';

--==============================================================
-- Table: PABYBH_ACCT_ENTRY_HIS
--==============================================================
create table PABYBH_ACCT_ENTRY_HIS (
   CHECKDATE            VARCHAR(8)             not null,
   ID                   VARCHAR(32)            not null,
   COURSE_CODE          VARCHAR(50)            not null,
   COURSE_NAME          VARCHAR(50)            not null,
   COURSE_ACCOUNT       VARCHAR(32)            not null,
   CDFLAG               VARCHAR(1)             not null,
   TRANSAMT             DECIMAL(16,2),
   REMARKCODE           VARCHAR(32),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_ACCT_ENTRY_HIS is
'会计分录历史表';

comment on column PABYBH_ACCT_ENTRY_HIS.CHECKDATE is
'对账清算日期';

comment on column PABYBH_ACCT_ENTRY_HIS.ID is
'分录序号';

comment on column PABYBH_ACCT_ENTRY_HIS.COURSE_CODE is
'科目代码';

comment on column PABYBH_ACCT_ENTRY_HIS.COURSE_NAME is
'科目名称';

comment on column PABYBH_ACCT_ENTRY_HIS.COURSE_ACCOUNT is
'科目账号';

comment on column PABYBH_ACCT_ENTRY_HIS.CDFLAG is
'借贷标志 0-借 1-贷';

comment on column PABYBH_ACCT_ENTRY_HIS.TRANSAMT is
'交易金额';

comment on column PABYBH_ACCT_ENTRY_HIS.REMARKCODE is
'摘要码';

comment on column PABYBH_ACCT_ENTRY_HIS.EXTFLD1 is
'扩展字段1';

comment on column PABYBH_ACCT_ENTRY_HIS.EXTFLD2 is
'扩展字段2';

comment on column PABYBH_ACCT_ENTRY_HIS.EXTFLD3 is
'扩展字段3';


--==============================================================
-- Table: PABYBH_ACCT_ENTRY
--==============================================================
create table PABYBH_ACCT_ENTRY (
   CHECKDATE            VARCHAR(8)             not null,
   ID                   VARCHAR(32)            not null,
   COURSE_CODE          VARCHAR(50)            not null,
   COURSE_NAME          VARCHAR(50)            not null,
   COURSE_ACCOUNT       VARCHAR(32)            not null,
   CDFLAG               VARCHAR(1)             not null,
   TRANSAMT             DECIMAL(16,2),
   REMARKCODE           VARCHAR(32),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PABYBH_ACCT_ENTRY_KEY primary key (CHECKDATE, ID)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_ACCT_ENTRY is
'会计分录表';

comment on column PABYBH_ACCT_ENTRY.CHECKDATE is
'对账清算日期';

comment on column PABYBH_ACCT_ENTRY.ID is
'分录序号';

comment on column PABYBH_ACCT_ENTRY.COURSE_CODE is
'科目代码';

comment on column PABYBH_ACCT_ENTRY.COURSE_NAME is
'科目名称';

comment on column PABYBH_ACCT_ENTRY.COURSE_ACCOUNT is
'科目账号';

comment on column PABYBH_ACCT_ENTRY.CDFLAG is
'借贷标志 0-借 1-贷';

comment on column PABYBH_ACCT_ENTRY.TRANSAMT is
'交易金额';

comment on column PABYBH_ACCT_ENTRY.REMARKCODE is
'摘要码';

comment on column PABYBH_ACCT_ENTRY.EXTFLD1 is
'扩展字段1';

comment on column PABYBH_ACCT_ENTRY.EXTFLD2 is
'扩展字段2';

comment on column PABYBH_ACCT_ENTRY.EXTFLD3 is
'扩展字段3';

--==============================================================
-- Table: PABYBH_CHECKCTL
--==============================================================
create table PABYBH_CHECKCTL (
   CHECKDATE            VARCHAR(8)             not null,
   COBANKNO             VARCHAR(12)            not null,
   SVRCODE              VARCHAR(6)             not null,
   MSGTYPE              VARCHAR(1)             not null,
   TOTALCOUNT           INTEGER,
   TOTALAMT             DECIMAL(16,2),
   INTOTCNT             INTEGER,
   INTOTAMT             DECIMAL(16,2),
   OUTTOTCNT            INTEGER,
   OUTTOTAMT            DECIMAL(16,2),
   BACKTOTALCOUNT       INTEGER,
   BACKTOTALAMT         DECIMAL(16,2),
   LOCALTOTALCOUNT      INTEGER,
   LOCALTOTALAMT        DECIMAL(16,2),
   LOCALBACKTOTALCOUNT  INTEGER,
   LOCALBACKTOTALAMT    DECIMAL(16,2),
   HOSTTOTALCOUNT       INTEGER,
   HOSTTOTALAMT         DECIMAL(16,2),
   HOSTBACKTOTALCOUNT   INTEGER,
   HOSTBACKTOTALAMT     DECIMAL(16,2),
   NETAMT               DECIMAL(16,2),
   NETTYPE              VARCHAR(1),
   IEPCHKFILE           VARCHAR(100),
   HOSTCHKFILE          VARCHAR(100),
   EXECSTEP             VARCHAR(2),
   EXECSTAT             VARCHAR(1),
   CHKDETAILRESULT      VARCHAR(1),
   CHKPABTOTALRESULT    VARCHAR(1),
   CHKHOSTTOTALRESULT   VARCHAR(1),
   SETTLEDATE           VARCHAR(8),
   SETTLESERNO          VARCHAR(40),
   TRANSDATE            VARCHAR(8),
   TRANSSERIALNO        VARCHAR(40),
   HOSTDATE             VARCHAR(40),
   HOSTSERIALNO         VARCHAR(40),
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(10),
   RESPCODE             VARCHAR(10),
   RESPMSG              VARCHAR(120),
   STAT                 VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(128),
   constraint PK_PABYBH_CHECKCTL primary key (CHECKDATE, COBANKNO, 
SVRCODE, MSGTYPE)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_CHECKCTL is
'对账控制表';

comment on column PABYBH_CHECKCTL.CHECKDATE is
'对账日期';

comment on column PABYBH_CHECKCTL.COBANKNO is
'合作行号';

comment on column PABYBH_CHECKCTL.SVRCODE is
'服务码';

comment on column PABYBH_CHECKCTL.MSGTYPE is
'对账类型0资金类1账户类（正常）2账户类（解约&销户）';

comment on column PABYBH_CHECKCTL.TOTALCOUNT is
'总笔数';

comment on column PABYBH_CHECKCTL.TOTALAMT is
'总金额';

comment on column PABYBH_CHECKCTL.INTOTCNT is
'转入总笔数';

comment on column PABYBH_CHECKCTL.INTOTAMT is
'转入总金额';

comment on column PABYBH_CHECKCTL.OUTTOTCNT is
'转出总笔数';

comment on column PABYBH_CHECKCTL.OUTTOTAMT is
'转出总金额';

comment on column PABYBH_CHECKCTL.BACKTOTALCOUNT is
'冲正总笔数';

comment on column PABYBH_CHECKCTL.BACKTOTALAMT is
'冲正总金额';

comment on column PABYBH_CHECKCTL.LOCALTOTALCOUNT is
'平台总笔数';

comment on column PABYBH_CHECKCTL.LOCALTOTALAMT is
'平台总金额';

comment on column PABYBH_CHECKCTL.LOCALBACKTOTALCOUNT is
'平台冲正总笔数';

comment on column PABYBH_CHECKCTL.LOCALBACKTOTALAMT is
'平台冲正总金额';

comment on column PABYBH_CHECKCTL.HOSTTOTALCOUNT is
'主机总笔数';

comment on column PABYBH_CHECKCTL.HOSTTOTALAMT is
'主机总金额';

comment on column PABYBH_CHECKCTL.HOSTBACKTOTALCOUNT is
'主机冲正总笔数';

comment on column PABYBH_CHECKCTL.HOSTBACKTOTALAMT is
'主机冲正总金额';

comment on column PABYBH_CHECKCTL.NETAMT is
'轧差金额';

comment on column PABYBH_CHECKCTL.NETTYPE is
'轧差方向 ''0收入 1支出''';

comment on column PABYBH_CHECKCTL.IEPCHKFILE is
'平安对账文件名';

comment on column PABYBH_CHECKCTL.HOSTCHKFILE is
'主机对账文件名';

comment on column PABYBH_CHECKCTL.EXECSTEP is
'执行步点''0-获取平安对账信息 1-平安对账文件入库 2-平安明细对账完成 3-请求提交主机 4-获取主机对账文件,主机生成对账文件入库 5
-主机明细对账完成''';

comment on column PABYBH_CHECKCTL.EXECSTAT is
'执行状态''0-成功 1-失败''';

comment on column PABYBH_CHECKCTL.CHKDETAILRESULT is
'明细对账结果''0 未对账 1 对账平 2对账不平 3对账出错 9 对账中''';

comment on column PABYBH_CHECKCTL.CHKPABTOTALRESULT is
'中心对总账结果''0 未对账 1 对账平 2对账不平 3对账出错 9 对账中''';

comment on column PABYBH_CHECKCTL.CHKHOSTTOTALRESULT is
'核心对总账结果''0 未对账 1 对账平 2对账不平 3对账出错 9 对账中''';

comment on column PABYBH_CHECKCTL.SETTLEDATE is
'清算日期';

comment on column PABYBH_CHECKCTL.SETTLESERNO is
'清算流水号';

comment on column PABYBH_CHECKCTL.TRANSDATE is
'交易日期';

comment on column PABYBH_CHECKCTL.TRANSSERIALNO is
'交易流水号';

comment on column PABYBH_CHECKCTL.HOSTDATE is
'清算核心日期';

comment on column PABYBH_CHECKCTL.HOSTSERIALNO is
'清算核心流水号';

comment on column PABYBH_CHECKCTL.TRANSORG is
'交易机构';

comment on column PABYBH_CHECKCTL.TRANSOPER is
'交易柜员';

comment on column PABYBH_CHECKCTL.RESPCODE is
'响应码';

comment on column PABYBH_CHECKCTL.RESPMSG is
'响应信息';

comment on column PABYBH_CHECKCTL.STAT is
'交易状态 0成功 1失败 6状态未知 7被冲正 8被撤销 9初始';

comment on column PABYBH_CHECKCTL.EXTFLD1 is
'备用字段1';

comment on column PABYBH_CHECKCTL.EXTFLD2 is
'备用字段2';

comment on column PABYBH_CHECKCTL.EXTFLD3 is
'备用字段3';

--==============================================================
-- Table: PABYBH_COURSE_INFO
--==============================================================
create table PABYBH_COURSE_INFO (
   ID                   VARCHAR(32)            not null,
   COURSE_CODE          VARCHAR(50)            not null,
   COURSE_NAME          VARCHAR(50)            not null,
   COURSE_ACCOUNT       VARCHAR(32)            not null,
   COURSE_DESC          VARCHAR(200),
   constraint PABYBH_COURSE_INFO_KEY primary key (ID)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_COURSE_INFO is
'科目信息表';

comment on column PABYBH_COURSE_INFO.ID is
'序号 ';

comment on column PABYBH_COURSE_INFO.COURSE_CODE is
'科目代码 ';

comment on column PABYBH_COURSE_INFO.COURSE_NAME is
'科目名称 ';

comment on column PABYBH_COURSE_INFO.COURSE_ACCOUNT is
'科目账号 ';

comment on column PABYBH_COURSE_INFO.COURSE_DESC is
'科目描述 ';

--==============================================================
-- Table: PABYBH_CUSTINFO
--==============================================================
create table PABYBH_CUSTINFO (
   CERTTYPE             VARCHAR(2)             not null,
   CERTNO               VARCHAR(32)            not null,
   CUSTTYPE             VARCHAR(2),
   CUSTNAME             VARCHAR(120),
   POST                 VARCHAR(6),
   ADDR                 VARCHAR(128),
   EMAIL                VARCHAR(120),
   PHONE                VARCHAR(16),
   MOBILE               VARCHAR(11),
   FAX                  VARCHAR(16),
   UPDATEDATE           VARCHAR(8),
   UPDATETIME           VARCHAR(6),
   CREATEDATE           VARCHAR(8),
   CREATETIME           VARCHAR(6),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PK_PABYBH_CUSTINFO primary key (CERTTYPE, CERTNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_CUSTINFO is
'客户信息表';

comment on column PABYBH_CUSTINFO.CERTTYPE is
'证件类型';

comment on column PABYBH_CUSTINFO.CERTNO is
'证件号码';

comment on column PABYBH_CUSTINFO.CUSTTYPE is
'客户类型 00-机构 01-个人';

comment on column PABYBH_CUSTINFO.CUSTNAME is
'客户名称';

comment on column PABYBH_CUSTINFO.POST is
'邮编';

comment on column PABYBH_CUSTINFO.ADDR is
'地址';

comment on column PABYBH_CUSTINFO.EMAIL is
'邮箱';

comment on column PABYBH_CUSTINFO.PHONE is
'联系方式';

comment on column PABYBH_CUSTINFO.MOBILE is
'手机号';

comment on column PABYBH_CUSTINFO.FAX is
'传真';

comment on column PABYBH_CUSTINFO.UPDATEDATE is
'更新日期';

comment on column PABYBH_CUSTINFO.UPDATETIME is
'更新时间';

comment on column PABYBH_CUSTINFO.CREATEDATE is
'创建日期';

comment on column PABYBH_CUSTINFO.CREATETIME is
'创建时间';

comment on column PABYBH_CUSTINFO.EXTFLD1 is
'扩展字段1';

comment on column PABYBH_CUSTINFO.EXTFLD2 is
'扩展字段2';

comment on column PABYBH_CUSTINFO.EXTFLD3 is
'扩展字段3';

--==============================================================
-- Table: PABYBH_DEPCHKINFO
--==============================================================
create table PABYBH_DEPCHKINFO (
   CHECKDATE            VARCHAR(8)             not null,
   TRANSDATE            VARCHAR(8)             not null,
   TRANSTIME            VARCHAR(6),
   TRANSFERTYPE         VARCHAR(1),
   ACCTNO               VARCHAR(32),
   STOCKCODE            VARCHAR(8)             not null,
   CAPITALACCTNO        VARCHAR(30)            not null,
   AMT                  DECIMAL(16,2),
   WORKSERIALNO         VARCHAR(30),
   IEPSERIALNO          VARCHAR(30)            not null,
   COBANKNO             VARCHAR(12)            not null,
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint PK_PABYBH_DEPCHKINFO primary key (CHECKDATE, IEPSERIALNO)

)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_DEPCHKINFO is
'平安银行存管对账明细表';

comment on column PABYBH_DEPCHKINFO.CHECKDATE is
'对账日期';

comment on column PABYBH_DEPCHKINFO.TRANSDATE is
'交易日期';

comment on column PABYBH_DEPCHKINFO.TRANSTIME is
'交易时间';

comment on column PABYBH_DEPCHKINFO.TRANSFERTYPE is
'资金类型''0--银转证1--证转银''      ';

comment on column PABYBH_DEPCHKINFO.ACCTNO is
'银行账号';

comment on column PABYBH_DEPCHKINFO.STOCKCODE is
'券商代码';

comment on column PABYBH_DEPCHKINFO.CAPITALACCTNO is
'证券资金台账号';

comment on column PABYBH_DEPCHKINFO.AMT is
'金额';

comment on column PABYBH_DEPCHKINFO.WORKSERIALNO is
'合作行流水号';

comment on column PABYBH_DEPCHKINFO.IEPSERIALNO is
'行E通流水号';

comment on column PABYBH_DEPCHKINFO.COBANKNO is
'合作行号';

comment on column PABYBH_DEPCHKINFO.EXTFLD1 is
'备用字段1';

comment on column PABYBH_DEPCHKINFO.EXTFLD2 is
'备用字段2';

--==============================================================
-- Index: K_PABYBH_DEPCHKINFO_1
--==============================================================
create index K_PABYBH_DEPCHKINFO_1 on PABYBH_DEPCHKINFO (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Table: PABYBH_DEPCHKINFO_HIS
--==============================================================
create table PABYBH_DEPCHKINFO_HIS (
   CHECKDATE            VARCHAR(8)             not null,
   TRANSDATE            VARCHAR(8)             not null,
   TRANSTIME            VARCHAR(6),
   TRANSFERTYPE         VARCHAR(1),
   ACCTNO               VARCHAR(32),
   STOCKCODE            VARCHAR(8)             not null,
   CAPITALACCTNO        VARCHAR(30)            not null,
   AMT                  DECIMAL(16,2),
   WORKSERIALNO         VARCHAR(30),
   IEPSERIALNO          VARCHAR(30)            not null,
   COBANKNO             VARCHAR(12)            not null,
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint PK_PABYBH_DEPCHKINFO_HIS primary key (CHECKDATE, 
IEPSERIALNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_DEPCHKINFO_HIS is
'平安银行存管对账明细表';

comment on column PABYBH_DEPCHKINFO_HIS.CHECKDATE is
'对账日期';

comment on column PABYBH_DEPCHKINFO_HIS.TRANSDATE is
'交易日期';

comment on column PABYBH_DEPCHKINFO_HIS.TRANSTIME is
'交易时间';

comment on column PABYBH_DEPCHKINFO_HIS.TRANSFERTYPE is
'资金类型''0--银转证1--证转银''      ';

comment on column PABYBH_DEPCHKINFO_HIS.ACCTNO is
'银行账号';

comment on column PABYBH_DEPCHKINFO_HIS.STOCKCODE is
'券商代码';

comment on column PABYBH_DEPCHKINFO_HIS.CAPITALACCTNO is
'证券资金台账号';

comment on column PABYBH_DEPCHKINFO_HIS.AMT is
'金额';

comment on column PABYBH_DEPCHKINFO_HIS.WORKSERIALNO is
'合作行流水号';

comment on column PABYBH_DEPCHKINFO_HIS.IEPSERIALNO is
'行E通流水号';

comment on column PABYBH_DEPCHKINFO_HIS.COBANKNO is
'合作行号';

comment on column PABYBH_DEPCHKINFO_HIS.EXTFLD1 is
'备用字段1';

comment on column PABYBH_DEPCHKINFO_HIS.EXTFLD2 is
'备用字段2';

--==============================================================
-- Index: K_PABYBH_DEPCHKINFO_2
--==============================================================
create index K_PABYBH_DEPCHKINFO_2 on PABYBH_DEPCHKINFO_HIS (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Table: PABYBH_HOSCHKINFO
--==============================================================
create table PABYBH_HOSCHKINFO (
   COBANKNO             VARCHAR(10)            not null,
   CHECKDATE            VARCHAR(8)             not null,
   WORKSERIALNO         VARCHAR(32)            not null,
   HOSTDATE             VARCHAR(8)             not null,
   HOSTSERIALNO         VARCHAR(32)            not null,
   HOSTBACKDATE         VARCHAR(8)             not null,
   HOSTBACKSERNO        VARCHAR(32)            not null,
   HOSTTRANSCODE        VARCHAR(16),
   ACCTNO               VARCHAR(32),
   TRANSAMT             DECIMAL(16,2),
   TRANSFARE            DECIMAL(16,2),
   CASHFLAG             VARCHAR(1),
   STAT                 VARCHAR(1),
   CDFLAG               VARCHAR(1),
   SVRTYPE              VARCHAR(10),
   REMARKCODE           VARCHAR(32),
   REMARK               VARCHAR(50),
   TRANSBRANCHNO        VARCHAR(10),
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(10),
   JOINCHKFLAG          VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PK_PABYBH_HOSCHKINFO primary key (HOSTDATE, HOSTSERIALNO)

)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_HOSCHKINFO is
'主机对账信息';

comment on column PABYBH_HOSCHKINFO.COBANKNO is
'合作行号';

comment on column PABYBH_HOSCHKINFO.CHECKDATE is
'对账日期';

comment on column PABYBH_HOSCHKINFO.WORKSERIALNO is
'平台业务流水号';

comment on column PABYBH_HOSCHKINFO.HOSTDATE is
'主机日期';

comment on column PABYBH_HOSCHKINFO.HOSTSERIALNO is
'主机流水号';

comment on column PABYBH_HOSCHKINFO.ACCTNO is
'银行账号';

comment on column PABYBH_HOSCHKINFO.TRANSAMT is
'交易金额';

comment on column PABYBH_HOSCHKINFO.TRANSFARE is
'手续费';

comment on column PABYBH_HOSCHKINFO.CASHFLAG is
'现转标志1-现金 2-转账';

comment on column PABYBH_HOSCHKINFO.STAT is
'交易状态0-正常 7-被冲正 8-被撤销 1-失败';

comment on column PABYBH_HOSCHKINFO.CDFLAG is
'借贷标志';

comment on column PABYBH_HOSCHKINFO.SVRTYPE is
'业务种类';

comment on column PABYBH_HOSCHKINFO.REMARKCODE is
'摘要码';

comment on column PABYBH_HOSCHKINFO.REMARK is
'摘要信息';

comment on column PABYBH_HOSCHKINFO.TRANSBRANCHNO is
'交易网点';

comment on column PABYBH_HOSCHKINFO.TRANSORG is
'交易机构';

comment on column PABYBH_HOSCHKINFO.TRANSOPER is
'交易柜员';

comment on column PABYBH_HOSCHKINFO.JOINCHKFLAG is
'参与对账标志，0-不参与，1-参与';

comment on column PABYBH_HOSCHKINFO.EXTFLD1 is
'备用字段1';

comment on column PABYBH_HOSCHKINFO.EXTFLD2 is
'备用字段2';

comment on column PABYBH_HOSCHKINFO.EXTFLD3 is
'备用字段3';

--==============================================================
-- Index: K_PABYBH_HOSCHKINFO_1
--==============================================================
create index K_PABYBH_HOSCHKINFO_1 on PABYBH_HOSCHKINFO (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Table: PABYBH_HOSCHKINFO_HIS
--==============================================================
create table PABYBH_HOSCHKINFO_HIS (
   COBANKNO             VARCHAR(10)            not null,
   CHECKDATE            VARCHAR(8)             not null,
   WORKSERIALNO         VARCHAR(32)            not null,
   HOSTDATE             VARCHAR(8)             not null,
   HOSTSERIALNO         VARCHAR(32)            not null,
   HOSTBACKDATE         VARCHAR(8)             not null,
   HOSTBACKSERNO        VARCHAR(32)            not null,
   HOSTTRANSCODE        VARCHAR(16),
   ACCTNO               VARCHAR(32),
   TRANSAMT             DECIMAL(16,2),
   TRANSFARE            DECIMAL(16,2),
   CASHFLAG             VARCHAR(1),
   STAT                 VARCHAR(1),
   CDFLAG               VARCHAR(1),
   SVRTYPE              VARCHAR(10),
   REMARKCODE           VARCHAR(32),
   REMARK               VARCHAR(50),
   TRANSBRANCHNO        VARCHAR(10),
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(10),
   JOINCHKFLAG          VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PK_PABYBH_HOSCHKINFO_HIS primary key (HOSTDATE, 
HOSTSERIALNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_HOSCHKINFO_HIS is
'主机对账信息';

comment on column PABYBH_HOSCHKINFO_HIS.COBANKNO is
'合作行号';

comment on column PABYBH_HOSCHKINFO_HIS.CHECKDATE is
'对账日期';

comment on column PABYBH_HOSCHKINFO_HIS.WORKSERIALNO is
'平台业务流水号';

comment on column PABYBH_HOSCHKINFO_HIS.HOSTDATE is
'主机日期';

comment on column PABYBH_HOSCHKINFO_HIS.HOSTSERIALNO is
'主机流水号';

comment on column PABYBH_HOSCHKINFO_HIS.ACCTNO is
'银行账号';

comment on column PABYBH_HOSCHKINFO_HIS.TRANSAMT is
'交易金额';

comment on column PABYBH_HOSCHKINFO_HIS.TRANSFARE is
'手续费';

comment on column PABYBH_HOSCHKINFO_HIS.CASHFLAG is
'现转标志1-现金 2-转账';

comment on column PABYBH_HOSCHKINFO_HIS.STAT is
'交易状态0-正常 7-被冲正 8-被撤销 1-失败';

comment on column PABYBH_HOSCHKINFO_HIS.CDFLAG is
'借贷标志';

comment on column PABYBH_HOSCHKINFO_HIS.SVRTYPE is
'业务种类';

comment on column PABYBH_HOSCHKINFO_HIS.REMARKCODE is
'摘要码';

comment on column PABYBH_HOSCHKINFO_HIS.REMARK is
'摘要信息';

comment on column PABYBH_HOSCHKINFO_HIS.TRANSBRANCHNO is
'交易网点';

comment on column PABYBH_HOSCHKINFO_HIS.TRANSORG is
'交易机构';

comment on column PABYBH_HOSCHKINFO_HIS.TRANSOPER is
'交易柜员';

comment on column PABYBH_HOSCHKINFO_HIS.JOINCHKFLAG is
'参与对账标志，0-不参与，1-参与';

comment on column PABYBH_HOSCHKINFO_HIS.EXTFLD1 is
'备用字段1';

comment on column PABYBH_HOSCHKINFO_HIS.EXTFLD2 is
'备用字段2';

comment on column PABYBH_HOSCHKINFO_HIS.EXTFLD3 is
'备用字段3';

--==============================================================
-- Index: K_PABYBH_HOSCHKINFO_2
--==============================================================
create index K_PABYBH_HOSCHKINFO_2 on PABYBH_HOSCHKINFO_HIS (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Table: PABYBH_NOTBAL
--==============================================================
create table PABYBH_NOTBAL (
   CHECKDATE            VARCHAR(8)             not null,
   COBANKNO             VARCHAR(12)            not null,
   SVRCODE              VARCHAR(4)             not null,
   TRANSFERTYPE         VARCHAR(1),
   STOCKCODE            VARCHAR(8),
   CAPITALACCTNO        VARCHAR(30),
   WORKSERIALNO         VARCHAR(30),
   BANKSTAT             VARCHAR(1),
   BANKACCTNO           VARCHAR(32),
   BANKAMT              DECIMAL(16,2),
   BANKTRANSCODE        VARCHAR(8),
   IEPSERIALNO          VARCHAR(30),
   IEPSTAT              VARCHAR(1),
   IEPACCTNO            VARCHAR(32),
   IEPAMT               DECIMAL(16,2),
   IEPTRANSCODE         VARCHAR(8),
   HOSTDATE             VARCHAR(8),
   HOSTSERIALNO         VARCHAR(30),
   HOSTSTAT             VARCHAR(1),
   HOSTACCTNO           VARCHAR(32),
   HOSTAMT              DECIMAL(16,2),
   HOSTTRANSCODE        VARCHAR(8),
   CHECKSTAT            VARCHAR(1),
   ADJUSTSTAT           VARCHAR(1),
   ADJUSTTRANSORG       VARCHAR(10),
   ADJUSTTRANSOPER      VARCHAR(10),
   ADJUSTDATE           VARCHAR(8),
   ADJUSTSERIALNO       VARCHAR(32),
   ADJUSTHOSTBSIDATE    VARCHAR(8),
   ADJUSTHOSTSERIALNO   VARCHAR(32),
   ADJUSTRESPCODE       VARCHAR(10),
   ADJUSTRESPMSG        VARCHAR(120),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_NOTBAL is
'对账不平明细';

comment on column PABYBH_NOTBAL.CHECKDATE is
'对账日期';

comment on column PABYBH_NOTBAL.COBANKNO is
'合作行号';

comment on column PABYBH_NOTBAL.SVRCODE is
'服务代码';

comment on column PABYBH_NOTBAL.TRANSFERTYPE is
'资金类型''0--出金，银转证1--证转银，入金''';

comment on column PABYBH_NOTBAL.STOCKCODE is
'券商代码';

comment on column PABYBH_NOTBAL.CAPITALACCTNO is
'证券资金台账号';

comment on column PABYBH_NOTBAL.WORKSERIALNO is
'合作行流水号';

comment on column PABYBH_NOTBAL.BANKSTAT is
'合作行状态';

comment on column PABYBH_NOTBAL.BANKACCTNO is
'平台银行账号';

comment on column PABYBH_NOTBAL.BANKAMT is
'平台交易金额';

comment on column PABYBH_NOTBAL.BANKTRANSCODE is
'平台交易代码';

comment on column PABYBH_NOTBAL.IEPSERIALNO is
'行E通流水号';

comment on column PABYBH_NOTBAL.IEPSTAT is
'行E通状态';

comment on column PABYBH_NOTBAL.IEPACCTNO is
'行E通银行账号';

comment on column PABYBH_NOTBAL.IEPAMT is
'行E通交易金额';

comment on column PABYBH_NOTBAL.IEPTRANSCODE is
'行E通交易代码';

comment on column PABYBH_NOTBAL.HOSTDATE is
'主机日期';

comment on column PABYBH_NOTBAL.HOSTSERIALNO is
'主机流水号';

comment on column PABYBH_NOTBAL.HOSTSTAT is
'主机状态';

comment on column PABYBH_NOTBAL.HOSTACCTNO is
'主机银行账号';

comment on column PABYBH_NOTBAL.HOSTAMT is
'主机交易金额';

comment on column PABYBH_NOTBAL.HOSTTRANSCODE is
'主机交易代码';

comment on column PABYBH_NOTBAL.CHECKSTAT is
'对账结果标志,0-未对账1-已对平2-平安多3-核心多  4-账号不符 5-金额不符 6-状态不符 ';

comment on column PABYBH_NOTBAL.ADJUSTSTAT is
'调账状态 0-成功 1-失败 7-超时 9-初始 ';

comment on column PABYBH_NOTBAL.ADJUSTTRANSORG is
'调账交易机构';

comment on column PABYBH_NOTBAL.ADJUSTTRANSOPER is
'调账交易柜员';

comment on column PABYBH_NOTBAL.ADJUSTDATE is
'调账日期';

comment on column PABYBH_NOTBAL.ADJUSTSERIALNO is
'调账业务流水号';

comment on column PABYBH_NOTBAL.ADJUSTHOSTBSIDATE is
'调账主机账务日期';

comment on column PABYBH_NOTBAL.ADJUSTHOSTSERIALNO is
'调账主机流水号';

comment on column PABYBH_NOTBAL.ADJUSTRESPCODE is
'调账响应码';

comment on column PABYBH_NOTBAL.ADJUSTRESPMSG is
'调账响应信息';

comment on column PABYBH_NOTBAL.EXTFLD1 is
'备用字段1';

comment on column PABYBH_NOTBAL.EXTFLD2 is
'备用字段2';

--==============================================================
-- Index: K_PABYBH_NOTBAL_1
--==============================================================
create index K_PABYBH_NOTBAL_1 on PABYBH_NOTBAL (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   SVRCODE              ASC
);

--==============================================================
-- Table: PABYBH_NOTBAL_HIS
--==============================================================
create table PABYBH_NOTBAL_HIS (
   CHECKDATE            VARCHAR(8)             not null,
   COBANKNO             VARCHAR(12)            not null,
   SVRCODE              VARCHAR(4)             not null,
   TRANSFERTYPE         VARCHAR(1),
   STOCKCODE            VARCHAR(8),
   CAPITALACCTNO        VARCHAR(30),
   WORKSERIALNO         VARCHAR(30),
   BANKSTAT             VARCHAR(1),
   BANKACCTNO           VARCHAR(32),
   BANKAMT              DECIMAL(16,2),
   BANKTRANSCODE        VARCHAR(8),
   IEPSERIALNO          VARCHAR(30),
   IEPSTAT              VARCHAR(1),
   IEPACCTNO            VARCHAR(32),
   IEPAMT               DECIMAL(16,2),
   IEPTRANSCODE         VARCHAR(8),
   HOSTDATE             VARCHAR(8),
   HOSTSERIALNO         VARCHAR(30),
   HOSTSTAT             VARCHAR(1),
   HOSTACCTNO           VARCHAR(32),
   HOSTAMT              DECIMAL(16,2),
   HOSTTRANSCODE        VARCHAR(8),
   CHECKSTAT            VARCHAR(1),
   ADJUSTSTAT           VARCHAR(1),
   ADJUSTTRANSORG       VARCHAR(10),
   ADJUSTTRANSOPER      VARCHAR(10),
   ADJUSTDATE           VARCHAR(8),
   ADJUSTSERIALNO       VARCHAR(32),
   ADJUSTHOSTBSIDATE    VARCHAR(8),
   ADJUSTHOSTSERIALNO   VARCHAR(32),
   ADJUSTRESPCODE       VARCHAR(10),
   ADJUSTRESPMSG        VARCHAR(120),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_NOTBAL_HIS is
'对账不平明细';

comment on column PABYBH_NOTBAL_HIS.CHECKDATE is
'对账日期';

comment on column PABYBH_NOTBAL_HIS.COBANKNO is
'合作行号';

comment on column PABYBH_NOTBAL_HIS.SVRCODE is
'服务代码';

comment on column PABYBH_NOTBAL_HIS.TRANSFERTYPE is
'资金类型''0--出金，银转证1--证转银，入金''';

comment on column PABYBH_NOTBAL_HIS.STOCKCODE is
'券商代码';

comment on column PABYBH_NOTBAL_HIS.CAPITALACCTNO is
'证券资金台账号';

comment on column PABYBH_NOTBAL_HIS.WORKSERIALNO is
'合作行流水号';

comment on column PABYBH_NOTBAL_HIS.BANKSTAT is
'合作行状态';

comment on column PABYBH_NOTBAL_HIS.BANKACCTNO is
'平台银行账号';

comment on column PABYBH_NOTBAL_HIS.BANKAMT is
'平台交易金额';

comment on column PABYBH_NOTBAL_HIS.BANKTRANSCODE is
'平台交易代码';

comment on column PABYBH_NOTBAL_HIS.IEPSERIALNO is
'行E通流水号';

comment on column PABYBH_NOTBAL_HIS.IEPSTAT is
'行E通状态';

comment on column PABYBH_NOTBAL_HIS.IEPACCTNO is
'行E通银行账号';

comment on column PABYBH_NOTBAL_HIS.IEPAMT is
'行E通交易金额';

comment on column PABYBH_NOTBAL_HIS.IEPTRANSCODE is
'行E通交易代码';

comment on column PABYBH_NOTBAL_HIS.HOSTDATE is
'主机日期';

comment on column PABYBH_NOTBAL_HIS.HOSTSERIALNO is
'主机流水号';

comment on column PABYBH_NOTBAL_HIS.HOSTSTAT is
'主机状态';

comment on column PABYBH_NOTBAL_HIS.HOSTACCTNO is
'主机银行账号';

comment on column PABYBH_NOTBAL_HIS.HOSTAMT is
'主机交易金额';

comment on column PABYBH_NOTBAL_HIS.HOSTTRANSCODE is
'主机交易代码';

comment on column PABYBH_NOTBAL_HIS.CHECKSTAT is
'对账结果标志,0-未对账1-已对平2-平安多3-核心多  4-账号不符 5-金额不符 6-状态不符 ';

comment on column PABYBH_NOTBAL_HIS.ADJUSTSTAT is
'调账状态 0-成功 1-失败 7-超时 9-初始 ';

comment on column PABYBH_NOTBAL_HIS.ADJUSTTRANSORG is
'调账交易机构';

comment on column PABYBH_NOTBAL_HIS.ADJUSTTRANSOPER is
'调账交易柜员';

comment on column PABYBH_NOTBAL_HIS.ADJUSTDATE is
'调账日期';

comment on column PABYBH_NOTBAL_HIS.ADJUSTSERIALNO is
'调账业务流水号';

comment on column PABYBH_NOTBAL_HIS.ADJUSTHOSTBSIDATE is
'调账主机账务日期';

comment on column PABYBH_NOTBAL_HIS.ADJUSTHOSTSERIALNO is
'调账主机流水号';

comment on column PABYBH_NOTBAL_HIS.ADJUSTRESPCODE is
'调账响应码';

comment on column PABYBH_NOTBAL_HIS.ADJUSTRESPMSG is
'调账响应信息';

comment on column PABYBH_NOTBAL_HIS.EXTFLD1 is
'备用字段1';

comment on column PABYBH_NOTBAL_HIS.EXTFLD2 is
'备用字段2';

--==============================================================
-- Index: K_PABYBH_NOTBAL_2
--==============================================================
create index K_PABYBH_NOTBAL_2 on PABYBH_NOTBAL_HIS (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   SVRCODE              ASC
);

--==============================================================
-- Table: PABYBH_ORGCFG
--==============================================================
create table PABYBH_ORGCFG (
   COBANKNO             VARCHAR(12)            not null,
   COBANKNAME           VARCHAR(100),
   CUSTMANAGERNO        VARCHAR(10),
   ACCT                 VARCHAR(32),
   ACCTNAME             VARCHAR(60),
   ACCT1                VARCHAR(32),
   ACCT1NAME            VARCHAR(60),
   ACCT2                VARCHAR(32),
   ACCT2NAME            VARCHAR(60),
   ACCT3                VARCHAR(32),
   ACCT3NAME            VARCHAR(60),
   ACCT4                VARCHAR(32),
   ACCT4NAME            VARCHAR(60),
   SIGNSTATUS           VARCHAR(1)             not null,
   AREACODE             VARCHAR(20),
   COORGNO              VARCHAR(20),
   WORKDATE             VARCHAR(8)             not null,
   WORKSERIALNO         VARCHAR(32),
   MAINTAINDATE         VARCHAR(8),
   MAINTAINTIME         VARCHAR(6),
   EXTFLD1              VARCHAR(64),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   EXTFLD4              VARCHAR(64),
   EXTFLD5              VARCHAR(255),
   EXTFLD6              VARCHAR(255),
   constraint PK_PABYBH_ORGCFG primary key (COBANKNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_ORGCFG is
'清算机构信息';

comment on column PABYBH_ORGCFG.COBANKNO is
'合作行号';

comment on column PABYBH_ORGCFG.COBANKNAME is
'合作行名称';

comment on column PABYBH_ORGCFG.CUSTMANAGERNO is
'虚拟客户经理号';

comment on column PABYBH_ORGCFG.ACCT is
'头寸账号';

comment on column PABYBH_ORGCFG.ACCTNAME is
'头寸账户名称';

comment on column PABYBH_ORGCFG.ACCT1 is
'内部清算过渡户1';

comment on column PABYBH_ORGCFG.ACCT1NAME is
'内部清算过渡户名称1';

comment on column PABYBH_ORGCFG.ACCT2 is
'内部清算过渡户2';

comment on column PABYBH_ORGCFG.ACCT2NAME is
'内部清算过渡户名称2';

comment on column PABYBH_ORGCFG.ACCT3 is
'内部清算过渡户3';

comment on column PABYBH_ORGCFG.ACCT3NAME is
'内部清算过渡户名称3';

comment on column PABYBH_ORGCFG.ACCT4 is
'内部清算过渡户4';

comment on column PABYBH_ORGCFG.ACCT4NAME is
'内部清算过渡户名称4';

comment on column PABYBH_ORGCFG.SIGNSTATUS is
'签到状态0-签到 1-签退';

comment on column PABYBH_ORGCFG.AREACODE is
'地区代码';

comment on column PABYBH_ORGCFG.COORGNO is
'合作行机构号';

comment on column PABYBH_ORGCFG.WORKDATE is
'业务日期';

comment on column PABYBH_ORGCFG.WORKSERIALNO is
'业务流水号';

comment on column PABYBH_ORGCFG.MAINTAINDATE is
'维护日期';

comment on column PABYBH_ORGCFG.MAINTAINTIME is
'维护时间';

comment on column PABYBH_ORGCFG.EXTFLD1 is
'备用字段1';

comment on column PABYBH_ORGCFG.EXTFLD2 is
'备用字段2';

comment on column PABYBH_ORGCFG.EXTFLD3 is
'备用字段3';

comment on column PABYBH_ORGCFG.EXTFLD4 is
'备用字段4';

comment on column PABYBH_ORGCFG.EXTFLD5 is
'备用字段5';

comment on column PABYBH_ORGCFG.EXTFLD6 is
'备用字段6';

--==============================================================
-- Table: PABYBH_PABTRANSCTL
--==============================================================
create table PABYBH_PABTRANSCTL (
   TRANSCODE            VARCHAR(10)            not null,
   TRANSNAME            VARCHAR(100)           not null,
   SVRCODE              VARCHAR(6)             not null,
   MACFLAG              VARCHAR(1)             not null,
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(32),
   EXTFLD3              VARCHAR(32),
   constraint PK_PABYBH_PABTRANSCTL primary key (TRANSCODE, SVRCODE)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_PABTRANSCTL is
'平安交易码控制';

comment on column PABYBH_PABTRANSCTL.TRANSCODE is
'交易代码';

comment on column PABYBH_PABTRANSCTL.TRANSNAME is
'交易名称';

comment on column PABYBH_PABTRANSCTL.SVRCODE is
'服务代码';

comment on column PABYBH_PABTRANSCTL.MACFLAG is
'MAC校验标志''1--开0--关''';

comment on column PABYBH_PABTRANSCTL.EXTFLD1 is
'备用字段1';

comment on column PABYBH_PABTRANSCTL.EXTFLD2 is
'备用字段2';

comment on column PABYBH_PABTRANSCTL.EXTFLD3 is
'备用字段3';

--==============================================================
-- Table: PABYBH_SECKEY
--==============================================================
create table PABYBH_SECKEY (
   COBANKNO             VARCHAR(12)            not null,
   ENCRYPTIP            VARCHAR(32),
   ENCRYPTPORT          VARCHAR(32),
   ENCRYPTSYSID         VARCHAR(32),
   ENCRYPTEXTID         VARCHAR(32),
   ZMK                  VARCHAR(255),
   ZAK                  VARCHAR(255)           not null,
   IEPZPK               VARCHAR(255)           not null,
   COUNTERZPK           VARCHAR(255),
   HOSTZPK              VARCHAR(255),
   EXTFLD1              VARCHAR(64),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(255),
   EXTFLD4              VARCHAR(255),
   constraint PK_PABYBH_SECKEY primary key (COBANKNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_SECKEY is
'秘钥信息';

comment on column PABYBH_SECKEY.COBANKNO is
'合作行号';

comment on column PABYBH_SECKEY.ENCRYPTIP is
'加密平台地址';

comment on column PABYBH_SECKEY.ENCRYPTPORT is
'加密平台端口';

comment on column PABYBH_SECKEY.ENCRYPTSYSID is
'加密平台系统ID';

comment on column PABYBH_SECKEY.ENCRYPTEXTID is
'加密平台外部ID';

comment on column PABYBH_SECKEY.ZMK is
'ZMK';

comment on column PABYBH_SECKEY.ZAK is
'ZAK';

comment on column PABYBH_SECKEY.IEPZPK is
'ZPK 平安';

comment on column PABYBH_SECKEY.COUNTERZPK is
'ZPK 柜面';

comment on column PABYBH_SECKEY.HOSTZPK is
'ZPK 核心组';

comment on column PABYBH_SECKEY.EXTFLD1 is
'扩展1';

comment on column PABYBH_SECKEY.EXTFLD2 is
'扩展2';

comment on column PABYBH_SECKEY.EXTFLD3 is
'扩展3';

comment on column PABYBH_SECKEY.EXTFLD4 is
'扩展4';

--==============================================================
-- Table: PABYBH_SERIAL
--==============================================================
create table PABYBH_SERIAL (
   TRANSDATE            VARCHAR(8)             not null,
   TRANSSERIALNO        VARCHAR(40)            not null,
   ORITRANSDATE         VARCHAR(8),
   ORITRANSSERIALNO     VARCHAR(40),
   TRANSTIME            VARCHAR(8)             not null,
   WORKDATE             VARCHAR(8)             not null,
   WORKSERIALNO         VARCHAR(40)            not null,
   REQDATE              VARCHAR(8)             not null,
   REQSERIALNO          VARCHAR(40)            not null,
   CLUSTERNODENAME      VARCHAR(30),
   CLUSTERNODEIP        VARCHAR(20),
   COBANKNO             VARCHAR(12)            not null,
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(10),
   AUTHORG              VARCHAR(10),
   AUTHOPER             VARCHAR(10),
   CNLTYPE              VARCHAR(5),
   TERMEQUINO           VARCHAR(20),
   TRANSCODE            VARCHAR(12),
   TRANSCODE1           VARCHAR(1),
   CUACOUNTYPE          VARCHAR(1),
   TRANSNAME            VARCHAR(100),
   CAPITALTYPE          VARCHAR(1),
   SVRCODE              VARCHAR(10),
   CUSTNAME             VARCHAR(80),
   CUSTTYPE             VARCHAR(2),
   ACCTNO               VARCHAR(32),
   ORIACCTNO            VARCHAR(32),
   ACCTNO2              VARCHAR(32),
   STOCKCODE            VARCHAR(8),
   CAPITALACCTNO        VARCHAR(32),
   TRANSAMT             DECIMAL(16,2),
   ORITRANSAMT          DECIMAL(16,2),
   AMT2                 DECIMAL(16,2),
   AMT3                 DECIMAL(16,2),
   CURR                 VARCHAR(3),
   CASHFLAG             VARCHAR(1),
   IEPSVRCODE           VARCHAR(8),
   IEPTRANSCODE         VARCHAR(16),
   IEPBSIDATE           VARCHAR(8),
   IEPTRADATE           VARCHAR(8),
   IEPSERIALNO          VARCHAR(32),
   ORIIEPBSIDATE        VARCHAR(8),
   ORIIEPSERIALNO       VARCHAR(32),
   IEPRESPCODE          VARCHAR(12),
   IEPRESPMSG           VARCHAR(120),
   HOSTBSIDATE          VARCHAR(8),
   HOSTSERIALNO         VARCHAR(32),
   HOSTTRANSCODE        VARCHAR(16),
   HOSTRESPCODE         VARCHAR(12),
   HOSTRESPMSG          VARCHAR(120),
   RESPCODE             VARCHAR(10),
   RESPMSG              VARCHAR(120),
   IEPSTAT              VARCHAR(1),
   HOSTSTAT             VARCHAR(1),
   STAT                 VARCHAR(1),
   ORISTAT              VARCHAR(1),
   CERTTYPE             VARCHAR(2),
   CERTNO               VARCHAR(32),
   PHONE                VARCHAR(20),
   AGENTNAME            VARCHAR(80),
   AGENTCERTY           VARCHAR(2),
   AGENTCERNO           VARCHAR(32),
   AGENTPHONE           VARCHAR(20),
   CHKFLAG              VARCHAR(1),
   MEMO                 VARCHAR(128),
   EXTFLD1              VARCHAR(64),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(128),
   EXTFLD4              VARCHAR(128),
   constraint PK_PABYBH_SERIAL primary key (TRANSDATE, TRANSSERIALNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_SERIAL is
'当日流水表';

comment on column PABYBH_SERIAL.TRANSDATE is
'交易日期';

comment on column PABYBH_SERIAL.TRANSSERIALNO is
'交易流水号';

comment on column PABYBH_SERIAL.ORITRANSDATE is
'原交易日期';

comment on column PABYBH_SERIAL.ORITRANSSERIALNO is
'原交易流水号';

comment on column PABYBH_SERIAL.TRANSTIME is
'交易时间';

comment on column PABYBH_SERIAL.WORKDATE is
'业务日期';

comment on column PABYBH_SERIAL.WORKSERIALNO is
'业务流水号';

comment on column PABYBH_SERIAL.REQDATE is
'发起方日期';

comment on column PABYBH_SERIAL.REQSERIALNO is
'发起方流水号 Y-中心发起 G-行内柜面发起 T-管理台发起';

comment on column PABYBH_SERIAL.CLUSTERNODENAME is
'集群服务器名称';

comment on column PABYBH_SERIAL.CLUSTERNODEIP is
'集群服务器IP';

comment on column PABYBH_SERIAL.COBANKNO is
'合作行号';

comment on column PABYBH_SERIAL.TRANSORG is
'交易机构';

comment on column PABYBH_SERIAL.TRANSOPER is
'交易柜员';

comment on column PABYBH_SERIAL.AUTHORG is
'授权机构';

comment on column PABYBH_SERIAL.AUTHOPER is
'授权柜员';

comment on column PABYBH_SERIAL.CNLTYPE is
'渠道类型 403-平安中心 200-管理台 201-柜面';

comment on column PABYBH_SERIAL.TERMEQUINO is
'终端设备编号';

comment on column PABYBH_SERIAL.TRANSCODE is
'交易代码';

comment on column PABYBH_SERIAL.TRANSCODE1 is
'附加交易代码  944302-（0 出金 1 入金 2开户手续费 3 补打工本费）
944316-（对账步点）';

comment on column PABYBH_SERIAL.CUACOUNTYPE is
'来往账标志 0-往账 1-来账';

comment on column PABYBH_SERIAL.TRANSNAME is
'交易名称';

comment on column PABYBH_SERIAL.CAPITALTYPE is
'资金类型,0 ---转出1--- 转入';

comment on column PABYBH_SERIAL.CUSTNAME is
'客户名称';

comment on column PABYBH_SERIAL.CUSTTYPE is
'客户类型 00-机构 01-个人';

comment on column PABYBH_SERIAL.ACCTNO is
'银行账号';

comment on column PABYBH_SERIAL.ORIACCTNO is
'用于中心对账保存原银行账号';

comment on column PABYBH_SERIAL.ACCTNO2 is
'帐号2   变更后的账户';

comment on column PABYBH_SERIAL.STOCKCODE is
'券商代码';

comment on column PABYBH_SERIAL.CAPITALACCTNO is
'资金帐号';

comment on column PABYBH_SERIAL.TRANSAMT is
'交易金额';

comment on column PABYBH_SERIAL.ORITRANSAMT is
'用于中心对账保存原交易金额';

comment on column PABYBH_SERIAL.AMT2 is
'金额2';

comment on column PABYBH_SERIAL.AMT3 is
'金额3';

comment on column PABYBH_SERIAL.CURR is
'币种';

comment on column PABYBH_SERIAL.CASHFLAG is
'钞汇标识';

comment on column PABYBH_SERIAL.IEPSVRCODE is
'行E通服务代码';

comment on column PABYBH_SERIAL.IEPTRANSCODE is
'行E通交易代码';

comment on column PABYBH_SERIAL.IEPBSIDATE is
'行E通业务日期';

comment on column PABYBH_SERIAL.IEPTRADATE is
'行E通交易日期';

comment on column PABYBH_SERIAL.IEPSERIALNO is
'行E通流水号';

comment on column PABYBH_SERIAL.ORIIEPBSIDATE is
'原行E通业务日期';

comment on column PABYBH_SERIAL.ORIIEPSERIALNO is
'原行E通流水号';

comment on column PABYBH_SERIAL.IEPRESPCODE is
'行E通响应代码';

comment on column PABYBH_SERIAL.IEPRESPMSG is
'行E通响应信息';

comment on column PABYBH_SERIAL.HOSTBSIDATE is
'主机账务日期';

comment on column PABYBH_SERIAL.HOSTSERIALNO is
'主机流水号';

comment on column PABYBH_SERIAL.HOSTTRANSCODE is
'主机交易代码';

comment on column PABYBH_SERIAL.HOSTRESPCODE is
'主机响应代码';

comment on column PABYBH_SERIAL.HOSTRESPMSG is
'主机响应信息';

comment on column PABYBH_SERIAL.RESPCODE is
'响应码';

comment on column PABYBH_SERIAL.RESPMSG is
'响应信息';

comment on column PABYBH_SERIAL.IEPSTAT is
'中心交易状态''0成功 1失败 6状态未知 7被冲正 8被撤销 9初始''';

comment on column PABYBH_SERIAL.HOSTSTAT is
'核心交易状态''0成功 1失败 6状态未知 7被冲正 8被撤销 9初始''';

comment on column PABYBH_SERIAL.STAT is
'交易状态''0成功 1失败 6状态未知 7被冲正 8被撤销 9初始''';

comment on column PABYBH_SERIAL.ORISTAT is
'用于中心对账保存原交易状态 ''0成功 1失败 6状态未知 7被冲正 8被撤销 9初始 X源流水不存在''';

comment on column PABYBH_SERIAL.CERTTYPE is
'证件类型';

comment on column PABYBH_SERIAL.CERTNO is
'证件号码';

comment on column PABYBH_SERIAL.CHKFLAG is
'对账标志,0-未对账1-已对平2-平安多3-核心多 X-平安已对账 ';

comment on column PABYBH_SERIAL.MEMO is
'备注';

comment on column PABYBH_SERIAL.EXTFLD1 is
'备用字段1 ';

comment on column PABYBH_SERIAL.EXTFLD2 is
'备用字段2';

comment on column PABYBH_SERIAL.EXTFLD3 is
'备用字段3';

comment on column PABYBH_SERIAL.EXTFLD4 is
'备用字段4';

--==============================================================
-- Index: K_PABYBH_SERIAL_1
--==============================================================
create unique index K_PABYBH_SERIAL_1 on PABYBH_SERIAL (
   REQSERIALNO          ASC
);

--==============================================================
-- Index: K_PABYBH_SERIAL_2
--==============================================================
create unique index K_PABYBH_SERIAL_2 on PABYBH_SERIAL (
   WORKDATE             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Index: K_PABYBH_SERIAL_3
--==============================================================
create index K_PABYBH_SERIAL_3 on PABYBH_SERIAL (
   WORKDATE             ASC,
   COBANKNO             ASC,
   SVRCODE              ASC,
   TRANSCODE            ASC
);

--==============================================================
-- Table: PABYBH_SERIAL_HIS
--==============================================================
create table PABYBH_SERIAL_HIS (
   TRANSDATE            VARCHAR(8)             not null,
   TRANSSERIALNO        VARCHAR(40)            not null,
   ORITRANSDATE         VARCHAR(8),
   ORITRANSSERIALNO     VARCHAR(40),
   TRANSTIME            VARCHAR(8)             not null,
   WORKDATE             VARCHAR(8)             not null,
   WORKSERIALNO         VARCHAR(40)            not null,
   REQDATE              VARCHAR(8)             not null,
   REQSERIALNO          VARCHAR(40)            not null,
   CLUSTERNODENAME      VARCHAR(30),
   CLUSTERNODEIP        VARCHAR(20),
   COBANKNO             VARCHAR(12)            not null,
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(10),
   AUTHORG              VARCHAR(10),
   AUTHOPER             VARCHAR(10),
   CNLTYPE              VARCHAR(5),
   TERMEQUINO           VARCHAR(20),
   TRANSCODE            VARCHAR(12),
   TRANSCODE1           VARCHAR(1),
   CUACOUNTYPE          VARCHAR(1),
   TRANSNAME            VARCHAR(100),
   CAPITALTYPE          VARCHAR(1),
   SVRCODE              VARCHAR(10),
   CUSTNAME             VARCHAR(80),
   CUSTTYPE             VARCHAR(2),
   ACCTNO               VARCHAR(32),
   ORIACCTNO            VARCHAR(32),
   ACCTNO2              VARCHAR(32),
   STOCKCODE            VARCHAR(8),
   CAPITALACCTNO        VARCHAR(32),
   TRANSAMT             DECIMAL(16,2),
   ORITRANSAMT          DECIMAL(16,2),
   AMT2                 DECIMAL(16,2),
   AMT3                 DECIMAL(16,2),
   CURR                 VARCHAR(3),
   CASHFLAG             VARCHAR(1),
   IEPSVRCODE           VARCHAR(8),
   IEPTRANSCODE         VARCHAR(16),
   IEPBSIDATE           VARCHAR(8),
   IEPTRADATE           VARCHAR(8),
   IEPSERIALNO          VARCHAR(32),
   ORIIEPBSIDATE        VARCHAR(8),
   ORIIEPSERIALNO       VARCHAR(32),
   IEPRESPCODE          VARCHAR(12),
   IEPRESPMSG           VARCHAR(120),
   HOSTBSIDATE          VARCHAR(8),
   HOSTSERIALNO         VARCHAR(32),
   HOSTTRANSCODE        VARCHAR(16),
   HOSTRESPCODE         VARCHAR(12),
   HOSTRESPMSG          VARCHAR(120),
   RESPCODE             VARCHAR(10),
   RESPMSG              VARCHAR(120),
   IEPSTAT              VARCHAR(1),
   HOSTSTAT             VARCHAR(1),
   STAT                 VARCHAR(1),
   ORISTAT              VARCHAR(1),
   CERTTYPE             VARCHAR(2),
   CERTNO               VARCHAR(32),
   PHONE                VARCHAR(20),
   AGENTNAME            VARCHAR(80),
   AGENTCERTY           VARCHAR(2),
   AGENTCERNO           VARCHAR(32),
   AGENTPHONE           VARCHAR(20),
   CHKFLAG              VARCHAR(1),
   MEMO                 VARCHAR(128),
   EXTFLD1              VARCHAR(64),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(128),
   EXTFLD4              VARCHAR(128),
   constraint PK_PABYBH_SERIAL_HIS primary key (TRANSDATE, 
TRANSSERIALNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_SERIAL_HIS is
'当日流水表';

comment on column PABYBH_SERIAL_HIS.TRANSDATE is
'交易日期';

comment on column PABYBH_SERIAL_HIS.TRANSSERIALNO is
'交易流水号';

comment on column PABYBH_SERIAL_HIS.ORITRANSDATE is
'原交易日期';

comment on column PABYBH_SERIAL_HIS.ORITRANSSERIALNO is
'原交易流水号';

comment on column PABYBH_SERIAL_HIS.TRANSTIME is
'交易时间';

comment on column PABYBH_SERIAL_HIS.WORKDATE is
'业务日期';

comment on column PABYBH_SERIAL_HIS.WORKSERIALNO is
'业务流水号';

comment on column PABYBH_SERIAL_HIS.REQDATE is
'发起方日期';

comment on column PABYBH_SERIAL_HIS.REQSERIALNO is
'发起方流水号 Y-中心发起 G-行内柜面发起 T-管理台发起';

comment on column PABYBH_SERIAL_HIS.CLUSTERNODENAME is
'集群服务器名称';

comment on column PABYBH_SERIAL_HIS.CLUSTERNODEIP is
'集群服务器IP';

comment on column PABYBH_SERIAL_HIS.COBANKNO is
'合作行号';

comment on column PABYBH_SERIAL_HIS.TRANSORG is
'交易机构';

comment on column PABYBH_SERIAL_HIS.TRANSOPER is
'交易柜员';

comment on column PABYBH_SERIAL_HIS.AUTHORG is
'授权机构';

comment on column PABYBH_SERIAL_HIS.AUTHOPER is
'授权柜员';

comment on column PABYBH_SERIAL_HIS.CNLTYPE is
'渠道类型 403-平安中心 200-管理台 201-柜面';

comment on column PABYBH_SERIAL_HIS.TERMEQUINO is
'终端设备编号';

comment on column PABYBH_SERIAL_HIS.TRANSCODE is
'交易代码';

comment on column PABYBH_SERIAL_HIS.TRANSCODE1 is
'附加交易代码  944302-（0 出金 1 入金 2开户手续费 3 补打工本费）
944316-（对账步点）';

comment on column PABYBH_SERIAL_HIS.CUACOUNTYPE is
'来往账标志 0-往账 1-来账';

comment on column PABYBH_SERIAL_HIS.TRANSNAME is
'交易名称';

comment on column PABYBH_SERIAL_HIS.CAPITALTYPE is
'资金类型,0 ---转出1--- 转入';

comment on column PABYBH_SERIAL_HIS.CUSTNAME is
'客户名称';

comment on column PABYBH_SERIAL_HIS.CUSTTYPE is
'客户类型 00-机构 01-个人';

comment on column PABYBH_SERIAL_HIS.ACCTNO is
'银行账号';

comment on column PABYBH_SERIAL_HIS.ORIACCTNO is
'用于中心对账保存原银行账号';

comment on column PABYBH_SERIAL_HIS.ACCTNO2 is
'帐号2   变更后的账户';

comment on column PABYBH_SERIAL_HIS.STOCKCODE is
'券商代码';

comment on column PABYBH_SERIAL_HIS.CAPITALACCTNO is
'资金帐号';

comment on column PABYBH_SERIAL_HIS.TRANSAMT is
'交易金额';

comment on column PABYBH_SERIAL_HIS.ORITRANSAMT is
'用于中心对账保存原交易金额';

comment on column PABYBH_SERIAL_HIS.AMT2 is
'金额2';

comment on column PABYBH_SERIAL_HIS.AMT3 is
'金额3';

comment on column PABYBH_SERIAL_HIS.CURR is
'币种';

comment on column PABYBH_SERIAL_HIS.CASHFLAG is
'钞汇标识';

comment on column PABYBH_SERIAL_HIS.IEPSVRCODE is
'行E通服务代码';

comment on column PABYBH_SERIAL_HIS.IEPTRANSCODE is
'行E通交易代码';

comment on column PABYBH_SERIAL_HIS.IEPBSIDATE is
'行E通业务日期';

comment on column PABYBH_SERIAL_HIS.IEPTRADATE is
'行E通交易日期';

comment on column PABYBH_SERIAL_HIS.IEPSERIALNO is
'行E通流水号';

comment on column PABYBH_SERIAL_HIS.ORIIEPBSIDATE is
'原行E通业务日期';

comment on column PABYBH_SERIAL_HIS.ORIIEPSERIALNO is
'原行E通流水号';

comment on column PABYBH_SERIAL_HIS.IEPRESPCODE is
'行E通响应代码';

comment on column PABYBH_SERIAL_HIS.IEPRESPMSG is
'行E通响应信息';

comment on column PABYBH_SERIAL_HIS.HOSTBSIDATE is
'主机账务日期';

comment on column PABYBH_SERIAL_HIS.HOSTSERIALNO is
'主机流水号';

comment on column PABYBH_SERIAL_HIS.HOSTTRANSCODE is
'主机交易代码';

comment on column PABYBH_SERIAL_HIS.HOSTRESPCODE is
'主机响应代码';

comment on column PABYBH_SERIAL_HIS.HOSTRESPMSG is
'主机响应信息';

comment on column PABYBH_SERIAL_HIS.RESPCODE is
'响应码';

comment on column PABYBH_SERIAL_HIS.RESPMSG is
'响应信息';

comment on column PABYBH_SERIAL_HIS.IEPSTAT is
'中心交易状态''0成功 1失败 6状态未知 7被冲正 8被撤销 9初始''';

comment on column PABYBH_SERIAL_HIS.HOSTSTAT is
'核心交易状态''0成功 1失败 6状态未知 7被冲正 8被撤销 9初始''';

comment on column PABYBH_SERIAL_HIS.STAT is
'交易状态''0成功 1失败 6状态未知 7被冲正 8被撤销 9初始''';

comment on column PABYBH_SERIAL_HIS.ORISTAT is
'用于中心对账保存原交易状态 ''0成功 1失败 6状态未知 7被冲正 8被撤销 9初始 X源流水不存在''';

comment on column PABYBH_SERIAL_HIS.CERTTYPE is
'证件类型';

comment on column PABYBH_SERIAL_HIS.CERTNO is
'证件号码';

comment on column PABYBH_SERIAL_HIS.CHKFLAG is
'对账标志,0-未对账1-已对平2-平安多3-核心多 X-平安已对账 ';

comment on column PABYBH_SERIAL_HIS.MEMO is
'备注';

comment on column PABYBH_SERIAL_HIS.EXTFLD1 is
'备用字段1 ';

comment on column PABYBH_SERIAL_HIS.EXTFLD2 is
'备用字段2';

comment on column PABYBH_SERIAL_HIS.EXTFLD3 is
'备用字段3';

comment on column PABYBH_SERIAL_HIS.EXTFLD4 is
'备用字段4';

--==============================================================
-- Index: K_PABYBH_SERIAL_4
--==============================================================
create unique index K_PABYBH_SERIAL_4 on PABYBH_SERIAL_HIS (
   REQSERIALNO          ASC
);

--==============================================================
-- Index: K_PABYBH_SERIAL_5
--==============================================================
create unique index K_PABYBH_SERIAL_5 on PABYBH_SERIAL_HIS (
   WORKDATE             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Index: K_PABYBH_SERIAL_6
--==============================================================
create index K_PABYBH_SERIAL_6 on PABYBH_SERIAL_HIS (
   WORKDATE             ASC,
   COBANKNO             ASC,
   SVRCODE              ASC,
   TRANSCODE            ASC
);

--==============================================================
-- Table: PABYBH_SIGN
--==============================================================
create table PABYBH_SIGN (
   PROTOCOLNO           VARCHAR(14)            not null,
   SIGNDATE             VARCHAR(8)             not null,
   SIGNTIME             VARCHAR(6),
   COBANKNO             VARCHAR(12)            not null,
   ACCTNO               VARCHAR(32)            not null,
   OLDACCTNO            VARCHAR(32),
   CERTTYPE             VARCHAR(2)             not null,
   CERTNO               VARCHAR(32)            not null,
   CUSTTYPE             VARCHAR(2),
   CUSTNAME             VARCHAR(120),
   STOCKCODE            VARCHAR(8)             not null,
   CAPITALACCTNO        VARCHAR(30)            not null,
   SVRCODE              VARCHAR(6)             not null,
   CURR                 VARCHAR(3),
   CUSTMANAGERID        VARCHAR(20),
   CUSTMANAGERNAME      VARCHAR(20),
   OPENORG              VARCHAR(10),
   BUSITYPE             VARCHAR(2)             not null,
   STAT                 VARCHAR(1),
   HOSTSTAT             VARCHAR(1),
   HOSTDATE             VARCHAR(8),
   HOSTSERIALNO         VARCHAR(40),
   CHKFLAG              VARCHAR(1),
   UPDATEDATE           VARCHAR(8),
   UPDATETIME           VARCHAR(6),
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(20),
   AGENTNAME            VARCHAR(80),
   AGENTCERTY           VARCHAR(2),
   AGENTCERNO           VARCHAR(32),
   AGENTPHONE           VARCHAR(20),
   MEMO                 VARCHAR(40),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(32),
   EXTFLD3              VARCHAR(64),
   EXTFLD4              VARCHAR(64),
   EXTFLD5              VARCHAR(64),
   EXTFLD6              VARCHAR(64),
   constraint PK_PABYBH_SIGN primary key (STOCKCODE, CAPITALACCTNO, 
BUSITYPE)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_SIGN is
'签约表';

comment on column PABYBH_SIGN.PROTOCOLNO is
'协议号';

comment on column PABYBH_SIGN.SIGNDATE is
'签约日期';

comment on column PABYBH_SIGN.SIGNTIME is
'签约时间';

comment on column PABYBH_SIGN.COBANKNO is
'合作行号';

comment on column PABYBH_SIGN.ACCTNO is
'银行账号';

comment on column PABYBH_SIGN.OLDACCTNO is
'老银行账号';

comment on column PABYBH_SIGN.CERTTYPE is
'证件类型';

comment on column PABYBH_SIGN.CERTNO is
'证件号码';

comment on column PABYBH_SIGN.CUSTTYPE is
'客户类型00-机构 01-个人';

comment on column PABYBH_SIGN.CUSTNAME is
'客户名称';

comment on column PABYBH_SIGN.STOCKCODE is
'券商代码';

comment on column PABYBH_SIGN.CAPITALACCTNO is
'资金账号';

comment on column PABYBH_SIGN.SVRCODE is
'服务代码0802-三方存管';

comment on column PABYBH_SIGN.CURR is
'币种';

comment on column PABYBH_SIGN.CUSTMANAGERID is
'客户经理号';

comment on column PABYBH_SIGN.CUSTMANAGERNAME is
'客户经理名';

comment on column PABYBH_SIGN.OPENORG is
'开户机构';

comment on column PABYBH_SIGN.BUSITYPE is
'业务类型';

comment on column PABYBH_SIGN.STAT is
'签约状态''9-待校验1-签约2-解约3-废除''';

comment on column PABYBH_SIGN.HOSTSTAT is
'核心状态 ''9-待校验1-签约2-解约‘';

comment on column PABYBH_SIGN.HOSTDATE is
'核心日期';

comment on column PABYBH_SIGN.HOSTSERIALNO is
'核心流水号';

comment on column PABYBH_SIGN.CHKFLAG is
'对账标志''0-未对账1-已对账''';

comment on column PABYBH_SIGN.UPDATEDATE is
'更新日期 ';

comment on column PABYBH_SIGN.UPDATETIME is
'更新时间';

comment on column PABYBH_SIGN.TRANSORG is
'交易机构';

comment on column PABYBH_SIGN.TRANSOPER is
'交易柜员';

comment on column PABYBH_SIGN.AGENTNAME is
'代理人名称';

comment on column PABYBH_SIGN.AGENTCERTY is
'证件类型';

comment on column PABYBH_SIGN.AGENTCERNO is
'证件号码';

comment on column PABYBH_SIGN.AGENTPHONE is
'代理人手机号';

comment on column PABYBH_SIGN.MEMO is
'备注';

comment on column PABYBH_SIGN.EXTFLD1 is
'备用字段1';

comment on column PABYBH_SIGN.EXTFLD2 is
'备用字段2';

comment on column PABYBH_SIGN.EXTFLD3 is
'备用字段3';

comment on column PABYBH_SIGN.EXTFLD4 is
'备用字段4';

comment on column PABYBH_SIGN.EXTFLD5 is
'备用字段5';

comment on column PABYBH_SIGN.EXTFLD6 is
'备用字段6';

--==============================================================
-- Index: K_PABYBH_SIGN_1
--==============================================================
create unique index K_PABYBH_SIGN_1 on PABYBH_SIGN (
   PROTOCOLNO           ASC
);

--==============================================================
-- Table: PABYBH_SVRINFO
--==============================================================
create table PABYBH_SVRINFO (
   COBANKNO             VARCHAR(12)            not null,
   SVRCODE              VARCHAR(6)             not null,
   SVRNAME              VARCHAR(100)           not null,
   WORKTIME             VARCHAR(32),
   SVRSTATUS            VARCHAR(1)             not null,
   EXTFLD1              VARCHAR(128),
   EXTFLD2              VARCHAR(128),
   EXTFLD3              VARCHAR(128),
   constraint PK_PABYBH_SVRINFO primary key (COBANKNO, SVRCODE)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_SVRINFO is
'业务信息';

comment on column PABYBH_SVRINFO.COBANKNO is
'联网行编号';

comment on column PABYBH_SVRINFO.SVRCODE is
'服务代码';

comment on column PABYBH_SVRINFO.SVRNAME is
'服务名称';

comment on column PABYBH_SVRINFO.WORKTIME is
'业务开展时间段';

comment on column PABYBH_SVRINFO.SVRSTATUS is
'服务状态';

comment on column PABYBH_SVRINFO.EXTFLD1 is
'备用字段1';

comment on column PABYBH_SVRINFO.EXTFLD2 is
'备用字段2';

comment on column PABYBH_SVRINFO.EXTFLD3 is
'备用字段3';


--==============================================================
-- Table: PABYBH_TRADER
--==============================================================
create table PABYBH_TRADER (
   STOCKCODE            VARCHAR(8)             not null,
   STOCKNAME            VARCHAR(120),
   ONESTEP              VARCHAR(1),
   ONLINETIME           VARCHAR(8),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PK_PABYBH_TRADER primary key (STOCKCODE)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_TRADER is
'券商代码信息';

comment on column PABYBH_TRADER.STOCKCODE is
'券商代码';

comment on column PABYBH_TRADER.STOCKNAME is
'券商名称';

comment on column PABYBH_TRADER.ONESTEP is
'是否一步式签约 1-是 0-否';

comment on column PABYBH_TRADER.ONLINETIME is
'上线时间';

comment on column PABYBH_TRADER.EXTFLD1 is
'扩展字段1';

comment on column PABYBH_TRADER.EXTFLD2 is
'扩展字段2';

comment on column PABYBH_TRADER.EXTFLD3 is
'扩展字段3';
