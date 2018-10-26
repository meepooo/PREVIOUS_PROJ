drop table agent_batch_clear;
--==============================================================
-- Table: AGENT_BATCH_CLEAR
--==============================================================
create table AGENT_BATCH_CLEAR
(
   qsrq                 CHAR(8)             not null,
   qssj                 CHAR(6),
   qsls                 VARCHAR(16)         not null,
   qsbs                 INTEGER,
   qsje                 DECIMAL(16,2),
   qslx                 CHAR(1)             not null,
   qsfx                 CHAR(1)             not null,
   qszt                 CHAR(1),
   sbyy                 VARCHAR(200),
   cpdm                 VARCHAR(16),
   cpmc                 VARCHAR(100),
   dwbh                 VARCHAR(16),
   dwmc                 VARCHAR(100),
   pkrq                 CHAR(8)             not null,
   ptpch                CHAR(8)             not null,
   batch_no             VARCHAR(32)         not null,
   file_name            VARCHAR(128),
   tot_succ_cnt         INTEGER,
   tot_succ_amt         DECIMAL(16,2),
   fkhhh                VARCHAR(32),
   fkrmc                VARCHAR(200),
   fkrzh                VARCHAR(32),
   skhhh                VARCHAR(32),
   skrmc                VARCHAR(200),
   skrzh                VARCHAR(32),
   ywbh                 VARCHAR(16)         not null,
   dzrq                 CHAR(8)             not null,
   kzzd1                VARCHAR(80),
   kzzd2                VARCHAR(80),
   kzzd3                VARCHAR(80),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_BATCH_CLEAR primary key (qsrq, qsls)
);

CREATE INDEX AGENT_BATCH_CLEAR_IDX1 ON AGENT_BATCH_CLEAR(ywbh,dzrq,batch_no);
CREATE INDEX AGENT_BATCH_CLEAR_IDX2 ON AGENT_BATCH_CLEAR(dzrq,qslx,qsfx);

comment on table AGENT_BATCH_CLEAR is
'批量代收代付清算流水表';

comment on column agent_batch_clear.qsrq is
'清算日期 YYYYMMDD';    
   
comment on column agent_batch_clear.qssj is
'清算时间 HHMMSS';      
   
comment on column agent_batch_clear.qsls is
'清算流水';             
   
comment on column agent_batch_clear.qsbs is
'清算笔数';             
   
comment on column agent_batch_clear.qsje is
'清算金额';

comment on column agent_batch_clear.qslx is
'清算类型 1-资金清算 2-手续费清算 3-批量代付退回';

comment on column agent_batch_clear.qsfx is
'清算方向 1-业务金额 2-费用1 3-费用2 4-费用3 5-费用4 6-费用5';

comment on column agent_batch_clear.qszt is
'清算状态 9-初始 1-成功 2-失败 3-超时';

comment on column agent_batch_clear.sbyy is
'失败原因';

comment on column agent_batch_clear.cpdm is
'产品代码';

comment on column agent_batch_clear.cpmc is
'产品名称';

comment on column agent_batch_clear.dwbh is
'单位编号';

comment on column agent_batch_clear.dwmc is
'单位名称';

comment on column agent_batch_clear.pkrq is
'批扣日期';

comment on column agent_batch_clear.ptpch is
'平台批次号';

comment on column agent_batch_clear.batch_no is
'商户批次号';

comment on column agent_batch_clear.file_name is
'来盘文件名';

comment on column agent_batch_clear.tot_succ_cnt is
'成功总笔数';

comment on column agent_batch_clear.tot_succ_amt is
'成功总金额';

comment on column agent_batch_clear.fkhhh is
'付款行行号';

comment on column agent_batch_clear.fkrmc is
'付款人名称';

comment on column agent_batch_clear.fkrzh is
'付款人账号';

comment on column agent_batch_clear.skhhh is
'收款行行号';

comment on column agent_batch_clear.skrmc is
'收款人名称';

comment on column agent_batch_clear.skrzh is
'收款人账号';

comment on column agent_batch_clear.ywbh is
'业务编号';

comment on column agent_batch_clear.dzrq is
'对账日期 YYYYMMDD';

comment on column agent_batch_clear.kzzd1 is
'扩展字段1';

comment on column agent_batch_clear.kzzd2 is
'扩展字段2';

comment on column agent_batch_clear.kzzd3 is
'扩展字段3';

comment on column agent_batch_clear.kzzd4 is
'扩展字段4';

comment on column agent_batch_clear.kzzd5 is
'扩展字段5';
