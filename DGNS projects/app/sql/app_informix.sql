--==============================================================
-- Database name:  GAPS4.1_ƽ̨����
-- DBMS name:      INFORMIX
-- Created on:     2014-11-2 10:32:30
-- Modify on :     2014-11-15 10:56  
--==============================================================
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

drop type CPDM restrict;

drop type DWBH restrict;

drop type JYDM restrict;

drop type JYGY restrict;

drop type JYJG restrict;

drop type PTLS restrict;

drop type PTRQ restrict;

drop type QDBS restrict;

drop type WHSJ restrict;

drop type YHH1 restrict;

drop type YHZH restrict;

drop type YWBH restrict;

drop type ZHMC restrict;

--==============================================================
-- Domain: CPDM
--==============================================================
create distinct type CPDM as CHAR(16);

--==============================================================
-- Domain: DWBH
--==============================================================
create distinct type DWBH as VARCHAR(16);

--==============================================================
-- Domain: JYDM
--==============================================================
create distinct type JYDM as CHAR(8);

--==============================================================
-- Domain: JYGY
--==============================================================
create distinct type JYGY as VARCHAR(16);

--==============================================================
-- Domain: JYJG
--==============================================================
create distinct type JYJG as VARCHAR(16);

--==============================================================
-- Domain: PTLS
--==============================================================
create distinct type PTLS as CHAR(8);

--==============================================================
-- Domain: PTRQ
--==============================================================
create distinct type PTRQ as CHAR(8);

--==============================================================
-- Domain: QDBS
--==============================================================
create distinct type QDBS as CHAR(3);

--==============================================================
-- Domain: WHSJ
--==============================================================
create distinct type WHSJ as VARCHAR(14);

--==============================================================
-- Domain: YHH1
--==============================================================
create distinct type YHH1 as VARCHAR(32);

--==============================================================
-- Domain: YHZH
--==============================================================
create distinct type YHZH as VARCHAR(32);

--==============================================================
-- Domain: YWBH
--==============================================================
create distinct type YWBH as CHAR(16);

--==============================================================
-- Domain: ZHMC
--==============================================================
create distinct type ZHMC as VARCHAR(80);

--==============================================================
-- Table: APP_CPJGGX
--==============================================================

create table APP_CPJGGX  
(
  CPDM                 VARCHAR(16)                     not null,
  JGBH                 VARCHAR(16)                     not null,
  SJKZBZ               VARCHAR(1),
  QSSJ                 VARCHAR(6),
  JSSJ                 VARCHAR(6),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
  ZT                   VARCHAR(1),
primary key (CPDM, JGBH)
      constraint PK_APP_CPJGGX
);

--==============================================================
-- Table: APP_CPJYFW
--==============================================================

create table APP_CPJYFW  
(
  CPDM                 VARCHAR(16)                     not null,
  JYDM                 VARCHAR(8)                      not null,
  SJKZBZ               VARCHAR(1),
  QSSJ                 VARCHAR(6),
  JSSJ                 VARCHAR(6),
  XEKZBZ               VARCHAR(1),
  ZXXE                 DECIMAL(16,2),
  ZDXE                 DECIMAL(16,2),
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
primary key (CPDM, JYDM)
      constraint PK_APP_CPJYFW
);

--==============================================================
-- Table: APP_CPJYGYED
--==============================================================

create table APP_CPJYGYED  
(
  CPDM                 VARCHAR(16)                     not null,
  JYDM                 VARCHAR(8)                      not null,
  JYBZ                 VARCHAR(3)                      not null,
  DBEDKZ               VARCHAR(1),
  RLJEDKZ              VARCHAR(1),
  YLJEDKZ              VARCHAR(1),
  GYJB                 VARCHAR(2)                      not null,
  DBED                 DECIMAL(16,2),
  YLJED                DECIMAL(16,2),
  RLJED                DECIMAL(16,2),
  CXCL                 VARCHAR(1),
  SQGYGW               VARCHAR(8),
  SQGYJB               VARCHAR(2),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
primary key (CPDM, JYDM, JYBZ, GYJB) constraint PK_APP_CPJYGYED
);

--==============================================================
-- Table: APP_CPJYGYKZ
--==============================================================

create table APP_CPJYGYKZ  
(
  CPDM                 VARCHAR(16)                     not null,
  JYDM                 VARCHAR(8)                      not null,
  KZBZ                 VARCHAR(1),
  GYJB                 VARCHAR(2)                      not null,
  CXCL                 VARCHAR(1),
  SQGYGW               VARCHAR(8),
  SQGYJB               VARCHAR(2),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
primary key (CPDM, JYDM) constraint PK_APP_CPJYGYKZ
);

--==============================================================
-- Table: APP_CPJYJGED
--==============================================================

