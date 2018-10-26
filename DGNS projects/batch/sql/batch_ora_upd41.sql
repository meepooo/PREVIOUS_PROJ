--请先备份以下各表数据

drop table BATCH_FILETYPE cascade constraints;

drop table BATCH_FLOWCFG cascade constraints;

drop table BATCH_STEPCFG cascade constraints;

drop table BATCH_RUNCTRL cascade constraints;

drop index K_BAT_PLRW_1;
drop index K_BAT_PLRW_3;
drop index K_BAT_PLRW_4;
drop table BATCH_PLRW cascade constraints;

drop index K_BAT_PLRW_2;
drop table BATCH_HIS_PLRW cascade constraints;

drop index K_BAT_PLRWBD_1;
drop table BATCH_PLRWBD cascade constraints;

drop index K_BAT_WBWJDJ_1;
drop index K_BAT_WBWJDJ_3;
drop index K_BAT_WBWJDJ_4;
drop table BATCH_WBWJDJ cascade constraints;

drop index K_BAT_WBWJDJ_2;

drop table BATCH_HIS_WBWJDJ cascade constraints;

--==============================================================--
-- Table: BATCH_FILETYPE                                        --
--==============================================================--
create table BATCH_FILETYPE  (
   FILEID               VARCHAR2(32)                    not null,
   FILEIDNOTE           VARCHAR2(40),
   FILETYPE             VARCHAR2(1),
   FILEFMT              VARCHAR2(2),
   CODEFMT              VARCHAR2(1)                     default '0',
   EXTFLD1              VARCHAR2(32),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_BATCH_FILETYPE primary key (FILEID)
);

comment on column BATCH_FILETYPE.FILETYPE is
'0- txt 1-DBF 2-xls 3-xlsx 4-dbf  默认 0';

comment on column BATCH_FILETYPE.FILEFMT is
'01  单明细
02  汇总＋单明细
03  单明细＋汇总
04  汇总＋单明细＋汇总
';

comment on column BATCH_FILETYPE.CODEFMT is
'编码格式 0-ascii 1-utf-8 2-base64';

--==============================================================--
-- Table: BATCH_FLOWCFG                                         --
--==============================================================--
create table BATCH_FLOWCFG  (
   FLOWID               VARCHAR2(32)                    not null,
   FLOWNAME             VARCHAR2(40),
   FLOWSN               INTEGER                         not null,
   STEPID               VARCHAR2(32),
   STEPSN               INTEGER,
   STEPNAME             VARCHAR2(32),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_BATCH_FLOWCFG primary key (FLOWID, FLOWSN)
);

--==============================================================--
-- Table: BATCH_STEPCFG                                         --
--==============================================================--
create table BATCH_STEPCFG  (
   FLOWID               VARCHAR2(32)                    not null,
   FLOWSN               INTEGER               default 1 not null ,
   STEPID               VARCHAR2(32)                    not null,
   ATTRIBNOTE           VARCHAR2(40),
   ATTRIBID             VARCHAR2(16)                    not null,
   ATTRIBTYPE           VARCHAR2(1),
   ATTRIBVALUE          VARCHAR2(60),
   constraint PK_BATCH_STEPCFG primary key (FLOWID, FLOWSN, STEPID, ATTRIBID)
);

comment on column BATCH_STEPCFG.FLOWSN is
'流程执行序号';

comment on column BATCH_STEPCFG.ATTRIBTYPE is
'0 运行属性 1开发属性';

comment on column BATCH_STEPCFG.FLOWSN is
'流程执行序号';

--==============================================================--
-- Table: BATCH_RUNCTRL                                         --
--==============================================================--
create table BATCH_RUNCTRL  (
   CPDM                 VARCHAR2(16)                    not null,
   FLOWID               VARCHAR2(32),
   MAXTASK              VARCHAR2(5),
   MAXTHREAD            VARCHAR2(5),
   ZJYSBS               VARCHAR2(32),
   WWYSBS               VARCHAR2(32),
   SHBZ                 VARCHAR2(1),
   TASKMODE             VARCHAR2(1),
   TASKPRI              VARCHAR2(3)                     default '0',
   PZBD                 VARCHAR2(2),
   EXTFLD1              VARCHAR2(60),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_BATCH_RUNCTRL primary key (CPDM)
);

