drop table agent_fsxq;

create table agent_fsxq
(
PCH        varchar2(32),
XH         INT,
ZXRTDBH    STRING(50),
ZXJGMC     STRING(300),
TZSHM      STRING(50),
KHMC       STRING(150),
YSJE       DOUBLE(20,2),
ZZNJ       DOUBLE(20,2),
FYNFS      INT,
ZH         STRING(50),
SKRMC      STRING(150),
BZ         STRING(300),
FYNF       STRING(4),
FY         DOUBLE(20,2),
BJ         DOUBLE(20,2),
ZNJ        DOUBLE(20,2),
ZNJTS      INT,
SJH        varchar2(16),
JFRQ       varchar2(8),
REMARK1    Varchar(200),
REMARK2    Varchar(200),
REMARK3    Varchar(200),
REMARK4    Varchar(200),
REMARK5    Varchar(200)
);

comment on table  agent_faxq  is '非税详情表' ;
comment on column agent_fsxq.PCH is '批次号';
comment on column agent_fsxq.XH is '序号';
comment on column agent_fsxq.ZXRTDBH is '执行人团队编号';
comment on column agent_fsxq.ZXJGMC is '执行机构名称';
comment on column agent_fsxq.TZSHM is '通知书号码';
comment on column agent_fsxq.KHMC is '客户名称';
comment on column agent_fsxq.YSJE is '应收金额';
comment on column agent_fsxq.ZZNJ is '总滞纳金';
comment on column agent_fsxq.FYNFS is '费用年份数';
comment on column agent_fsxq.ZH is '账号';
comment on column agent_fsxq.SKRMC is '收款人名称';
comment on column agent_fsxq.BZ is '备注';
comment on column agent_fsxq.FYNF is '费用年份';
comment on column agent_fsxq.FY is '费用';
comment on column agent_fsxq.BJ is '本金';
comment on column agent_fsxq.ZNJ is '滞纳金';
comment on column agent_fsxq.ZNJTS is '滞纳金天数';
comment on column agent_fsxq.SJH is '手机号';
comment on column agent_fsxq.JFRQ is '缴费日期';
comment on column agent_fsxq.REMARK1 is '备用字段1';
comment on column agent_fsxq.REMARK2 is '备用字段2';
comment on column agent_fsxq.REMARK3 is '备用字段3';
comment on column agent_fsxq.REMARK4 is '备用字段4';
comment on column agent_fsxq.REMARK5 is '备用字段5';
