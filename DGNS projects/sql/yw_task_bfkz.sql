drop table yw_task_bfkz;
--==============================================================
-- Table:  yw_task_bfkz 
--==============================================================
create table  yw_task_bfkz 
(
    cpdm           VARCHAR(32)           not null,
    rwdm           VARCHAR(32)           not null,
    qtzd           VARCHAR(32)           not null,
    bfbz           CHAR(1),
    bfjg           VARCHAR(5),
    by1            VARCHAR(16),
   constraint  pk_yw_task_bfkz  primary key ( cpdm,rwdm,qtzd )
);

comment on table yw_task_bfkz is
'任务并发控制表';

comment on column yw_task_bfkz.cpdm is
'产品代码';

comment on column yw_task_bfkz.rwdm is
'任务代码';

comment on column yw_task_bfkz.qtzd is
'其他字段,当利用同一流程并发时，用于区分不同业务的其他字段';

comment on column yw_task_bfkz.bfbz is
'并发标志，0-不允许并发，1-允许并发';

comment on column yw_task_bfkz.bfjg is
'并发时间间隔－备用字段';

comment on column yw_task_bfkz.by1 is
'备用1';
