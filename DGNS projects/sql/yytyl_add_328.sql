--INSERT INTO YYT_HOSPCODE (UNIT_ALIAS, UNIT_ID, UNIT_NAME, IMAGE, ADDRESS, AREA_ID, UNIT_LEVEL, UNIT_SPELL, PHONE, PAYMENT, REMARK1, REMARK2, UNIT_FLAG, TAKENO_FLAG, CREATE_FLAG, QUERYQUEUEIN_FLAG, QUERYCHECK_FLAG, QUERYASSAY_FLAG) 
--VALUES ('', '328', '东莞市黄江医院', '', '广东省东莞市黄江镇北岸社区西环路南段1号', '3334', 'H', '', '0769-83636120', '0', '', '', '1', '1', '1', '1', '1', '1');

delete APP_DWCPXY where dwbh='003000510006';
insert into APP_DWCPXY values('003000510006','0030005','003000510006','东莞市黄江医院','003000510006','drc','yytyl','01','','380010190010007152','','','','','','','','','','','',
to_char(sysdate,'yyyymmdd'),0.00,'00000','admin',to_char(sysdate,'yyyymmddhh24miss'),'','','0','','','','','','','','','','','','');

delete APP_DWXX where dwbh='003000510006';
insert into APP_DWXX values('003000510006','莞医通诊中医疗_东莞市黄江医院','','','','','','','00000','admin',to_char(sysdate,'yyyymmddhh24miss'),'','','0');

delete ywty_acctinfo where dwbh='003000510006';
insert into ywty_acctinfo values(
'0030005','003000510006','003000510006','莞医通诊中医疗_东莞市黄江医院','000010104620600029','000010104620300036','','','380010190010007152','admin',to_char(sysdate,'yyyymmdd'),'0','','');

update yyt_hospcode set UNIT_FLAG='1',TAKENO_FLAG='1',CREATE_FLAG='1',QUERYQUEUEIN_FLAG='1',QUERYCHECK_FLAG='1',QUERYASSAY_FLAG='1'
WHERE unit_id='328';

