alter table app_dwcpxy
    add fwrx varchar(32)
    add jfbhxsmc varchar(100)
    add khh varchar(32)
    add nbhzhmc varchar(100)
    add nbhzh varchar(32)
    add sxfnbhzhmc varchar(100)
    add sxfnbhzh varchar(32)
    add scfs varchar(2)
    add shzt varchar(1)
    add shsj varchar(14)
    add shgy varchar(16)
    add shjg varchar(32);
comment on column app_dwcpxy.fwrx is'服务热线';
comment on column app_dwcpxy.jfbhxsmc is'缴费编号显示名称';
comment on column app_dwcpxy.khh is'客户号';
comment on column app_dwcpxy.nbhzhmc is'内部户账号名称';
comment on column app_dwcpxy.nbhzh is'内部户账号';
comment on column app_dwcpxy.sxfnbhzhmc is'手续费内部户账号名称';
comment on column app_dwcpxy.sxfnbhzh is'手续费内部户账号';
comment on column app_dwcpxy.scfs is'上传方式 01-缴费平台 02-自有系统 03-线下代理';
comment on column app_dwcpxy.shzt is'审核状态 9-未审核 1-审核通过 2-审核拒绝';
comment on column app_dwcpxy.shsj is'审核时间';
comment on column app_dwcpxy.shgy is'审核柜员';
comment on column app_dwcpxy.shjg is'审核机构';
reorg table app_dwcpxy;

alter table APP_CPXX add sxftkbz varchar(1);
comment on column APP_CPXX.sxftkbz is'手续费退款标志 0-退 1-不退';
reorg table APP_CPXX;

ALTER TABLE YWTY_BUSI_DZ ALTER COLUMN dzcpno SET DATA TYPE varchar(9);
reorg table YWTY_BUSI_DZ;

--==============================================================
-- DBMS name:      IBM DB2 UDB 9.0 Common Server
-- Created on:     2017-01-03 11:30:24
--==============================================================


drop table YWTY_ZFWG_DZ;

drop table agent_csys;

drop table agent_ddxx;

drop table agent_ggxx;

drop index agent_jfhz_index_2;

drop index agent_jfhz_index_1;

drop table agent_jfhz;

drop table agent_jfxm;

drop table agent_jfxq;

drop table agent_khjfbh;

drop index agent_qsls_Index_1;

drop table agent_qsls;

