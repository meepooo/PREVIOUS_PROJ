drop table BATCH_AUDITINGCFG;

drop table BATCH_AUDITINGFUNC;

drop table BATCH_AUDITINGPARA;

drop table BATCH_AUDITINGREG;

drop table BATCH_CLI_PARA;

drop table BATCH_CLI_USER;

drop table BATCH_ENCRYPTREG;

drop table BATCH_FILECOLUMN;

drop index K_BAT_FILEMAP_1;
drop index K_BAT_FILEMAP_2;
drop index K_BAT_FILEMAP_3;
drop index K_BAT_FILEMAP_4;
drop table BATCH_FILEMAP;

drop table BATCH_FILESORT;

drop table BATCH_FILETYPE;

drop table BATCH_FLOWCFG;

drop index K_BAT_PLRW_2;

drop table BATCH_HIS_PLRW;

drop index K_BAT_WBWJDJ_2;

drop table BATCH_HIS_WBWJDJ;

drop table BATCH_MAPINFO;

drop table BATCH_MAPRESP;

drop index K_BAT_PLRW_1;
drop index K_BAT_PLRW_3;
drop index K_BAT_PLRW_4;
drop table BATCH_PLRW;

drop index K_BAT_PLRWBD_1;
drop table BATCH_PLRWBD;

drop table BATCH_RUNCTRL;

drop table BATCH_STEPATTRIB;

drop table BATCH_STEPCFG;
drop index K_BAT_WBWJDJ_1;
drop index K_BAT_WBWJDJ_3;
drop index K_BAT_WBWJDJ_4;
drop table BATCH_WBWJDJ;

--==============================================================
-- Table: BATCH_AUDITINGCFG
--==============================================================
create table BATCH_AUDITINGCFG  
(
  AUDITINGID           VARCHAR(32)                     not null,
  AUDITINGSN           INTEGER                         not null,
  FUNCPARASN           INTEGER                         not null,
  FUNCPARA             VARCHAR(128),
  SNOTE                VARCHAR(32),
primary key (AUDITINGID, AUDITINGSN, FUNCPARASN)  constraint PK_BATCH_AUDITINGCFG
);

--==============================================================
-- Table: BATCH_AUDITINGFUNC
--==============================================================
create table BATCH_AUDITINGFUNC  
(
  AUDITINGID           VARCHAR(32)                     not null,
  AUDITINGSN           INTEGER                         not null,
  FUNCID               VARCHAR(32),
  SHSBBZ               VARCHAR(1),
  SNOTE                VARCHAR(32),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
primary key (AUDITINGID, AUDITINGSN) constraint PK_BATCH_AUDITINGFUNC
);

--==============================================================
-- Table: BATCH_AUDITINGPARA
--==============================================================
create table BATCH_AUDITINGPARA  
(
  FUNCID               VARCHAR(32)                     not null,
  PARASN               INTEGER                         not null,
  PARAVALUE            VARCHAR(60),
  SNOTE                VARCHAR(32),
primary key (FUNCID, PARASN)  constraint PK_BATCH_AUDITINGPARA
);

--==============================================================
-- Table: BATCH_AUDITINGREG
--==============================================================
create table BATCH_AUDITINGREG  
(
  FUNCID               VARCHAR(32)                     not null,
  FUNCNAME             VARCHAR(32),
  FUNCRUN              VARCHAR(32),
  FUNCFILE             VARCHAR(32),
  SNOTE                VARCHAR(32),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
primary key (FUNCID) constraint PK_BATCH_AUDITINGREG
);

--==============================================================
-- Table: BATCH_CLI_PARA
--==============================================================

create table BATCH_CLI_PARA  
(
  SJBCTS               INTEGER,
  SJBFLJ               VARCHAR(128),
  SNOTE                VARCHAR(120)
);

--==============================================================
-- Table: BATCH_CLI_USER
--==============================================================

create table BATCH_CLI_USER  
(  
   CONTRACT_NO          VARCHAR(32)                    not null,
   USER_ID              VARCHAR(32),
   USER_NAME            VARCHAR(80),
   CONTACT              VARCHAR(32),
   PHONE                VARCHAR(16),
   MOBILE               VARCHAR(12),
   EMAIL                VARCHAR(50),
   PTRQ                 VARCHAR(8),
   TRAN_TIME            VARCHAR(6),
   PTLS                 VARCHAR(16),
   BRANCH               VARCHAR(16),
   OPER                 VARCHAR(16),
   ACCT_MANAGER         VARCHAR(32),
   ACCT_NAME            VARCHAR(80),
   ACCT_NO              VARCHAR(32),
   STATUS               CHAR(1),
   SEND_FLAG            INTEGER,
   KEY                  VARCHAR(32),
   EXTFLD1              VARCHAR(16),
   EXTFLD2              VARCHAR(32),
   EXTFLD3              VARCHAR(50),
   EXTFLD4              VARCHAR(64),
   primary key (CONTRACT_NO) constraint PK_BATCH_CLI_USER ,
   unique (USER_ID) constraint AK_KEY_2_BATCH_CL 
);