create table APP_CPJYJGED  
(
  CPDM                 VARCHAR(16)                     not null,
  JYDM                 VARCHAR(8)                      not null,
  JYBZ                 VARCHAR(3)                      not null,
  DBEDKZ               VARCHAR(1),
  RLJEDKZ              VARCHAR(1),
  YLJEDKZ              VARCHAR(1),
  JGJB                 VARCHAR(16)                     not null,
  DBED                 DECIMAL(16,2),
  YLJED                DECIMAL(16,2),
  RLJED                DECIMAL(16,2),
  CXCL                 VARCHAR(1),
  SQGYGW               VARCHAR(8),
  SQGYJB               VARCHAR(2),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
primary key (CPDM, JYDM, JYBZ, JGJB) constraint PK_APP_CPJYJGED
);

--==============================================================
-- Table: APP_CPPZGX
--==============================================================

create table APP_CPPZGX  
(
  CPDM                 VARCHAR(16)                     not null,
  PZXH                 INTEGER                         not null,
  PZZL                 VARCHAR(3)                      not null,
  CPPZSM               VARCHAR(40),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
primary key (CPDM, PZXH) constraint PK_APP_CPPZGX
);

--==============================================================
-- Table: APP_CPQDGX
--==============================================================

create table APP_CPQDGX  
(
  CPDM                 VARCHAR(16)                     not null,
  QDBS                 VARCHAR(3)                      not null,
  SJKZBZ               VARCHAR(1),
  QSSJ                 VARCHAR(6),
  JSSJ                 VARCHAR(6),
  XEKZBZ               VARCHAR(1),
  ZXXE                 DECIMAL(16,2),
  ZDXE                 DECIMAL(16,2),
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
primary key (CPDM, QDBS) constraint PK_APP_CPQDGX
);

--==============================================================
-- Table: APP_CPSXFGX
--==============================================================

create table APP_CPSXFGX  
(
  CPDM                 VARCHAR(16)                     not null,
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
  FLBS                 VARCHAR(32)                     not null,
  QYRQ                 VARCHAR(8)                      not null,
  SXRQ                 VARCHAR(8)                      not null,
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  EXTFLD1              VARCHAR(20),
  EXTFLD2              VARCHAR(40),
  SM                   VARCHAR(40)
);

--==============================================================
-- Index: K_APP_CPSXFGX_1
--==============================================================
create unique  index K_APP_CPSXFGX_1 on APP_CPSXFGX (
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
  CPDM                 VARCHAR(16)                     not null,
  XH                   VARCHAR(2),
  KZSX                 VARCHAR(32)                     not null,
  KZSXM                VARCHAR(40)                     not null,
  SXLYLX               VARCHAR(1),
  KZSXLY               VARCHAR(40),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
primary key (CPDM, KZSX) constraint PK_APP_CPSXFKZ
);

--==============================================================
-- Table: APP_CPXX
--==============================================================

create table APP_CPXX  
(
  CPDM                 VARCHAR(16)                     not null,
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
  
  primary key (CPDM) constraint PK_APP_CPXX
);

--==============================================================
-- Table: APP_CSKZ
--==============================================================

create table APP_CSKZ  
(
  CSJZ                 VARCHAR(20)                     not null,
  CSLX                 VARCHAR(1),
  CSTJ                 VARCHAR(8),
  JDM                  VARCHAR(80)                     not null,
  JDZ                  VARCHAR(40)                     not null,
  REMARK               VARCHAR(40),
  JZLX                 VARCHAR(1),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  primary key (CSJZ) constraint PK_APP_CSKZ
);

--==============================================================
-- Table: APP_DICT
--==============================================================

create table APP_DICT  
(
  PKEY                 VARCHAR(20)                     not null,
  KEYJS                VARCHAR(30)                     not null,
  PVAL                 VARCHAR(20)                     not null,
  PROMPT               VARCHAR(60)                     not null,
  SSYY                 VARCHAR(8)                      not null,
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  primary key (PKEY, PVAL) constraint PK_APP_DICT 
);

--==============================================================
-- Table: APP_DRLS
--==============================================================

create table APP_DRLS  
(
  PTRQ                 VARCHAR(8)                      not null,
  PTLS                 INTEGER                         not null,
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
  JYJE                 DECIMAL(16,2),
  SXF                  DECIMAL(16,2),
  PCBH                 INTEGER,
  JYXYM                VARCHAR(8),
  JYXYXX               VARCHAR(60),
  JYZT                 VARCHAR(1),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
primary key (PTRQ, PTLS) constraint PK_APP_DRLS
);

--==============================================================
-- Index: K_APP_DRLS_1
--==============================================================
create   index K_APP_DRLS_1 on APP_DRLS (
        PTRQ                 ASC,
        PTLS                 ASC,
        YWBH                 ASC
);

--==============================================================
-- Table: APP_DWCPXY
--==============================================================

create table APP_DWCPXY  
(
  DWBH                 VARCHAR(16)                     not null,
  CPDM                 VARCHAR(16)                     not null,
  YWBH                 VARCHAR(16)                     not null,
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
  ZHZDED               DECIMAL(16,2),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
  QYZT                 VARCHAR(1),
primary key (YWBH)
      constraint PK_APP_DWCPXY,
unique (DWBH, CPDM)
      constraint AK_K_APP_CPDWXY_1_APP_DWCP
);

--==============================================================
-- Table: APP_DWXX
--==============================================================

create table APP_DWXX  
(
  DWBH                 VARCHAR(16)                     not null,
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
primary key (DWBH) constraint PK_APP_DWXX
);

