drop table ywty_busi_dz;
create table ywty_busi_dz
(
	dzpano varchar(26),
	dzfgno varchar(8),
	dzcpno varchar(9),
	dzfuac varchar(32),
	dzshac varchar(32),
	dztram decimal(20,2),
	dzcyno varchar(2),
	dzeydt varchar(8),
	dzqyno varchar(26)
) --IN GAPS_DATA INDEX IN GAPS_INDEX 
;

create unique index index_ywty_busi_dz_1 on ywty_busi_dz( DZPANO );
comment on table  ywty_busi_dz  is 'ywty_busi_dz' ;
comment on column ywty_busi_dz.DZPANO is '平台流水号' ;
comment on column ywty_busi_dz.DZFGNO is '业务类型' ;
comment on column ywty_busi_dz.DZCPNO is '业务子类' ;
comment on column ywty_busi_dz.DZFUAC is '借方银行账号' ;
comment on column ywty_busi_dz.DZSHAC is '贷方银行账号' ;
comment on column ywty_busi_dz.DZTRAM is '金额' ;
comment on column ywty_busi_dz.DZCYNO is '币种' ;
comment on column ywty_busi_dz.DZEYDT is '核心记账日期' ;
comment on column ywty_busi_dz.DZQYNO is '核心流水号' ;