--==============================================================
-- Table: BATCH_ENCRYPTREG
--==============================================================

create table BATCH_ENCRYPTREG  
(
  ENCRYPTID            VARCHAR(50)                     not null,
  ENCRYPTMODE          VARCHAR(1),
  ENCRYPTTYPE          VARCHAR(1),
  SVRNAME              VARCHAR(128),
  FILENAME             VARCHAR(128),
  FUNCNAME             VARCHAR(128),
  ENCRYNOTE            VARCHAR(120),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
primary key (ENCRYPTID) constraint PK_BATCH_ENCRYPTREG
);

--==============================================================
-- Table: BATCH_FILECOLUMN
--==============================================================

create table BATCH_FILECOLUMN  
(
  FILEID               VARCHAR(32)                     not null,
  FILECLASSSN          INTEGER                         not null,
  COLUMNSN             INTEGER                         not null,
  COLUMNID             VARCHAR(32),
  ISID                 VARCHAR(1),
  COLUMNNAME           VARCHAR(40),
  LSX                  VARCHAR(1),
  OFFSET               INTEGER,
  COLUMNLEN            INTEGER,
  IPRECISION           INTEGER,
  IZOOM                INTEGER,
  REGULAR              VARCHAR(1),
  IFILLER              INTEGER,
  FLDREF               VARCHAR(32),
  SNOTE                VARCHAR(32),
  EXTFLD1              VARCHAR(60),
primary key (FILEID, FILECLASSSN, COLUMNSN) constraint PK_BATCH_FILECOLUMN
);

--==============================================================
-- Table: BATCH_FILEMAP
--==============================================================

create table BATCH_FILEMAP  
(
  MAPID                VARCHAR(32)                     not null,
  FLXH                 INTEGER                         not null,
  COLUMNSN             INTEGER                         not null,
  COLUMNID             VARCHAR(16),
  LYLX                 VARCHAR(1),
  LYWZ                 VARCHAR(60),
  ZJSZWZ               INTEGER,
  ZJJGWZ               INTEGER,
  THGXBZ               VARCHAR(1),
  HPWJWZ               INTEGER,
primary key (MAPID, FLXH, COLUMNSN) constraint PK_BATCH_FILEMAP
);

--==============================================================--
-- Index: K_BAT_FILEMAP_1                                       --
--==============================================================--
create index K_BAT_FILEMAP_1 on BATCH_FILEMAP (
   MAPID ASC,
   COLUMNSN ASC
);

--==============================================================--
-- Index: K_BAT_FILEMAP_2                                       --
--==============================================================--
create index K_BAT_FILEMAP_2 on BATCH_FILEMAP (
   MAPID ASC,
   ZJSZWZ ASC
);

--==============================================================--
-- Index: K_BAT_FILEMAP_3                                       --
--==============================================================--
create index K_BAT_FILEMAP_3 on BATCH_FILEMAP (
   MAPID ASC,
   THGXBZ ASC,
   COLUMNSN ASC
);

--==============================================================--
-- Index: K_BAT_FILEMAP_4                                       --
--==============================================================--
create index K_BAT_FILEMAP_4 on BATCH_FILEMAP (
   MAPID ASC,
   HPWJWZ ASC
);

--==============================================================
-- Table: BATCH_FILESORT
--==============================================================

create table BATCH_FILESORT  
(
  FILEID               VARCHAR(32)                     not null,
  FILECLASSSN          INTEGER                         not null,
  CLASSNAME            VARCHAR(40),
  CLASSTYPE            VARCHAR(1),
  HIGHERUPSN           INTEGER,
  POSITIONFLAG         VARCHAR(1),
  CLASSPOSITION        VARCHAR(32),
  COLUMNNO             INTEGER,
  ROWSPRTR             VARCHAR(32),
  SPRTRATTRIB          VARCHAR(1),
  COLUMNFLAG           VARCHAR(1),
  COLUMNSPRTR          VARCHAR(32),
  EXTFLD1              VARCHAR(60),
   primary key (FILEID, FILECLASSSN) constraint PK_BATCH_FILESORT
);

--==============================================================
-- Table: BATCH_FILETYPE
--==============================================================

create table BATCH_FILETYPE  
(
  FILEID               VARCHAR(32)                     not null,
  FILEIDNOTE           VARCHAR(40),
  FILETYPE             VARCHAR(1),
  FILEFMT              VARCHAR(2),
  CODEFMT              VARCHAR(1)                     default '0',
  EXTFLD1              VARCHAR(32),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  primary key (FILEID) constraint PK_BATCH_FILETYPE
);

