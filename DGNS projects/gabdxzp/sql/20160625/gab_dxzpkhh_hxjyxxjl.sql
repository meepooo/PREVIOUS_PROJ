drop table gab_dxzpkhh_hxjyxxjl;
create table gab_dxzpkhh_hxjyxxjl  (
   khhywsqbh          varchar(40)                     not null,
   ywsqbh             varchar(40)                     not null,
   jybm               char(6)                         not null,
   jylx               char(1)                         not null,
   fsjgbh             varchar(12),
   tjhxwjm            varchar(200),
   hxfhjgwjm1         varchar(200),
   oldhxfhjgwjm1         varchar(200),
   hxfhjgwjm2         varchar(200),
   oldhxfhjgwjm2         varchar(200),
   hxfhjgwjm3         varchar(200),
   oldhxfhjgwjm3         varchar(200),
   by1                varchar(30),
   by2                varchar(254),
   by3                varchar(254),
   constraint pkgab_dxzpkhh_hxjyxxjl primary key (khhywsqbh, jybm,jylx)
);
/*==============================================================*/
/* Table: gab_dxzpkhh_hxjyxxjl                                  */
/*==============================================================*/
comment on table gab_dxzpkhh_hxjyxxjl is
'记录电信诈骗核心交易信息';

comment on column gab_dxzpkhh_hxjyxxjl.ywsqbh is
'主键，请求单流水号，用于标识查控请求单';

comment on column gab_dxzpkhh_hxjyxxjl.jybm is
'交易编码';

comment on column gab_dxzpkhh_hxjyxxjl.jylx is
'交易类型 0-普通交易,1-动态查询第N次交易,N大于1';

comment on column gab_dxzpkhh_hxjyxxjl.fsjgbh is
'发送机构编号';

comment on column gab_dxzpkhh_hxjyxxjl.tjhxwjm is
'提交核心文件名';

comment on column gab_dxzpkhh_hxjyxxjl.hxfhjgwjm1 is
'核心返回结果文件名1';

comment on column gab_dxzpkhh_hxjyxxjl.oldhxfhjgwjm1 is
'老核心返回结果文件名1';

comment on column gab_dxzpkhh_hxjyxxjl.hxfhjgwjm2 is
'核心返回结果文件名2';

comment on column gab_dxzpkhh_hxjyxxjl.oldhxfhjgwjm2 is
'老核心返回结果文件名2';

comment on column gab_dxzpkhh_hxjyxxjl.hxfhjgwjm3 is
'核心返回结果文件名3';

comment on column gab_dxzpkhh_hxjyxxjl.oldhxfhjgwjm3 is
'老核心返回结果文件名3';

comment on column gab_dxzpkhh_hxjyxxjl.by1 is
'备用1';

comment on column gab_dxzpkhh_hxjyxxjl.by2 is
'备用2';

comment on column gab_dxzpkhh_hxjyxxjl.by3 is
'备用3';
