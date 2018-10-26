alter table app_dwcpxy
    add fwrx varchar(32)
    add jfbhxsmc varchar(100)
    add khh varchar(32)
    add nbhzhmc varchar(100)
    add nbhzh varchar(32)
    add sxfnbhzhmc varchar(100)
    add sxfnbhzh varchar(32)
    add scfs varchar(2)
    add shzt varchar(1)
    add shsj varchar(14)
    add shgy varchar(16)
    add shjg varchar(32);

comment on column app_dwcpxy.fwrx is
'服务热线';

comment on column app_dwcpxy.jfbhxsmc is
'缴费编号显示名称';

comment on column app_dwcpxy.khh is
'客户号';

comment on column app_dwcpxy.nbhzhmc is
'内部户账号名称';

comment on column app_dwcpxy.nbhzh is
'内部户账号';

comment on column app_dwcpxy.sxfnbhzhmc is
'手续费内部户账号名称';

comment on column app_dwcpxy.sxfnbhzh is
'手续费内部户账号';

comment on column app_dwcpxy.scfs is
'上传方式 01-缴费平台 02-自有系统 03-线下代理';

comment on column app_dwcpxy.shzt is
'审核状态 9-未审核 1-审核通过 2-审核拒绝';

comment on column app_dwcpxy.shsj is
'审核时间';

comment on column app_dwcpxy.shgy is
'审核柜员';

comment on column app_dwcpxy.shjg is
'审核机构';