--==============================================================
-- Table: APP_GYSQED
--==============================================================

create table APP_GYSQED  
(
  CPDM                 VARCHAR(16)                     not null,
  JYDM                 VARCHAR(8)                      not null,
  GYJB                 VARCHAR(8)                      not null,
  GYGW                 VARCHAR(8)                      not null,
  JYBZ                 VARCHAR(3)                      not null,
  GYDBSQED             DECIMAL(16,2),
  GYRLJSQED            DECIMAL(16,2),
  GYYLJSQED            DECIMAL(16,2),
  JGDBSQED             DECIMAL(16,2),
  JGRLJSQED            DECIMAL(16,2),
  JGYLJSQED            DECIMAL(16,2),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
  primary key (CPDM, JYDM, GYJB, GYGW, JYBZ) constraint PK_APP_GYSQED
);

--==============================================================
-- Table: APP_GYXX
--==============================================================

create table APP_GYXX  
(
  GYH                  VARCHAR(16)                     not null,
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
  primary key (GYH) constraint PK_APP_GYXX
);

--==============================================================
-- Table: APP_HIS_DRLS
--==============================================================

create table APP_HIS_DRLS  
(
  PTRQ                 VARCHAR(8)                      not null,
  PTLS                 INTEGER                         not null,
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
  JYJE                 DECIMAL(16,2),
  SXF                  DECIMAL(16,2),
  PCBH                 INTEGER,
  JYXYM                VARCHAR(8),
  JYXYXX               VARCHAR(60),
  JYZT                 VARCHAR(1),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
  primary key (PTRQ, PTLS) constraint PK_APP_HIS_DRLS
);

--==============================================================
-- Index: K_APP_DRLS_2
--==============================================================
create   index K_APP_DRLS_2 on APP_HIS_DRLS (
        PTRQ                 ASC,
        PTLS                 ASC,
        YWBH                 ASC
);

--==============================================================
-- Table: APP_JJRDJ
--==============================================================

create table APP_JJRDJ  
(
  RQ                   VARCHAR(8)                      not null,
  JRBZ                 VARCHAR(1)                      not null,
  EXTFLD1              VARCHAR(20),
  primary key (RQ) constraint PK_APP_JJRDJ
);

--==============================================================
-- Table: APP_JYXX
--==============================================================

create table APP_JYXX  
(
  JYDM                 VARCHAR(8)                      not null,
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
  primary key (JYDM) constraint PK_APP_JYXX
);

--==============================================================
-- Table: APP_KHCPQY
--==============================================================

create table APP_KHCPQY  
(
  XYBH                 VARCHAR(20)                     not null,
  KHBH                 VARCHAR(16),
  CPDM                 VARCHAR(16)                     not null,
  YWBH                 VARCHAR(16)                     not null,
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
  KKZDXE               DECIMAL(13,2),
  KKZQ                 VARCHAR(1),
  YDKKRQ               VARCHAR(8),
  KKZT                 VARCHAR(1),
  KKRQ                 VARCHAR(8),
  DXTZBZ               VARCHAR(1),
  ZHZDED               DECIMAL(13,2),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
  EXTFLD3              VARCHAR(40),
  EXTFLD4              VARCHAR(40),
  EXTFLD5              VARCHAR(40),
  EXTFLD6              VARCHAR(254),
  QYZT                 VARCHAR(1),
  primary key (XYBH, CPDM) constraint PK_APP_KHCPQY
);

--==============================================================
-- Index: K_APP_INDEX_1
--==============================================================
create   index K_APP_INDEX_1 on APP_KHCPQY (
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
  KHBH                 VARCHAR(16)                     not null,
  KHXM                 VARCHAR(80),
  YWXM                 VARCHAR(40),
  BM                   VARCHAR(20),
  KHLX                 VARCHAR(1),
  ZJKHBH               VARCHAR(32),
  ZJLX                 VARCHAR(3)                      not null,
  ZJHM                 VARCHAR(32)                     not null,
  CSNY                 VARCHAR(8),
  SEX                  VARCHAR(1),
  GJ                   VARCHAR(3),
  HK                   VARCHAR(60),
  HYZK                 VARCHAR(1),
  JYCD                 VARCHAR(1),
  ZY                   VARCHAR(3),
  ZW                   VARCHAR(20),
  SRQK                 DECIMAL(16,2),
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
primary key (KHBH)
      constraint PK_APP_KHXX,
unique (ZJLX, ZJHM)
      constraint AK_K_APP_KHXX_2_APP_KHXX
);

--==============================================================
-- Table: APP_KZSX
--==============================================================

create table APP_KZSX 
(
  PKEY                 VARCHAR(40)                     not null,
  CSMC                 VARCHAR(20)                     not null,
  CSSM                 VARCHAR(80)                     not null,
  CSZ                  VARCHAR(80),
  EXTFLD               VARCHAR(40),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
primary key (PKEY, CSMC) constraint PK_APP_KZSX
);

--==============================================================
-- Table: APP_MJSJ
--==============================================================

