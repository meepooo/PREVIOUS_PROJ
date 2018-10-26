--创建超时查证统一视图
--系统编号,业务申请编号,业务日期,业务流水号,请求单状态
drop view sfck_timeout;
create view sfck_timeout (xtbh,ywbm,ywsqbh,ywrq,ywlsh,qqdzt) as 
    select 'gabdxzp','gab_dxzp_xdxx',ywsqbh,ywrq,ywlsh,qqdzt from gab_dxzp_xdxx where qqdzt in ('23','33')
    ;