--==============================================================
-- Table: BATCH_FLOWCFG
--==============================================================

create table BATCH_FLOWCFG  
(
  FLOWID               VARCHAR(32)                     not null,
  FLOWNAME             VARCHAR(40),
  FLOWSN               INTEGER                         not null,
  STEPID               VARCHAR(32),
  STEPSN               INTEGER,
  STEPNAME             VARCHAR(32),
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
primary key (FLOWID, FLOWSN) constraint PK_BATCH_FLOWCFG
);

--==============================================================
-- Table: BATCH_HIS_PLRW
--==============================================================

create table BATCH_HIS_PLRW 
(
  PKRQ                 VARCHAR(8)                      not null,
  PTPCH                VARCHAR(8)                      not null,
  TASKPRI              VARCHAR(3),
  SHPCH                VARCHAR(32),
  ZJPCH                VARCHAR(32),
  YWBH                 VARCHAR(16)                     not null,
  DWBH                 VARCHAR(16),
  TJRQ                 VARCHAR(8),
  TJSJ                 VARCHAR(6),
  CLRQ                 VARCHAR(8),
  CLSJ                 VARCHAR(6),
  ZJE                  DECIMAL(16,2),
  ZBS                  INTEGER,
  SJZJE                DECIMAL(16,2),
  SJZBS                INTEGER,
  CGZJE                DECIMAL(16,2),
  CGZBS                INTEGER,
  SBZJE                DECIMAL(16,2),
  SBZBS                INTEGER,
  SXFJE                DECIMAL(16,2),
  XKHBS                INTEGER,
  XKHJE                DECIMAL(16,2),
  LPWJM                VARCHAR(60),
  SCZJWJM              VARCHAR(60),
  ZJHFWJM              VARCHAR(60),
  SHCGWJM              VARCHAR(60),
  SHSBWJM              VARCHAR(60),
  DQBD                 VARCHAR(2),
  FZBD                 VARCHAR(2),
  BDZT                 VARCHAR(1),
  RWZT                 VARCHAR(1),
  XYDM                 VARCHAR(8),
  XYXX                 VARCHAR(60),
  BQTPKRQ              VARCHAR(8),
  BQTPTPCH             VARCHAR(8),
  QTBZ                 VARCHAR(1)                 default '0',
  QTPKRQ               VARCHAR(8),
  QTPTPCH              VARCHAR(8),
primary key (PKRQ, PTPCH) constraint PK_BATCH_HIS_PLRW
);

--==============================================================
-- Index: K_BAT_PLRW_2
--==============================================================
create   index K_BAT_PLRW_2 on BATCH_HIS_PLRW (
        YWBH                 ASC,
        PKRQ                 ASC,
        PTPCH                ASC
);

--==============================================================
-- Table: BATCH_HIS_WBWJDJ
--==============================================================

create table BATCH_HIS_WBWJDJ  
(
  DJRQ                 VARCHAR(8)                      not null,
  DJLSH                INTEGER                         not null,
  DJSJ                 VARCHAR(6),
  YWBH                 VARCHAR(16)                     not null,
  DJJG                 VARCHAR(16)                     not null,
  DJGY                 VARCHAR(16)                     not null,
  SHJG                 VARCHAR(16),
  SHGY                 VARCHAR(16),
  SHPCH                VARCHAR(32),
  PKRQ                 VARCHAR(8),
  PTPCH                VARCHAR(8),
  LPWJLJ               VARCHAR(254),
  LPWJM                VARCHAR(60),
  ZBS                  VARCHAR(8),
  ZJE                  DECIMAL(16,2),
  THREADNO             INTEGER,
  TASKMODE             VARCHAR(1),
  PCZT                 VARCHAR(1),
  SHZT                 VARCHAR(1),
  NOTE                 VARCHAR(128),
  BREAKDATA            TEXT,
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
  EXTFLD3              VARCHAR(40),
primary key (DJRQ, DJLSH) constraint PK_BATCH_HIS_WBWJDJ
);

--==============================================================
-- Index: K_BAT_WBWJDJ_2
--==============================================================
create   index K_BAT_WBWJDJ_2 on BATCH_HIS_WBWJDJ (
        DJRQ                 ASC,
        SHPCH                ASC
);

--==============================================================
-- Table: BATCH_MAPINFO
--==============================================================

create table BATCH_MAPINFO  
(
  MAPID                VARCHAR(32)                     not null,
  MAPTYPE              VARCHAR(1)                      not null,
  MAPIDNOTE            VARCHAR(40),
  YWBM                 VARCHAR(32),
  LPWJBS               VARCHAR(32),
  HPWJBS               VARCHAR(32),
  TJWJBS               VARCHAR(32),
  THWJBS               VARCHAR(32),
  JLSXZ                INTEGER                        default 0,
  ZHBZ                 VARCHAR(1),
  ZHBS                 VARCHAR(32),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
primary key (MAPID)
      constraint PK_BATCH_MAPINFO
);

