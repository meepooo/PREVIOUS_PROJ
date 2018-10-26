drop table APP_CPJGGX;

drop table APP_CPJYFW;

drop table APP_CPJYGYED;

drop table APP_CPJYGYKZ;

drop table APP_CPJYJGED;

drop table APP_CPPZGX;

drop table APP_CPQDGX;

drop index K_APP_CPSXFGX_1;

drop table APP_CPSXFGX;

drop table APP_CPSXFKZ;

drop table APP_CPXX;

drop table APP_CSKZ;

drop table APP_DICT;

drop index K_APP_DRLS_1;

drop table APP_DRLS;

drop table APP_DWCPXY;

drop table APP_DWXX;

drop table APP_GYSQED;

drop table APP_GYXX;

drop index K_APP_DRLS_2;

drop table APP_HIS_DRLS;

drop table APP_JJRDJ;

drop table APP_JYXX;

drop index K_APP_INDEX_1;

drop table APP_KHCPQY;

drop table APP_KHXX;

drop table APP_KZSX;

drop table APP_MJSJ;

drop table APP_MJSX;

drop table APP_PZGLKZ;

drop table APP_PZHMDJ;

drop table APP_PZSLDJ;

drop index K_APP_PZXX_2;

drop index K_APP_PZXX_1;

drop table APP_PZXX;

drop table APP_PZZL;

drop table APP_QDXX;

drop index INDEX_RWJKB_1;

drop table APP_RWJKB;

drop index K_APP_RZPZ_1;

drop table APP_RZPZ;

drop table APP_SXFFL;

drop index K_APP_SXFLS_1;

drop table APP_SXFLS;

drop index K_APP_SXFWHLS_1;

drop table APP_SXFWHLS;

drop table APP_TXAQXX;

drop table APP_XLKZ;

drop table APP_YWRQ;

drop table APP_YYXX;

drop distinct type CPDM;

drop distinct type DWBH;

drop distinct type JYDM;

drop distinct type JYGY;

drop distinct type JYJG;

drop distinct type PTLS;

drop distinct type PTRQ;

drop distinct type QDBS;

drop distinct type WHSJ;

drop distinct type YHH1;

drop distinct type YHZH;

drop distinct type YWBH;

drop distinct type ZHMC;

--==============================================================
-- Domain: CPDM
--==============================================================
create distinct type CPDM as CHAR(16) with comparisons;

--==============================================================
-- Domain: DWBH
--==============================================================
create distinct type DWBH as VARCHAR(16) with comparisons;

--==============================================================
-- Domain: JYDM
--==============================================================
create distinct type JYDM as CHAR(8) with comparisons;

--==============================================================
-- Domain: JYGY
--==============================================================
create distinct type JYGY as VARCHAR(16) with comparisons;

--==============================================================
-- Domain: JYJG
--==============================================================
create distinct type JYJG as VARCHAR(16) with comparisons;

--==============================================================
-- Domain: PTLS
--==============================================================
create distinct type PTLS as CHAR(8) with comparisons;

--==============================================================
-- Domain: PTRQ
--==============================================================
create distinct type PTRQ as CHAR(8) with comparisons;

--==============================================================
-- Domain: QDBS
--==============================================================
create distinct type QDBS as CHAR(3) with comparisons;

--==============================================================
-- Domain: WHSJ
--==============================================================
create distinct type WHSJ as VARCHAR(14) with comparisons;

--==============================================================
-- Domain: YHH1
--==============================================================
create distinct type YHH1 as VARCHAR(32) with comparisons;

--==============================================================
-- Domain: YHZH
--==============================================================
create distinct type YHZH as VARCHAR(32) with comparisons;

--==============================================================
-- Domain: YWBH
--==============================================================
create distinct type YWBH as CHAR(16) with comparisons;

--==============================================================
-- Domain: ZHMC
--==============================================================
create distinct type ZHMC as VARCHAR(80) with comparisons;

