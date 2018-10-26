--创建索引--
create  index xdxx_gaywbm_fsjg on gab_dxzp_xdxx(gaywsqbh,fsjgbm);

-- 前置参数信息 --
delete APP_CSKZ where csjz='K_DXZP_SYNFLAG';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_DXZP_SYNFLAG','0','040','/gabdxzp/hxsynflg','0','同步标志0-同步 1-异步','0','00000','admin','20151019090000');

delete APP_CSKZ where csjz='K_GABDXZP_MDYZZL';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_GABDXZP_MDYZZL','0','040','/gabdxzp/mdyzzl','1','名单验证直连 0-否 1-是','0','00000','admin','20151019090000');

delete APP_CSKZ where csjz='K_DXZP_SUB_JYDM';
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_SUB_JYDM', '0', '040', '/gabdxzp/subjydm', '945126', '批量文件导入子流程', '0', '00000', 'admin', '20151019090000');

delete gab_dxzp_bwpz where jylxbm in('100301','100303','100307','100309','100201','100203','100205','100101','100103','100105','100402');
insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100301', '交易明细查询', '945106', '交易明细查询', '1', '0', '0', '100302', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100303', '主体查询', '945107', '主体查询', '1', '0', '0', '100304', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100307', '动态解除查询', '945109', '动态解除查询', '1', '0', '0', '100308', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100309', '客户全账号查询', '945110', '客户全账号查询', '1', '0', '0', '100310', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100201', '冻结', '945103', '冻结', '1', '0', '0', '100202', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100203', '冻结解除', '945104', '冻结解除', '1', '0', '0', '100204', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100205', '冻结延期', '945105', '冻结延期', '1', '0', '0', '100206', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100101', '止付', '945100', '止付', '1', '0', '0', '100102', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100103', '止付解除', '945101', '止付解除', '1', '0', '0', '100104', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100105', '止付延期', '945102', '止付延期', '1', '0', '0', '100106', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100402', '案件举报反馈', '945127', '案件举报反馈', '1', '0', '0', '100402', '', '');

commit;