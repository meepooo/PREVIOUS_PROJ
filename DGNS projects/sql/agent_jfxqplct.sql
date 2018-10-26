drop table agent_jfxqplct;

--==============================================================
-- Table: agent_jfxqplct
--==============================================================
create table agent_jfxqplct
(
   pch                  VARCHAR(32)            not null,
   xh                   INTEGER                not null,
   xm                   VARCHAR(100),
   jfnd                 VARCHAR(4),
   jfyf                 VARCHAR(2),
   shlxdm               VARCHAR(16),
   shlxmc               VARCHAR(100),
   jfxmdm               VARCHAR(32),
   jfxmmc               VARCHAR(100),
   shdm                 VARCHAR(16),
   shmc                 VARCHAR(200),
   qsyxrq               VARCHAR(8),
   zzyxrq               VARCHAR(8),
   jfbh                 VARCHAR(32),
   qfje                 DECIMAL(17,2),
   znj                  DECIMAL(17,2),
   tkje                 DECIMAL(17,2),
   bz1                  VARCHAR(512),
   bz2                  VARCHAR(1024),
   khh                  VARCHAR(16),
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   yxbz                 VARCHAR(1)             not null,
   zt                   VARCHAR(2)             not null,
   jfrq                 VARCHAR(8),
   jfls                 VARCHAR(16),
   tkrq                 VARCHAR(8),
   tkls                 VARCHAR(16),
   qszt                 VARCHAR(1)             not null,
   qsrq                 VARCHAR(8),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_jfxqplct primary key (pch, xh)
);

comment on table agent_jfxqplct is
'缴费详情批量重提表';

comment on column agent_jfxqplct.pch is
'批次号';

comment on column agent_jfxqplct.xh is
'序号';

comment on column agent_jfxqplct.xm is
'姓名';

comment on column agent_jfxqplct.jfnd is
'缴费年度 YYYY';

comment on column agent_jfxqplct.jfyf is
'缴费月份 MM';

comment on column agent_jfxqplct.shlxdm is
'商户类型代码';

comment on column agent_jfxqplct.shlxmc is
'商户类型名称';

comment on column agent_jfxqplct.jfxmdm is
'缴费项目代码';

comment on column agent_jfxqplct.jfxmmc is
'缴费项目名称';

comment on column agent_jfxqplct.shdm is
'商户代码';

comment on column agent_jfxqplct.shmc is
'商户名称';

comment on column agent_jfxqplct.qsyxrq is
'起始有效日期 YYYYMMDD';

comment on column agent_jfxqplct.zzyxrq is
'终止有效日期 YYYYMMDD';

comment on column agent_jfxqplct.jfbh is
'缴费编号';

comment on column agent_jfxqplct.qfje is
'欠费金额';

comment on column agent_jfxqplct.znj is
'手续费';

comment on column agent_jfxqplct.tkje is
'退款金额';

comment on column agent_jfxqplct.bz1 is
'备注1';

comment on column agent_jfxqplct.bz2 is
'备注2';

comment on column agent_jfxqplct.khh is
'客户号';

comment on column agent_jfxqplct.whsj is
'维护时间 YYYYMMDDHHMMSS';

comment on column agent_jfxqplct.why is
'维护员';

comment on column agent_jfxqplct.whjg is
'维护机构';

comment on column agent_jfxqplct.yxbz is
'有效标志 1-有效 2-无效';

comment on column agent_jfxqplct.zt is
'状态 90-初始 10-预缴 20-缴中 21-已缴 30-退款中 31-已退款';

comment on column agent_jfxqplct.jfrq is
'缴费日期 YYYYMMDD';

comment on column agent_jfxqplct.jfls is
'缴费流水';

comment on column agent_jfxqplct.tkrq is
'退款日期 YYYYMMDD';

comment on column agent_jfxqplct.tkls is
'退款流水';

comment on column agent_jfxqplct.qszt is
'清算状态 1-未清算 2-已清算';

comment on column agent_jfxqplct.qsrq is
'清算日期 YYYYMMDD';

comment on column agent_jfxqplct.kzzd1 is
'扩展字段1';

comment on column agent_jfxqplct.kzzd2 is
'扩展字段2';

comment on column agent_jfxqplct.kzzd3 is
'扩展字段3';

comment on column agent_jfxqplct.kzzd4 is
'扩展字段4';

comment on column agent_jfxqplct.kzzd5 is
'扩展字段5';