comment on column BATCH_RUNCTRL.SHBZ is
'0：需要审核外部文件，1：不需要审核外部文件';

comment on column BATCH_RUNCTRL.TASKMODE is
'1：立即，2：手动（默认为1）';

comment on column BATCH_RUNCTRL.TASKPRI is
'任务优先级 0-低级 1-中级 2-高级';

comment on column BATCH_RUNCTRL.PZBD is
'配置步点';

--==============================================================--
-- Table: BATCH_PLRW                                            --
--==============================================================--
create table BATCH_PLRW  (
   PKRQ                 VARCHAR2(8)                     not null,
   PTPCH                VARCHAR2(8)                     not null,
   TASKPRI              VARCHAR2(3),
   SHPCH                VARCHAR2(32),
   ZJPCH                VARCHAR2(32),
   YWBH                 VARCHAR2(16)                    not null,
   DWBH                 VARCHAR2(16),
   TJRQ                 VARCHAR2(8),
   TJSJ                 VARCHAR2(6),
   CLRQ                 VARCHAR2(8),
   CLSJ                 VARCHAR2(6),
   ZJE                  NUMBER(16,2),
   ZBS                  INTEGER,
   SJZJE                NUMBER(16,2),
   SJZBS                INTEGER,
   CGZJE                NUMBER(16,2),
   CGZBS                INTEGER,
   SBZJE                NUMBER(16,2),
   SBZBS                INTEGER,
   SXFJE                NUMBER(16,2),
   XKHBS                INTEGER,
   XKHJE                NUMBER(16,2),
   LPWJM                VARCHAR2(60),
   SCZJWJM              VARCHAR2(60),
   ZJHFWJM              VARCHAR2(60),
   SHCGWJM              VARCHAR2(60),
   SHSBWJM              VARCHAR2(60),
   DQBD                 VARCHAR2(2),
   FZBD                 VARCHAR2(2)                 default '00',
   BDZT                 VARCHAR2(1),
   RWZT                 VARCHAR2(1),
   XYDM                 VARCHAR2(8),
   XYXX                 VARCHAR2(60),
   BQTPKRQ              VARCHAR2(8),
   BQTPTPCH             VARCHAR2(8),
   QTBZ                 VARCHAR2(1)                 default '0',
   QTPKRQ               VARCHAR2(8),
   QTPTPCH              VARCHAR2(8),
   constraint PK_BATCH_PLRW primary key (PKRQ, PTPCH)
);

comment on table BATCH_PLRW is
'批量业务任务表';

comment on column BATCH_PLRW.PKRQ is
'批扣日期(平台日期)';

comment on column BATCH_PLRW.PTPCH is
'平台批次号';

comment on column BATCH_PLRW.TASKPRI is
'任务优先级';

comment on column BATCH_PLRW.SHPCH is
'商户批次号';

comment on column BATCH_PLRW.ZJPCH is
'主机批次号';

comment on column BATCH_PLRW.YWBH is
'业务编号';

comment on column BATCH_PLRW.DWBH is
'单位编号';

comment on column BATCH_PLRW.TJRQ is
'外围提交任务的日期';

comment on column BATCH_PLRW.TJSJ is
'提交时间';

comment on column BATCH_PLRW.CLRQ is
'处理结束日期';

comment on column BATCH_PLRW.CLSJ is
'处理时间';

comment on column BATCH_PLRW.ZJE is
'请求总金额（任务）';

comment on column BATCH_PLRW.ZBS is
'请求总笔数（任务）';

comment on column BATCH_PLRW.SJZJE is
'实际总金额（文件内）';

comment on column BATCH_PLRW.SJZBS is
'实际总笔数（文件内）';