create table APP_MJSJ  
(
  MJID                 VARCHAR(16)                     not null,
  MJSM                 VARCHAR(40),
  SJXH                 INTEGER                         not null,
  QSBZ                 VARCHAR(1),
  REQ1                 VARCHAR(40)                     not null,
  REQ2                 VARCHAR(40),
  REQ3                 VARCHAR(40),
  REQ4                 VARCHAR(40),
  REQ5                 VARCHAR(40),
  REQ6                 VARCHAR(40),
  REQ7                 VARCHAR(40),
  REQ8                 VARCHAR(40),
  REQ9                 VARCHAR(40),
  REQ10                VARCHAR(40),
  RESP1                VARCHAR(40)                     not null,
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
  primary key (MJID, SJXH) constraint PK_APP_MJSJ
);

--==============================================================
-- Table: APP_MJSX
--==============================================================

create table APP_MJSX  
(
  MJID                 VARCHAR(16)                     not null,
  MJSM                 VARCHAR(40)                     not null,
  SXLX                 VARCHAR(1)                      not null,
  SXXH                 VARCHAR(2)                      not null,
  SXMC                 VARCHAR(16)                     not null,
  SXNR                 VARCHAR(40)                     not null,
  SXSM                 VARCHAR(40),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
primary key (MJID, SXLX, SXXH) constraint PK_APP_MJSX
);

--==============================================================
-- Table: APP_PZGLKZ
--==============================================================

create table APP_PZGLKZ  
(
  PTRQ                 VARCHAR(8)                      not null,
  PTSJ                 VARCHAR(6),
  PTLS                 INTEGER                         not null,
  JYJG                 VARCHAR(16)                     not null,
  JYGY                 VARCHAR(16)                     not null,
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
);

--==============================================================
-- Table: APP_PZHMDJ
--==============================================================

create table APP_PZHMDJ  
(
  PZZL                 VARCHAR(3)                      not null,
  PZHM                 VARCHAR(32)                     not null,
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
  primary key (PZZL, PZHM) constraint PK_APP_PZHMDJ
);

--==============================================================
-- Table: APP_PZSLDJ
--==============================================================

create table APP_PZSLDJ  
(
  PZZL                 VARCHAR(3)                      not null,
  PZWZ                 VARCHAR(34)                     not null,
  NBJG                 VARCHAR(34),
  PZZT                 VARCHAR(1)                      not null,
  PZSL                 INTEGER,
  EXFLD                VARCHAR(40),
  SM                   VARCHAR(40),
  primary key (PZZL, PZWZ, PZZT) constraint PK_APP_PZSLDJ
);

--==============================================================
-- Table: APP_PZXX
--==============================================================

create table APP_PZXX  
(
  PTRQ                 VARCHAR(8)                      not null,
  PTLS                 INTEGER                         not null,
  PZXH                 INTEGER                         not null,
  YWLS                 INTEGER,
  YWRQ                 VARCHAR(8),
  YYBS                 VARCHAR(8),
  CPDM                 VARCHAR(16)                     not null,
  YHBH                 VARCHAR(32),
  YHBSH                VARCHAR(32),
  KHMC                 VARCHAR(80),
  YHZH                 VARCHAR(32),
  JYJE                 DECIMAL(16,2),
  JYJE2                DECIMAL(16,2),
  JYJE3                DECIMAL(16,2),
  SXF                  DECIMAL(16,2),
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
  PZNR                 BYTE,
  primary key (PTRQ, PTLS, PZXH) constraint PK_APP_PZXX
);

--==============================================================
-- Index: K_APP_PZXX_1
--==============================================================
create   index K_APP_PZXX_1 on APP_PZXX (
        PTRQ                 ASC,
        PTLS                 ASC
);

--==============================================================
-- Index: K_APP_PZXX_2
--==============================================================
create   index K_APP_PZXX_2 on APP_PZXX (
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
  PZZL                 VARCHAR(3)                      not null,
  PZMC                 VARCHAR(40)                     not null,
  PZSM                 VARCHAR(80),
  PZLB                 VARCHAR(1),
  PZJB                 VARCHAR(1),
  PZLY                 VARCHAR(16),
  PZZGJG               VARCHAR(16)                     not null,
  ZJPZZL               VARCHAR(8),
  DSFPZZL              VARCHAR(8),
  PZGS                 VARCHAR(40),
  KZLX                 VARCHAR(1)                      not null,
  WHJG                 VARCHAR(16)                     not null,
  WHGY                 VARCHAR(16)                     not null,
  WHSJ                 VARCHAR(14),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
  primary key (PZZL) constraint PK_APP_PZZL
);

--==============================================================
-- Table: APP_QDXX
--==============================================================

create table APP_QDXX  
(
  QDBS                 VARCHAR(3)                      not null,
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
primary key (QDBS) constraint PK_APP_QDXX
);

--==============================================================
-- Table: APP_RWJKB
--==============================================================

