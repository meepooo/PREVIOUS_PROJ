drop table zjyw_ordersum;
create table zjyw_ordersum
(
	tran_date varchar(8),
	ywlx varchar(2),
	zflx varchar(1),
	qdbs varchar(10),
	area_code varchar(10),
	order_count integer,
	tran_amt decimal(20,2),
	unit_id1 varchar(30),
	unit_name1 varchar(150),
	unit_id2 varchar(30),
	unit_name2 varchar(150),
	unit_id3 varchar(30),
	unit_name3 varchar(150),
	state varchar(10),
	remark1 varchar(40),
	remark2 varchar(40),
	remark3 varchar(40),
	remark4 varchar(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

create unique index index_zjyw_ordersum_1 on zjyw_ordersum( TRAN_DATE, YWLX, ZFLX, QDBS, STATE );
comment on table  zjyw_ordersum  is 'zjyw_ordersum' ;
comment on column zjyw_ordersum.TRAN_DATE is '��������' ;
comment on column zjyw_ordersum.YWLX is 'ҵ������' ;
comment on column zjyw_ordersum.ZFLX is '֧������' ;
comment on column zjyw_ordersum.QDBS is '����' ;
comment on column zjyw_ordersum.AREA_CODE is '��������' ;
comment on column zjyw_ordersum.ORDER_COUNT is '����������' ;
comment on column zjyw_ordersum.TRAN_AMT is '�������' ;
comment on column zjyw_ordersum.UNIT_ID1 is 'һ��ID' ;
comment on column zjyw_ordersum.UNIT_NAME1 is 'һ������' ;
comment on column zjyw_ordersum.UNIT_ID2 is '����ID' ;
comment on column zjyw_ordersum.UNIT_NAME2 is '��������' ;
comment on column zjyw_ordersum.UNIT_ID3 is '����ID' ;
comment on column zjyw_ordersum.UNIT_NAME3 is '��������' ;
comment on column zjyw_ordersum.STATE is '״̬' ;
comment on column zjyw_ordersum.REMARK1 is '��ע1' ;
comment on column zjyw_ordersum.REMARK2 is '��ע2' ;
comment on column zjyw_ordersum.REMARK3 is '��ע3' ;
comment on column zjyw_ordersum.REMARK4 is '��ע4' ;
