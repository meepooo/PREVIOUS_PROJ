    --银医通医院代码表增加字段
alter table yyt_hospcode add column UNIT_FLAG varchar(1) add TAKENO_FLAG varchar(1) add CREATE_FLAG varchar(1) add QUERYQUEUEIN_FLAG varchar(1) add QUERYCHECK_FLAG varchar(1) add QUERYASSAY_FLAG varchar(1);
reorg table yyt_hospcode;