create table APP_RWJKB  
(
  YYBS                 VARCHAR(8),
  YYMC                 VARCHAR(40),
  CPDM                 VARCHAR(16)                     not null,
  CPMC                 VARCHAR(40),
  RWMC                 VARCHAR(50),
  JYDM                 VARCHAR(8),
  JYMC                 VARCHAR(40),
  PTLS                 INTEGER                         not null,
  PTRQ                 VARCHAR(8)                      not null,
  JYJG                 VARCHAR(16)                     not null,
  JYGY                 VARCHAR(16)                     not null,
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
  primary key (PTLS, PTRQ) constraint PK_APP_RWJKB
);

--==============================================================
-- Index: INDEX_RWJKB_1
--==============================================================
create   index INDEX_RWJKB_1 on APP_RWJKB (
        JYDM                 ASC,
        PTRQ                 ASC
);

--==============================================================
-- Table: APP_RZPZ
--==============================================================

create table APP_RZPZ  
(
  SSYY                 VARCHAR(8)                      not null,
  CZLX                 VARCHAR(1)                      not null,
  DXLX                 VARCHAR(1)                      not null,
  CZDX1                VARCHAR(128)                    not null,
  CZDX2                VARCHAR(128),
  CZTJ                 VARCHAR(254),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  EXTFLD1              VARCHAR(20),
  EXTFLD2              VARCHAR(20),
primary key (CZLX, DXLX, CZDX1)
      constraint PK_APP_RZPZ
);

--==============================================================
-- Index: K_APP_RZPZ_1
--==============================================================
create   index K_APP_RZPZ_1 on APP_RZPZ (
        SSYY                 ASC,
        CZLX                 ASC,
        DXLX                 ASC
);

--==============================================================
-- Table: APP_SXFFL
--==============================================================

create table APP_SXFFL  
(
  FLBS                 VARCHAR(32)                     not null,
  XH                   VARCHAR(2)                      not null,
  FDBZ                 VARCHAR(1)                      not null,
  NWKBZ                VARCHAR(1),
  SXXKZ                VARCHAR(1)                      not null,
  SXJE                 DECIMAL(16,2),
  XXJE                 DECIMAL(16,2),
  JSLX                 VARCHAR(1)                      not null,
  JSCS                 DECIMAL(16,6)                   not null,
  KJBZ                 VARCHAR(1),
  KJCS                 DECIMAL(16,6),
  FDLX                 VARCHAR(1),
  LJBZ                 VARCHAR(1),
  BHBZ                 VARCHAR(1),
  QSS                  VARCHAR(16),
  JSS                  VARCHAR(16),
  SM                   VARCHAR(40),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
primary key (FLBS, XH) constraint PK_APP_SXFFL
);

--==============================================================
-- Table: APP_SXFLS                                             
--==============================================================
create table APP_SXFLS  
(
   PTRQ                 VARCHAR(8)                     not null,
   PTLS                 VARCHAR(16)                    not null,
   FLBS                 VARCHAR(32)                    not null,
   YYBS                 VARCHAR(3),
   YWBH                 VARCHAR(16),
   CPDM                 VARCHAR(16)                    not null,
   QDBS                 VARCHAR(3),
   JGBS                 VARCHAR(16)                    not null,
   KHLX                 VARCHAR(1),
   KHBH                 VARCHAR(32),
   YHH                  VARCHAR(32),
   DWBH                 VARCHAR(16),
   XTNBZ                VARCHAR(1),
   JYLSH                VARCHAR(16),
   JYLX                 VARCHAR(1),
   JYRQ                 VARCHAR(8),
   JYGY                 VARCHAR(16)                    not null,
   JYJG                 VARCHAR(16)                    not null,
   JYJE                 DECIMAL(16,2),
   JYBS                 INTEGER,
   SXFJE                DECIMAL(16,2)                    not null,
   SFZT                 VARCHAR(1),
   JFZH                 VARCHAR(32),
   DFZH                 VARCHAR(32),
   SFRQ                 VARCHAR(8),
   SFJYGY               VARCHAR(16)                    not null,
   SFJYJG               VARCHAR(16)                    not null,
   SFLS                 VARCHAR(16),
   LSZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(40),
   SM                   VARCHAR(40),
   primary key (PTRQ, PTLS) constraint PK_APP_SXFLS 
);

--==============================================================
-- Index: K_APP_SXFLS_1                                         
--==============================================================
create index K_APP_SXFLS_1 on APP_SXFLS (
   JYLSH ASC,
   JYRQ ASC
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
   WHGY                 VARCHAR(16)                    not null,
   WHJG                 VARCHAR(16)                    not null,
   SQGY                 VARCHAR(16),
   SQJG                 VARCHAR(16),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(40),
   SM                   VARCHAR(40)
);

--==============================================================
-- Index: K_APP_SXFWHLS_1                                       
--==============================================================
create index K_APP_SXFWHLS_1 on APP_SXFWHLS (
   CPDM ASC,
   FLBS ASC,
   CZBM ASC,
   WHRQ ASC
);

--==============================================================
-- Table: APP_TXAQXX                                            
--==============================================================
create table APP_TXAQXX  
(
   LJBS                 VARCHAR(8)                     not null,
   LJMC                 VARCHAR(40),
   LJLX                 VARCHAR(1),
   DWBH                 VARCHAR(16),
   QDKZ                 VARCHAR(1),
   TXMS                 VARCHAR(1),
   TXDZ                 VARCHAR(16),
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
   primary key (LJBS) constraint PK_APP_TXAQXX 
);

