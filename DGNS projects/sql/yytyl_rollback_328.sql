delete APP_DWCPXY where dwbh='003000510006';

delete APP_DWXX where dwbh='003000510006';

delete ywty_acctinfo where dwbh='003000510006';

update yyt_hospcode set UNIT_FLAG='0',TAKENO_FLAG='0',CREATE_FLAG='0',QUERYQUEUEIN_FLAG='0',QUERYCHECK_FLAG='0',QUERYASSAY_FLAG='0'
WHERE unit_id='328';