--==============================================================
-- Table: YWTY_ZFWG_DZ
--==============================================================
create table YWTY_ZFWG_DZ
(
   JYSX                 VARCHAR(4) NOT NULL,
   QSRQ                 VARCHAR(8) NOT NULL,
   TRAN_TIME            VARCHAR(14) NOT NULL,
   ORDER_NO             VARCHAR(32) NOT NULL,
   Merchant_SEQ         VARCHAR(32) NOT NULL,
   Merchant_Id          VARCHAR(19) NOT NULL,
   TRAN_AMT             DECIMAL(20,2) NOT NULL,
   SXF_AMT              DECIMAL(20,2) NOT NULL,
   QSJE_AMT             DECIMAL(20,2) NOT NULL,
   RESPCODE             VARCHAR(8) NOT NULL,
   REMARK1              VARCHAR(32) NOT NULL,
   REMARK2              VARCHAR(32) ,
   DZ_FLAG              VARCHAR(1) ,
   constraint P_YWTY_ZFWG_DZ primary key (QSRQ, Merchant_SEQ)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table YWTY_ZFWG_DZ is
'支付网关对账数据表';

comment on column YWTY_ZFWG_DZ.JYSX is
'交易缩写';

comment on column YWTY_ZFWG_DZ.QSRQ is
'清算日期';

comment on column YWTY_ZFWG_DZ.TRAN_TIME is
'交易发生时间';

comment on column YWTY_ZFWG_DZ.ORDER_NO is
'订单号';

comment on column YWTY_ZFWG_DZ."Merchant_SEQ" is
'第三方统一支付平台流水号';

comment on column YWTY_ZFWG_DZ."Merchant_Id" is
'商户号';

comment on column YWTY_ZFWG_DZ.TRAN_AMT is
'交易金额';

comment on column YWTY_ZFWG_DZ.SXF_AMT is
'手续费';

comment on column YWTY_ZFWG_DZ.QSJE_AMT is
'净清算金额';

comment on column YWTY_ZFWG_DZ.RESPCODE is
'响应吗';

comment on column YWTY_ZFWG_DZ.REMARK1 is
'商户保留1';

comment on column YWTY_ZFWG_DZ.REMARK2 is
'商户保留2';

comment on column YWTY_ZFWG_DZ.DZ_FLAG is
'对账标识:1-参与对账 0-不参与对账';

--==============================================================
-- Table: agent_csys
--==============================================================
create table agent_csys
(
   lb                   VARCHAR(32)            not null,
   srcs                 VARCHAR(128)           not null,
   sccs                 VARCHAR(128),
   ms                   VARCHAR(256),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_CSYS primary key (lb, srcs)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_csys is
'参数映射表';

comment on column agent_csys.lb is
'类别';

comment on column agent_csys.srcs is
'输入参数';

comment on column agent_csys.sccs is
'输出参数';

comment on column agent_csys.ms is
'描述';

comment on column agent_csys.kzzd1 is
'扩展字段1';

comment on column agent_csys.kzzd2 is
'扩展字段2';

comment on column agent_csys.kzzd3 is
'扩展字段3';

comment on column agent_csys.kzzd4 is
'扩展字段4';

comment on column agent_csys.kzzd5 is
'扩展字段5';

--==============================================================
-- Table: agent_ddxx
--==============================================================
create table agent_ddxx
(
   ddh                  VARCHAR(32)            not null,
   jfbs                 INTEGER,
   jfje                 DECIMAL(17,2),
   yjsxf                DECIMAL(17,2),
   cgbs                 INTEGER,
   cgje                 DECIMAL(17,2),
   sssxf                DECIMAL(17,2),
   zt                   VARCHAR(1),
   fkhhh                VARCHAR(32),
   fkrmc                VARCHAR(200),
   fkrzh                VARCHAR(32),
   skhhh                VARCHAR(32),
   skrmc                VARCHAR(200),
   skrzh                VARCHAR(32),
   pch                  VARCHAR(32)            not null,
   xh                   INTEGER                not null,
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_DDXX primary key (ddh)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_ddxx is
'订单信息表';

comment on column agent_ddxx.ddh is
'订单号';

comment on column agent_ddxx.jfbs is
'缴费笔数';

comment on column agent_ddxx.jfje is
'缴费金额';

comment on column agent_ddxx.yjsxf is
'应缴手续费';

comment on column agent_ddxx.cgbs is
'成功笔数';

comment on column agent_ddxx.cgje is
'成功金额';

comment on column agent_ddxx.sssxf is
'实收手续费';

comment on column agent_ddxx.zt is
'状态 1-预缴 2-缴中 3-已缴';

comment on column agent_ddxx.fkhhh is
'付款行行号';

comment on column agent_ddxx.fkrmc is
'付款人名称';

comment on column agent_ddxx.fkrzh is
'付款人账号';

comment on column agent_ddxx.skhhh is
'收款行行号';

comment on column agent_ddxx.skrmc is
'收款人名称';

comment on column agent_ddxx.skrzh is
'收款人账号';

comment on column agent_ddxx.pch is
'批次号';

comment on column agent_ddxx.xh is
'平台流水';

comment on column agent_ddxx.whsj is
'维护时间 YYYYMMDDHHMMSS';

comment on column agent_ddxx.why is
'维护员';

comment on column agent_ddxx.whjg is
'维护机构';

comment on column agent_ddxx.kzzd1 is
'扩展字段1';

comment on column agent_ddxx.kzzd2 is
'扩展字段2';

comment on column agent_ddxx.kzzd3 is
'扩展字段3';

comment on column agent_ddxx.kzzd4 is
'扩展字段4';

comment on column agent_ddxx.kzzd5 is
'扩展字段5';

--==============================================================
-- Table: agent_ggxx
--==============================================================
create table agent_ggxx
(
   bt                   VARCHAR(256)           not null,
   ggxx                 VARCHAR(2048)          not null,
   yxbz                 VARCHAR(1)             not null,
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_GGXX primary key (bt)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_ggxx is
'公告信息表';

comment on column agent_ggxx.bt is
'标题';

comment on column agent_ggxx.ggxx is
'公告信息';

comment on column agent_ggxx.yxbz is
'有效标志 1-有效 2-无效';

comment on column agent_ggxx.whsj is
'维护时间 YYYYMMDDHHMMSS';

comment on column agent_ggxx.why is
'维护员';

comment on column agent_ggxx.whjg is
'维护机构';

comment on column agent_ggxx.kzzd1 is
'扩展字段1';

comment on column agent_ggxx.kzzd2 is
'扩展字段2';

comment on column agent_ggxx.kzzd3 is
'扩展字段3';

comment on column agent_ggxx.kzzd4 is
'扩展字段4';

comment on column agent_ggxx.kzzd5 is
'扩展字段5';

--==============================================================
-- Table: agent_jfhz
--==============================================================
create table agent_jfhz
(
   pch                  VARCHAR(32)            not null,
   wjm                  VARCHAR(256)           not null,
   ptrq                 VARCHAR(8)             not null,
   ptls                 VARCHAR(16)            not null,
   ptsj                 VARCHAR(6),
   zbs                  INTEGER,
   zje                  DECIMAL(17,2),
   zznj                 DECIMAL(17,2),
   drzt                 VARCHAR(1)             not null,
   sbyy                 VARCHAR(200),
   jfnd                 VARCHAR(4),
   jfyf                 VARCHAR(2),
   shlxdm               VARCHAR(16),
   jfxmdm               VARCHAR(32),
   shdm                 VARCHAR(16),
   qsyxrq               VARCHAR(8),
   zzyxrq               VARCHAR(8),
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   khh                  VARCHAR(16),
   scfs                 VARCHAR(2),
   pljfzbs              INTEGER,
   pljfzje              NUMERIC(17,2),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_JFHZ primary key (pch)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_jfhz is
'缴费汇总表';

comment on column agent_jfhz.pch is
'批次号';

comment on column agent_jfhz.wjm is
'文件名';

comment on column agent_jfhz.ptrq is
'平台日期 YYYYMMDD';

comment on column agent_jfhz.ptls is
'平台流水';

comment on column agent_jfhz.ptsj is
'平台时间 HHMMSS';

comment on column agent_jfhz.zbs is
'总笔数';

comment on column agent_jfhz.zje is
'总金额';

comment on column agent_jfhz.zznj is
'总滞纳金';

comment on column agent_jfhz.drzt is
'导入状态 9-导入中 1-导入成功 2-导入失败';

comment on column agent_jfhz.sbyy is
'失败原因';

comment on column agent_jfhz.jfnd is
'缴费年度 YYYY';

comment on column agent_jfhz.jfyf is
'缴费月份 MM';

comment on column agent_jfhz.shlxdm is
'商户类型代码';

comment on column agent_jfhz.jfxmdm is
'缴费项目代码';

comment on column agent_jfhz.shdm is
'商户代码';

comment on column agent_jfhz.qsyxrq is
'起始有效日期 YYYYMMDD';

comment on column agent_jfhz.zzyxrq is
'终止有效日期 YYYYMMDD';

comment on column agent_jfhz.whsj is
'维护时间 YYYYMMDDHHMMSS';

comment on column agent_jfhz.why is
'维护员';

comment on column agent_jfhz.whjg is
'维护机构';

comment on column agent_jfhz.khh is
'客户号';

comment on column agent_jfhz.scfs is
'上传方式 01-缴费平台 02-自有系统 03-线下代理';

comment on column agent_jfhz.pljfzbs is
'批量缴费总笔数';

comment on column agent_jfhz.pljfzje is
'批量缴费总金额';

comment on column agent_jfhz.kzzd1 is
'扩展字段1';

comment on column agent_jfhz.kzzd2 is
'扩展字段2';

comment on column agent_jfhz.kzzd3 is
'扩展字段3';

comment on column agent_jfhz.kzzd4 is
'扩展字段2';

comment on column agent_jfhz.kzzd5 is
'扩展字段2';

--==============================================================
-- Index: agent_jfhz_index_1
--==============================================================
create unique index agent_jfhz_index_1 on agent_jfhz (
   wjm                  ASC
);

--==============================================================
-- Index: agent_jfhz_index_2
--==============================================================
create unique index agent_jfhz_index_2 on agent_jfhz (
   ptrq                 ASC,
   ptls                 ASC
);

--==============================================================
-- Table: agent_jfxm
--==============================================================
create table agent_jfxm
(
   shlxdm               VARCHAR(16)            not null,
   jfxmdm               VARCHAR(32)            not null,
   jfxmmc               VARCHAR(100)           not null,
   shbz                 VARCHAR(1)             not null,
   yxbz                 VARCHAR(1)             not null,
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   shsj                 VARCHAR(14),
   shy                  VARCHAR(16),
   shjg                 VARCHAR(16),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_JFXM primary key (shlxdm, jfxmdm)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_jfxm is
'缴费项目表';

comment on column agent_jfxm.shlxdm is
'商户类型代码';

comment on column agent_jfxm.jfxmdm is
'缴费项目代码';

comment on column agent_jfxm.jfxmmc is
'缴费项目名称';

comment on column agent_jfxm.shbz is
'审核标志 9-未审核 1-审核通过 2-审核拒绝';

comment on column agent_jfxm.yxbz is
'有效标志 1-有效 2-无效';

comment on column agent_jfxm.whsj is
'维护时间 YYYYMMDDHHMMSS';

comment on column agent_jfxm.why is
'维护员';

comment on column agent_jfxm.whjg is
'维护机构';

comment on column agent_jfxm.shsj is
'审核时间';

comment on column agent_jfxm.shy is
'审核员';

comment on column agent_jfxm.shjg is
'审核机构';

comment on column agent_jfxm.kzzd1 is
'扩展字段1';

comment on column agent_jfxm.kzzd2 is
'扩展字段2';

comment on column agent_jfxm.kzzd3 is
'扩展字段3';

comment on column agent_jfxm.kzzd4 is
'扩展字段4';

comment on column agent_jfxm.kzzd5 is
'扩展字段5';

--==============================================================
-- Table: agent_jfxq
--==============================================================
create table agent_jfxq
(
   pch                  VARCHAR(32)            not null,
   xh                   INTEGER                not null,
   xm                   VARCHAR(100),
   jfnd                 VARCHAR(4),
   jfyf                 VARCHAR(2),
   shlxdm               VARCHAR(16),
   jfxmdm               VARCHAR(32),
   shdm                 VARCHAR(16),
   qsyxrq               VARCHAR(8),
   zzyxrq               VARCHAR(8),
   jfbh                 VARCHAR(32),
   qfje                 DECIMAL(17,2),
   znj                  DECIMAL(17,2),
   tkje                 DECIMAL(17,2),
   khzh                 VARCHAR(32),
   kxrq                 VARCHAR(8),
   sjh                  VARCHAR(16),
   zjhm                 VARCHAR(32),
   glfy1                DECIMAL(17,2),
   glfy2                DECIMAL(17,2),
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
   tkyy                 VARCHAR(100),
   qszt                 VARCHAR(1)             not null,
   qsrq                 VARCHAR(8),
   zflx                 VARCHAR(1),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_JFXQ primary key (pch, xh)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_jfxq is
'缴费详情表';

comment on column agent_jfxq.pch is
'批次号';

comment on column agent_jfxq.xh is
'序号';

comment on column agent_jfxq.xm is
'姓名';

comment on column agent_jfxq.jfnd is
'缴费年度 YYYY';

comment on column agent_jfxq.jfyf is
'缴费月份 MM';

comment on column agent_jfxq.shlxdm is
'商户类型代码';

comment on column agent_jfxq.jfxmdm is
'缴费项目代码';

comment on column agent_jfxq.shdm is
'商户代码';

comment on column agent_jfxq.qsyxrq is
'起始有效日期 YYYYMMDD';

comment on column agent_jfxq.zzyxrq is
'终止有效日期 YYYYMMDD';

comment on column agent_jfxq.jfbh is
'缴费编号';

comment on column agent_jfxq.qfje is
'欠费金额';

comment on column agent_jfxq.znj is
'手续费';

comment on column agent_jfxq.tkje is
'退款金额';

comment on column agent_jfxq.khzh is
'客户账号';

comment on column agent_jfxq.kxrq is
'款项日期';

comment on column agent_jfxq.sjh is
'手机号';

comment on column agent_jfxq.zjhm is
'证件号码';

comment on column agent_jfxq.glfy1 is
'关联费用1';

comment on column agent_jfxq.glfy2 is
'关联费用2';

comment on column agent_jfxq.bz1 is
'备注1';

comment on column agent_jfxq.bz2 is
'备注2';

comment on column agent_jfxq.khh is
'客户号';

comment on column agent_jfxq.whsj is
'维护时间 YYYYMMDDHHMMSS';

comment on column agent_jfxq.why is
'维护员';

comment on column agent_jfxq.whjg is
'维护机构';

comment on column agent_jfxq.yxbz is
'有效标志 1-有效 2-无效';

comment on column agent_jfxq.zt is
'状态 90-初始 10-预缴 20-缴中 21-已缴 30-退款中 31-已退款';

comment on column agent_jfxq.jfrq is
'缴费日期 YYYYMMDD';

comment on column agent_jfxq.jfls is
'缴费流水';

comment on column agent_jfxq.tkrq is
'退款日期 YYYYMMDD';

comment on column agent_jfxq.tkls is
'退款流水';

comment on column agent_jfxq.tkyy is
'退款原因';

comment on column agent_jfxq.qszt is
'清算状态 1-未清算 2-已清算';

comment on column agent_jfxq.qsrq is
'清算日期 YYYYMMDD';

comment on column agent_jfxq.zflx is
'支付类型 1-线上支付 2-线下支付 3-批量支付';

comment on column agent_jfxq.kzzd1 is
'扩展字段1';

comment on column agent_jfxq.kzzd2 is
'扩展字段2';

comment on column agent_jfxq.kzzd3 is
'扩展字段3';

comment on column agent_jfxq.kzzd4 is
'扩展字段4';

comment on column agent_jfxq.kzzd5 is
'扩展字段5';

--==============================================================
-- Table: agent_khjfbh
--==============================================================
create table agent_khjfbh
(
   khh                  VARCHAR(16)            not null,
   shlxdm               VARCHAR(16)            not null,
   shdm                 VARCHAR(16)            not null,
   jfbh                 VARCHAR(32)            not null,
   yhm                  VARCHAR(200),
   bz                   VARCHAR(256),
   yxbz                 VARCHAR(1),
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_KHJFBH primary key (khh, shlxdm, shdm, jfbh)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_khjfbh is
'客户缴费编号表';

comment on column agent_khjfbh.khh is
'客户号';

comment on column agent_khjfbh.shlxdm is
'商户类型代码';

comment on column agent_khjfbh.shdm is
'商户代码';

comment on column agent_khjfbh.jfbh is
'缴费编号';

comment on column agent_khjfbh.yhm is
'用户名';

comment on column agent_khjfbh.bz is
'备注';

comment on column agent_khjfbh.yxbz is
'有效标志 1-有效 2-无效';

comment on column agent_khjfbh.whsj is
'维护时间 YYYYMMDDHHMMSS';

comment on column agent_khjfbh.why is
'维护员';

comment on column agent_khjfbh.whjg is
'维护机构';

comment on column agent_khjfbh.kzzd1 is
'扩展字段1';

comment on column agent_khjfbh.kzzd2 is
'扩展字段2';

comment on column agent_khjfbh.kzzd3 is
'扩展字段3';

comment on column agent_khjfbh.kzzd4 is
'扩展字段4';

comment on column agent_khjfbh.kzzd5 is
'扩展字段5';

--==============================================================
-- Table: agent_qsls
--==============================================================
create table agent_qsls
(
   qsrq                 VARCHAR(8)             not null,
   qssj                 VARCHAR(6),
   qsls                 VARCHAR(16)            not null,
   qsbs                 INTEGER,
   qsje                 DECIMAL(17,2),
   qslx                 VARCHAR(1)             not null,
   qsfx                 VARCHAR(1)             not null,
   qszt                 VARCHAR(1),
   sbyy                 VARCHAR(200),
   shlxdm               VARCHAR(16),
   shdm                 VARCHAR(16),
   fkhhh                VARCHAR(32),
   fkrmc                VARCHAR(200),
   fkrzh                VARCHAR(32),
   skhhh                VARCHAR(32),
   skrmc                VARCHAR(200),
   skrzh                VARCHAR(32),
   ywbh                 VARCHAR(16)            not null,
   dzrq                 VARCHAR(8)             not null,
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_QSLS primary key (qsrq, qsls)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_qsls is
'清算流水表';

comment on column agent_qsls.qsrq is
'清算日期 YYYYMMDD';

comment on column agent_qsls.qssj is
'清算时间 HHMMSS';

comment on column agent_qsls.qsls is
'清算流水';

comment on column agent_qsls.qsbs is
'清算笔数';

comment on column agent_qsls.qsje is
'清算金额';

comment on column agent_qsls.qslx is
'清算类型 1-资金清算 2-手续费清算';

comment on column agent_qsls.qsfx is
'清算方向 1-银行内清算(订单缴费) 2-银行内清算(直接缴费)  3-银行与客户清算 ';

comment on column agent_qsls.qszt is
'清算状态 9-初始 1-成功 2-失败 3-超时';

comment on column agent_qsls.sbyy is
'失败原因';

comment on column agent_qsls.shlxdm is
'商户类型代码';

comment on column agent_qsls.shdm is
'商户代码';

comment on column agent_qsls.fkhhh is
'付款行行号';

comment on column agent_qsls.fkrmc is
'付款人名称';

comment on column agent_qsls.fkrzh is
'付款人账号';

comment on column agent_qsls.skhhh is
'收款行行号';

comment on column agent_qsls.skrmc is
'收款人名称';

comment on column agent_qsls.skrzh is
'收款人账号';

comment on column agent_qsls.ywbh is
'业务编号';

comment on column agent_qsls.dzrq is
'对账日期 YYYYMMDD';

comment on column agent_qsls.kzzd1 is
'扩展字段1';

comment on column agent_qsls.kzzd2 is
'扩展字段2';

comment on column agent_qsls.kzzd3 is
'扩展字段3';

comment on column agent_qsls.kzzd4 is
'扩展字段4';

comment on column agent_qsls.kzzd5 is
'扩展字段5';

--==============================================================
-- Index: agent_qsls_Index_1
--==============================================================
create index agent_qsls_Index_1 on agent_qsls (
   ywbh                 ASC,
   dzrq                 ASC
);

