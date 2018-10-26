drop table ywty_xtywzt ;
drop SEQUENCE SEQ_SERIAL ;
create table ywty_xtywzt
(
  zwrq  char(8) not null,
  zhqzlsh integer not null,
  ywzt char(1) not null
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on column ywty_xtywzt.zwrq is '��������' ;
comment on column ywty_xtywzt.zhqzlsh is '�ۺ�ǰ����ˮ' ;
comment on column ywty_xtywzt.ywzt is 'ҵ��״̬' ;

insert into ywty_xtywzt values(to_char(sysdate,'yyyymmdd'),0,'1') ;


CREATE SEQUENCE SEQ_SERIAL START WITH 1 INCREMENT BY 1 MINVALUE 1 MAXVALUE 99999999 CACHE 100 CYCLE ORDER ;
