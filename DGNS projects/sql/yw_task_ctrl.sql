drop table yw_task_ctrl;
--==============================================================
-- Table:  yw_task_ctrl 
--==============================================================
create table  yw_task_ctrl 
(
    rwrq           CHAR(8)               not null,
    rwsj           CHAR(6)               not null,
    cpdm           VARCHAR(32)           not null,
    rwdm           VARCHAR(32)           not null,
    qtzd           VARCHAR(32)           not null,
    qzlsh          VARCHAR(8)            not null,
    rwzt           CHAR(1)               not null,
    ptxym          VARCHAR(16),
    ptxyxx         VARCHAR(32),
    by1            VARCHAR(16),
   constraint  pk_yw_task_ctrl  primary key ( rwrq,rwsj,cpdm,rwdm,qtzd )
);

comment on table yw_task_ctrl is
'任务控制表';

comment on column yw_task_ctrl.rwrq is
'任务日期';

comment on column yw_task_ctrl.rwsj is
'任务时间';

comment on column yw_task_ctrl.cpdm is
'产品代码';

comment on column yw_task_ctrl.rwdm is
'任务代码';

comment on column yw_task_ctrl.qtzd is
'其他字段,当利用同一流程并发时，用于区分不同业务的其他字段';

comment on column yw_task_ctrl.qzlsh is
'前置流水号';

comment on column yw_task_ctrl.rwzt is
'任务状态，0-成功，1-失败，9-处理中';

comment on column yw_task_ctrl.ptxym is
'平台响应码';

comment on column yw_task_ctrl.ptxyxx is
'平台响应信息';

comment on column yw_task_ctrl.by1 is
'备用1';