--==============================================================
-- Table: BATCH_MAPRESP
--==============================================================

create table BATCH_MAPRESP  
(
  MAPID                VARCHAR(32)                     not null,
  NOTE                 VARCHAR(40),
  RESP_S               VARCHAR(10)                     not null,
  RESP_D               VARCHAR(20)                     not null,
  MSG_D                VARCHAR(40),
  BZ                   VARCHAR(1),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
primary key (MAPID, RESP_S) constraint PK_BATCH_MAPRESP
);

--==============================================================
-- Table: BATCH_PLRW
--==============================================================

create table BATCH_PLRW  
(
  PKRQ                 VARCHAR(8)                      not null,
  PTPCH                VARCHAR(8)                      not null,
  TASKPRI              VARCHAR(3),
  SHPCH                VARCHAR(32),
  ZJPCH                VARCHAR(32),
  YWBH                 VARCHAR(16)                     not null,
  DWBH                 VARCHAR(16),
  TJRQ                 VARCHAR(8),
  TJSJ                 VARCHAR(6),
  CLRQ                 VARCHAR(8),
  CLSJ                 VARCHAR(6),
  ZJE                  DECIMAL(16,2),
  ZBS                  INTEGER,
  SJZJE                DECIMAL(16,2),
  SJZBS                INTEGER,
  CGZJE                DECIMAL(16,2),
  CGZBS                INTEGER,
  SBZJE                DECIMAL(16,2),
  SBZBS                INTEGER,
  SXFJE                DECIMAL(16,2),
  XKHBS                INTEGER,
  XKHJE                DECIMAL(16,2),
  LPWJM                VARCHAR(60),
  SCZJWJM              VARCHAR(60),
  ZJHFWJM              VARCHAR(60),
  SHCGWJM              VARCHAR(60),
  SHSBWJM              VARCHAR(60),
   DQBD                 VARCHAR(2),
   FZBD                 VARCHAR(2)                 default '00',
   BDZT                 VARCHAR(1),
   RWZT                 VARCHAR(1),
   XYDM                 VARCHAR(8),
   XYXX                 VARCHAR(120),
   BQTPKRQ              VARCHAR(8),
   BQTPTPCH             VARCHAR(8),
   QTBZ                 VARCHAR(1)                 default '0',
   QTPKRQ               VARCHAR(8),
   QTPTPCH              VARCHAR(8),
primary key (PKRQ, PTPCH) constraint PK_BATCH_PLRW
);

--==============================================================
-- Index: K_BAT_PLRW_1
--==============================================================
create   index K_BAT_PLRW_1 on BATCH_PLRW (
        YWBH                 ASC,
        PKRQ                 ASC,
        PTPCH                ASC
);

--==============================================================--
-- Index: K_BAT_PLRW_3                                          --
--==============================================================--
create index K_BAT_PLRW_3 on BATCH_PLRW (
   BQTPKRQ ASC,
   BQTPTPCH ASC
);

--==============================================================--
-- Index: K_BAT_PLRW_4                                          --
--==============================================================--
create index K_BAT_PLRW_4 on BATCH_PLRW (
   QTPKRQ ASC,
   QTPTPCH ASC
);

--==============================================================
-- Table: BATCH_PLRWBD
--==============================================================

create table BATCH_PLRWBD  
(
  PKRQ                 VARCHAR(8)                      not null,
  PTPCH                VARCHAR(8)                      not null,
  FLOWSN               INTEGER               default 1 not null ,
  CZBD                 VARCHAR(2)                     not null,
  FZBD                 VARCHAR(2)                 default '00',
  BDZT                 VARCHAR(1),
  CLJG                 VARCHAR(16)                     not null,
  CLGY                 VARCHAR(16)                     not null,
  CLKSRQ               VARCHAR(8),
  CLKSSJ               VARCHAR(6),
  CLJSRQ               VARCHAR(8),
  CLJSSJ               VARCHAR(6),
  CLCS                 INTEGER,
  XYDM                 VARCHAR(8),
  XYXX                 VARCHAR(60),
primary key (PKRQ, PTPCH, FLOWSN, CZBD)  constraint PK_BATCH_PLRWBD
);

create index K_BAT_PLRWBD_1 on BATCH_PLRWBD (
   PKRQ ASC,
   PTPCH ASC,
   CZBD ASC
);

--==============================================================
-- Table: BATCH_RUNCTRL
--==============================================================