--==============================================================
-- Table: APP_CPJGGX
--==============================================================
create table APP_CPJGGX
(
   CPDM                 VARCHAR(16)            not null,
   JGBH                 VARCHAR(16)            not null,
   SJKZBZ               VARCHAR(1),
   QSSJ                 VARCHAR(6),
   JSSJ                 VARCHAR(6),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   ZT                   VARCHAR(1),
   constraint P_K_APP_CPJGGX_1 primary key (CPDM, JGBH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CPJGGX is
'产品机构关系表
负责产品的准入控制';

comment on column APP_CPJGGX.CPDM is
'产品代码';

comment on column APP_CPJGGX.JGBH is
'机构编号';

comment on column APP_CPJGGX.SJKZBZ is
'时间控制标志  0控制 1不控制';

comment on column APP_CPJGGX.QSSJ is
'起始时间';

comment on column APP_CPJGGX.JSSJ is
'结束时间';

comment on column APP_CPJGGX.EXTFLD1 is
'扩展参数1';

comment on column APP_CPJGGX.EXTFLD2 is
'扩展参数1';

comment on column APP_CPJGGX.ZT is
'状态 0允许 1不允许';

--==============================================================
-- Table: APP_CPJYFW
--==============================================================
create table APP_CPJYFW
(
   CPDM                 VARCHAR(16)            not null,
   JYDM                 VARCHAR(8)             not null,
   SJKZBZ               VARCHAR(1),
   QSSJ                 VARCHAR(6),
   JSSJ                 VARCHAR(6),
   XEKZBZ               VARCHAR(1),
   ZXXE                 NUMERIC(16,2),
   ZDXE                 NUMERIC(16,2),
   QYKZBZ               VARCHAR(1),
   QXKZ                 VARCHAR(8),
   QYEDKZFS             VARCHAR(1),
   JGEDKZFS             VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   QTBZ                 VARCHAR(1),
   constraint P_K_APP_CPJYFW_1 primary key (CPDM, JYDM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CPJYFW is
'产品交易服务关系表';

comment on column APP_CPJYFW.CPDM is
'产品代码';

comment on column APP_CPJYFW.JYDM is
'交易代码';

comment on column APP_CPJYFW.SJKZBZ is
'时间控制标志  0控制 1不控制';

comment on column APP_CPJYFW.QSSJ is
'起始时间 hhmmss';

comment on column APP_CPJYFW.JSSJ is
'结束时间 hhmmss';

comment on column APP_CPJYFW.XEKZBZ is
'限额控制标志 0控制 1不控制';

comment on column APP_CPJYFW.ZXXE is
'最小限额';

comment on column APP_CPJYFW.ZDXE is
'最大限额';

comment on column APP_CPJYFW.QYKZBZ is
'签约关系控制  0校验 1不校验';

comment on column APP_CPJYFW.QXKZ is
' 默认都是 0 不控制 ';

comment on column APP_CPJYFW.QYEDKZFS is
'柜员额度控制方式    0不控制 1 控制级别 9控制所有机构';

comment on column APP_CPJYFW.JGEDKZFS is
'机构额度控制方式    0不控制 1 控制级别 9控制所有机构';

comment on column APP_CPJYFW.EXTFLD1 is
'扩展参数1';

comment on column APP_CPJYFW.EXTFLD2 is
'扩展参数1';

comment on column APP_CPJYFW.QTBZ is
'启停标志 0开启 1关闭';

--==============================================================
-- Table: APP_CPJYGYED
--==============================================================
create table APP_CPJYGYED
(
   CPDM                 VARCHAR(16)            not null,
   JYDM                 VARCHAR(8)             not null,
   JYBZ                 VARCHAR(3)             not null,
   DBEDKZ               VARCHAR(1),
   RLJEDKZ              VARCHAR(1),
   YLJEDKZ              VARCHAR(1),
   GYJB                 VARCHAR(2)             not null,
   DBED                 NUMERIC(16,2),
   YLJED                NUMERIC(16,2),
   RLJED                NUMERIC(16,2),
   CXCL                 VARCHAR(1),
   SQGYGW               VARCHAR(8),
   SQGYJB               VARCHAR(2),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_CPJYGYED_1 primary key (CPDM, JYDM, JYBZ, GYJB)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CPJYGYED is
'产品柜员交易额度控制表';

comment on column APP_CPJYGYED.CPDM is
'产品代码';

comment on column APP_CPJYGYED.JYDM is
'交易代码';

comment on column APP_CPJYGYED.DBEDKZ is
'0 不控制 1控制级别 9控制所有柜员';

comment on column APP_CPJYGYED.RLJEDKZ is
'0 不控制 1控制级别 9控制所有柜员';

comment on column APP_CPJYGYED.YLJEDKZ is
'0 不控制 1控制级别 9控制所有柜员';

comment on column APP_CPJYGYED.GYJB is
'数据字典K_APP_GYJB';

comment on column APP_CPJYGYED.CXCL is
'0 交易拒绝 1 检查授权柜员级别 2 检查授权柜员岗位 3 检查授权柜员级别和岗位';

comment on column APP_CPJYGYED.EXTFLD1 is
'扩展参数1';

comment on column APP_CPJYGYED.EXTFLD2 is
'扩展参数1';

--==============================================================
-- Table: APP_CPJYGYKZ
--==============================================================
create table APP_CPJYGYKZ
(
   CPDM                 VARCHAR(16)            not null,
   JYDM                 VARCHAR(8)             not null,
   KZBZ                 VARCHAR(1),
   GYJB                 VARCHAR(2)             not null,
   CXCL                 VARCHAR(1),
   SQGYGW               VARCHAR(8),
   SQGYJB               VARCHAR(2),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_CPJYGYKZ_1 primary key (CPDM, JYDM)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CPJYGYKZ is
'产品柜员交易岗位级别控制表';

comment on column APP_CPJYGYKZ.CPDM is
'产品代码';

comment on column APP_CPJYGYKZ.JYDM is
'交易代码';

comment on column APP_CPJYGYKZ.KZBZ is
'0 不控制 1控制';

comment on column APP_CPJYGYKZ.GYJB is
'数据字典 K_APP_GYJB';

comment on column APP_CPJYGYKZ.CXCL is
'0 交易拒绝 1 检查授权柜员级别 2 检查授权柜员岗位 3 检查授权柜员级别和岗位';

comment on column APP_CPJYGYKZ.SQGYGW is
'数据字典K_APP_GYGW';

comment on column APP_CPJYGYKZ.SQGYJB is
'数据字典K_APP_GYJB';

comment on column APP_CPJYGYKZ.EXTFLD1 is
'扩展参数1';

comment on column APP_CPJYGYKZ.EXTFLD2 is
'扩展参数1';

--==============================================================
-- Table: APP_CPJYJGED
--==============================================================
create table APP_CPJYJGED
(
   CPDM                 VARCHAR(16)            not null,
   JYDM                 VARCHAR(8)             not null,
   JYBZ                 VARCHAR(3)             not null,
   DBEDKZ               VARCHAR(1),
   RLJEDKZ              VARCHAR(1),
   YLJEDKZ              VARCHAR(1),
   JGJB                 VARCHAR(16)            not null,
   DBED                 NUMERIC(16,2),
   YLJED                NUMERIC(16,2),
   RLJED                NUMERIC(16,2),
   CXCL                 VARCHAR(1),
   SQGYGW               VARCHAR(8),
   SQGYJB               VARCHAR(2),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_CPJYJGED_1 primary key (CPDM, JYDM, JYBZ, JGJB)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CPJYJGED is
'产品机构交易额度控制表';

comment on column APP_CPJYJGED.CPDM is
'产品代码';

comment on column APP_CPJYJGED.JYDM is
'交易代码';

comment on column APP_CPJYJGED.DBEDKZ is
'0 不控制 1控制级别 9控制所有机构';

comment on column APP_CPJYJGED.RLJEDKZ is
'0 不控制 1控制级别 9控制所有机构';

comment on column APP_CPJYJGED.YLJEDKZ is
'0 不控制 1控制级别 9控制所有机构';

comment on column APP_CPJYJGED.CXCL is
'0 交易拒绝 1 检查授权柜员级别 2 检查授权柜员岗位 3 检查授权柜员级别和岗位';

comment on column APP_CPJYJGED.EXTFLD1 is
'扩展参数1';

comment on column APP_CPJYJGED.EXTFLD2 is
'扩展参数1';

--==============================================================
-- Table: APP_CPPZGX
--==============================================================
create table APP_CPPZGX
(
   CPDM                 VARCHAR(16)            not null,
   PZXH                 INTEGER                not null,
   PZZL                 VARCHAR(3)             not null,
   CPPZSM               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_CPPZGX_1 primary key (CPDM, PZXH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CPPZGX is
'产品凭证关系表';

comment on column APP_CPPZGX.CPDM is
'产品代码';

comment on column APP_CPPZGX.PZXH is
'凭证序号';

comment on column APP_CPPZGX.PZZL is
'凭证种类';

comment on column APP_CPPZGX.CPPZSM is
'产品凭证说明';

comment on column APP_CPPZGX.EXTFLD1 is
'扩展字段';

comment on column APP_CPPZGX.EXTFLD2 is
'扩展字段2';

--==============================================================
-- Table: APP_CPQDGX
--==============================================================
create table APP_CPQDGX
(
   CPDM                 VARCHAR(16)            not null,
   QDBS                 VARCHAR(3)             not null,
   SJKZBZ               VARCHAR(1),
   QSSJ                 VARCHAR(6),
   JSSJ                 VARCHAR(6),
   XEKZBZ               VARCHAR(1),
   ZXXE                 NUMERIC(16,2),
   ZDXE                 NUMERIC(16,2),
   CZBZ                 VARCHAR(1),
   ZDCZBZ               VARCHAR(1),
   FPBCBZ               VARCHAR(1),
   FPCSFS               VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   ZT                   VARCHAR(1),
   constraint P_K_APP_CPQDGX_1 primary key (CPDM, QDBS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CPQDGX is
'产品渠道关系表';

comment on column APP_CPQDGX.CPDM is
'产品代码';

comment on column APP_CPQDGX.QDBS is
'渠道标识';

comment on column APP_CPQDGX.SJKZBZ is
'时间控制标志  0控制 1不控制';

comment on column APP_CPQDGX.QSSJ is
'起始时间';

comment on column APP_CPQDGX.JSSJ is
'结束时间';

comment on column APP_CPQDGX.XEKZBZ is
'限额控制标志 0控制 1不控制';

comment on column APP_CPQDGX.ZXXE is
'最小限额';

comment on column APP_CPQDGX.ZDXE is
'最大限额';

comment on column APP_CPQDGX.CZBZ is
'是否允许冲正  0允许 1不允许';

comment on column APP_CPQDGX.ZDCZBZ is
'                0：不处理  
                1：异步冲正
                2：同步冲正
                3：重发';

comment on column APP_CPQDGX.FPBCBZ is
'发票保存标志 0保存 1不保存';

comment on column APP_CPQDGX.FPCSFS is
'发票传输方式 0报文 1文件';

comment on column APP_CPQDGX.EXTFLD1 is
'扩展参数1';

comment on column APP_CPQDGX.EXTFLD2 is
'扩展参数2';

comment on column APP_CPQDGX.ZT is
'状态 0允许 1不允许';

--==============================================================
-- Table: APP_CPSXFGX
--==============================================================
create table APP_CPSXFGX
(
   CPDM                 VARCHAR(16)            not null,
   KZTJ1                VARCHAR(32),
   KZTJ2                VARCHAR(32),
   KZTJ3                VARCHAR(32),
   KZTJ4                VARCHAR(32),
   KZTJ5                VARCHAR(32),
   KZTJ6                VARCHAR(32),
   KZTJ7                VARCHAR(32),
   KZTJ8                VARCHAR(32),
   KZTJ9                VARCHAR(32),
   KZTJ10               VARCHAR(32),
   FLBS                 VARCHAR(32)            not null,
   QYRQ                 VARCHAR(8)             not null,
   SXRQ                 VARCHAR(8)             not null,
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(40),
   SM                   VARCHAR(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CPSXFGX is
'根据产品手续费控制属性，建立产品与手续费的关系';

comment on column APP_CPSXFGX.CPDM is
'产品代码';

comment on column APP_CPSXFGX.KZTJ1 is
'从产品手续费控制表中获取的控制属性';

comment on column APP_CPSXFGX.KZTJ2 is
'从产品手续费控制表中获取的控制属性';

comment on column APP_CPSXFGX.KZTJ3 is
'从产品手续费控制表中获取的控制属性';

comment on column APP_CPSXFGX.KZTJ4 is
'从产品手续费控制表中获取的控制属性';

comment on column APP_CPSXFGX.KZTJ5 is
'从产品手续费控制表中获取的控制属性';

comment on column APP_CPSXFGX.KZTJ6 is
'从产品手续费控制表中获取的控制属性';

comment on column APP_CPSXFGX.KZTJ7 is
'从产品手续费控制表中获取的控制属性';

comment on column APP_CPSXFGX.KZTJ8 is
'从产品手续费控制表中获取的控制属性';

comment on column APP_CPSXFGX.KZTJ9 is
'从产品手续费控制表中获取的控制属性';

comment on column APP_CPSXFGX.KZTJ10 is
'从产品手续费控制表中获取的控制属性';

comment on column APP_CPSXFGX.FLBS is
'费率标识';

comment on column APP_CPSXFGX.QYRQ is
'费率启用日期';

comment on column APP_CPSXFGX.SXRQ is
'费率失效日期';

--==============================================================
-- Index: K_APP_CPSXFGX_1
--==============================================================
create unique index K_APP_CPSXFGX_1 on APP_CPSXFGX (
   CPDM                 ASC,
   KZTJ1                ASC,
   KZTJ2                ASC,
   KZTJ3                ASC,
   KZTJ4                ASC,
   KZTJ5                ASC,
   FLBS                 ASC,
   QYRQ                 ASC,
   SXRQ                 ASC
);

--==============================================================
-- Table: APP_CPSXFKZ
--==============================================================
create table APP_CPSXFKZ
(
   CPDM                 VARCHAR(16)            not null,
   XH                   VARCHAR(2),
   KZSX                 VARCHAR(32)            not null,
   KZSXM                VARCHAR(40)            not null,
   SXLYLX               VARCHAR(1),
   KZSXLY               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_CPSXFKZ_1 primary key (CPDM, KZSX)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CPSXFKZ is
'手续费控制表';

comment on column APP_CPSXFKZ.CPDM is
'产品代码';

comment on column APP_CPSXFKZ.XH is
'产品有多个控制属性时，各属性自动生成序号排列，从1开始，与关系表的条件位置对应';

comment on column APP_CPSXFKZ.KZSX is
'如：/app/sxf/khlx';

comment on column APP_CPSXFKZ.KZSXM is
'控制属性的中文说明';

comment on column APP_CPSXFKZ.SXLYLX is
'控制属性值的来源，1 数据库 2 数据字典，用于维护手续费关系时选择控制属性的输入来源';

comment on column APP_CPSXFKZ.KZSXLY is
'如果来源类型为 数据字典，存放字典键值;如果来源是数据库，存放库名和字段名中间逗号隔开,如 T_ORG,org_id  表示控制属性来自机构表的机构号';

comment on column APP_CPSXFKZ.EXTFLD1 is
'说明 ';

comment on column APP_CPSXFKZ.EXTFLD2 is
'说明 ';

--==============================================================
-- Table: APP_CPXX
--==============================================================
create table APP_CPXX
(
   CPDM                 VARCHAR(16)            not null,
   CPMC                 VARCHAR(40),
   YYBS                 VARCHAR(8),
   ZBJG                 VARCHAR(16),
   ZBGY                 VARCHAR(16),
   KHJL                 VARCHAR(20),
   YWRQLX               VARCHAR(1),
   QDKZBZ               VARCHAR(1),
   JGKZCS               VARCHAR(1),
   SXFBZ                VARCHAR(1),
   SFQYBZ               VARCHAR(1),
   QYMS                 VARCHAR(1),
   XYXLJZ               VARCHAR(16),
   KKFS                 VARCHAR(1),
   JZSX                 VARCHAR(1),
   DZMS                 VARCHAR(1),
   ZJYYH                VARCHAR(16),
   ZJZYYH               VARCHAR(16),
   LSBLTS               INTEGER,
   PDBLTS               INTEGER,
   JYFS                 VARCHAR(1),
   RZMS                 VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   CPZT                 VARCHAR(1),
   constraint P_K_APP_CPXX_1 primary key (CPDM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CPXX is
'维护产品的通用属性';

comment on column APP_CPXX.CPDM is
'产品代码';

comment on column APP_CPXX.CPMC is
'产品名称';

comment on column APP_CPXX.ZBJG is
'主办机构';

comment on column APP_CPXX.ZBGY is
'主办柜员';

comment on column APP_CPXX.KHJL is
'客户经理';

comment on column APP_CPXX.YWRQLX is
'业务日期类型 1公共 2私有 默认 1';

comment on column APP_CPXX.QDKZBZ is
'渠道控制标志 0控制 1不控制 默认1';

comment on column APP_CPXX.JGKZCS is
'机构控制参数 见数据字典 KEY=K_JGKZCS 默认0 不控制';

comment on column APP_CPXX.SXFBZ is
'手续费收取标志 0收取 1免收 默认1';

comment on column APP_CPXX.SFQYBZ is
'0不需要签约，1 第三方签约，2主机签约，3 同时签约  默认0 ';

comment on column APP_CPXX.QYMS is
'1  产品代码＋银行帐号 2 产品代码＋用户号 3 产品代码＋银行帐号＋用户号  默认2';

comment on column APP_CPXX.XYXLJZ is
'协议序列键值 默认 K_KHCPQY';

comment on column APP_CPXX.KKFS is
'1全额扣款，2 部分扣款 默认1';

comment on column APP_CPXX.JZSX is
'记账顺序：0先上主机后上第三方（默认）
                    1先上第三方后上主机';

comment on column APP_CPXX.DZMS is
'对帐模式 1银行为主 2第三方为主';

comment on column APP_CPXX.LSBLTS is
'流水保留天数';

comment on column APP_CPXX.PDBLTS is
'凭单保留天数';

comment on column APP_CPXX.JYFS is
'交易方式 见数据字典 KEY=K_JYFS';

comment on column APP_CPXX.RZMS is
'0调试  1 生产 默认 1';

comment on column APP_CPXX.EXTFLD1 is
'扩展参数1';

comment on column APP_CPXX.EXTFLD2 is
'扩展参数2';

comment on column APP_CPXX.CPZT is
'产品状态 见数据字典 KEY=K_CPZT';

--==============================================================
-- Table: APP_CSKZ
--==============================================================
create table APP_CSKZ
(
   CSJZ                 VARCHAR(20)            not null,
   CSLX                 VARCHAR(1),
   CSTJ                 VARCHAR(8),
   JDM                  VARCHAR(80)            not null,
   JDZ                  VARCHAR(40)            not null,
   REMARK               VARCHAR(40),
   JZLX                 VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_CSKZ_1 primary key (CSJZ)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_CSKZ is
'参数控制表';

comment on column APP_CSKZ.CSJZ is
'参数键值';

comment on column APP_CSKZ.CSLX is
'参数类型 见数据字典 KEY=K_CSLX';

comment on column APP_CSKZ.CSTJ is
'参数条件 如果类型为渠道则输入渠道标识如果为应用输入应用标识';

comment on column APP_CSKZ.JDM is
'节点名';

comment on column APP_CSKZ.JDZ is
'节点值';

comment on column APP_CSKZ.REMARK is
'说明';

comment on column APP_CSKZ.JZLX is
'加载类型 0自动 1非自动';

--==============================================================
-- Table: APP_DICT
--==============================================================
create table APP_DICT
(
   PKEY                 VARCHAR(20)            not null,
   KEYJS                VARCHAR(30)            not null,
   PVAL                 VARCHAR(20)            not null,
   PROMPT               VARCHAR(60)            not null,
   SSYY                 VARCHAR(8)             not null,
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_DICT_1 primary key (PKEY, PVAL)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_DICT is
'数据字典表';

comment on column APP_DICT.KEYJS is
'KEY值解释';

comment on column APP_DICT.SSYY is
'应用标识';

--==============================================================
-- Table: APP_DRLS
--==============================================================
create table APP_DRLS
(
   PTRQ                 VARCHAR(8)             not null,
   PTLS                 INTEGER                not null,
   PTSJ                 VARCHAR(6),
   RZBZ                 VARCHAR(1),
   JYLX                 VARCHAR(1),
   YPTLS                INTEGER,
   JYJG                 VARCHAR(16),
   JYGY                 VARCHAR(16),
   QDBS                 VARCHAR(3),
   ZDSBBH               VARCHAR(8),
   YYBS                 VARCHAR(8),
   CPDM                 VARCHAR(16),
   YWBH                 VARCHAR(16),
   JYDM                 VARCHAR(8),
   YHBH                 VARCHAR(32),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   ZHLX                 VARCHAR(2),
   YHZH                 VARCHAR(32),
   DFZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   PCBH                 INTEGER,
   JYXYM                VARCHAR(8),
   JYXYXX               VARCHAR(60),
   JYZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_PK_APP_DRLS primary key (PTRQ, PTLS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_DRLS is
'平台公共流水表';

comment on column APP_DRLS.PTRQ is
'平台日期 YYYYMMDD';

comment on column APP_DRLS.PTLS is
'平台流水号';

comment on column APP_DRLS.PTSJ is
'平台时间 HHMMSS';

comment on column APP_DRLS.RZBZ is
'入帐标志 0入帐 1非入帐';

comment on column APP_DRLS.JYLX is
'交易类型 0正交易 1反交易 9其他';

comment on column APP_DRLS.YPTLS is
'原平台流水号';

comment on column APP_DRLS.JYJG is
'交易机构';

comment on column APP_DRLS.JYGY is
'交易柜员';

comment on column APP_DRLS.QDBS is
'渠道标识 ';

comment on column APP_DRLS.ZDSBBH is
'终端设备编号';

comment on column APP_DRLS.YYBS is
'应用标识 ';

comment on column APP_DRLS.CPDM is
'产品代码';

comment on column APP_DRLS.YWBH is
'业务编号';

comment on column APP_DRLS.JYDM is
'交易代码';

comment on column APP_DRLS.YHBH is
'用户编号 如手机号';

comment on column APP_DRLS.XZBZ is
'现转标志  0现金 1转帐';

comment on column APP_DRLS.JDBZ is
'借贷标志  见数据字典KEY=K_JDBZ';

comment on column APP_DRLS.ZHLX is
'帐户类型  见数据字典KEY=K_ZHLX';

comment on column APP_DRLS.YHZH is
'银行帐号';

comment on column APP_DRLS.DFZH is
'对方帐号';

comment on column APP_DRLS.JYJE is
'交易金额';

comment on column APP_DRLS.SXF is
'手续费';

comment on column APP_DRLS.PCBH is
'批次编号';

comment on column APP_DRLS.JYXYM is
'交易响应码';

comment on column APP_DRLS.JYXYXX is
'交易响应信息';

comment on column APP_DRLS.JYZT is
'交易状态见数据字典KEY=K_JYZT';

comment on column APP_DRLS.EXTFLD1 is
'扩展1';

comment on column APP_DRLS.EXTFLD2 is
'扩展2';

--==============================================================
-- Index: K_APP_DRLS_1
--==============================================================
create index K_APP_DRLS_1 on APP_DRLS (
   PTRQ                 ASC,
   PTLS                 ASC,
   YWBH                 ASC
);

--==============================================================
-- Table: APP_DWCPXY
--==============================================================
create table APP_DWCPXY
(
   DWBH                 VARCHAR(16)            not null,
   CPDM                 VARCHAR(16)            not null,
   YWBH                 VARCHAR(16)            not null,
   YWMC                 VARCHAR(40),
   XYBH                 VARCHAR(20),
   YHDM                 VARCHAR(16),
   LJBS                 VARCHAR(8),
   ZHLX                 VARCHAR(2),
   SFBZ                 VARCHAR(1),
   DSZH                 VARCHAR(32),
   DSZHMC               VARCHAR(80),
   DFZH                 VARCHAR(32),
   DFZHMC               VARCHAR(80),
   KHJL                 VARCHAR(20),
   LXR                  VARCHAR(20),
   EMAIL                VARCHAR(32),
   LXDH                 VARCHAR(16),
   HYKSRQ               VARCHAR(8),
   HYJSRQ               VARCHAR(8),
   BLJG                 VARCHAR(16),
   BLGY                 VARCHAR(16),
   BLRQ                 VARCHAR(8),
   ZHZDED               NUMERIC(16,2),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   QYZT                 VARCHAR(1),
   constraint P_K_APP_DWCPXY_2 primary key (YWBH),
   constraint A_K_APP_CPDWXY_1 unique (DWBH, CPDM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_DWCPXY is
'单位产品协议表';

comment on column APP_DWCPXY.DWBH is
'单位编号';

comment on column APP_DWCPXY.CPDM is
'产品代码';

comment on column APP_DWCPXY.YWBH is
'业务编号 代收付业务填代理业务编号，银保通填险种';

comment on column APP_DWCPXY.XYBH is
'合同编号';

comment on column APP_DWCPXY.YHDM is
'银行在第三方的编码';

comment on column APP_DWCPXY.ZHLX is
'账户类型 见数据字典 KEY=K_ZHLX';

comment on column APP_DWCPXY.SFBZ is
'1 收 2 付 3 其他 
见数据字典 K_SFBZ';

comment on column APP_DWCPXY.DSZH is
'签约账户';

comment on column APP_DWCPXY.DSZHMC is
'账户户名';

comment on column APP_DWCPXY.DFZH is
'签约账户';

comment on column APP_DWCPXY.DFZHMC is
'账户户名';

comment on column APP_DWCPXY.KHJL is
'客户经理';

comment on column APP_DWCPXY.HYKSRQ is
'合约开始日期';

comment on column APP_DWCPXY.HYJSRQ is
'合约结束日期';

comment on column APP_DWCPXY.BLJG is
'办理机构';

comment on column APP_DWCPXY.BLGY is
'办理柜员';

comment on column APP_DWCPXY.BLRQ is
'办理日期';

comment on column APP_DWCPXY.ZHZDED is
'账户最低额度';

comment on column APP_DWCPXY.EXTFLD1 is
'扩展参数1';

comment on column APP_DWCPXY.EXTFLD2 is
'扩展参数2';

comment on column APP_DWCPXY.QYZT is
'签约状态 0正常 1撤消';

--==============================================================
-- Table: APP_DWXX
--==============================================================
create table APP_DWXX
(
   DWBH                 VARCHAR(16)            not null,
   DWMC                 VARCHAR(80),
   DWZJLX               VARCHAR(2),
   DWZJHM               VARCHAR(32),
   DWLXR                VARCHAR(16),
   DWLXRDH              VARCHAR(16),
   DWDZ                 VARCHAR(60),
   DWEMAIL              VARCHAR(32),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   ZT                   VARCHAR(1),
   constraint P_K_APP_DWXX_1 primary key (DWBH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_DWXX is
'单位信息表';

comment on column APP_DWXX.DWMC is
'单位名称';

comment on column APP_DWXX.DWZJLX is
'单位证件类型 见数据字典 KEY=K_DWZJLX';

comment on column APP_DWXX.DWZJHM is
'单位证件号码';

comment on column APP_DWXX.DWLXR is
'单位联系人名称';

comment on column APP_DWXX.DWLXRDH is
'单位联系人电话';

comment on column APP_DWXX.DWDZ is
'单位联系地址';

comment on column APP_DWXX.DWEMAIL is
'单位联系email';

comment on column APP_DWXX.EXTFLD1 is
'扩展参数1';

comment on column APP_DWXX.EXTFLD2 is
'扩展参数2';

comment on column APP_DWXX.ZT is
'状态 0 正常 X删除';

--==============================================================
-- Table: APP_GYSQED
--==============================================================
create table APP_GYSQED
(
   CPDM                 VARCHAR(16)            not null,
   JYDM                 VARCHAR(8)             not null,
   GYJB                 VARCHAR(8)             not null,
   GYGW                 VARCHAR(8)             not null,
   JYBZ                 VARCHAR(3)             not null,
   GYDBSQED             NUMERIC(16,2),
   GYRLJSQED            NUMERIC(16,2),
   GYYLJSQED            NUMERIC(16,2),
   JGDBSQED             NUMERIC(16,2),
   JGRLJSQED            NUMERIC(16,2),
   JGYLJSQED            NUMERIC(16,2),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_GYSQED_1 primary key (CPDM, JYDM, GYJB, GYGW, JYBZ)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_GYSQED is
'柜员产品授权额度表';

comment on column APP_GYSQED.CPDM is
'产品代码';

comment on column APP_GYSQED.JYDM is
'交易代码';

comment on column APP_GYSQED.GYJB is
'柜员级别';

comment on column APP_GYSQED.GYGW is
'柜员岗位';

comment on column APP_GYSQED.JYBZ is
'交易币种';

comment on column APP_GYSQED.GYDBSQED is
'柜员单笔额度';

comment on column APP_GYSQED.GYRLJSQED is
'柜员日累计额度';

comment on column APP_GYSQED.GYYLJSQED is
'柜员月累计额度';

comment on column APP_GYSQED.JGDBSQED is
'机构单笔额度';

comment on column APP_GYSQED.JGRLJSQED is
'机构日累计额度';

comment on column APP_GYSQED.JGYLJSQED is
'机构累计额度';

comment on column APP_GYSQED.EXTFLD1 is
'扩展参数1';

comment on column APP_GYSQED.EXTFLD2 is
'扩展参数2';

--==============================================================
-- Table: APP_GYXX
--==============================================================
create table APP_GYXX
(
   GYH                  VARCHAR(16)            not null,
   JGBH                 VARCHAR(16),
   MM                   VARCHAR(32),
   GYJB                 VARCHAR(2),
   GYGW                 VARCHAR(32),
   GYMC                 VARCHAR(16),
   EMAIL                VARCHAR(32),
   FAX                  VARCHAR(16),
   TEL                  VARCHAR(16),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   ZT                   VARCHAR(1),
   constraint P_K_APP_QYXX_1 primary key (GYH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_GYXX is
'柜员信息表';

comment on column APP_GYXX.GYH is
'柜员号';

comment on column APP_GYXX.JGBH is
'机构编号';

comment on column APP_GYXX.MM is
'柜员密码';

comment on column APP_GYXX.GYJB is
'柜员级别';

comment on column APP_GYXX.GYGW is
'柜员岗位';

comment on column APP_GYXX.GYMC is
'柜员名称';

comment on column APP_GYXX.EMAIL is
'email地址';

comment on column APP_GYXX.FAX is
'传真';

comment on column APP_GYXX.TEL is
'电话';

comment on column APP_GYXX.EXTFLD1 is
'扩展参数1';

comment on column APP_GYXX.EXTFLD2 is
'扩展参数2';

comment on column APP_GYXX.ZT is
'状态';

--==============================================================
-- Table: APP_HIS_DRLS
--==============================================================
create table APP_HIS_DRLS
(
   PTRQ                 VARCHAR(8)             not null,
   PTLS                 INTEGER                not null,
   PTSJ                 VARCHAR(6),
   RZBZ                 VARCHAR(1),
   JYLX                 VARCHAR(1),
   YPTLS                INTEGER,
   JYJG                 VARCHAR(16),
   JYGY                 VARCHAR(16),
   QDBS                 VARCHAR(3),
   ZDSBBH               VARCHAR(8),
   YYBS                 VARCHAR(8),
   CPDM                 VARCHAR(16),
   YWBH                 VARCHAR(16),
   JYDM                 VARCHAR(8),
   YHBH                 VARCHAR(32),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   ZHLX                 VARCHAR(2),
   YHZH                 VARCHAR(32),
   DFZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   PCBH                 INTEGER,
   JYXYM                VARCHAR(8),
   JYXYXX               VARCHAR(60),
   JYZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_PK_APP_DRLS primary key (PTRQ, PTLS)
) IN GAPS_HIS_DATA INDEX IN GAPS_HIS_INDEX ;

comment on table APP_HIS_DRLS is
'平台公共流水表历史表';

comment on column APP_HIS_DRLS.PTRQ is
'平台日期 YYYYMMDD';

comment on column APP_HIS_DRLS.PTLS is
'平台流水号';

comment on column APP_HIS_DRLS.PTSJ is
'平台时间 HHMMSS';

comment on column APP_HIS_DRLS.RZBZ is
'入帐标志 0入帐 1非入帐';

comment on column APP_HIS_DRLS.JYLX is
'交易类型 0正交易 1反交易 9其他';

comment on column APP_HIS_DRLS.YPTLS is
'原平台流水号';

comment on column APP_HIS_DRLS.JYJG is
'交易机构';

comment on column APP_HIS_DRLS.JYGY is
'交易柜员';

comment on column APP_HIS_DRLS.QDBS is
'渠道标识 ';

comment on column APP_HIS_DRLS.ZDSBBH is
'终端设备编号';

comment on column APP_HIS_DRLS.YYBS is
'应用标识 ';

comment on column APP_HIS_DRLS.CPDM is
'产品代码';

comment on column APP_HIS_DRLS.YWBH is
'业务编号';

comment on column APP_HIS_DRLS.JYDM is
'交易代码';

comment on column APP_HIS_DRLS.YHBH is
'用户编号 如手机号 水务号';

comment on column APP_HIS_DRLS.XZBZ is
'现转标志  0现金 1转帐';

comment on column APP_HIS_DRLS.JDBZ is
'借贷标志  见数据字典KEY=K_JDBZ';

comment on column APP_HIS_DRLS.ZHLX is
'帐户类型  见数据字典KEY=K_ZHLX';

comment on column APP_HIS_DRLS.YHZH is
'银行帐号';

comment on column APP_HIS_DRLS.DFZH is
'对方帐号';

comment on column APP_HIS_DRLS.JYJE is
'交易金额';

comment on column APP_HIS_DRLS.SXF is
'手续费';

comment on column APP_HIS_DRLS.PCBH is
'批次编号';

comment on column APP_HIS_DRLS.JYXYM is
'交易响应码';

comment on column APP_HIS_DRLS.JYXYXX is
'交易响应信息';

comment on column APP_HIS_DRLS.JYZT is
'交易状态见数据字典KEY=K_JYZT';

comment on column APP_HIS_DRLS.EXTFLD1 is
'扩展1';

comment on column APP_HIS_DRLS.EXTFLD2 is
'扩展2';

--==============================================================
-- Index: K_APP_DRLS_2
--==============================================================
create index K_APP_DRLS_2 on APP_HIS_DRLS (
   PTRQ                 ASC,
   PTLS                 ASC,
   YWBH                 ASC
);

--==============================================================
-- Table: APP_JJRDJ
--==============================================================
create table APP_JJRDJ
(
   RQ                   VARCHAR(8)             not null,
   JRBZ                 VARCHAR(1)             not null,
   EXTFLD1              VARCHAR(20),
   constraint P_K_APP_JJRDJ_1 primary key (RQ)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_JJRDJ is
'设置节日标志';

comment on column APP_JJRDJ.RQ is
'日期';

comment on column APP_JJRDJ.JRBZ is
'节假日标志 0  是 1否 ';

comment on column APP_JJRDJ.EXTFLD1 is
'扩展1';

--==============================================================
-- Table: APP_JYXX
--==============================================================
create table APP_JYXX
(
   JYDM                 VARCHAR(8)             not null,
   JYMC                 VARCHAR(40),
   YYBS                 VARCHAR(8),
   JYLX                 VARCHAR(1),
   LSJLBZ               VARCHAR(1),
   RZBZ                 VARCHAR(1),
   BBBZ                 VARCHAR(1),
   CPXG                 VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   QTBZ                 VARCHAR(1),
   constraint P_K_APP_JYXX_1 primary key (JYDM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_JYXX is
'交易信息控制表';

comment on column APP_JYXX.JYDM is
'交易代码';

comment on column APP_JYXX.JYMC is
'交易名称';

comment on column APP_JYXX.YYBS is
'应用标识 应用标识 见app_yyxx表';

comment on column APP_JYXX.JYLX is
'交易类型 0正交易 1反交易 9其他';

comment on column APP_JYXX.LSJLBZ is
'流水记录标志 0记录 1不记录';

comment on column APP_JYXX.RZBZ is
'入帐标志 0入帐 1非入帐';

comment on column APP_JYXX.BBBZ is
'报表标志 0报表 1非报表';

comment on column APP_JYXX.CPXG is
'产品相关 0相关 1不相关(交易与产品无关时，交易的机构，渠道，交易时间，限额等都不做控制)';

comment on column APP_JYXX.EXTFLD1 is
'扩展参数1';

comment on column APP_JYXX.EXTFLD2 is
'扩展参数2';

comment on column APP_JYXX.QTBZ is
'启停标志 0开启 1关闭';

--==============================================================
-- Table: APP_KHCPQY
--==============================================================
create table APP_KHCPQY
(
   XYBH                 VARCHAR(20)            not null,
   KHBH                 VARCHAR(16),
   CPDM                 VARCHAR(16)            not null,
   YWBH                 VARCHAR(16)            not null,
   ZHLX                 VARCHAR(2),
   KHJG                 VARCHAR(16),
   QYZH                 VARCHAR(32),
   ZHHM                 VARCHAR(80),
   DLZJLX               VARCHAR(3),
   DLZJHM               VARCHAR(32),
   ZJLX                 VARCHAR(3),
   ZJHM                 VARCHAR(32),
   QYLX                 VARCHAR(1),
   KHJL                 VARCHAR(20),
   HYKSRQ               VARCHAR(8),
   HYJSRQ               VARCHAR(8),
   KTQD                 VARCHAR(60),
   BLJG                 VARCHAR(16),
   BLGY                 VARCHAR(16),
   BLRQ                 VARCHAR(8),
   YHH1                 VARCHAR(32),
   YHH2                 VARCHAR(32),
   YHH3                 VARCHAR(32),
   YHMC                 VARCHAR(80),
   YHLX                 VARCHAR(16),
   YHYB                 VARCHAR(6),
   YHDH                 VARCHAR(12),
   YHDZ                 VARCHAR(60),
   JYBZ                 VARCHAR(3),
   KKZDXE               NUMERIC(13,2),
   KKZQ                 VARCHAR(1),
   YDKKRQ               VARCHAR(8),
   KKZT                 VARCHAR(1),
   KKRQ                 VARCHAR(8),
   DXTZBZ               VARCHAR(1),
   ZHZDED               NUMERIC(13,2),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   EXTFLD4              VARCHAR(40),
   EXTFLD5              VARCHAR(40),
   EXTFLD6              VARCHAR(254),
   QYZT                 VARCHAR(1),
   constraint P_K_APP_CPKHQY_1 primary key (XYBH, CPDM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_KHCPQY is
'客户产品签约表';

comment on column APP_KHCPQY.XYBH is
'协议编号 由序列生成（产品信息表中配置）';

comment on column APP_KHCPQY.CPDM is
'产品代码';

comment on column APP_KHCPQY.YWBH is
'业务编号 ';

comment on column APP_KHCPQY.ZHLX is
'账户类型 ';

comment on column APP_KHCPQY.KHJG is
'签约账户开户机构';

comment on column APP_KHCPQY.QYZH is
'签约账户';

comment on column APP_KHCPQY.ZHHM is
'账户户名';

comment on column APP_KHCPQY.DLZJLX is
'代理人证件类型 见数据字典 KEY=K_ZJLX';

comment on column APP_KHCPQY.DLZJHM is
'代理人证件号码';

comment on column APP_KHCPQY.ZJLX is
'证件类型 见数据字典 KEY=K_ZJLX';

comment on column APP_KHCPQY.ZJHM is
'证件号码';

comment on column APP_KHCPQY.QYLX is
'签约类型 0联机 1批量 9其他';

comment on column APP_KHCPQY.KHJL is
'客户经理';

comment on column APP_KHCPQY.HYKSRQ is
'合约开始日期';

comment on column APP_KHCPQY.HYJSRQ is
'合约结束日期';

comment on column APP_KHCPQY.KTQD is
'开通渠道  渠道标识通过 | 后分隔， ALL表示全开通';

comment on column APP_KHCPQY.BLJG is
'办理机构';

comment on column APP_KHCPQY.BLGY is
'办理柜员';

comment on column APP_KHCPQY.BLRQ is
'办理日期';

comment on column APP_KHCPQY.YHH1 is
'用户号1';

comment on column APP_KHCPQY.YHH2 is
'用户号2';

comment on column APP_KHCPQY.YHH3 is
'用户号3';

comment on column APP_KHCPQY.YHMC is
'用户名称(第三方用户名称)';

comment on column APP_KHCPQY.YHLX is
'用户类型(第三方用户类型)';

comment on column APP_KHCPQY.YHYB is
'用户邮编(第三方用户邮编)';

comment on column APP_KHCPQY.YHDH is
'用户电话(第三方用户电话)';

comment on column APP_KHCPQY.YHDZ is
'用户地址(第三方用户地址)';

comment on column APP_KHCPQY.JYBZ is
'交易币种';

comment on column APP_KHCPQY.KKZDXE is
'扣款最大限额';

comment on column APP_KHCPQY.KKZQ is
'扣款周期  --0-没周期，1-日，2-周，3-月，4-年';

comment on column APP_KHCPQY.YDKKRQ is
'约定扣款日期';

comment on column APP_KHCPQY.KKZT is
'最近一次扣款状态 0 – 成功  1 – 部分成功  2-失败 
';

comment on column APP_KHCPQY.KKRQ is
'最近一次扣款日期';

comment on column APP_KHCPQY.DXTZBZ is
'短信通知标志 0通知 1不通知';

comment on column APP_KHCPQY.ZHZDED is
'账户最低额度';

comment on column APP_KHCPQY.EXTFLD1 is
'扩展参数1';

comment on column APP_KHCPQY.EXTFLD2 is
'扩展参数2';

comment on column APP_KHCPQY.EXTFLD3 is
'扩展参数3';

comment on column APP_KHCPQY.EXTFLD4 is
'扩展参数4';

comment on column APP_KHCPQY.EXTFLD5 is
'扩展参数5';

comment on column APP_KHCPQY.EXTFLD6 is
'扩展参数6';

comment on column APP_KHCPQY.QYZT is
'签约状态 0正常 1撤消';

--==============================================================
-- Index: K_APP_INDEX_1
--==============================================================
create index K_APP_INDEX_1 on APP_KHCPQY (
   CPDM                 ASC,
   QYZH                 ASC,
   YHH1                 ASC,
   QYZT                 ASC
);

--==============================================================
-- Table: APP_KHXX
--==============================================================
create table APP_KHXX
(
   KHBH                 VARCHAR(16)            not null,
   KHXM                 VARCHAR(80),
   YWXM                 VARCHAR(40),
   BM                   VARCHAR(20),
   KHLX                 VARCHAR(1),
   ZJKHBH               VARCHAR(32),
   ZJLX                 VARCHAR(3)             not null,
   ZJHM                 VARCHAR(32)            not null,
   CSNY                 VARCHAR(8),
   SEX                  VARCHAR(1),
   GJ                   VARCHAR(3),
   HK                   VARCHAR(60),
   HYZK                 VARCHAR(1),
   JYCD                 VARCHAR(1),
   ZY                   VARCHAR(3),
   ZW                   VARCHAR(20),
   SRQK                 NUMERIC(16,2),
   GSDZ                 VARCHAR(60),
   GSYB                 VARCHAR(6),
   GSDH                 VARCHAR(16),
   ZZDZ                 VARCHAR(60),
   ZZYB                 VARCHAR(6),
   ZZDH                 VARCHAR(16),
   SJHM                 VARCHAR(16),
   MEMAIL               VARCHAR(32),
   YJDZLX               VARCHAR(1),
   BZ                   VARCHAR(1),
   constraint P_K_APP_KHXX_1 primary key (KHBH),
   constraint A_K_APP_KHXX_2 unique (ZJLX, ZJHM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_KHXX is
'客户信息表';

comment on column APP_KHXX.KHBH is
'客户编号 由序列 K_KHBH 生成';

comment on column APP_KHXX.KHXM is
'客户姓名';

comment on column APP_KHXX.YWXM is
'英文姓名';

comment on column APP_KHXX.BM is
'别名';

comment on column APP_KHXX.KHLX is
'客户类型 见数据字典KEY=K_KHLX';

comment on column APP_KHXX.ZJKHBH is
'主机客户编号';

comment on column APP_KHXX.ZJLX is
'证件类型 见数据字典KEY=K_ZJLX';

comment on column APP_KHXX.ZJHM is
'证件号码';

comment on column APP_KHXX.CSNY is
'出生年月';

comment on column APP_KHXX.SEX is
'性别 见数据字典KEY=K_SEX';

comment on column APP_KHXX.GJ is
'国籍';

comment on column APP_KHXX.HK is
'户口';

comment on column APP_KHXX.HYZK is
'婚姻状况 0未婚 1已婚 2离婚 9未知';

comment on column APP_KHXX.JYCD is
'教育程度 见数据字典KEY=K_JYCD';

comment on column APP_KHXX.ZY is
'职业  根据国家标准';

comment on column APP_KHXX.ZW is
'职务';

comment on column APP_KHXX.SRQK is
'收入情况年';

comment on column APP_KHXX.GSDZ is
'公司地址';

comment on column APP_KHXX.GSYB is
'公司邮编';

comment on column APP_KHXX.GSDH is
'公司电话';

comment on column APP_KHXX.ZZDZ is
'住宅地址';

comment on column APP_KHXX.ZZYB is
'住宅邮编';

comment on column APP_KHXX.ZZDH is
'住宅电话';

comment on column APP_KHXX.SJHM is
'手机号码';

comment on column APP_KHXX.MEMAIL is
'电子邮箱';

comment on column APP_KHXX.YJDZLX is
'邮寄地址类型 1公司地址2住宅地址';

comment on column APP_KHXX.BZ is
'标志 0正常 1无效 X删除';

--==============================================================
-- Table: APP_KZSX
--==============================================================
create table APP_KZSX
(
   PKEY                 VARCHAR(40)            not null,
   CSMC                 VARCHAR(20)            not null,
   CSSM                 VARCHAR(80)            not null,
   CSZ                  VARCHAR(80),
   EXTFLD               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_KZSX_1 primary key (PKEY, CSMC)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_KZSX is
'扩展属性表';

comment on column APP_KZSX.PKEY is
'键值 存放需要扩充参数的表的表名 + 记录的唯一关键值，存在多个字段通过"|"分隔
如 CPXX_001';

comment on column APP_KZSX.CSMC is
'表示扩充后的字段用英文字母表示，类似于表字段名称';

comment on column APP_KZSX.CSSM is
'参数说明';

comment on column APP_KZSX.CSZ is
'参数的值';

comment on column APP_KZSX.EXTFLD is
'扩展参数 存放关联表名';

--==============================================================
-- Table: APP_MJSJ
--==============================================================
create table APP_MJSJ
(
   MJID                 VARCHAR(16)            not null,
   MJSM                 VARCHAR(40),
   SJXH                 INTEGER                not null,
   QSBZ                 VARCHAR(1),
   REQ1                 VARCHAR(40)            not null,
   REQ2                 VARCHAR(40),
   REQ3                 VARCHAR(40),
   REQ4                 VARCHAR(40),
   REQ5                 VARCHAR(40),
   REQ6                 VARCHAR(40),
   REQ7                 VARCHAR(40),
   REQ8                 VARCHAR(40),
   REQ9                 VARCHAR(40),
   REQ10                VARCHAR(40),
   RESP1                VARCHAR(40)            not null,
   RESP2                VARCHAR(40),
   RESP3                VARCHAR(40),
   RESP4                VARCHAR(40),
   RESP5                VARCHAR(40),
   RESP6                VARCHAR(40),
   RESP7                VARCHAR(40),
   RESP8                VARCHAR(40),
   RESP9                VARCHAR(40),
   RESP10               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_MJSJ_1 primary key (MJID, SJXH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_MJSJ is
'枚举数据表';

comment on column APP_MJSJ.MJID is
'枚举ID';

comment on column APP_MJSJ.MJSM is
'枚举说明';

comment on column APP_MJSJ.SJXH is
'数据序号';

comment on column APP_MJSJ.QSBZ is
'缺省标识  0是 1非';

--==============================================================
-- Table: APP_MJSX
--==============================================================
create table APP_MJSX
(
   MJID                 VARCHAR(16)            not null,
   MJSM                 VARCHAR(40)            not null,
   SXLX                 VARCHAR(1)             not null,
   SXXH                 VARCHAR(2)             not null,
   SXMC                 VARCHAR(16)            not null,
   SXNR                 VARCHAR(40)            not null,
   SXSM                 VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_MJSX_1 primary key (MJID, SXLX, SXXH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_MJSX is
'枚举属性控制表';

comment on column APP_MJSX.MJID is
'枚举ID';

comment on column APP_MJSX.MJSM is
'枚举说明';

comment on column APP_MJSX.SXLX is
'属性类型 1条件 2结果';

comment on column APP_MJSX.SXXH is
'属性根据属性类型，从1开始，不能大于10，与关系表的位置相对应';

comment on column APP_MJSX.SXMC is
'属性名称';

comment on column APP_MJSX.SXNR is
'如果类型为条件，表示数据的来源，如果类型为结果，数据的目的';

comment on column APP_MJSX.SXSM is
'属性的中文说明';

--==============================================================
-- Table: APP_PZGLKZ
--==============================================================
create table APP_PZGLKZ
(
   PTRQ                 VARCHAR(8)             not null,
   PTSJ                 VARCHAR(6),
   PTLS                 INTEGER                not null,
   JYJG                 VARCHAR(16)            not null,
   JYGY                 VARCHAR(16)            not null,
   PZCZDZ               VARCHAR(2),
   CZLX                 VARCHAR(1),
   CZFX                 VARCHAR(1),
   PZLY                 VARCHAR(32),
   PZMD                 VARCHAR(32),
   PZSL                 INTEGER,
   QSHM                 VARCHAR(32),
   JSHM                 VARCHAR(32),
   JYZT                 VARCHAR(1),
   EXTFLD               VARCHAR(40),
   SM                   VARCHAR(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_PZGLKZ is
'凭证管理控制表';

comment on column APP_PZGLKZ.PTRQ is
'平台日期';

comment on column APP_PZGLKZ.PTSJ is
'平台时间';

comment on column APP_PZGLKZ.PTLS is
'平台流水号';

comment on column APP_PZGLKZ.JYJG is
'交易机构';

comment on column APP_PZGLKZ.JYGY is
'交易柜员';

comment on column APP_PZGLKZ.PZCZDZ is
'凭证操作动作  见数据字典 KEY=K_PZCZDZ';

comment on column APP_PZGLKZ.CZLX is
'操作类型 0 系统内 1系统外';

comment on column APP_PZGLKZ.CZFX is
'操作方向 0 向上级 1向下级 2对外 3其他';

comment on column APP_PZGLKZ.PZLY is
'凭证来源 格式：机构|柜员 ，如果为机构间操作，柜员为空';

comment on column APP_PZGLKZ.PZMD is
'凭证目的 格式：机构|柜员 ，如果为机构间操作，柜员为空';

comment on column APP_PZGLKZ.PZSL is
'凭证数量';

comment on column APP_PZGLKZ.QSHM is
'起始号码';

comment on column APP_PZGLKZ.JSHM is
'结束号码';

comment on column APP_PZGLKZ.JYZT is
'交易状态 0 请求 1完成 9取消';

comment on column APP_PZGLKZ.EXTFLD is
'扩展字段';

comment on column APP_PZGLKZ.SM is
'说明';

--==============================================================
-- Table: APP_PZHMDJ
--==============================================================
create table APP_PZHMDJ
(
   PZZL                 VARCHAR(3)             not null,
   PZHM                 VARCHAR(32)            not null,
   PZWZ                 VARCHAR(34),
   NBJG                 VARCHAR(34),
   PZZT                 VARCHAR(1),
   GXRQ                 VARCHAR(8),
   GXSJ                 VARCHAR(6),
   GXLS                 INTEGER,
   GXJG                 VARCHAR(16),
   GXGY                 VARCHAR(16),
   GXSM                 VARCHAR(40),
   PZNR                 VARCHAR(80),
   EXFLD                VARCHAR(40),
   SM                   VARCHAR(40),
   constraint P_K_APP_PZHMDJ_1 primary key (PZZL, PZHM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_PZHMDJ is
'凭证号码登记表';

comment on column APP_PZHMDJ.PZZL is
'凭证种类';

comment on column APP_PZHMDJ.PZHM is
'凭证号码';

comment on column APP_PZHMDJ.PZWZ is
'凭证位置 格式：机构|柜员';

comment on column APP_PZHMDJ.NBJG is
'内部机构';

comment on column APP_PZHMDJ.PZZT is
'凭证状态 0正常 1已使用 2已作废 3在途';

comment on column APP_PZHMDJ.GXRQ is
'更新日期';

comment on column APP_PZHMDJ.GXSJ is
'更新时间';

comment on column APP_PZHMDJ.GXLS is
'更新流水';

comment on column APP_PZHMDJ.GXJG is
'更新机构';

comment on column APP_PZHMDJ.GXGY is
'更新柜员';

comment on column APP_PZHMDJ.GXSM is
'更新说明';

comment on column APP_PZHMDJ.PZNR is
'凭证内容';

comment on column APP_PZHMDJ.EXFLD is
'扩展字段';

comment on column APP_PZHMDJ.SM is
'说明';

--==============================================================
-- Table: APP_PZSLDJ
--==============================================================
create table APP_PZSLDJ
(
   PZZL                 VARCHAR(3)             not null,
   PZWZ                 VARCHAR(34)            not null,
   NBJG                 VARCHAR(34),
   PZZT                 VARCHAR(1)             not null,
   PZSL                 INTEGER,
   EXFLD                VARCHAR(40),
   SM                   VARCHAR(40),
   constraint P_K_APP_PZSLDJ_1 primary key (PZZL, PZWZ, PZZT)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_PZSLDJ is
'凭证数量登记表';

comment on column APP_PZSLDJ.PZZL is
'凭证种类';

comment on column APP_PZSLDJ.PZWZ is
'凭证位置 格式：机构|柜员';

comment on column APP_PZSLDJ.NBJG is
'内部机构';

comment on column APP_PZSLDJ.PZZT is
'凭证状态 0正常 1已使用 2已作废 3在途';

comment on column APP_PZSLDJ.PZSL is
'凭证数量';

comment on column APP_PZSLDJ.EXFLD is
'扩展字段';

comment on column APP_PZSLDJ.SM is
'说明';

--==============================================================
-- Table: APP_PZXX
--==============================================================
create table APP_PZXX
(
   PTRQ                 VARCHAR(8)             not null,
   PTLS                 INTEGER                not null,
   PZXH                 INTEGER                not null,
   YWLS                 INTEGER,
   YWRQ                 VARCHAR(8),
   YYBS                 VARCHAR(8),
   CPDM                 VARCHAR(16)            not null,
   YHBH                 VARCHAR(32),
   YHBSH                VARCHAR(32),
   KHMC                 VARCHAR(80),
   YHZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   JYJE2                NUMERIC(16,2),
   JYJE3                NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   JFZQ                 VARCHAR(16),
   QSRQ                 VARCHAR(10),
   JSRQ                 VARCHAR(10),
   SJDM                 VARCHAR(10),
   QDBS                 VARCHAR(3),
   PZZL                 VARCHAR(3),
   PZHM                 VARCHAR(32),
   PZSM                 VARCHAR(40),
   DYRQ                 VARCHAR(8),
   DYSJ                 VARCHAR(6),
   DYLS                 INTEGER,
   DYJG                 VARCHAR(16),
   DYGY                 VARCHAR(16),
   DYCS                 INTEGER,
   JLBZ                 VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   PZNR                 CLOB                   not compact not logged,
   constraint "P_Key_1" primary key (PTRQ, PTLS, PZXH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_PZXX is
'凭证内容信息表';

comment on column APP_PZXX.PTRQ is
'平台日期 产生凭证的交易平台日期YYYYMMDD';

comment on column APP_PZXX.PTLS is
'平台流水号';

comment on column APP_PZXX.PZXH is
'凭证序号';

comment on column APP_PZXX.YWLS is
'业务流水';

comment on column APP_PZXX.YWRQ is
'业务日期';

comment on column APP_PZXX.YYBS is
'应用标识';

comment on column APP_PZXX.CPDM is
'产品代码';

comment on column APP_PZXX.YHBH is
'用户编号';

comment on column APP_PZXX.YHBSH is
'客户标识号';

comment on column APP_PZXX.KHMC is
'客户名称';

comment on column APP_PZXX.YHZH is
'银行帐号';

comment on column APP_PZXX.JYJE is
'交易金额';

comment on column APP_PZXX.JYJE2 is
'交易金额2';

comment on column APP_PZXX.JYJE3 is
'交易金额3';

comment on column APP_PZXX.SXF is
'手续费';

comment on column APP_PZXX.JFZQ is
'缴费周期';

comment on column APP_PZXX.QSRQ is
'起始日期';

comment on column APP_PZXX.JSRQ is
'结束日期';

comment on column APP_PZXX.SJDM is
'税局代码';

comment on column APP_PZXX.QDBS is
'交易渠道';

comment on column APP_PZXX.PZZL is
'凭证种类';

comment on column APP_PZXX.PZHM is
'凭证号码';

comment on column APP_PZXX.PZSM is
'凭证说明';

comment on column APP_PZXX.DYRQ is
'打印日期';

comment on column APP_PZXX.DYSJ is
'打印时间';

comment on column APP_PZXX.DYLS is
'打印流水号';

comment on column APP_PZXX.DYJG is
'打印机构';

comment on column APP_PZXX.DYGY is
'打印柜员';

comment on column APP_PZXX.DYCS is
'打印次数';

comment on column APP_PZXX.JLBZ is
'记录标志 0正常 1撤消';

comment on column APP_PZXX.EXTFLD1 is
'扩展字段1';

comment on column APP_PZXX.EXTFLD2 is
'扩展字段2';

comment on column APP_PZXX.PZNR is
'凭证内容';

--==============================================================
-- Index: K_APP_PZXX_1
--==============================================================
create index K_APP_PZXX_1 on APP_PZXX (
   PTRQ                 ASC,
   PTLS                 ASC
);

--==============================================================
-- Index: K_APP_PZXX_2
--==============================================================
create index K_APP_PZXX_2 on APP_PZXX (
   PTRQ                 ASC,
   PTLS                 ASC,
   CPDM                 ASC,
   YHBH                 ASC,
   YHZH                 ASC
);

--==============================================================
-- Table: APP_PZZL
--==============================================================
create table APP_PZZL
(
   PZZL                 VARCHAR(3)             not null,
   PZMC                 VARCHAR(40)            not null,
   PZSM                 VARCHAR(80),
   PZLB                 VARCHAR(1),
   PZJB                 VARCHAR(1),
   PZLY                 VARCHAR(16),
   PZZGJG               VARCHAR(16)            not null,
   ZJPZZL               VARCHAR(8),
   DSFPZZL              VARCHAR(8),
   PZGS                 VARCHAR(40),
   KZLX                 VARCHAR(1)             not null,
   WHJG                 VARCHAR(16)            not null,
   WHGY                 VARCHAR(16)            not null,
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_PZZL_1 primary key (PZZL)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_PZZL is
'凭证种类表';

comment on column APP_PZZL.PZZL is
'手工输入或者 由序列生成 KEY=K_PZBH';

comment on column APP_PZZL.PZMC is
'凭证名称';

comment on column APP_PZZL.PZSM is
'凭证说明';

comment on column APP_PZZL.PZLB is
'凭证类别 见数据字典 KEY=K_PZLB';

comment on column APP_PZZL.PZJB is
'凭证级别 0一般 1重要';

comment on column APP_PZZL.PZLY is
'凭证来源 可存放第三方单位编码';

comment on column APP_PZZL.PZZGJG is
'凭证主管机构';

comment on column APP_PZZL.ZJPZZL is
'主机凭证种类';

comment on column APP_PZZL.DSFPZZL is
'第三方凭证种类';

comment on column APP_PZZL.PZGS is
'凭证格式';

comment on column APP_PZZL.KZLX is
'控制类型 0不控制 1控制数量 2控制号码';

comment on column APP_PZZL.EXTFLD1 is
'扩展参数1';

comment on column APP_PZZL.EXTFLD2 is
'扩展参数2';

--==============================================================
-- Table: APP_QDXX
--==============================================================
create table APP_QDXX
(
   QDBS                 VARCHAR(3)             not null,
   QDMC                 VARCHAR(40),
   QDSM                 VARCHAR(80),
   SJKZBZ               VARCHAR(1),
   QSSJ                 VARCHAR(8),
   JSSJ                 VARCHAR(8),
   CZBZ                 VARCHAR(1),
   ZDCZBZ               VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   QDZT                 VARCHAR(1),
   constraint P_K_APP_QDXX_1 primary key (QDBS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_QDXX is
'渠道信息表';

comment on column APP_QDXX.QDBS is
'渠道标识 见数据字典 KEY=K_QDBS ';

comment on column APP_QDXX.QDMC is
'渠道名称';

comment on column APP_QDXX.QDSM is
'渠道说明';

comment on column APP_QDXX.SJKZBZ is
'时间控制标志 0 控制 1不控制';

comment on column APP_QDXX.QSSJ is
'起始时间 ';

comment on column APP_QDXX.JSSJ is
'结束时间';

comment on column APP_QDXX.CZBZ is
'是否允许冲正  0允许 1不允许';

comment on column APP_QDXX.ZDCZBZ is
'系统异常是否自动冲正  0是 1否';

comment on column APP_QDXX.EXTFLD1 is
'扩展字段1';

comment on column APP_QDXX.EXTFLD2 is
'扩展字段2';

comment on column APP_QDXX.QDZT is
'渠道状态 0开启 1关闭';

--==============================================================
-- Table: APP_RWJKB
--==============================================================
create table APP_RWJKB
(
   YYBS                 VARCHAR(8),
   YYMC                 VARCHAR(40),
   CPDM                 VARCHAR(16)            not null,
   CPMC                 VARCHAR(40),
   RWMC                 VARCHAR(50),
   JYDM                 VARCHAR(8),
   JYMC                 VARCHAR(40),
   PTLS                 INTEGER                not null,
   PTRQ                 VARCHAR(8)             not null,
   JYJG                 VARCHAR(16)            not null,
   JYGY                 VARCHAR(16)            not null,
   QDBS                 VARCHAR(3),
   KSSJ                 VARCHAR(19),
   JSSJ                 VARCHAR(19),
   YXSJ                 INTEGER,
   ZXCS                 INTEGER,
   ZXZT                 VARCHAR(1),
   XYM                  VARCHAR(5),
   XYXX                 VARCHAR(60),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(20),
   constraint "P_Key_1" primary key (PTLS, PTRQ)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on column APP_RWJKB.YYBS is
'应用标识';

comment on column APP_RWJKB.YYMC is
'应用名称';

comment on column APP_RWJKB.CPDM is
'产品代码';

comment on column APP_RWJKB.CPMC is
'产品名称';

comment on column APP_RWJKB.RWMC is
'任务名称';

comment on column APP_RWJKB.JYDM is
'交易代码';

comment on column APP_RWJKB.JYMC is
'交易名称';

comment on column APP_RWJKB.PTLS is
'平台流水';

comment on column APP_RWJKB.PTRQ is
'平台日期';

comment on column APP_RWJKB.JYJG is
'提醒机构';

comment on column APP_RWJKB.JYGY is
'提醒柜员';

comment on column APP_RWJKB.QDBS is
'渠道标识';

comment on column APP_RWJKB.KSSJ is
'开始时间戳';

comment on column APP_RWJKB.JSSJ is
'结束时间戳';

comment on column APP_RWJKB.YXSJ is
'运行毫秒数';

comment on column APP_RWJKB.ZXCS is
'运行次数';

comment on column APP_RWJKB.ZXZT is
'执行状态0:执行成功1:执行失败9:执行中';

comment on column APP_RWJKB.XYM is
'响应代码';

comment on column APP_RWJKB.XYXX is
'响应信息';

comment on column APP_RWJKB.EXTFLD1 is
'扩展1';

comment on column APP_RWJKB.EXTFLD2 is
'扩展2';

--==============================================================
-- Index: INDEX_RWJKB_1
--==============================================================
create index INDEX_RWJKB_1 on APP_RWJKB (
   JYDM                 ASC,
   PTRQ                 ASC
);

--==============================================================
-- Table: APP_RZPZ
--==============================================================
create table APP_RZPZ
(
   SSYY                 VARCHAR(8)             not null,
   CZLX                 VARCHAR(1)             not null,
   DXLX                 VARCHAR(1)             not null,
   CZDX1                VARCHAR(128)           not null,
   CZDX2                VARCHAR(128),
   CZTJ                 VARCHAR(254),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(20),
   constraint "P_Key_1" primary key (CZLX, DXLX, CZDX1)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_RZPZ is
'配置日终时需要平台统一归档和清理的库表，文件等';

comment on column APP_RZPZ.SSYY is
'应用标识';

comment on column APP_RZPZ.CZLX is
'1 归档 2 清理 3 备份 ';

comment on column APP_RZPZ.DXLX is
'1 数据库 2 文件';

comment on column APP_RZPZ.CZDX1 is
'归档时存放源表；源文件路径';

comment on column APP_RZPZ.CZDX2 is
'归档时存放目标表；目标文件路径';

comment on column APP_RZPZ.CZTJ is
'数据库表的 sql条件';

comment on column APP_RZPZ.EXTFLD1 is
'扩展1';

comment on column APP_RZPZ.EXTFLD2 is
'扩展2';

--==============================================================
-- Index: K_APP_RZPZ_1
--==============================================================
create index K_APP_RZPZ_1 on APP_RZPZ (
   SSYY                 ASC,
   CZLX                 ASC,
   DXLX                 ASC
);

--==============================================================
-- Table: APP_SXFFL
--==============================================================
create table APP_SXFFL
(
   FLBS                 VARCHAR(32)            not null,
   XH                   VARCHAR(2)             not null,
   FDBZ                 VARCHAR(1)             not null,
   NWKBZ                VARCHAR(1),
   SXXKZ                VARCHAR(1)             not null,
   SXJE                 NUMERIC(16,2),
   XXJE                 NUMERIC(16,2),
   JSLX                 VARCHAR(1)             not null,
   JSCS                 NUMERIC(16,6)          not null,
   KJBZ                 VARCHAR(1),
   KJCS                 NUMERIC(16,6),
   FDLX                 VARCHAR(1),
   LJBZ                 VARCHAR(1),
   BHBZ                 VARCHAR(1),
   QSS                  VARCHAR(16),
   JSS                  VARCHAR(16),
   SM                   VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_SXFFL_1 primary key (FLBS, XH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_SXFFL is
'手续费费率表';

comment on column APP_SXFFL.FLBS is
'手工输入';

comment on column APP_SXFFL.XH is
'浮动费率时多个费率分段的序号';

comment on column APP_SXFFL.FDBZ is
'0 不浮动， 1 浮动 ';

comment on column APP_SXFFL.NWKBZ is
'0外扣  1 内扣  默认 0';

comment on column APP_SXFFL.SXXKZ is
'0 控制  1 不控制 ';

comment on column APP_SXFFL.JSLX is
'计算参数类型 1 金额  2百分比   如果为1 ，表示手续费计算针对交易笔数的，如果是百分比，表示手续费计算针对交易金额。';

comment on column APP_SXFFL.JSCS is
'计算参数 计算类型为1 输入金额 输入1 表示1元；类型为2，输入百分比 如输入1 ，表示1％';

comment on column APP_SXFFL.KJBZ is
'0无优惠 1 打折 2 金额扣减 默认0';

comment on column APP_SXFFL.FDLX is
'浮动类型 1 交易笔数浮动 2 交易金额浮动';

comment on column APP_SXFFL.LJBZ is
'0 不累进  1 累进 默认0';

comment on column APP_SXFFL.BHBZ is
'计算参数包含上限标志  1 包含上限 0包含下限';

comment on column APP_SXFFL.SM is
'说明';

--==============================================================
-- Table: APP_SXFLS
--==============================================================
create table APP_SXFLS
(
   PTRQ                 VARCHAR(8)             not null,
   PTLS                 VARCHAR(16)            not null,
   FLBS                 VARCHAR(32)            not null,
   YYBS                 VARCHAR(3),
   YWBH                 VARCHAR(16),
   CPDM                 VARCHAR(16)            not null,
   QDBS                 VARCHAR(3),
   JGBS                 VARCHAR(16)            not null,
   KHLX                 VARCHAR(1),
   KHBH                 VARCHAR(32),
   YHH                  VARCHAR(32),
   DWBH                 VARCHAR(16),
   XTNBZ                VARCHAR(1),
   JYLSH                VARCHAR(16),
   JYLX                 VARCHAR(1),
   JYRQ                 VARCHAR(8),
   JYGY                 VARCHAR(16)            not null,
   JYJG                 VARCHAR(16)            not null,
   JYJE                 NUMERIC(16,2),
   JYBS                 INTEGER,
   SXFJE                NUMERIC(16,2)          not null,
   SFZT                 VARCHAR(1),
   JFZH                 VARCHAR(32),
   DFZH                 VARCHAR(32),
   SFRQ                 VARCHAR(8),
   SFJYGY               VARCHAR(16)            not null,
   SFJYJG               VARCHAR(16)            not null,
   SFLS                 VARCHAR(16),
   LSZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(40),
   SM                   VARCHAR(40),
   constraint "P_Key_1" primary key (PTRQ, PTLS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_SXFLS is
'手续费流水表';

comment on column APP_SXFLS.PTRQ is
'平台日期';

comment on column APP_SXFLS.PTLS is
'平台流水号';

comment on column APP_SXFLS.FLBS is
'费率标识';

comment on column APP_SXFLS.KHBH is
'客户在银行编号';

comment on column APP_SXFLS.YHH is
'用户在第三方客户号';

comment on column APP_SXFLS.XTNBZ is
'1 系统内  0 系统外';

comment on column APP_SXFLS.JYLSH is
'收取手续费的原交易流水号';

comment on column APP_SXFLS.JYLX is
'交易类型 0 联机 1批量';

comment on column APP_SXFLS.JYJE is
'交易金额';

comment on column APP_SXFLS.SXFJE is
'费用金额';

comment on column APP_SXFLS.SFZT is
'收取状态 0 未收取 1已收取';

comment on column APP_SXFLS.JFZH is
'借方帐户';

comment on column APP_SXFLS.DFZH is
'贷方帐户';

comment on column APP_SXFLS.SFRQ is
'收费日期';

comment on column APP_SXFLS.LSZT is
'流水状态 0 正常 1取消';

comment on column APP_SXFLS.SM is
'说明';

--==============================================================
-- Index: K_APP_SXFLS_1
--==============================================================
create index K_APP_SXFLS_1 on APP_SXFLS (
   JYLSH                ASC,
   JYRQ                 ASC
);

--==============================================================
-- Table: APP_SXFWHLS
--==============================================================
create table APP_SXFWHLS
(
   CPDM                 VARCHAR(16),
   FLBS                 VARCHAR(32),
   CZNR                 VARCHAR(254),
   CZBM                 VARCHAR(32),
   WHLX                 VARCHAR(1),
   WHRQ                 VARCHAR(8),
   WHSJ                 VARCHAR(6),
   WHGY                 VARCHAR(16)            not null,
   WHJG                 VARCHAR(16)            not null,
   SQGY                 VARCHAR(16),
   SQJG                 VARCHAR(16),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(40),
   SM                   VARCHAR(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_SXFWHLS is
'手续费维护流水表，记录维护基础费率，产品手续费控制，产品手续费关系的维护信息';

comment on column APP_SXFWHLS.CPDM is
'产品代码';

comment on column APP_SXFWHLS.FLBS is
'费率标识';

comment on column APP_SXFWHLS.CZNR is
'操作SQL';

comment on column APP_SXFWHLS.CZBM is
'操作的数据库表名';

comment on column APP_SXFWHLS.WHLX is
'1 增加， 2 修改， 3 删除';

--==============================================================
-- Index: K_APP_SXFWHLS_1
--==============================================================
create index K_APP_SXFWHLS_1 on APP_SXFWHLS (
   CPDM                 ASC,
   FLBS                 ASC,
   CZBM                 ASC,
   WHRQ                 ASC
);

--==============================================================
-- Table: APP_TXAQXX
--==============================================================
create table APP_TXAQXX
(
   LJBS                 VARCHAR(8)             not null,
   LJMC                 VARCHAR(40),
   LJLX                 VARCHAR(1),
   DWBH                 VARCHAR(16),
   QDKZ                 VARCHAR(1),
   TXMS                 VARCHAR(1),
   TXDZ                 VARCHAR(100),
   TXDK                 VARCHAR(6),
   FSCS                 INTEGER,
   JSCS                 INTEGER,
   LJJGH                VARCHAR(16),
   LJGYH                VARCHAR(16),
   LJZDH                VARCHAR(16),
   KEY1                 VARCHAR(128),
   KEY2                 VARCHAR(128),
   KEY3                 VARCHAR(128),
   FTPDZ                VARCHAR(16),
   FTPYH                VARCHAR(16),
   FTPMM                VARCHAR(32),
   FTPGZFS              VARCHAR(1),
   FTPCSFS              VARCHAR(1),
   FTPZDMS              VARCHAR(1),
   FTPDFLJ              VARCHAR(40),
   FTPBDLJ              VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(254),
   TXZT                 VARCHAR(1),
   QDZT                 VARCHAR(1),
   constraint P_K_APP_TXAQXX_1 primary key (LJBS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_TXAQXX is
'通讯安全信息表';

comment on column APP_TXAQXX.LJBS is
'联机标识 L_';

comment on column APP_TXAQXX.LJMC is
'联机名称';

comment on column APP_TXAQXX.LJLX is
'联机类型 1行内主机 2行内其他系统 3外联单位 9其他';

comment on column APP_TXAQXX.DWBH is
'单位编号 联机方编号';

comment on column APP_TXAQXX.QDKZ is
'是否控制签到状态（默认1）
0 控制 1不控制';

comment on column APP_TXAQXX.TXMS is
'通讯模式见数据字典 KEY=K_TXMS';

comment on column APP_TXAQXX.TXDZ is
'通讯地址';

comment on column APP_TXAQXX.TXDK is
'通讯端口';

comment on column APP_TXAQXX.FSCS is
'发送超时';

comment on column APP_TXAQXX.JSCS is
'接收超时';

comment on column APP_TXAQXX.LJJGH is
'联机机构号';

comment on column APP_TXAQXX.LJGYH is
'联机柜员号';

comment on column APP_TXAQXX.LJZDH is
'联机终端号';

comment on column APP_TXAQXX.KEY1 is
'密钥1';

comment on column APP_TXAQXX.KEY2 is
'密钥2';

comment on column APP_TXAQXX.KEY3 is
'密钥3';

comment on column APP_TXAQXX.FTPDZ is
'ftp地址，默认同通讯地址';

comment on column APP_TXAQXX.FTPYH is
'ftp用户名称';

comment on column APP_TXAQXX.FTPMM is
'ftp用户密码';

comment on column APP_TXAQXX.FTPGZFS is
'(1 主动模式 2 被动模式ii)';

comment on column APP_TXAQXX.FTPCSFS is
'ftp传输方式(1 bin 2 ascii)';

comment on column APP_TXAQXX.FTPZDMS is
'0-主动PORT 1-被动PASV';

comment on column APP_TXAQXX.FTPDFLJ is
'对方文件存放路径';

comment on column APP_TXAQXX.FTPBDLJ is
'本地文件存放路径';

comment on column APP_TXAQXX.EXTFLD1 is
'扩展字段1';

comment on column APP_TXAQXX.EXTFLD2 is
'扩展字段2';

comment on column APP_TXAQXX.TXZT is
'通讯状态 0正常 9无效';

comment on column APP_TXAQXX.QDZT is
'签到状态  1签退 2签到 ';

--==============================================================
-- Table: APP_XLKZ
--==============================================================
create table APP_XLKZ
(
   PKEY                 VARCHAR(20)            not null,
   CURR_VALUE           INTEGER                not null,
   PINC                 INTEGER                not null,
   MIN_VALUE            INTEGER                not null,
   MAX_VALUE            INTEGER                not null,
   REMARK               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_XLKZ_1 primary key (PKEY)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_XLKZ is
'序列控制表';

--==============================================================
-- Table: APP_YWRQ
--==============================================================
create table APP_YWRQ
(
   PKEY                 VARCHAR(20)            not null,
   SYYWRQ               VARCHAR(8),
   YWRQ                 VARCHAR(8)             not null,
   XYYWRQ               VARCHAR(8),
   CCH                  VARCHAR(2),
   LSH                  INTEGER,
   EXTFLD               VARCHAR(40),
   SM                   VARCHAR(40),
   constraint P_K_APP_YWRQ_1 primary key (PKEY)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_YWRQ is
'业务日期表';

comment on column APP_YWRQ.PKEY is
'键值  产品代码';

comment on column APP_YWRQ.SYYWRQ is
'上一业务日期';

comment on column APP_YWRQ.YWRQ is
'产品业务日期';

comment on column APP_YWRQ.XYYWRQ is
'下一业务日期';

comment on column APP_YWRQ.CCH is
'场次号';

comment on column APP_YWRQ.LSH is
'流水号';

comment on column APP_YWRQ.EXTFLD is
'扩展参数';

comment on column APP_YWRQ.SM is
'说明';

--==============================================================
-- Table: APP_YYXX
--==============================================================
create table APP_YYXX
(
   YYBS                 VARCHAR(8)             not null,
   YYMC                 VARCHAR(40),
   YYSM                 VARCHAR(80),
   YYKFKSRQ             VARCHAR(8),
   YYKFJSRQ             VARCHAR(8),
   YYFBRQ               VARCHAR(8),
   YYBBH                VARCHAR(20),
   YHH                  VARCHAR(40),
   SQH                  VARCHAR(40),
   YYKFJL               VARCHAR(40),
   YYZBJL               VARCHAR(40),
   YYZT                 VARCHAR(1),
   EXTFLD               VARCHAR(40),
   constraint P_K_APP_YYXX_1 primary key (YYBS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_YYXX is
'应用信息表';

comment on column APP_YYXX.YYBS is
'应用标识 ';

comment on column APP_YYXX.YYMC is
'应用名称';

comment on column APP_YYXX.YYSM is
'应用说明';

comment on column APP_YYXX.YYKFKSRQ is
'应用开发开始日期';

comment on column APP_YYXX.YYKFJSRQ is
'应用开发结束日期';

comment on column APP_YYXX.YYFBRQ is
'应用发布日期';

comment on column APP_YYXX.YYBBH is
'应用版本号';

comment on column APP_YYXX.YHH is
'用户号';

comment on column APP_YYXX.SQH is
'授权号';

comment on column APP_YYXX.YYKFJL is
'应用开发经理';

comment on column APP_YYXX.YYZBJL is
'应用质保经理';

comment on column APP_YYXX.YYZT is
'0正常 1关闭';

comment on column APP_YYXX.EXTFLD is
'扩展字段';

/* 参数 */
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_PTLSGD', '0', '', '/app/ptlsgd', '2', '平台公共流水归档天数', '1', '00000','admin');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_PTLSQL', '0', '', '/app/ptlsql', '7', '平台公共流水清理保留天数', '1', '00000','admin' );

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_QYCXXZ', '0', '', '/app/custom/qycxxz', '100', '签约查询返回最大记录数', '0', '00000','admin' );

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_ZXLSH', '0', '', '/app/zxlsh', '1', '最小流水号', '0', '00000','admin' );

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_LSH_RETURN', '0', '', '/app/lshreturn', '0', '流水号归重置标志 0-重置', '0', '00000','admin' );

/* 序列信息  */
insert into app_xlkz (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY )
values ('K_KHBH', 10000000, 1, 1, 99999999, '客户编号', '00000','admin' );

insert into app_xlkz (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY )
values ('K_KHCPQY', 10000000, 1, 1, 99999999, '客户产品签约序列', '00000','admin' );

/*数据字典*/
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_GYJB', '柜员级别', '11', '网点经办', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_GYJB', '柜员级别', '12', '网点主办', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_GYJB', '柜员级别', '22', '支行主办', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_GYJB', '柜员级别', '32', '分行主办', '001', '00000', 'admin', '20110915');

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JDBZ','借贷标志','D','借','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JDBZ','借贷标志','C','贷','001','00000','admin' );
                                           
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','性别标志','0','未知的性别','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','性别标志','1','男性','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','性别标志','2','女性','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','性别标志','9','未说明性别','001','00000','admin' );
                                                                                      
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','交易状态','0','成功','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','交易状态','1','失败','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','交易状态','6','状态未知','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','交易状态','7','交易被冲正','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','交易状态','8','交易被撤消','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','交易状态','9','初始','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_YXBZ','有效标志','1','正常','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_YXBZ','有效标志','2','关闭','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_YXBZ','有效标志','9','未授权','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','机构控制参数','0','不控制','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','机构控制参数','1','一级机构控制','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','机构控制参数','2','二级机构控制','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','机构控制参数','3','三级机构控制','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','交易方式','1','联机','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','交易方式','2','批量','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','交易方式','3','日间批量','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','交易方式','4','夜间批量','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','交易方式','5','联机及批量','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','交易方式','6','联机及日间批量','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','交易方式','7','联机及夜间批量','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','交易方式','8','联机及批转联','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','交易方式','9','其他','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CPZT','产品状态','0','正常','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CPZT','产品状态','1','暂停','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CSLX','参数类型','0','系统参数','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CSLX','参数类型','1','渠道参数','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CSLX','参数类型','2','应用参数','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DWZJLX','单位证件类型','1','营业执照','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','通讯模式','1','TCP/IP','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','通讯模式','2','CICSCLI','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','通讯模式','3','TUXEDOCLI','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','通讯模式','4','IBM MQ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','通讯模式','9','其他','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','帐户类型','01','对公活期','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','帐户类型','02','对私活期','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','帐户类型','03','对公定期','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','帐户类型','04','对私定期','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','帐户类型','05','保证金','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','帐户类型','06','贷款','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','帐户类型','07','内部账','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','帐户类型','08','表外账','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','0','身份证','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','1','户口簿','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','2','护照','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','3','军官证','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','4','士兵证','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','5','港澳居民来往内地通行证','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','6','台湾同胞来往内地通行证','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','7','临时身份证','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','8','外国人居留证','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','9','警官证','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','证件类型','X','其它','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','凭证类别','0','对公类','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','凭证类别','1','对私类','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','凭证类别','2','中间业务类','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','凭证类别','3','卡类','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','凭证类别','4','有价单证类','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','凭证类别','9','其他','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','凭证操作动作','01','请领','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','凭证操作动作','02','入库','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','凭证操作动作','03','出库','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','凭证操作动作','04','划拨','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','凭证操作动作','05','回划','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','凭证操作动作','06','调整','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','凭证操作动作','07','使用','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','CNY','人民币','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','HKD','港币','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','USD','美元','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','EUR','欧元','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','JPY','日元','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','MOP','澳门元','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','CHF','瑞士法郎','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','GBP','英镑','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','RUR','俄罗斯卢布','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','CAD','加拿大元','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','DKK','丹麦克朗','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','AUD','澳大利亚元','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','SEK','瑞典克朗','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','KRW','韩元','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','交易币种','SGD','新元','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','客户类型','1','普通用户','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','客户类型','2','银卡贵宾','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','客户类型','3','金卡贵宾','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','客户类型','4','钻石卡贵宾','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','客户类型','9','其他','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','教育程度','1','文盲','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','教育程度','2','小学','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','教育程度','3','初中','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','教育程度','4','高中','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','教育程度','5','大专','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','教育程度','6','大本','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','教育程度','7','硕士研究生','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','教育程度','8','博士研究生','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','教育程度','9','未知或其他','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SFBZ','收付标志','1','收','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SFBZ','收付标志','2','付','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SFBZ','收付标志','3','其他','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','签约标志','0','不需要签约','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','签约标志','1','第三方签约','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','签约标志','2','核心签约','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','签约标志','3','核心第三方同时签约','001','00000','admin' );
                                           
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KKFS','扣款方式','1','全额扣款','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KKFS','扣款方式','2','允许部分扣款','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_RZMS','日志模式','0','调试模式','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_RZMS','日志模式','1','生产模式','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','签约模式','1','产品代码＋银行帐号','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','签约模式','2','产品代码＋用户号','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','签约模式','3','产品代码＋银行帐号＋用户号','001','00000','admin' );


INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CZLX', '操作类型', '1', '归档', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CZLX', '操作类型', '2', '清理', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CZLX', '操作类型', '3', '备份', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_DXLX', '对象类型', '1', '数据库', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_BATCH_MXCGBZ', '明细成功标志', '0', '成功', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_BATCH_MXCGBZ', '明细成功标志', '1', '部分成功', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_BATCH_MXCGBZ', '明细成功标志', '2', '处理失败', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_DXLX', '对象类型', '2', '文件', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_HQSJFS', '获取数据方式', '0', 'FTP主动取', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_HQSJFS', '获取数据方式', '1', 'WEB服务端数据', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_HQSJFS', '获取数据方式', '2', '交易', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXTJBZ', '明细提交标志', '0', '提交所有未处理或处理失败明细', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXTJBZ', '明细提交标志', '1', '提交本批次未处理或处理失败明细', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXTJBZ', '明细提交标志', '2', '提交本批次未处理明细', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '明细回盘标志', '0', '生成所有批次明细', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '明细回盘标志', '1', '生成本批次所有明细', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '明细回盘标志', '2', '生成本批次处理成功明细', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '明细回盘标志', '3', '生成本批次处理失败明细', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '明细回盘标志', '4', '分别生成成功失败明细', '002', '00000', 'admin', NULL);

INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_FSSJFS', '发送数据方式', '0', 'FTP主动发送', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_FSSJFS', '发送数据方式', '1', 'WEB服务端数据', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_FSSJFS', '发送数据方式', '2', '交易', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '超限处理', '0', '交易拒绝', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '超限处理', '1', '检查授权柜员级别', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '超限处理', '2', '检查授权柜员岗位', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '超限处理', '3', '检查授权柜员级别和岗位', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_EDKZFS', '额度控制方式', '1', '不控制', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_EDKZFS', '额度控制方式', '0', '控制级别', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_EDKZFS', '额度控制方式', '9', '控制所有', '001', '00000', 'admin', '20110915');

INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_KZBL', '控制变量', '0', '00', '001', '00000', 'admin', '20110830');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_JZSX', '记账顺序', '0', '先上主机', '001', '00000', 'admin', '20110917');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_JZSX', '记账顺序', '1', '先上第三方', '001', '00000', 'admin', '20110917');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_JJMBZ', '加解密标志', '0', '加密', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_JJMBZ', '加解密标志', '1', '不加密', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_WJLXZHBZ', '文件类型转换标志 ', '0', '转换', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_WJLXZHBZ', '文件类型转换标志 ', '1', '不转换', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_CFCZBZ', '重复操作标志', '0', '允许', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_CFCZBZ', '重复操作标志', '1', '不允许', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_SHSBBZ', '审核失败标志 ', '0', '跳过', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_SHSBBZ', '审核失败标志 ', '1', '失败退出', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_XYMZHBZ', '响应码转换标志', '0', '转换', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_XYMZHBZ', '响应码转换标志', '1', '不转换', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_DDBZ', '断点标志', '0', '无断点', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_DDBZ', '断点标志', '1', '断点', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_DDBZ', '断点标志', '2', '返回', '002', '00000', 'admin', NULL);

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZLSLX','对账流水类型','1','主机对账不平','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZLSLX','对账流水类型','2','第三方对账不平','003','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','对账处理状态','0','未处理','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','对账处理状态','1','处理成功','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','对账处理状态','8','处理出错','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','对账处理状态','9','处理中','003','00000','admin' );

/* 应用信息 */
insert into app_yyxx (YYBS, YYMC, YYSM, YYKFKSRQ, YYKFJSRQ, YYFBRQ, YYBBH, YHH, SQH, YYKFJL, YYZBJL, YYZT, EXTFLD)
values ('001', 'app', 'App公共业务服务', '', '', '20111001', '2.1.0.1', '', '', 'YangDong', 'YangDong', '0', '');

/* 交易信息 */
insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900001', '交易服务启停', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900002', '应用启停', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900003', '渠道启停', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900004', '数据归档', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900005', '数据清理', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900006', '数据备份', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900007', '数据恢复', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900008', '平台日切', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900010', '产品交易服务启停', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900011', '日期查询', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900012', '节假日设置', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900013', '产品业务启停', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900014', '机构柜员信息同步', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900015', '手续费计算', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900016', '手续费流水登记', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900017', '手续费基础报表', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900018', '凭证校验', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900019', '凭证使用', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900020', '凭证请领', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900021', '凭证请领撤销', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900022', '凭证请领查询', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900023', '凭证入库', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900024', '凭证出库', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900025', '凭证划拨', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900026', '凭证回划', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900027', '凭证查询', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900028', '凭证调整', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900029', '凭证出库撤销', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900030', '凭证入库撤销', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900031', '撤销签约关系', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900032', '登记签约关系', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900033', '查询签约关系', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900034', '更新签约关系', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900040', 'shell命令运行', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

/*渠道信息 */
insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('200', 'tamc', 'TAMC管理台渠道', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('201', 'cxs', '储蓄柜面渠道', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('202', 'netbk', '网上银行渠道', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('203', 'telbk', '电话银行渠道', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('204', 'mbbk', '手机银行渠道', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('205', 'atm', 'ATM渠道', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('206', 'pos', 'POS渠道', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

/* 日终任务配置 */
insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpjggx', '', '', '产品机构关系', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_dwcpxy', '', '', '单位产品协议', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_dwxx', '', '', '单位信息', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_jjrdj', '', '', '节假日登记', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_jyxx', '', '', '交易信息', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_kzsx', '', '', '扩展属性', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_khcpqy', '', '', '客户产品签约', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_khxx', '', '', '交易信息', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_pzhmdj', '', '', '凭证号码登记', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_pzsldj', '', '', '凭证数量登记', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_pzzl', '', '', '凭证种类', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_qdxx', '', '', '渠道信息', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_rzpz', '', '', '任务配置', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_sxffl', '', '', '手续费费率', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'APP_CPJYJGED', '', '', '产品交易机构额度控制', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'APP_CPJYGYED', '', '', '产品交易柜员额度控制', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'APP_CPJYGYKZ', '', '', '产品交易柜员权限控制', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_txaqxx', '', '', '通讯安全信息', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_xlkz', '', '', '序列控制', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_yyxx', '', '', '应用信息', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpjyfw', '', '', '产品交易服务', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cppzgx', '', '', '产品凭证关系', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpqdgx', '', '', '产品渠道关系', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpsxfgx', '', '', '产品手续费关系', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpsxfkz', '', '', '产品手续费控制', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpxx', '', '', '产品信息', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cskz', '', '', '参数控制', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_dict', '', '', '数据字典', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '1', '1', 'app_drls', 'app_his_drls', 'C;ptrq;=;K_APP_PTLSGD;;|', '平台公共流水归档 ', ' ', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '2', '1', 'app_drls', '', 'C;ptrq;=;K_APP_PTLSQL;;|', '平台流水当前表清理', ' ', '00000','admin' );
