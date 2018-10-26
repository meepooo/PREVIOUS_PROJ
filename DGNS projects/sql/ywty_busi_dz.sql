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
comment on column ywty_busi_dz.DZPANO is 'ƽ̨��ˮ��' ;
comment on column ywty_busi_dz.DZFGNO is 'ҵ������' ;
comment on column ywty_busi_dz.DZCPNO is 'ҵ������' ;
comment on column ywty_busi_dz.DZFUAC is '�跽�����˺�' ;
comment on column ywty_busi_dz.DZSHAC is '���������˺�' ;
comment on column ywty_busi_dz.DZTRAM is '���' ;
comment on column ywty_busi_dz.DZCYNO is '����' ;
comment on column ywty_busi_dz.DZEYDT is '���ļ�������' ;
comment on column ywty_busi_dz.DZQYNO is '������ˮ��' ;