create table BATCH_RUNCTRL  
(
  CPDM                 VARCHAR(16)                     not null,
  FLOWID               VARCHAR(32),
  MAXTASK              VARCHAR(5),
  MAXTHREAD            VARCHAR(5),
  ZJYSBS               VARCHAR(32),
  WWYSBS               VARCHAR(32),
  SHBZ                 VARCHAR(1),
  TASKMODE             VARCHAR(1),
  TASKPRI              VARCHAR(3)                     default '0',
  PZBD                 VARCHAR(2),
  EXTFLD1              VARCHAR(60),
  WHJG                 VARCHAR(16),
  WHGY                 VARCHAR(16),
  WHSJ                 VARCHAR(14),
  primary key (CPDM) constraint PK_BATCH_RUNCTRL
);

--==============================================================
-- Table: BATCH_STEPATTRIB
--==============================================================

create table BATCH_STEPATTRIB  
(
  STEPID               VARCHAR(32)                     not null,
  STEPNAME             VARCHAR(40),
  ATTRIBID             VARCHAR(16)                     not null,
  ATTRIBNOTE           VARCHAR(32),
  ATTRIBVALUE          VARCHAR(32),
  primary key (STEPID, ATTRIBID) constraint PK_BATCH_STEPATTRIB
);

--==============================================================
-- Table: BATCH_STEPCFG
--==============================================================

create table BATCH_STEPCFG  
(
  FLOWID               VARCHAR(32)                     not null,
  FLOWSN               INTEGER               default 1 not null ,
  STEPID               VARCHAR(32)                     not null,
  ATTRIBNOTE           VARCHAR(40),
  ATTRIBID             VARCHAR(16)                     not null,
  ATTRIBTYPE           VARCHAR(1),
  ATTRIBVALUE          VARCHAR(60),
primary key (FLOWID, STEPID, ATTRIBID) constraint PK_BATCH_STEPCFG
);

--==============================================================
-- Table: BATCH_WBWJDJ
--==============================================================

create table BATCH_WBWJDJ  
(
  DJRQ                 VARCHAR(8)                      not null,
  DJLSH                INTEGER                         not null,
  DJSJ                 VARCHAR(6),
  YWBH                 VARCHAR(16)                     not null,
  DJJG                 VARCHAR(16)                     not null,
  DJGY                 VARCHAR(16)                     not null,
  SHJG                 VARCHAR(16),
  SHGY                 VARCHAR(16),
  SHPCH                VARCHAR(32),
  PKRQ                 VARCHAR(8),
  PTPCH                VARCHAR(8),
  LPWJLJ               VARCHAR(254),
  LPWJM                VARCHAR(60),
  ZBS                  VARCHAR(8),
  ZJE                  DECIMAL(16,2),
  THREADNO             INTEGER,
  TASKMODE             VARCHAR(1),
  PCZT                 VARCHAR(1),
  SHZT                 VARCHAR(1),
  NOTE                 VARCHAR(128),
  BREAKDATA            TEXT,
  EXTFLD1              VARCHAR(40),
  EXTFLD2              VARCHAR(40),
  EXTFLD3              VARCHAR(40),
  primary key (DJRQ, DJLSH)  constraint PK_BATCH_WBWJDJ
);

--==============================================================--
-- Index: K_BAT_WBWJDJ_1                                        --
--==============================================================--
create index K_BAT_WBWJDJ_1 on BATCH_WBWJDJ (
   SHPCH ASC
);
--==============================================================--
-- Index: K_BAT_WBWJDJ_3                                        --
--==============================================================--
create index K_BAT_WBWJDJ_3 on BATCH_WBWJDJ (
   PKRQ ASC,
   PTPCH ASC
);

--==============================================================--
-- Index: K_BAT_WBWJDJ_4                                        --
--==============================================================--
create index K_BAT_WBWJDJ_4 on BATCH_WBWJDJ (
   LPWJM ASC
);

delete from app_yyxx where YYBS='002';
insert into app_yyxx (YYBS, YYMC, YYSM, YYKFKSRQ, YYKFJSRQ, YYFBRQ, YYBBH, YHH, SQH, YYKFJL, YYZBJL, YYZT, EXTFLD)
values ('002', 'batch', '批量基础服务', '', '', '20150820', '4.1.0.1', '', '', 'Tuql', 'Tuql', '0', '');

