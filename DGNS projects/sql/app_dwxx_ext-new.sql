drop table app_dwxx_ext;
--==============================================================
-- Table: APP_DWXX_EXT
--==============================================================
create table APP_DWXX_EXT
(
   DWBH                 CHAR(16)            not null,
   SXFBZ                CHAR(1),
   SXFGSBZ              CHAR(1),
   SXFKHFS              CHAR(1),
   SXFZHLX              CHAR(1),
   SXFFKZH              CHAR(32),
   SXFFKZHMC            VARCHAR(100),
   SXFJSFS              CHAR(1),
   SXFJSCS              CHAR(10),
   SXFJEXX              NUMERIC(7,2),
   SXFJESX              NUMERIC(7,2),
   KHQYFS               CHAR(1),
   KKFS                 CHAR(1),
   TZBZ                 CHAR(1),
   TZED                 NUMERIC(15,2),
   TZDFZH               CHAR(32),
   YJBZ                 CHAR(1),
   YEYBBL               NUMERIC(7,2),
   JCHMBZ               CHAR(1),
   YQBZ                 CHAR(1),
   YQMY                 VARCHAR(128),
   FYYWLX1              VARCHAR(3),
   FYRZZH1              VARCHAR(32),
   FYZHLX1              VARCHAR(1),
   FYYWLX2              VARCHAR(3),
   FYRZZH2              VARCHAR(32),
   FYZHLX2              VARCHAR(1),
   FYYWLX3              VARCHAR(3),
   FYRZZH3              VARCHAR(32),
   FYZHLX3              VARCHAR(1),
   FYYWLX4              VARCHAR(3),
   FYRZZH4              VARCHAR(32),
   FYZHLX4              VARCHAR(1),
   FYYWLX5              VARCHAR(3),
   FYRZZH5              VARCHAR(32),
   FYZHLX5              VARCHAR(1),
   EXTFLD1              VARCHAR(80),
   EXTFLD2              VARCHAR(80),
   EXTFLD3              VARCHAR(80),
   EXTFLD4              VARCHAR(80),
   EXTFLD5              VARCHAR(80),
   EXTFLD6              VARCHAR(160),
   QYLX                 CHAR(1),
   DFFS                 CHAR(1),
   QSBZ                 CHAR(1),
   BYFLAG1              CHAR(2),
   BYFLAG2              CHAR(3),
   BYFLAG3              CHAR(4),
   BYZD1                CHAR(10),
   BYZD2                CHAR(20),
   BYZD3                CHAR(30),
   BYZD4                CHAR(50),
   BYZD5                CHAR(80),
   BYZD6                CHAR(100),
   constraint P_K_APP_DWXX_EXT_1 primary key (DWBH)
);

comment on table APP_DWXX_EXT is
'单位信息扩展表';

comment on column APP_DWXX_EXT.DWBH is
'单位编号';

comment on column APP_DWXX_EXT.SXFBZ is
'手续费标志 0-收取，1-免收';

comment on column APP_DWXX_EXT.SXFGSBZ is
'手续费归属标志 0-单位，1-其他，2-个人';

comment on column APP_DWXX_EXT.SXFKHFS is
'手续费扣划方式 0-自动，1-现金';

comment on column APP_DWXX_EXT.SXFZHLX is
'手续费付款账号类型';

comment on column APP_DWXX_EXT.SXFFKZH is
'手续费付款账号';

comment on column APP_DWXX_EXT.SXFFKZHMC is
'手续费付款账号名称';

comment on column APP_DWXX_EXT.SXFJSFS is
'手续费计算方式 0-按比例 1-按单笔';

comment on column APP_DWXX_EXT.SXFJSCS is
'手续费计算参数';

comment on column APP_DWXX_EXT.SXFJEXX is
'手续费金额下限';

comment on column APP_DWXX_EXT.SXFJESX is
'手续费金额上限';

comment on column APP_DWXX_EXT.KHQYFS is
'客户签约方式 0-银行 1-委托单位 2-银行或委托单位';

comment on column APP_DWXX_EXT.KKFS is
'部分扣款标志';

comment on column APP_DWXX_EXT.TZBZ is
'透支标志';

comment on column APP_DWXX_EXT.TZED is
'透支额度';

comment on column APP_DWXX_EXT.TZDFZH is
'垫付账号';

comment on column APP_DWXX_EXT.YJBZ is
'预警标志';

comment on column APP_DWXX_EXT.YEYBBL is
'余额预报比率';

comment on column APP_DWXX_EXT.JCHMBZ is
'检查户名标志';

comment on column APP_DWXX_EXT.YQBZ is
'验签标志';

comment on column APP_DWXX_EXT.YQMY is
'验签密钥';

comment on column APP_DWXX_EXT.FYYWLX1 is
'费用1业务种类';

comment on column APP_DWXX_EXT.FYRZZH1 is
'费用1入账账号';

comment on column APP_DWXX_EXT.FYZHLX1 is
'费用1账号类型';

comment on column APP_DWXX_EXT.FYYWLX2 is
'费用2业务种类';

comment on column APP_DWXX_EXT.FYRZZH2 is
'费用2入账账号';

comment on column APP_DWXX_EXT.FYZHLX2 is
'费用2账号类型';

comment on column APP_DWXX_EXT.FYYWLX3 is
'费用3业务种类';

comment on column APP_DWXX_EXT.FYRZZH3 is
'费用3入账账号';

comment on column APP_DWXX_EXT.FYZHLX3 is
'费用3账号类型';

comment on column APP_DWXX_EXT.FYYWLX4 is
'费用4业务种类';

comment on column APP_DWXX_EXT.FYRZZH4 is
'费用4入账账号';

comment on column APP_DWXX_EXT.FYZHLX4 is
'费用4账号类型';

comment on column APP_DWXX_EXT.FYYWLX5 is
'费用5业务种类';

comment on column APP_DWXX_EXT.FYRZZH5 is
'费用5入账账号';

comment on column APP_DWXX_EXT.FYZHLX5 is
'费用5账号类型';

comment on column APP_DWXX_EXT.EXTFLD1 is
'扩展字段1';

comment on column APP_DWXX_EXT.EXTFLD2 is
'扩展字段2';

comment on column APP_DWXX_EXT.EXTFLD3 is
'扩展字段3';

comment on column APP_DWXX_EXT.EXTFLD4 is
'扩展字段4';

comment on column APP_DWXX_EXT.EXTFLD5 is
'扩展字段5';

comment on column APP_DWXX_EXT.EXTFLD6 is
'扩展字段6';

comment on column APP_DWXX_EXT.QYLX is
'企业类型';

comment on column APP_DWXX_EXT.DFFS is
'代付方式';

comment on column APP_DWXX_EXT.QSBZ is
'清算方式';