--==============================================================
-- Table: APP_XLKZ                                              
--==============================================================
create table APP_XLKZ  
(
   PKEY                 VARCHAR(20)                    not null,
   CURR_VALUE           INTEGER                         not null,
   PINC                 INTEGER                         not null,
   MIN_VALUE            INTEGER                         not null,
   MAX_VALUE            INTEGER                         not null,
   REMARK               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   primary key (PKEY) constraint PK_APP_XLKZ
);

--==============================================================
-- Table: APP_YWRQ                                              
--==============================================================
create table APP_YWRQ  
(
   PKEY                 VARCHAR(20)                    not null,
   SYYWRQ               VARCHAR(8),
   YWRQ                 VARCHAR(8)                     not null,
   XYYWRQ               VARCHAR(8),
   CCH                  VARCHAR(2),
   LSH                  INTEGER,
   EXTFLD               VARCHAR(40),
   SM                   VARCHAR(40),
   primary key (PKEY) constraint PK_APP_YWRQ
);

--==============================================================
-- Table: APP_YYXX                                              
--==============================================================
create table APP_YYXX  
(
   YYBS                 VARCHAR(8)                     not null,
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
   primary key (YYBS) constraint PK_APP_YYXX 
);

-- ���� --
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_PTLSGD', '0', '', '/app/ptlsgd', '2', 'ƽ̨������ˮ�鵵����', '1', '00000','admin');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_PTLSQL', '0', '', '/app/ptlsql', '7', 'ƽ̨������ˮ����������', '1', '00000','admin' );

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_QYCXXZ', '0', '', '/app/custom/qycxxz', '100', 'ǩԼ��ѯ��������¼��', '0', '00000','admin' );

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_ZXLSH', '0', '', '/app/zxlsh', '1', '��С��ˮ��', '0', '00000','admin' );

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_LSH_RETURN', '0', '', '/app/lshreturn', '0', '��ˮ�Ź����ñ�־ 0-����', '0', '00000','admin' );

-- ������Ϣ --
insert into app_xlkz (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY ) 
values ('K_KHBH', 10000000, 1, 1, 99999999, '�ͻ����', '00000','admin' );

insert into app_xlkz (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY ) 
values ('K_KHCPQY', 10000000, 1, 1, 99999999, '�ͻ���ƷǩԼ����', '00000','admin' );

insert into app_xlkz (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY )
values ('K_DWBH', 1, 1, 1, 999999, '��λ���', '00000','admin' );

--�����ֵ�--
insert into app_dict (pkey,keyjs,pval,prompt,ssyy,WHJG,WHGY) values('K_APP_GYJB','��Ա����','11','���㾭��','001','00000','admin');
insert into app_dict (pkey,keyjs,pval,prompt,ssyy,WHJG,WHGY) values('K_APP_GYJB','��Ա����','12','��������','001','00000','admin');
insert into app_dict (pkey,keyjs,pval,prompt,ssyy,WHJG,WHGY) values('K_APP_GYJB','��Ա����','22','������������','001','00000','admin');
insert into app_dict (pkey,keyjs,pval,prompt,ssyy,WHJG,WHGY) values('K_APP_GYJB','��Ա����','32','һ����������','001','00000','admin');

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JDBZ','�����־','D','��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JDBZ','�����־','C','��','001','00000','admin' );
                                           
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','�Ա��־','0','δ֪���Ա�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','�Ա��־','1','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','�Ա��־','2','Ů��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','�Ա��־','9','δ˵���Ա�','001','00000','admin' );
                                                                                      
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','0','�ɹ�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','1','ʧ��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','6','״̬δ֪','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','7','���ױ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','8','���ױ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','9','��ʼ','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_YXBZ','��Ч��־','1','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_YXBZ','��Ч��־','2','�ر�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_YXBZ','��Ч��־','9','δ��Ȩ','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','�������Ʋ���','0','������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','�������Ʋ���','1','һ����������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','�������Ʋ���','2','������������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','�������Ʋ���','3','������������','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','1','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','2','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','3','�ռ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','4','ҹ������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','5','����������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','6','�������ռ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','7','������ҹ������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','8','��������ת��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','9','����','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CPZT','��Ʒ״̬','0','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CPZT','��Ʒ״̬','1','��ͣ','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CSLX','��������','0','ϵͳ����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CSLX','��������','1','��������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CSLX','��������','2','Ӧ�ò���','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DWZJLX','��λ֤������','1','Ӫҵִ��','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','ͨѶģʽ','1','TCP/IP','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','ͨѶģʽ','2','CICSCLI','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','ͨѶģʽ','3','TUXEDOCLI','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','ͨѶģʽ','4','IBM MQ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','ͨѶģʽ','9','����','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','01','�Թ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','02','��˽����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','03','�Թ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','04','��˽����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','05','��֤��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','06','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','07','�ڲ���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','08','������','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','0','���֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','1','���ڲ�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','2','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','3','����֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','4','ʿ��֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','5','�۰ľ��������ڵ�ͨ��֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','6','̨��ͬ�������ڵ�ͨ��֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','7','��ʱ���֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','8','����˾���֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','9','����֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','X','����','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','0','�Թ���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','1','��˽��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','2','�м�ҵ����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','3','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','4','�м۵�֤��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','9','����','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','01','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','02','���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','03','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','04','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','05','�ػ�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','06','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','07','ʹ��','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','CNY','�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','HKD','�۱�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','USD','��Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','EUR','ŷԪ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','JPY','��Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','MOP','����Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','CHF','��ʿ����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','GBP','Ӣ��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','RUR','����˹¬��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','CAD','���ô�Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','DKK','�������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','AUD','�Ĵ�����Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','SEK','������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','KRW','��Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','SGD','��Ԫ','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','�ͻ�����','1','��ͨ�û�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','�ͻ�����','2','�������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','�ͻ�����','3','�𿨹��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','�ͻ�����','4','��ʯ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','�ͻ�����','9','����','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','1','��ä','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','2','Сѧ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','3','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','4','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','5','��ר','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','6','��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','7','˶ʿ�о���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','8','��ʿ�о���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','9','δ֪������','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SFBZ','�ո���־','1','��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SFBZ','�ո���־','2','��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SFBZ','�ո���־','3','����','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','ǩԼ��־','0','����ҪǩԼ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','ǩԼ��־','1','������ǩԼ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','ǩԼ��־','2','����ǩԼ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','ǩԼ��־','3','���ĵ�����ͬʱǩԼ','001','00000','admin' );
                                           
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KKFS','�ۿʽ','1','ȫ��ۿ�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KKFS','�ۿʽ','2','�����ֿۿ�','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_RZMS','��־ģʽ','0','����ģʽ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_RZMS','��־ģʽ','1','����ģʽ','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','ǩԼģʽ','1','��Ʒ���룫�����ʺ�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','ǩԼģʽ','2','��Ʒ���룫�û���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','ǩԼģʽ','3','��Ʒ���룫�����ʺţ��û���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','ǩԼģʽ','4','ҵ���ţ��û���','001','00000','admin' );

INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CZLX', '��������', '1', '�鵵', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CZLX', '��������', '2', '����', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CZLX', '��������', '3', '����', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_DXLX', '��������', '1', '���ݿ�', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_BATCH_MXCGBZ', '��ϸ�ɹ���־', '0', '�ɹ�', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_BATCH_MXCGBZ', '��ϸ�ɹ���־', '1', '���ֳɹ�', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_BATCH_MXCGBZ', '��ϸ�ɹ���־', '2', '����ʧ��', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_DXLX', '��������', '2', '�ļ�', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_HQSJFS', '��ȡ���ݷ�ʽ', '0', 'FTP����ȡ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_HQSJFS', '��ȡ���ݷ�ʽ', '1', 'WEB���������', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_HQSJFS', '��ȡ���ݷ�ʽ', '2', '����', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXTJBZ', '��ϸ�ύ��־', '0', '�ύ����δ�������ʧ����ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXTJBZ', '��ϸ�ύ��־', '1', '�ύ������δ�������ʧ����ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXTJBZ', '��ϸ�ύ��־', '2', '�ύ������δ������ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '��ϸ���̱�־', '0', '��������������ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '��ϸ���̱�־', '1', '���ɱ�����������ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '��ϸ���̱�־', '2', '���ɱ����δ���ɹ���ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '��ϸ���̱�־', '3', '���ɱ����δ���ʧ����ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '��ϸ���̱�־', '4', '�ֱ����ɳɹ�ʧ����ϸ', '002', '00000', 'admin', NULL);

INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_FSSJFS', '�������ݷ�ʽ', '0', 'FTP��������', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_FSSJFS', '�������ݷ�ʽ', '1', 'WEB���������', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_FSSJFS', '�������ݷ�ʽ', '2', '����', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '���޴���', '0', '���׾ܾ�', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '���޴���', '1', '�����Ȩ��Ա����', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '���޴���', '2', '�����Ȩ��Ա��λ', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '���޴���', '3', '�����Ȩ��Ա����͸�λ', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_EDKZFS', '��ȿ��Ʒ�ʽ', '1', '������', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_EDKZFS', '��ȿ��Ʒ�ʽ', '0', '���Ƽ���', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_EDKZFS', '��ȿ��Ʒ�ʽ', '9', '��������', '001', '00000', 'admin', '20110915');

INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_KZBL', '���Ʊ���', '0', '00', '001', '00000', 'admin', '20110830');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_JZSX', '����˳��', '0', '��������', '001', '00000', 'admin', '20110917');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_JZSX', '����˳��', '1', '���ϵ�����', '001', '00000', 'admin', '20110917');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_JJMBZ', '�ӽ��ܱ�־', '0', '����', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_JJMBZ', '�ӽ��ܱ�־', '1', '������', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_WJLXZHBZ', '�ļ�����ת����־ ', '0', 'ת��', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_WJLXZHBZ', '�ļ�����ת����־ ', '1', '��ת��', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_CFCZBZ', '�ظ�������־', '0', '����', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_CFCZBZ', '�ظ�������־', '1', '������', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_SHSBBZ', '���ʧ�ܱ�־ ', '0', '����', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_SHSBBZ', '���ʧ�ܱ�־ ', '1', 'ʧ���˳�', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_XYMZHBZ', '��Ӧ��ת����־', '0', 'ת��', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_XYMZHBZ', '��Ӧ��ת����־', '1', '��ת��', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_DDBZ', '�ϵ��־', '0', '�޶ϵ�', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_DDBZ', '�ϵ��־', '1', '�ϵ�', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_DDBZ', '�ϵ��־', '2', '����', '002', '00000', 'admin', NULL);

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZLSLX','������ˮ����','1','�������˲�ƽ','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZLSLX','������ˮ����','2','���������˲�ƽ','003','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','���˴���״̬','0','δ����','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','���˴���״̬','1','����ɹ�','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','���˴���״̬','8','�������','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','���˴���״̬','9','������','003','00000','admin' );

-- Ӧ����Ϣ --
insert into app_yyxx (YYBS, YYMC, YYSM, YYKFKSRQ, YYKFJSRQ, YYFBRQ, YYBBH, YHH, SQH, YYKFJL, YYZBJL, YYZT, EXTFLD) values ('001', 'app', '������������', '', '', '20130220', '2.1.3.0', '', '', 'YangDong', 'YangDong', '0', '');

-- ������Ϣ --
insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900001', '���׷�����ͣ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900002', 'Ӧ����ͣ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900003', '������ͣ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900004', '���ݹ鵵', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900005', '��������', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900006', '���ݱ���', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900007', '���ݻָ�', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900008', 'ƽ̨����', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900010', '��Ʒ���׷�����ͣ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900011', '���ڲ�ѯ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900012', '�ڼ�������', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900013', '��Ʒҵ����ͣ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900014', '������Ա��Ϣͬ��', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900015', '�����Ѽ���', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900016', '��������ˮ�Ǽ�', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900017', '�����ѻ�������', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900018', 'ƾ֤У��', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900019', 'ƾ֤ʹ��', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900020', 'ƾ֤����', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900021', 'ƾ֤���쳷��', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900022', 'ƾ֤�����ѯ', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900023', 'ƾ֤���', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900024', 'ƾ֤����', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900025', 'ƾ֤����', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900026', 'ƾ֤�ػ�', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900027', 'ƾ֤��ѯ', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900028', 'ƾ֤����', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900029', 'ƾ֤���⳷��', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900030', 'ƾ֤��⳷��', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900031', '����ǩԼ��ϵ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900032', '�Ǽ�ǩԼ��ϵ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900033', '��ѯǩԼ��ϵ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900034', '����ǩԼ��ϵ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900040', 'shell��������', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900041', '������λǩԼ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900042', '�޸ĵ�λǩԼ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900043', '��ѯ��λǩԼ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

--������Ϣ --
insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('200', 'tamc', 'TAMC����̨����', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('201', 'cxs', '�����������', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('202', 'netbk', '������������', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('203', 'telbk', '�绰��������', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('204', 'mbbk', '�ֻ���������', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('205', 'atm', 'ATM����', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('206', 'pos', 'POS����', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('299', 'systask', 'systask�Զ�����', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

-- ������������ --
insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpjggx', '', '', '��Ʒ������ϵ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_dwcpxy', '', '', '��λ��ƷЭ��', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_dwxx', '', '', '��λ��Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_jjrdj', '', '', '�ڼ��յǼ�', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_jyxx', '', '', '������Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_kzsx', '', '', '��չ����', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_khcpqy', '', '', '�ͻ���ƷǩԼ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_khxx', '', '', '������Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_pzhmdj', '', '', 'ƾ֤����Ǽ�', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_pzsldj', '', '', 'ƾ֤�����Ǽ�', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_pzzl', '', '', 'ƾ֤����', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_qdxx', '', '', '������Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_rzpz', '', '', '��������', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_sxffl', '', '', '�����ѷ���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'APP_CPJYJGED', '', '', '��Ʒ���׻�����ȿ���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'APP_CPJYGYED', '', '', '��Ʒ���׹�Ա��ȿ���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'APP_CPJYGYKZ', '', '', '��Ʒ���׹�ԱȨ�޿���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_txaqxx', '', '', 'ͨѶ��ȫ��Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_xlkz', '', '', '���п���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_yyxx', '', '', 'Ӧ����Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpjyfw', '', '', '��Ʒ���׷���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cppzgx', '', '', '��Ʒƾ֤��ϵ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpqdgx', '', '', '��Ʒ������ϵ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpsxfgx', '', '', '��Ʒ�����ѹ�ϵ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpsxfkz', '', '', '��Ʒ�����ѿ���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpxx', '', '', '��Ʒ��Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cskz', '', '', '��������', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_dict', '', '', '�����ֵ�', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '1', '1', 'app_drls', 'app_his_drls', 'C;ptrq;=;K_APP_PTLSGD;;|', 'ƽ̨������ˮ�鵵 ', ' ', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '2', '1', 'app_drls', '', 'C;ptrq;=;K_APP_PTLSQL;;|', 'ƽ̨��ˮ��ǰ������', ' ', '00000','admin' );