delete from APP_CSKZ where csjz='K_BATCH_MAXTASK';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj ) values('K_BATCH_MAXTASK','2','002','/batch/maxtasknum','10','最大并发批量任务','0','00000','admin', '20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_SJTJ_MAXWAIT';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj ) values('K_BATCH_SJTJ_MAXWAIT','2','002','/batch/sjtj/maxwait','43200','提交核心最长等待时间(秒)','0','00000','admin', '20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_SJTJ_ITVL';     
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj ) values ('K_BATCH_SJTJ_ITVL', '2', '002', '/batch/sjtj/interval', '5', '提交核心文件间隔时间(秒)', '0', '100000', 'yd', '20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_HOME';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj ) values('K_BATCH_HOME','2','002','/batch/HOME','/agent/gapsdb2/','批量平台HOME路径','0','00000','admin', '20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_WEB_IP';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_WEB_IP','2','002','/batch/web/serverip','127.0.0.1','WEB服务端ip','1','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_WEB_OVERTIME';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_WEB_OVERTIME','2','002','/batch/web/overtime','360','WEB端服务超时时间(秒)','1','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_WEB_PORT';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_WEB_PORT','2','002','/batch/web/serverport','50005','WEB服务端port','1','00000','admin','20150820090000');

--add by tuql 20150608--
delete from APP_CSKZ where csjz='K_BATCH_MON_NORM';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_MON_NORM','2','002','/batch/mon/norm','MON_BATCH_NORM','批量业务正常受理监控','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_MON_UNORM';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_MON_UNORM','2','002','/batch/mon/unorm','MON_BATCH_UNORM','批量业务异常处理监控','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_FLPATH';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_FLPATH','2','002','/batch/flpath','/dep3/agent21d/AIX32/file/batch','批量文件路径','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_ABNFLOWID';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_ABNFLOWID','2','002','/test/abnflowid','FLOW_xxx','批量业务人为失败流程设定','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_ABNFLOWSN';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_ABNFLOWSN','2','002','/test/abnflowsn','2','批量任务人为失败流程执行序号','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_PRIHIGHPROC';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_PRIHIGHPROC','2','002','/batch/priproc/high','3','批量任务繁忙时中高级优先处理数','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_HOSTFILE';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_HOSTFILE','2','002','/batch/host/fileflg','0','批量任务与主机交互文件标志0-保留,1-删除','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_BQTIP';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_BQTIP','2','002','/batch/bqtrw/ip','192.168.53.25','被嵌套任务通讯IP','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_BQTPORT';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_BQTPORT','2','002','/batch/bqtrw/port','33008','被嵌套任务通讯端口','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_BQTTOUT';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_BQTTOUT','2','002','/batch/bqtrw/tout','60','被嵌套任务通讯超时时间','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_FDSHD_INDEX';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values ('K_BATCH_FDSHD_INDEX','0',null,'/batch/index','9|12','批量业务表数据字段部分屏蔽索引','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_GDQLTS';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values ('K_BATCH_GDQLTS','0',null,'/batch/qlts','7','业务表清理、归档默认天数','1','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_ABNOR_AUTO';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values ('K_BATCH_ABNOR_AUTO','0','002','/batch/abnorauto','1','批量任务异常处理0-不处理 1-处理(缺省)','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_ATASK_DAYS';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values ('K_BATCH_ATASK_DAYS','0','002','/batch/autotask/days','-30','批量自动任务处理天数','0','00000','admin','20150820090000');

delete from app_xlkz where PKEY='K_BATCH_PCH';
insert into APP_XLKZ (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY, WHSJ )
values ('K_BATCH_PCH', 1, 1, 1, 999999999, '批量业务批次号','00000','admin', '20150820090000' );

delete from app_xlkz where PKEY='K_ZCBINDEX';
INSERT INTO APP_XLKZ(PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY, WHSJ)
VALUES('K_ZCBINDEX', 1, 1, 1, 99999999, '注册表索引标识序列', '00000', 'admin', '20150820090000');

delete from app_xlkz where PKEY='K_BATCH_KHBH';
insert into APP_XLKZ (pkey,curr_value,pinc,min_value,max_value,remark,whjg,whgy,whsj)
values('K_BATCH_KHBH',100000,1,1,99999999,'批量客户编号','00000','admin','20150820090000');

delete from app_xlkz where PKEY='K_BATCH_XYBH';
insert into APP_XLKZ (pkey,curr_value,pinc,min_value,max_value,remark,whjg,whgy,whsj)
values('K_BATCH_XYBH',100000,1,1,99999999,'批量客户协议编号','00000','admin','20150820090000');

delete from app_dict where ssyy='002';
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_STEP_DDBZ','断点标志','0','无断点','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_STEP_DDBZ','断点标志','1','断点','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_STEP_DDBZ','断点标志','2','返回','002','00000','admin' ); 

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_BATCH_MXCGBZ','明细成功标志','0','成功','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_BATCH_MXCGBZ','明细成功标志','1','部分成功','002','00000','admin');
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_BATCH_MXCGBZ','明细成功标志','2','处理失败','002','00000','admin'); 

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_CFCZBZ','重复操作标志','0','允许','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_CFCZBZ','重复操作标志','1','不允许','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_HQSJFS','获取数据方式','0','FTP主动取','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_HQSJFS','获取数据方式','1','WEB服务端数据','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_HQSJFS','获取数据方式','2','交易获取','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXTJBZ','明细提交标志','1','提交所有未处理或处理失败明细','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXTJBZ','明细提交标志','2','提交本批次未处理明细','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXHPBZ','明细回盘标志','0','生成所有批次明细','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXHPBZ','明细回盘标志','1','生成本批次所有明细','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXHPBZ','明细回盘标志','2','生成本批次处理成功明细','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXHPBZ','明细回盘标志','3','生成本批次处理失败明细','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXHPBZ','明细回盘标志','4','分别生成成功失败明细','002','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_XYMZHBZ','响应码转换标志','0','转换','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_XYMZHBZ','响应码转换标志','1','不转换','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_FSSJFS','发送数据方式','0','FTP主动发送','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_FSSJFS','发送数据方式','1','WEB服务端数据','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_FSSJFS','发送数据方式','2','交易','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_JJMBZ','加解密标志','0','需要','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_JJMBZ','加解密标志','1','不需要','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_WJLXZHBZ','文件类型转换标志 ','0','需要','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_WJLXZHBZ','文件类型转换标志 ','1','不需要','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_SHSBBZ','审核失败标志 ','0','不跳过','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_SHSBBZ','审核失败标志 ','1','跳过','002','00000','admin' );

INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CGBZ', '成功标志', '0', '成功', '002', '00000', 'admin', '20120116044021');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CGBZ', '成功标志', '1', '部分成功', '002', '00000', 'admin', '20120116044032');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CGBZ', '成功标志', '2', '处理失败', '002', '00000', 'admin', '20120116044044');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CGBZ', '成功标志', '9', '初始状态', '002', '00000', 'admin', '20120116043959');
--INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CLZT', '处理状态', '0', '未处理', '002', '00000', 'admin', '20120116043839');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CLZT', '处理状态', '1', '已处理', '002', '00000', 'admin', '20120116043855');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CLZT', '处理状态', '9', '初始状态', '002', '00000', 'admin', '20120116043815');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_SHZT', '审核状态', '0', '审核通过', '002', '00000', 'admin', '20120116043700');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_SHZT', '审核状态', '1', '审核失败', '002', '00000', 'admin', '20120116043729');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_SHZT', '审核状态', '9', '初始状态', '002', '00000', 'admin', '20120116043603');
  
  
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_YXJ', '优先级', '0', '低级', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_YXJ', '优先级', '1', '中级', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_YXJ', '优先级', '2', '高级', '002', '00000', 'admin', '20150820090000');
   
