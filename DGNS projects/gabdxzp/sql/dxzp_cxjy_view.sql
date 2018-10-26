-- 创建查询类交易视图 --
drop view view_dxzp_cxjy;
create view view_dxzp_cxjy(ywsqbh,zh,zhmc,zjlx,zjhm,zhjg,zhjgmc,cxnr) as 
      select ywsqbh,zh,zhmc,'','',khyh,khyhmc,cxnr from gab_dxzp_jymx where 1=1
    union all
      select ywsqbh,zh,zhmc,'','',khyh,khyhmc,'' from gab_dxzp_ztcx where 1=1
    union all
      select ywsqbh,zh,zhmc,'','',khyh,khyhmc,'' from gab_dxzp_dtcx where 1=1
    union all
      select ywsqbh,'','',cxzjlx,cxzjhm,'','',cxnr from gab_dxzp_qhcx where 1=1;