comment on column BATCH_PLRW.CGZJE is
'成功总金额';

comment on column BATCH_PLRW.CGZBS is
'成功总笔数';

comment on column BATCH_PLRW.SBZJE is
'失败总金额';

comment on column BATCH_PLRW.SBZBS is
'失败总笔数';

comment on column BATCH_PLRW.SXFJE is
'手续费金额';

comment on column BATCH_PLRW.XKHBS is
'新开户笔数';

comment on column BATCH_PLRW.XKHJE is
'新开户金额';

comment on column BATCH_PLRW.LPWJM is
'商户来盘文件名';

comment on column BATCH_PLRW.SCZJWJM is
'上传主机文件名';

comment on column BATCH_PLRW.ZJHFWJM is
'主机回复文件名';

comment on column BATCH_PLRW.SHCGWJM is
'回复商户成功文件名（回盘文件名）';

comment on column BATCH_PLRW.SHSBWJM is
'回复商户失败文件名';

comment on column BATCH_PLRW.DQBD is
'操作步点 0 获取数据 1 数据入库 2 数据校验 3 提交主机 4主机提回  5回盘';

comment on column BATCH_PLRW.FZBD is
'辅助步点
当操作步点为7－任务嵌套时才有效，其他步点使用00
00-待受理  09-受理中 10-待返回  19-返回中 11-已返回 99-步点终态';

comment on column BATCH_PLRW.BDZT is
' 0中止 1结束 2断点 3返回 4等待 9在处理中  X 撤销 C冲正 Z终止';

comment on column BATCH_PLRW.RWZT is
' 0中止 1结束 2断点 3返回 4等待 9在处理中  X 撤销 C冲正 Z终止';

comment on column BATCH_PLRW.XYDM is
'响应代码';

comment on column BATCH_PLRW.XYXX is
'响应信息';

comment on column BATCH_PLRW.BQTPKRQ is
'被嵌套批扣日期';

comment on column BATCH_PLRW.BQTPTPCH is
'被嵌套平台批次号';

comment on column BATCH_PLRW.QTBZ is
'嵌套标志 0-非嵌套 1-嵌套 2-被嵌套 3-既被嵌套又嵌套';

comment on column BATCH_PLRW.QTPKRQ is
'嵌套批扣日期';

comment on column BATCH_PLRW.QTPTPCH is
'嵌套平台批次号';

