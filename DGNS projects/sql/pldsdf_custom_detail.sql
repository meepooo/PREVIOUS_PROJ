drop table pldsdf_custom_detail;
--==============================================================
-- Table: pldsdf_custom_detail
--==============================================================
create table pldsdf_custom_detail		--批量核心回盘数据
(
 	pch				varchar(32) not null,
    wjxh            integer     not null,
    wjmc            varchar(150) not null,
    hth             varchar(20) not null,
    tyxybh          varchar(65),
    xybh            varchar(65),
    xydm            varchar(12),
    yhzh            varchar(32) not null,
    yhzhmc          varchar(150),
    zjhm            varchar(40),
    xyjlzt          char(1),
    lxdh            varchar(15),
    lxdz            varchar(150),
    qysxrq          char(8),
    qydqrq          char(8),
    qyrq            char(8),
    jyrq            char(8),
    qygy            varchar(16),
    jygy            varchar(16),
    qyjg            varchar(16),
    fhxxm           char(7),
    cwzwms          varchar(512),
    extfld1         varchar(80),
    extfld2         varchar(80),
    extfld3         varchar(80),
    extfld4         varchar(80),
    extfld5         varchar(80),
    extfld6         varchar(160),
    constraint PK_pldsdf_custom_detail primary key (pch,wjxh)
)IN AGENT_DATA INDEX IN AGENT_INDEX ;

comment on table pldsdf_custom_detail is
'批量客户签约明细表';

comment on column pldsdf_custom_detail.wjxh is '文件序号';

comment on column pldsdf_custom_detail.hth is '合同号';

comment on column pldsdf_custom_detail.tyxybh is '统一协议编号';

comment on column pldsdf_custom_detail.xybh is '协议编号';

comment on column pldsdf_custom_detail.xydm is '协议代码';

comment on column pldsdf_custom_detail.yhzh is '银行账号';

comment on column pldsdf_custom_detail.yhzhmc is '银行账号名称';

comment on column pldsdf_custom_detail.zjhm is '证件号码';

comment on column pldsdf_custom_detail.xyjlzt is '协议记录状态 0-正常 1-删除';

comment on column pldsdf_custom_detail.lxdh is '联系电话';

comment on column pldsdf_custom_detail.lxdz is '联系地址';

comment on column pldsdf_custom_detail.qysxrq is '签约生效日期';

comment on column pldsdf_custom_detail.qydqrq is '签约到期日期';

comment on column pldsdf_custom_detail.qyrq is '签约日期';

comment on column pldsdf_custom_detail.jyrq is '解约日期';

comment on column pldsdf_custom_detail.qygy is '签约柜员';

comment on column pldsdf_custom_detail.jygy is '解约柜员';

comment on column pldsdf_custom_detail.qyjg is '签约机构';

comment on column pldsdf_custom_detail.fhxxm is '返回信息码';

comment on column pldsdf_custom_detail.cwzwms is '错误中文描述';

comment on column pldsdf_custom_detail.EXTFLD1 is '扩展字段1';

comment on column pldsdf_custom_detail.EXTFLD2 is '扩展字段2';

comment on column pldsdf_custom_detail.EXTFLD3 is '扩展字段3';

comment on column pldsdf_custom_detail.EXTFLD4 is '扩展字段4';

comment on column pldsdf_custom_detail.EXTFLD5 is '扩展字段5';

comment on column pldsdf_custom_detail.EXTFLD6 is '扩展字段6';