delete from app_jyxx where yybs='002';
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910001', '批量业务录入申请', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910002', '批量任务发起','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910003', '批量业务等待触发', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910004', '批量业务断点触发', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910005', '批量业务获取数据', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910006', '批量业务数据入库', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910007', '批量业务数据审核', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910008', '批量业务数据提交', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910009', '批量业务数据提回', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910030', '批量业务任务嵌套', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910031', '批量业务后续处理', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910010', '批量业务主机批次状态查询', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910011', '批量业务数据回盘', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910012', '批量业务任务状态查询', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910013', '批量业务任务取消','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910014', '批量业务主机批次撤销', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910015', '批量业务第三方撤销', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910016', '批量业务自动发起失败/等待交易', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910020', '批量业务任务直接发起','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
 
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910021', '批量客户端领用','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910022', '批量客户端领用信息修改','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910023', '批量客户端领用信息查询','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910024', '批量客户端KEY查询','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into BATCH_AUDITINGPARA (FUNCID, PARASN, PARAVALUE, SNOTE ) values ('FUNC_K_2', 1, 'yhzh', '借方帐号' );
insert into BATCH_AUDITINGPARA (FUNCID, PARASN, PARAVALUE, SNOTE ) values ('FUNC_K_2', 2, '20', '长度' );

