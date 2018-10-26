drop index K_AGT_DRLS_3;

drop index K_AGT_DRLS_2;

drop index K_AGT_DRLS_1;

drop table AGENT_DRLS;

drop index K_AGT_DZBPB_3;

drop index K_AGT_DZBPB_2;

drop index K_AGT_DZBPB_1;

drop table AGENT_DZBPB;

drop index K_AGT_DZLSB_1;

drop table AGENT_DZLSB;

drop index K_AGT_DRLS_6;

drop index K_AGT_DRLS_5;

drop index K_AGT_DRLS_4;

drop table AGENT_HIS_DRLS;

drop table AGENT_RZZT;

drop table AGENT_TJ;

--==============================================================
-- Table: AGENT_DRLS
--==============================================================
create table AGENT_DRLS
(
   PTRQ                 VARCHAR(8)             not null,
   PTSJ                 VARCHAR(6),
   PTLS                 INTEGER                not null,
   JYXH                 INTEGER                not null default 1,
   YPTLSH               INTEGER,
   JYJG                 VARCHAR(16),
   JYGY                 VARCHAR(16),
   SQJG                 VARCHAR(16),
   SQGY                 VARCHAR(16),
   QDBS                 VARCHAR(3),
   ZDSBBH               VARCHAR(8),
   CPDM                 VARCHAR(16),
   YWBH                 VARCHAR(16),
   YWRQ                 VARCHAR(8),
   YWLSH                INTEGER,
   JYDM                 VARCHAR(8),
   KHMC                 VARCHAR(80),
   KHBH                 VARCHAR(32),
   DQDM                 VARCHAR(8),
   YHLX                 VARCHAR(16),
   YHH1                 VARCHAR(32),
   YHBSH                VARCHAR(32),
   YHMC                 VARCHAR(80),
   JYBZ                 VARCHAR(3),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   ZHLX                 VARCHAR(2),
   YHZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   JYJE2                NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   ZNJ                  NUMERIC(16,2),
   PZZL                 VARCHAR(3),
   PZHM                 VARCHAR(32),
   JFBSH                VARCHAR(32),
   CXLSH                INTEGER,
   JYZY                 VARCHAR(40),
   FQFLSH               VARCHAR(32),
   FQFRQ                VARCHAR(8),
   FQFSJ                VARCHAR(6),
   FQFJYDM              VARCHAR(8),
   DSFLSH               VARCHAR(22),
   DSFRQ                VARCHAR(14),
   DSFJYLX              VARCHAR(8),
   DSFJYDM              VARCHAR(8),
   DSFXYM               VARCHAR(8),
   DSFXYXX              VARCHAR(60),
   DSFJYZT              VARCHAR(1),
   ZJLSH                VARCHAR(32),
   ZJRQ                 VARCHAR(14),
   ZJJYDM               VARCHAR(8),
   ZJXYM                VARCHAR(8),
   ZJXYXX               VARCHAR(60),
   ZJJYZT               VARCHAR(1),
   JYXYM                VARCHAR(8),
   JYXYXX               VARCHAR(60),
   JYZT                 VARCHAR(1),
   DSFDZBZ              VARCHAR(1),
   ZJDZBZ               VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   EXTFLD4              VARCHAR(40),
   EXTFLD5              VARCHAR(40),
   EXTFLD6              VARCHAR(40),
   constraint P_PK_AGENT_DRLS primary key (PTRQ, PTLS, JYXH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table AGENT_DRLS is
'代收付应用当日流水表';

comment on column AGENT_DRLS.PTRQ is
'平台日期 YYYYMMDD';

comment on column AGENT_DRLS.PTSJ is
'平台时间 HHMMSS';

comment on column AGENT_DRLS.PTLS is
'平台流水号';

comment on column AGENT_DRLS.JYXH is
'交易序列号';

comment on column AGENT_DRLS.YPTLSH is
'原平台流水号(撤销交易填原正交易平台流水号)';

comment on column AGENT_DRLS.JYJG is
'交易机构';

comment on column AGENT_DRLS.JYGY is
'交易柜员';

comment on column AGENT_DRLS.SQJG is
'授权机构';

comment on column AGENT_DRLS.SQGY is
'授权柜员';

comment on column AGENT_DRLS.QDBS is
'渠道标识 ';

comment on column AGENT_DRLS.ZDSBBH is
'终端设备编号';

comment on column AGENT_DRLS.CPDM is
'产品代码';

comment on column AGENT_DRLS.YWBH is
'产品代码';

comment on column AGENT_DRLS.YWRQ is
'业务日期';

comment on column AGENT_DRLS.YWLSH is
'业务流水号';

comment on column AGENT_DRLS.JYDM is
'交易代码';

comment on column AGENT_DRLS.KHMC is
'客户名称(行内客户名称)';

comment on column AGENT_DRLS.KHBH is
'客户编号(行内客户编)';

comment on column AGENT_DRLS.DQDM is
'地区代码(第三方地区代码)';

comment on column AGENT_DRLS.YHLX is
'用户类型  用户在第三方的用户类型';

comment on column AGENT_DRLS.YHH1 is
'用户编号 如手机号 水务号';

comment on column AGENT_DRLS.YHBSH is
'用户标识号 如 用户在第三方的合同号';

comment on column AGENT_DRLS.YHMC is
'用户名称';

comment on column AGENT_DRLS.JYBZ is
'交易币种 见数据字典KEY=K_JYBZ';

comment on column AGENT_DRLS.XZBZ is
'现转标志  0现金 1转帐';

comment on column AGENT_DRLS.JDBZ is
'借贷标志  见数据字典KEY=K_JDBZ';

comment on column AGENT_DRLS.ZHLX is
'帐户类型  见数据字典KEY=K_ZHLX';

comment on column AGENT_DRLS.YHZH is
'银行帐号';

comment on column AGENT_DRLS.JYJE is
'交易金额';

comment on column AGENT_DRLS.JYJE2 is
'交易金额2';

comment on column AGENT_DRLS.SXF is
'手续费';

comment on column AGENT_DRLS.ZNJ is
'滞纳金';

comment on column AGENT_DRLS.PZZL is
'凭证种类';

comment on column AGENT_DRLS.PZHM is
'凭证号码';

comment on column AGENT_DRLS.JFBSH is
'第三方缴费标识号';

comment on column AGENT_DRLS.CXLSH is
'查询流水号';

comment on column AGENT_DRLS.JYZY is
'交易摘要';

comment on column AGENT_DRLS.FQFLSH is
'发起方流水号';

comment on column AGENT_DRLS.FQFRQ is
'发起方日期';

comment on column AGENT_DRLS.FQFSJ is
'发起方时间';

comment on column AGENT_DRLS.FQFJYDM is
'发起方交易代码';

comment on column AGENT_DRLS.DSFLSH is
'第三方流水号';

comment on column AGENT_DRLS.DSFRQ is
'第三方日期';

comment on column AGENT_DRLS.DSFJYLX is
'第三方交易类型( 如 区分 预存 缴费)';

comment on column AGENT_DRLS.DSFJYDM is
'第三方交易代码';

comment on column AGENT_DRLS.DSFXYM is
'第三方响应码';

comment on column AGENT_DRLS.DSFXYXX is
'第三方响应信息';

comment on column AGENT_DRLS.DSFJYZT is
'第三方交易状态 见数据字典KEY=K_JYZT';

comment on column AGENT_DRLS.ZJLSH is
'主机流水号';

comment on column AGENT_DRLS.ZJRQ is
'主机日期';

comment on column AGENT_DRLS.ZJJYDM is
'主机交易代码';

comment on column AGENT_DRLS.ZJXYM is
'主机响应码';

comment on column AGENT_DRLS.ZJXYXX is
'主机响应信息';

comment on column AGENT_DRLS.ZJJYZT is
'主机交易状态见数据字典KEY=K_JYZT';

comment on column AGENT_DRLS.JYXYM is
'交易响应码';

comment on column AGENT_DRLS.JYXYXX is
'交易响应信息';

comment on column AGENT_DRLS.JYZT is
'交易状态见数据字典KEY=K_JYZT';

comment on column AGENT_DRLS.DSFDZBZ is
'对帐标志  0 未对账 1 平 2 平台多 3 平台少';

comment on column AGENT_DRLS.ZJDZBZ is
'对帐标志  0 未对账 1 平 2 平台多 3 平台少';

comment on column AGENT_DRLS.EXTFLD1 is
'扩展1';

comment on column AGENT_DRLS.EXTFLD2 is
'扩展2';

comment on column AGENT_DRLS.EXTFLD3 is
'扩展3';

comment on column AGENT_DRLS.EXTFLD4 is
'扩展4';

comment on column AGENT_DRLS.EXTFLD5 is
'扩展5';

comment on column AGENT_DRLS.EXTFLD6 is
'扩展6';

--==============================================================
-- Index: K_AGT_DRLS_1
--==============================================================
create index K_AGT_DRLS_1 on AGENT_DRLS (
   PTRQ                 ASC,
   PTLS                 ASC
);

--==============================================================
-- Index: K_AGT_DRLS_2
--==============================================================
create index K_AGT_DRLS_2 on AGENT_DRLS (
   YWRQ                 ASC,
   YWLSH                ASC
);

--==============================================================
-- Index: K_AGT_DRLS_3
--==============================================================
create index K_AGT_DRLS_3 on AGENT_DRLS (
   PTRQ                 ASC,
   JYJG                 ASC,
   QDBS                 ASC
);

--==============================================================
-- Table: AGENT_DZBPB
--==============================================================
create table AGENT_DZBPB
(
   DZRQ                 VARCHAR(8)             not null,
   PTRQ                 VARCHAR(8),
   PTLS                 INTEGER,
   ZJRQ                 VARCHAR(8),
   ZJLS                 VARCHAR(32),
   JYJG                 VARCHAR(16)            not null,
   JYGY                 VARCHAR(16)            not null,
   JYBZ                 VARCHAR(3),
   YWBH                 VARCHAR(16)            not null,
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   JYJE                 NUMERIC(16,2),
   PTJYJE               NUMERIC(16,2),
   JFZH                 VARCHAR(32),
   JFFZH                VARCHAR(10),
   DFZH                 VARCHAR(32),
   DFFZH                VARCHAR(10),
   YWLSH                VARCHAR(16),
   YWRQ                 VARCHAR(8),
   LSLX                 VARCHAR(1),
   DZBZ                 VARCHAR(1),
   TZLSH                VARCHAR(22),
   CLZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(20),
   EXTFLD3              VARCHAR(20)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table AGENT_DZBPB is
'对帐不平表';

comment on column AGENT_DZBPB.PTLS is
'平台流水号';

comment on column AGENT_DZBPB.ZJRQ is
'主机日期';

comment on column AGENT_DZBPB.ZJLS is
'主机流水号';

comment on column AGENT_DZBPB.JYJG is
'交易机构';

comment on column AGENT_DZBPB.JYGY is
'交易柜员';

comment on column AGENT_DZBPB.JYBZ is
'交易币种 见数据字典 KEY = K_JYBZ';

comment on column AGENT_DZBPB.YWBH is
'业务编号';

comment on column AGENT_DZBPB.XZBZ is
'现转标志 0现金 1转帐';

comment on column AGENT_DZBPB.JDBZ is
'借贷标志(D 借 C贷)';

comment on column AGENT_DZBPB.JYJE is
'交易金额';

comment on column AGENT_DZBPB.PTJYJE is
'平台交易金额';

comment on column AGENT_DZBPB.JFZH is
'借方帐号';

comment on column AGENT_DZBPB.JFFZH is
'借方分帐号';

comment on column AGENT_DZBPB.DFZH is
'贷方帐号';

comment on column AGENT_DZBPB.DFFZH is
'贷方分帐号';

comment on column AGENT_DZBPB.YWLSH is
'业务流水号';

comment on column AGENT_DZBPB.YWRQ is
'业务日期';

comment on column AGENT_DZBPB.LSLX is
'1 主机对账 2 第三方对账';

comment on column AGENT_DZBPB.DZBZ is
'2 平台多 3 平台少';

comment on column AGENT_DZBPB.TZLSH is
'调账流水号';

comment on column AGENT_DZBPB.CLZT is
'处理状态（0 未处理 1 已处理 8 处理出错 9 处理中）';

comment on column AGENT_DZBPB.EXTFLD1 is
'扩展字段1';

comment on column AGENT_DZBPB.EXTFLD2 is
'扩展字段2';

comment on column AGENT_DZBPB.EXTFLD3 is
'扩展字段3';

--==============================================================
-- Index: K_AGT_DZBPB_1
--==============================================================
create index K_AGT_DZBPB_1 on AGENT_DZBPB (
   PTRQ                 ASC,
   PTLS                 ASC
);

--==============================================================
-- Index: K_AGT_DZBPB_2
--==============================================================
create index K_AGT_DZBPB_2 on AGENT_DZBPB (
   ZJRQ                 ASC,
   ZJLS                 ASC
);

--==============================================================
-- Index: K_AGT_DZBPB_3
--==============================================================
create index K_AGT_DZBPB_3 on AGENT_DZBPB (
   YWLSH                ASC,
   YWRQ                 ASC
);

--==============================================================
-- Table: AGENT_DZLSB
--==============================================================
create table AGENT_DZLSB
(
   PTRQ                 VARCHAR(8),
   PTLS                 INTEGER,
   ZJRQ                 VARCHAR(8)             not null,
   ZJLS                 VARCHAR(32)            not null,
   JYJG                 VARCHAR(16)            not null,
   JYGY                 VARCHAR(16)            not null,
   JYBZ                 VARCHAR(3),
   YWBH                 VARCHAR(16)            not null,
   CPDM                 VARCHAR(8),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   JYJE                 NUMERIC(16,2),
   JFZH                 VARCHAR(32),
   JFFZH                VARCHAR(10),
   DFZH                 VARCHAR(32),
   DFFZH                VARCHAR(10),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(20),
   EXTFLD3              VARCHAR(20),
   JYZT                 VARCHAR(1),
   ZJDZBZ               VARCHAR(1),
   constraint "P_Key_1" primary key (ZJRQ, ZJLS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table AGENT_DZLSB is
'对帐流水表';

comment on column AGENT_DZLSB.PTRQ is
'平台日期';

comment on column AGENT_DZLSB.PTLS is
'平台流水号';

comment on column AGENT_DZLSB.ZJRQ is
'主机日期';

comment on column AGENT_DZLSB.ZJLS is
'主机流水号';

comment on column AGENT_DZLSB.JYJG is
'交易机构';

comment on column AGENT_DZLSB.JYGY is
'交易柜员';

comment on column AGENT_DZLSB.JYBZ is
'交易币种 见数据字典 KEY = K_JYBZ';

comment on column AGENT_DZLSB.YWBH is
'业务编号';

comment on column AGENT_DZLSB.CPDM is
'产品代码';

comment on column AGENT_DZLSB.XZBZ is
'现转标志 0现金 1转帐';

comment on column AGENT_DZLSB.JDBZ is
'借贷标志(D 借 C贷)';

comment on column AGENT_DZLSB.JYJE is
'交易金额';

comment on column AGENT_DZLSB.JFZH is
'借方帐号';

comment on column AGENT_DZLSB.JFFZH is
'借方分帐号';

comment on column AGENT_DZLSB.DFZH is
'贷方帐号';

comment on column AGENT_DZLSB.DFFZH is
'贷方分帐号';

comment on column AGENT_DZLSB.EXTFLD1 is
'扩展字段1';

comment on column AGENT_DZLSB.EXTFLD2 is
'扩展字段2';

comment on column AGENT_DZLSB.EXTFLD3 is
'扩展字段3';

comment on column AGENT_DZLSB.JYZT is
'交易状态 K_JYZT';

comment on column AGENT_DZLSB.ZJDZBZ is
'对帐标志  0 未对账 1 平 2 平台多 3 平台少';

--==============================================================
-- Index: K_AGT_DZLSB_1
--==============================================================
create index K_AGT_DZLSB_1 on AGENT_DZLSB (
   PTRQ                 ASC,
   PTLS                 ASC
);

--==============================================================
-- Table: AGENT_HIS_DRLS
--==============================================================
create table AGENT_HIS_DRLS
(
   PTRQ                 VARCHAR(8)             not null,
   PTSJ                 VARCHAR(6),
   PTLS                 INTEGER                not null,
   JYXH                 INTEGER                not null default 1,
   YPTLSH               INTEGER,
   JYJG                 VARCHAR(16),
   JYGY                 VARCHAR(16),
   SQJG                 VARCHAR(16),
   SQGY                 VARCHAR(16),
   QDBS                 VARCHAR(3),
   ZDSBBH               VARCHAR(8),
   CPDM                 VARCHAR(16),
   YWBH                 VARCHAR(16),
   YWRQ                 VARCHAR(8),
   YWLSH                INTEGER,
   JYDM                 VARCHAR(8),
   KHMC                 VARCHAR(80),
   KHBH                 VARCHAR(32),
   DQDM                 VARCHAR(8),
   YHLX                 VARCHAR(16),
   YHH1                 VARCHAR(32),
   YHBSH                VARCHAR(32),
   YHMC                 VARCHAR(80),
   JYBZ                 VARCHAR(3),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   ZHLX                 VARCHAR(2),
   YHZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   JYJE2                NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   ZNJ                  NUMERIC(16,2),
   PZZL                 VARCHAR(3),
   PZHM                 VARCHAR(32),
   JFBSH                VARCHAR(32),
   CXLSH                INTEGER,
   JYZY                 VARCHAR(40),
   FQFLSH               VARCHAR(22),
   FQFRQ                VARCHAR(8),
   FQFSJ                VARCHAR(6),
   FQFJYDM              VARCHAR(8),
   DSFLSH               VARCHAR(22),
   DSFRQ                VARCHAR(14),
   DSFJYLX              VARCHAR(8),
   DSFJYDM              VARCHAR(8),
   DSFXYM               VARCHAR(8),
   DSFXYXX              VARCHAR(60),
   DSFJYZT              VARCHAR(1),
   ZJLSH                VARCHAR(22),
   ZJRQ                 VARCHAR(14),
   ZJJYDM               VARCHAR(8),
   ZJXYM                VARCHAR(8),
   ZJXYXX               VARCHAR(60),
   ZJJYZT               VARCHAR(1),
   JYXYM                VARCHAR(8),
   JYXYXX               VARCHAR(60),
   JYZT                 VARCHAR(1),
   DSFDZBZ              VARCHAR(1),
   ZJDZBZ               VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   EXTFLD4              VARCHAR(40),
   EXTFLD5              VARCHAR(40),
   EXTFLD6              VARCHAR(40),
   constraint P_PK_AGENT_DRLS primary key (PTRQ, PTLS, JYXH)
)IN GAPS_HIS_DATA INDEX IN GAPS_HIS_INDEX ;

comment on table AGENT_HIS_DRLS is
'代收付应用历史流水表';

comment on column AGENT_HIS_DRLS.PTRQ is
'平台日期 YYYYMMDD';

comment on column AGENT_HIS_DRLS.PTSJ is
'平台时间 HHMMSS';

comment on column AGENT_HIS_DRLS.PTLS is
'平台流水号';

comment on column AGENT_HIS_DRLS.JYXH is
'交易序列号';

comment on column AGENT_HIS_DRLS.YPTLSH is
'原平台流水号(撤销交易填原正交易平台流水号)';

comment on column AGENT_HIS_DRLS.JYJG is
'交易机构';

comment on column AGENT_HIS_DRLS.JYGY is
'交易柜员';

comment on column AGENT_HIS_DRLS.SQJG is
'授权机构';

comment on column AGENT_HIS_DRLS.SQGY is
'授权柜员';

comment on column AGENT_HIS_DRLS.QDBS is
'渠道标识 ';

comment on column AGENT_HIS_DRLS.ZDSBBH is
'终端设备编号';

comment on column AGENT_HIS_DRLS.CPDM is
'产品代码';

comment on column AGENT_HIS_DRLS.YWBH is
'产品代码';

comment on column AGENT_HIS_DRLS.YWRQ is
'业务日期';

comment on column AGENT_HIS_DRLS.YWLSH is
'业务流水号';

comment on column AGENT_HIS_DRLS.JYDM is
'交易代码';

comment on column AGENT_HIS_DRLS.KHMC is
'客户名称(行内客户名称)';

comment on column AGENT_HIS_DRLS.KHBH is
'客户编号(行内客户编)';

comment on column AGENT_HIS_DRLS.DQDM is
'地区代码(第三方地区代码)';

comment on column AGENT_HIS_DRLS.YHLX is
'用户类型  用户在第三方的用户类型';

comment on column AGENT_HIS_DRLS.YHH1 is
'用户编号 如手机号 水务号';

comment on column AGENT_HIS_DRLS.YHBSH is
'用户标识号 如 用户在第三方的合同号';

comment on column AGENT_HIS_DRLS.YHMC is
'用户名称';

comment on column AGENT_HIS_DRLS.JYBZ is
'交易币种 见数据字典KEY=K_JYBZ';

comment on column AGENT_HIS_DRLS.XZBZ is
'现转标志  0现金 1转帐';

comment on column AGENT_HIS_DRLS.JDBZ is
'借贷标志  见数据字典KEY=K_JDBZ';

comment on column AGENT_HIS_DRLS.ZHLX is
'帐户类型  见数据字典KEY=K_ZHLX';

comment on column AGENT_HIS_DRLS.YHZH is
'银行帐号';

comment on column AGENT_HIS_DRLS.JYJE is
'交易金额';

comment on column AGENT_HIS_DRLS.JYJE2 is
'交易金额2';

comment on column AGENT_HIS_DRLS.SXF is
'手续费';

comment on column AGENT_HIS_DRLS.ZNJ is
'滞纳金';

comment on column AGENT_HIS_DRLS.PZZL is
'凭证种类';

comment on column AGENT_HIS_DRLS.PZHM is
'凭证号码';

comment on column AGENT_HIS_DRLS.JFBSH is
'第三方缴费标识号';

comment on column AGENT_HIS_DRLS.CXLSH is
'查询流水号';

comment on column AGENT_HIS_DRLS.JYZY is
'交易摘要';

comment on column AGENT_HIS_DRLS.FQFLSH is
'发起方流水号';

comment on column AGENT_HIS_DRLS.FQFRQ is
'发起方日期';

comment on column AGENT_HIS_DRLS.FQFSJ is
'发起方时间';

comment on column AGENT_HIS_DRLS.FQFJYDM is
'发起方交易代码';

comment on column AGENT_HIS_DRLS.DSFLSH is
'第三方流水号';

comment on column AGENT_HIS_DRLS.DSFRQ is
'第三方日期';

comment on column AGENT_HIS_DRLS.DSFJYLX is
'第三方交易类型( 如 区分 预存 缴费)';

comment on column AGENT_HIS_DRLS.DSFJYDM is
'第三方交易代码';

comment on column AGENT_HIS_DRLS.DSFXYM is
'第三方响应码';

comment on column AGENT_HIS_DRLS.DSFXYXX is
'第三方响应信息';

comment on column AGENT_HIS_DRLS.DSFJYZT is
'第三方交易状态 见数据字典KEY=K_JYZT';

comment on column AGENT_HIS_DRLS.ZJLSH is
'主机流水号';

comment on column AGENT_HIS_DRLS.ZJRQ is
'主机日期';

comment on column AGENT_HIS_DRLS.ZJJYDM is
'主机交易代码';

comment on column AGENT_HIS_DRLS.ZJXYM is
'主机响应码';

comment on column AGENT_HIS_DRLS.ZJXYXX is
'主机响应信息';

comment on column AGENT_HIS_DRLS.ZJJYZT is
'主机交易状态见数据字典KEY=K_JYZT';

comment on column AGENT_HIS_DRLS.JYXYM is
'交易响应码';

comment on column AGENT_HIS_DRLS.JYXYXX is
'交易响应信息';

comment on column AGENT_HIS_DRLS.JYZT is
'交易状态见数据字典KEY=K_JYZT';

comment on column AGENT_HIS_DRLS.DSFDZBZ is
'对帐标志  0 未对账 1 平 2 平台多 3 平台少';

comment on column AGENT_HIS_DRLS.ZJDZBZ is
'对帐标志  0 未对账 1 平 2 平台多 3 平台少';

comment on column AGENT_HIS_DRLS.EXTFLD1 is
'扩展1';

comment on column AGENT_HIS_DRLS.EXTFLD2 is
'扩展2';

comment on column AGENT_HIS_DRLS.EXTFLD3 is
'扩展3';

comment on column AGENT_HIS_DRLS.EXTFLD4 is
'扩展4';

comment on column AGENT_HIS_DRLS.EXTFLD5 is
'扩展5';

comment on column AGENT_HIS_DRLS.EXTFLD6 is
'扩展6';

--==============================================================
-- Index: K_AGT_DRLS_4
--==============================================================
create index K_AGT_DRLS_4 on AGENT_HIS_DRLS (
   PTRQ                 ASC,
   PTLS                 ASC
);

--==============================================================
-- Index: K_AGT_DRLS_5
--==============================================================
create index K_AGT_DRLS_5 on AGENT_HIS_DRLS (
   YWRQ                 ASC,
   YWLSH                ASC
);

--==============================================================
-- Index: K_AGT_DRLS_6
--==============================================================
create index K_AGT_DRLS_6 on AGENT_HIS_DRLS (
   PTRQ                 ASC,
   JYJG                 ASC,
   QDBS                 ASC
);

--==============================================================
-- Table: AGENT_RZZT
--==============================================================
create table AGENT_RZZT
(
   YWBH                 VARCHAR(16)            not null,
   PTRQ                 VARCHAR(8)             not null,
   YWRQ                 VARCHAR(8)             not null,
   ZJMXDZZT             VARCHAR(1),
   ZJZZDZZT             VARCHAR(1),
   DSFMXDZZT            VARCHAR(1),
   DSFZZDZZT            VARCHAR(1),
   ZJZJE                NUMERIC(16,2),
   ZJZBS                INTEGER,
   DSFZJE               NUMERIC(16,2),
   DSFZBS               INTEGER,
   GDZT                 VARCHAR(1),
   QLZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(20),
   constraint "P_Key_1" primary key (YWBH, PTRQ, YWRQ)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on column AGENT_RZZT.ZJMXDZZT is
'0 未对账 1 对账平 2 对账不平 9 对账中';

comment on column AGENT_RZZT.ZJZZDZZT is
'0 未对账 1 对账平 2 对账不平 9 对账中';

comment on column AGENT_RZZT.DSFMXDZZT is
'0 未对账 1 对账平 2 对账不平 9 对账中';

comment on column AGENT_RZZT.DSFZZDZZT is
'0 未对账 1 对账平 2 对账不平 9 对账中';

comment on column AGENT_RZZT.EXTFLD1 is
'扩展字段1';

comment on column AGENT_RZZT.EXTFLD2 is
'扩展字段2';

--==============================================================
-- Table: AGENT_TJ
--==============================================================
create table AGENT_TJ
(
   PTRQ                 VARCHAR(8)             not null,
   JYJG                 VARCHAR(16)            not null,
   JYGY                 VARCHAR(16)            not null,
   QDBS                 VARCHAR(3)             not null,
   YWBH                 VARCHAR(16)            not null,
   JDBZ                 VARCHAR(1),
   JYJE                 NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   constraint "P_Key_1" primary key (PTRQ, JYJG, JYGY, QDBS, YWBH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table AGENT_TJ is
'代收付应用统计表';

comment on column AGENT_TJ.PTRQ is
'平台日期 YYYYMMDD';

comment on column AGENT_TJ.JYJG is
'交易机构';

comment on column AGENT_TJ.JYGY is
'交易柜员';

comment on column AGENT_TJ.QDBS is
'渠道标识 ';

comment on column AGENT_TJ.YWBH is
'业务流水号';

comment on column AGENT_TJ.JDBZ is
'借贷标志  见数据字典KEY=K_JDBZ';

comment on column AGENT_TJ.JYJE is
'交易金额';

comment on column AGENT_TJ.SXF is
'手续费';

comment on column AGENT_TJ.EXTFLD1 is
'扩展1';

comment on column AGENT_TJ.EXTFLD2 is
'扩展2';

comment on column AGENT_TJ.EXTFLD3 is
'扩展3';


delete from app_yyxx where yybs='003';
insert into app_yyxx (YYBS, YYMC, YYSM, YYKFKSRQ, YYKFJSRQ, YYFBRQ, YYBBH, YHH, SQH, YYKFJL, YYZBJL, YYZT, EXTFLD)
values ('003', 'agent', 'AGENT代收付应用', '20110801', '', '', '2.1.0.0', '', '', 'yd', 'yd', '0', '');


delete from app_jyxx where yybs='003';
insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2,WHJG, WHGY,QTBZ)
values ('920002', '代收付与银行对总账', '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920003', '代收付与银行对明细', '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920005', '代收付与商户对总账','003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920006', '代收付与商户对明细',  '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920008', '委托关系核对',  '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920313', '对账不平主机调账',  '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920314', '对账不平第三方调账',  '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920315', '对账不平流水状态调整',  '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920011', '数据归档',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920012', '数据清理', '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920013', '数据备份',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920015', '产品日切', '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920016', '业务报表',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920101', '流水列表查询', '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920102', '流水列表查询',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920103', '代理业务主机流水查询',  '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920104', '商户签到',  '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2,WHJG, WHGY,QTBZ)
values ('920105', '业务下载',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920106', '客户(账户)信息查询', '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920107', '客户信息查询',  '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920108', '欠费查询',  '003', '0', '0', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920109', '第三方缴费查询',  '003', '0', '0', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920201', '客户签约',  '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920202', '客户解约', '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2,WHJG, WHGY,QTBZ)
values ('920203', '签约修改',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920204', '签约查询',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('920205', '单边解约', '003', '0', '1', '1', '1', '1', '00000', 'admin', '20111222103301', '', '', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920301', '银行代收(查询模式)', '003', '0', '1', '0', '0', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920302', '银行代收(直接缴费)',  '003', '0', '0', '0', '0', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920303', '银行代付(查询模式)',  '003', '0', '1', '0', '0', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920304', '银行代付(直接缴费)',  '003', '0', '0', '0', '0', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2,WHJG, WHGY,QTBZ)
values ('920311', '撤销', '003', '1', '1', '0', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920312', '冲正', '003', '1', '1', '0', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920401', '发票打印',  '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920402', '发票批量打印', '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920403', '发票查询', '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920501', '通用穿透交易', '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2,WHJG, WHGY,QTBZ)
values ('920007', '取第三方对账结果', '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

delete from app_cskz where csjz='K_AGENT_DRLSQL';
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_AGENT_DRLSQL', '0', '', '/app/cskz', '7', '代收付流水当前表保留天数', '1' , '00000','admin');

delete from app_cskz where csjz='K_AGENT_DRLSGD';
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_AGENT_DRLSGD', '0', '', '/app/cskz', '2', '代收付流水归档天数', '1', '00000','admin');

delete from app_rzpz where ssyy='003';
insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG, WHGY )
values ('003', '1', '1', 'agent_drls', 'agent_his_drls', 'C;ptrq;=;K_AGENT_DRLSGD;;|', '代收付业务流水归档 ', ' ', '00000','admin');

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG, WHGY)
values ('003', '2', '1', 'agent_drls', '', 'C;ptrq;=;K_AGENT_DRLSQL;;|', '代收付业务流水清理', ' ',  '00000','admin');