--==============================================================--
-- Index: K_BAT_PLRW_1                                          --
--==============================================================--
create index K_BAT_PLRW_1 on BATCH_PLRW (
   YWBH ASC,
   PKRQ ASC,
   PTPCH ASC
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

--==============================================================--
-- Table: BATCH_HIS_PLRW                                        --
--==============================================================--
create table BATCH_HIS_PLRW  (
   PKRQ                 VARCHAR2(8)                     not null,
   PTPCH                VARCHAR2(8)                     not null,
   TASKPRI              VARCHAR2(3),
   SHPCH                VARCHAR2(32),
   ZJPCH                VARCHAR2(32),
   YWBH                 VARCHAR2(16)                    not null,
   DWBH                 VARCHAR2(16),
   TJRQ                 VARCHAR2(8),
   TJSJ                 VARCHAR2(6),
   CLRQ                 VARCHAR2(8),
   CLSJ                 VARCHAR2(6),
   ZJE                  NUMBER(16,2),
   ZBS                  INTEGER,
   SJZJE                NUMBER(16,2),
   SJZBS                INTEGER,
   CGZJE                NUMBER(16,2),
   CGZBS                INTEGER,
   SBZJE                NUMBER(16,2),
   SBZBS                INTEGER,
   SXFJE                NUMBER(16,2),
   XKHBS                INTEGER,
   XKHJE                NUMBER(16,2),
   LPWJM                VARCHAR2(60),
   SCZJWJM              VARCHAR2(60),
   ZJHFWJM              VARCHAR2(60),
   SHCGWJM              VARCHAR2(60),
   SHSBWJM              VARCHAR2(60),
   DQBD                 VARCHAR2(2),
   FZBD                 VARCHAR2(2)                 default '00',
   BDZT                 VARCHAR2(1),
   RWZT                 VARCHAR2(1),
   XYDM                 VARCHAR2(8),
   XYXX                 VARCHAR2(60),
   BQTPKRQ              VARCHAR2(8),
   BQTPTPCH             VARCHAR2(8),
   QTBZ                 VARCHAR2(1)                 default '0',
   QTPKRQ               VARCHAR2(8),
   QTPTPCH              VARCHAR2(8),
   constraint PK_BATCH_HIS_PLRW primary key (PKRQ, PTPCH)
);

comment on table BATCH_HIS_PLRW is
'批量业务任务历史表';

comment on column BATCH_HIS_PLRW.PKRQ is
'批扣日期(平台日期)';

comment on column BATCH_HIS_PLRW.PTPCH is
'平台批次号';

comment on column BATCH_HIS_PLRW.TASKPRI is
'任务优先级';

comment on column BATCH_HIS_PLRW.SHPCH is
'商户批次号';

comment on column BATCH_HIS_PLRW.ZJPCH is
'主机批次号';

comment on column BATCH_HIS_PLRW.YWBH is
'业务编号';

comment on column BATCH_HIS_PLRW.DWBH is
'单位编号';

comment on column BATCH_HIS_PLRW.TJRQ is
'外围提交任务的日期';

comment on column BATCH_HIS_PLRW.TJSJ is
'提交时间';

comment on column BATCH_HIS_PLRW.CLRQ is
'处理结束日期';

comment on column BATCH_HIS_PLRW.CLSJ is
'处理时间';

comment on column BATCH_HIS_PLRW.ZJE is
'请求总金额（任务）';

comment on column BATCH_HIS_PLRW.ZBS is
'请求总笔数（任务）';

comment on column BATCH_HIS_PLRW.SJZJE is
'实际总金额（文件内）';

comment on column BATCH_HIS_PLRW.SJZBS is
'实际总笔数（文件内）';

comment on column BATCH_HIS_PLRW.CGZJE is
'成功总金额';

comment on column BATCH_HIS_PLRW.CGZBS is
'成功总笔数';

comment on column BATCH_HIS_PLRW.SBZJE is
'失败总金额';

comment on column BATCH_HIS_PLRW.SBZBS is
'失败总笔数';

comment on column BATCH_HIS_PLRW.SXFJE is
'手续费金额';

comment on column BATCH_HIS_PLRW.XKHBS is
'新开户笔数';

comment on column BATCH_HIS_PLRW.XKHJE is
'新开户金额';

comment on column BATCH_HIS_PLRW.LPWJM is
'商户来盘文件名';

comment on column BATCH_HIS_PLRW.SCZJWJM is
'上传主机文件名';

comment on column BATCH_HIS_PLRW.ZJHFWJM is
'主机回复文件名';

comment on column BATCH_HIS_PLRW.SHCGWJM is
'回复商户成功文件名（回盘文件名）';

comment on column BATCH_HIS_PLRW.SHSBWJM is
'回复商户失败文件名';

comment on column BATCH_HIS_PLRW.DQBD is
'操作步点 0 获取数据 1 数据入库 2 数据校验 3 提交主机 4主机提回  5回盘';

comment on column BATCH_HIS_PLRW.FZBD is
'辅助步点
当操作步点为7－任务嵌套时才有效，其他步点使用00，批量任务处理结束99-步点终态
00-待受理  09-受理中 10-待返回  19-返回中 11-已返回 ';

comment on column BATCH_HIS_PLRW.BDZT is
' 0中止 1结束 2断点 3返回 4等待 9在处理中  X 撤销 C冲正';

comment on column BATCH_HIS_PLRW.RWZT is
' 0中止 1结束 2断点 3返回 4等待 9在处理中  X 撤销 C冲正';

comment on column BATCH_HIS_PLRW.XYDM is
'响应代码';

comment on column BATCH_HIS_PLRW.XYXX is
'响应信息';

comment on column BATCH_HIS_PLRW.BQTPKRQ is
'被嵌套批扣日期';

comment on column BATCH_HIS_PLRW.BQTPTPCH is
'被嵌套平台批次号';

comment on column BATCH_HIS_PLRW.QTBZ is
'嵌套标志 0-非嵌套 1-嵌套 2-被嵌套 3-既被嵌套又嵌套';

comment on column BATCH_HIS_PLRW.QTPKRQ is
'嵌套批扣日期';

comment on column BATCH_HIS_PLRW.QTPTPCH is
'嵌套平台批次号';

--==============================================================--
-- Index: K_BAT_PLRW_2                                          --
--==============================================================--
create index K_BAT_PLRW_2 on BATCH_HIS_PLRW (
   YWBH ASC,
   PKRQ ASC,
   PTPCH ASC
);

--==============================================================--
-- Table: BATCH_PLRWBD                                          --
--==============================================================--
create table BATCH_PLRWBD  (
   PKRQ                 VARCHAR2(8)                     not null,
   PTPCH                VARCHAR2(8)                     not null,
   FLOWSN               INTEGER               default 1 not null ,
   CZBD                 VARCHAR2(2)                     not null,
   FZBD                 VARCHAR2(2),
   BDZT                 VARCHAR2(1),
   CLJG                 VARCHAR2(16)                    not null,
   CLGY                 VARCHAR2(16)                    not null,
   CLKSRQ               VARCHAR2(8),
   CLKSSJ               VARCHAR2(6),
   CLJSRQ               VARCHAR2(8),
   CLJSSJ               VARCHAR2(6),
   CLCS                 INTEGER,
   XYDM                 VARCHAR2(8),
   XYXX                 VARCHAR2(60),
   constraint PK_BATCH_PLRWBD primary key (PKRQ, PTPCH, FLOWSN, CZBD)
);

comment on table BATCH_PLRWBD is
'批量业务任务步点明细表';

comment on column BATCH_PLRWBD.PKRQ is
'批扣日期(平台日期)';

comment on column BATCH_PLRWBD.PTPCH is
'平台批次号';

comment on column BATCH_PLRWBD.FLOWSN is
'流程执行序号';

comment on column BATCH_PLRWBD.CZBD is
'操作步点 0 获取数据 1 数据入库 2 数据审核 3 数据提交 4数据提回  5企业回盘  ';

comment on column BATCH_PLRWBD.FZBD is
'辅助步点
当操作步点为7－任务嵌套时才有效，其他步点使用00，批量任务处理结束99-步点终态
00-待受理  09-受理中 10-待返回  19-返回中 11-已返回 ';

comment on column BATCH_PLRWBD.BDZT is
' 0中止 1结束 2断点 3返回 4等待 9在处理中 ';

comment on column BATCH_PLRWBD.CLJG is
'处理机构';

comment on column BATCH_PLRWBD.CLGY is
'处理柜员';

comment on column BATCH_PLRWBD.XYDM is
'响应代码';

comment on column BATCH_PLRWBD.XYXX is
'响应信息';

--==============================================================--
-- Index: K_BAT_PLRWBD_1                                      --
--==============================================================--
create index K_BAT_PLRWBD_1 on BATCH_PLRWBD (
   PKRQ ASC,
   PTPCH ASC,
   CZBD ASC
);

--==============================================================--
-- Table: BATCH_WBWJDJ                                          --
--==============================================================--
create table BATCH_WBWJDJ  (
   DJRQ                 VARCHAR2(8)                     not null,
   DJLSH                INTEGER                         not null,
   DJSJ                 VARCHAR2(6),
   YWBH                 VARCHAR2(16)                    not null,
   DJJG                 VARCHAR2(16)                    not null,
   DJGY                 VARCHAR2(16)                    not null,
   SHJG                 VARCHAR2(16),
   SHGY                 VARCHAR2(16),
   SHPCH                VARCHAR2(32),
   PKRQ                 VARCHAR2(8),
   PTPCH                VARCHAR2(8),
   LPWJLJ               VARCHAR2(254),
   LPWJM                VARCHAR2(60),
   ZBS                  VARCHAR2(8),
   ZJE                  NUMBER(16,2),
   THREADNO             INTEGER,
   TASKMODE             VARCHAR2(1),
   PCZT                 VARCHAR2(1),
   SHZT                 VARCHAR2(1),
   NOTE                 VARCHAR2(128),
   BREAKDATA            BLOB,
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   EXTFLD3              VARCHAR2(40),
   constraint PK_BATCH_WBWJDJ primary key (DJRQ, DJLSH)
);

comment on column BATCH_WBWJDJ.THREADNO is
'（高级选项默认为1）';

comment on column BATCH_WBWJDJ.TASKMODE is
'1：立即，2：手动（默认为1）';

comment on column BATCH_WBWJDJ.PCZT is
'1：正在上传，2：就绪，3：正在处理，4：已返回，5：处理失败，X：撤销, C:冲正，Z:终止';

comment on column BATCH_WBWJDJ.SHZT is
'0：审核通过，1：未审核，2：审核失败';

comment on column BATCH_WBWJDJ.SHJG is
'审核机构';

comment on column BATCH_WBWJDJ.SHGY is
'审核柜员';
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
--==============================================================--
-- Table: BATCH_HIS_WBWJDJ                                      --
--==============================================================--
create table BATCH_HIS_WBWJDJ  (
   DJRQ                 VARCHAR2(8)                     not null,
   DJLSH                INTEGER                         not null,
   DJSJ                 VARCHAR2(6),
   YWBH                 VARCHAR2(16)                    not null,
   DJJG                 VARCHAR2(16)                    not null,
   DJGY                 VARCHAR2(16)                    not null,
   SHJG                 VARCHAR2(16),
   SHGY                 VARCHAR2(16),
   SHPCH                VARCHAR2(32),
   PKRQ                 VARCHAR2(8),
   PTPCH                VARCHAR2(8),
   LPWJLJ               VARCHAR2(254),   
   LPWJM                VARCHAR2(60),
   ZBS                  VARCHAR2(8),
   ZJE                  NUMBER(16,2),
   THREADNO             INTEGER,
   TASKMODE             VARCHAR2(1),
   PCZT                 VARCHAR2(1),
   SHZT                 VARCHAR2(1),
   NOTE                 VARCHAR2(128),
   BREAKDATA            BLOB,
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   EXTFLD3              VARCHAR2(40),
   constraint PK_BATCH_HIS_WBWJDJ primary key (DJRQ, DJLSH)
);

comment on column BATCH_HIS_WBWJDJ.THREADNO is
'（高级选项默认为1）';

comment on column BATCH_HIS_WBWJDJ.TASKMODE is
'1：立即，2：手动（默认为1）';

comment on column BATCH_HIS_WBWJDJ.PCZT is
'1：正在上传，2：就绪，3：正在处理，4：已返回，5：处理失败，X：撤销, C:冲正，Z:终止';

comment on column BATCH_HIS_WBWJDJ.SHZT is
'0：审核通过，1：未审核，2：审核失败';

--==============================================================--
-- Index: K_BAT_WBWJDJ_2                                        --
--==============================================================--
create index K_BAT_WBWJDJ_2 on BATCH_HIS_WBWJDJ (
   DJRQ ASC,
   SHPCH ASC
);

--@BATCH_FILETYPE.sql
--@BATCH_FLOWCFG.sql
--UPDATE BATCH_FLOWCFG SET STEPSN=FLOWSN,STEPNAME=STEPID WHERE 1=1;
--commit;
--@BATCH_RUNCTRL.sql
--@BATCH_PLRW.sql
--@BATCH_HIS_PLRW.sql
--@BATCH_PLRWBD.sql
--@BATCH_WBWJDJ.sql
--@BATCH_HIS_WBWJDJ.sql