insert into BATCH_AUDITINGREG (FUNCID, FUNCNAME, FUNCRUN, FUNCFILE, SNOTE, WHJG, WHGY ) values ('FUNC_K_1', 'BATCH_CHECKALLNUM', 'BATCH_CHECKALLNUM', 'BAT_CHECK.so', '批量业务校验总笔数总金额','00000','admin' );
insert into BATCH_AUDITINGREG (FUNCID, FUNCNAME, FUNCRUN, FUNCFILE, SNOTE, WHJG, WHGY ) values ('FUNC_K_2', 'BATCH_CHECKLEN', 'BATCH_CHECKLEN', 'BAT_CHECK.so', '批量业务审核列长度','00000','admin' );
insert into BATCH_AUDITINGREG (FUNCID, FUNCNAME, FUNCRUN, FUNCFILE, SNOTE, WHJG, WHGY ) values ('FUNC_K_3', 'BATCH_CHECKSIGN', 'BATCH_CHECKSIGN', 'BAT_CHECK.so', '批量业务校验签约关系','00000','admin' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'ddbz', '断点标志','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'ddsj', '断点时间(秒)','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'cllcm', '处理流程名','flow_batch_step_hqsj' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'hqsjfs', '获取数据方式','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'filename', '文件名','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'filedir', '文件本地路径','file/batch/dsf' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'ftpip', 'FTPIP地址','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'ftpuser', 'FTP用户','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'ftppwd', 'FTP密码','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'ftpmlj', 'FTP远程路径','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'ftpmode', 'FTP主动被动模式','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '获取数据', 'ftptype', 'FTP传输模式','' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '数据入库', 'cllcm', '处理流程名','flow_batch_step_sjrk' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '数据入库', 'ddbz', '断点标志','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '数据入库', 'ddsj', '断点时间(秒)','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '数据入库', 'jjmbz', '加解密标志','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '数据入库', 'jjmbs', '加解密服务标识','subflow_batch_des_proc' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '数据入库', 'wjlxzhbz', '文件类型转换标志','1' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjsh', '数据审核', 'cllcm', '处理流程名','flow_batch_step_sjsh' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjsh', '数据审核', 'ddbz', '断点标志','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjsh', '数据审核', 'ddsj', '断点时间(秒)','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjsh', '数据审核', 'shbs', '数据审核标识','' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '数据提交', 'cllcm', '处理流程名','flow_batch_step_sjtj' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '数据提交', 'ddbz', '断点标志','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '数据提交', 'gdddsj', '固定断点时间(秒)','5' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '数据提交', 'fdddsj', '浮动断点时间(秒)','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '数据提交', 'cfczbz', '重复操作标志','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '数据提交', 'mxtjbz', '明细提交标志','2' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '数据提交', 'expwhere', '明细导出条件eg: AND shzt !=#1# ','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '数据提交', 'ksclsj', '夜间批量开始处理时间','220000' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjth', '数据提回', 'cllcm', '处理流程名','flow_batch_step_sjth' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjth', '数据提回', 'cfczbz', '重复操作标志','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjth', '数据提回', 'ddbz', '断点标志','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjth', '数据提回', 'ddsj', '断点时间(秒)','5' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjth', '数据提回', 'cftjbz', '重复提交标志','1' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'cllcm', '处理流程名','flow_batch_step_sjhp' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'cfczbz', '重复操作标志','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'fssjfs', '发送数据方式','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'jjmbz', '加解密标志','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'jjmbs', '加解密服务标识','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'wjlxzhbz', '文件类型转换标志','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'ftpip', 'FTPIP地址','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'ftpuser', 'FTP用户','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'ftppwd', 'FTP密码','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'ftpmlj', 'FTP远程路径','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'mxhpbz', '明细回盘标志','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'filename', '成功回盘文件名','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '数据回盘', 'filename_f', '失败回盘文件名','' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '任务嵌套', 'cllcm', '处理流程名','flow_batch_step_rwqt' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '任务嵌套', 'bqtcpdm', '被嵌套产品代码','xxxx' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '任务嵌套', 'bqtywbh', '被嵌套业务编号','xxxx' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '任务嵌套', 'qtwjys', '嵌套文件映射','MAP_' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '任务嵌套', 'qtwjdc', '嵌套文件导出WHERE eg: yhzh=#123#',' 1=1 ' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '任务嵌套', 'cfczbz', '重复操作标志','0' );

delete from APP_TABLEINFO where TABLECODE='batch_mxmb';
insert into  APP_TABLEINFO (TABLECODE,TABLENAME,TABLETYPE,WHJG,WHGY ) values ('batch_mxmb','批量业务明细模板','2','00000','admin' );

delete from APP_TABLEREG where TABLENAME='batch_mxmb';
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 1, 'pkrq', '批扣日期', 'C', '8', null, '0', '1');
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 2, 'ptpch', '平台批次号', 'C', '8', null, '0', '1');
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 3, 'lsxh', '流水序号', 'I', null, null, '0', '1' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 4, 'wjxh', '文件序号', 'I', null, null, '1', '1' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 5, 'ywbh', '业务编号', 'C', '16', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 6, 'dwbh', '单位编号', 'C', '16', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 7, 'jlbs', '记录标识', 'C', '32', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 8, 'yhh1', '用户号', 'C', '32', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 9, 'yhxm', '用户姓名', 'C', '80', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 10, 'zjhm', '证件号码', 'C', '32', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 11, 'yhzh', '用户帐户', 'C', '32', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 12, 'jyje', '交易金额', 'D', '15', '2', '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 13, 'sjje', '实际金额', 'D', '15', '2', '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 14, 'shzt', '审核状态', 'C', '1', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 15, 'clzt', '处理状态', 'C', '1', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 16, 'cgbz', '成功标志', 'C', '1', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 17, 'xym', '响应码', 'C', '8', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 18, 'xyxx', '响应信息', 'C', '60', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 19, 'dsfxym', '第三方响应码', 'C', '8', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 20, 'dsfxyxx', '第三方响应信息', 'C', '60', null, '1', '0' );
