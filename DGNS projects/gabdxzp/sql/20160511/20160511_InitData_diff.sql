--��������--
create  index xdxx_gaywbm_fsjg on gab_dxzp_xdxx(gaywsqbh,fsjgbm);

-- ǰ�ò�����Ϣ --
delete APP_CSKZ where csjz='K_DXZP_SYNFLAG';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_DXZP_SYNFLAG','0','040','/gabdxzp/hxsynflg','0','ͬ����־0-ͬ�� 1-�첽','0','00000','admin','20151019090000');

delete APP_CSKZ where csjz='K_GABDXZP_MDYZZL';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_GABDXZP_MDYZZL','0','040','/gabdxzp/mdyzzl','1','������ֱ֤�� 0-�� 1-��','0','00000','admin','20151019090000');

delete APP_CSKZ where csjz='K_DXZP_SUB_JYDM';
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_SUB_JYDM', '0', '040', '/gabdxzp/subjydm', '945126', '�����ļ�����������', '0', '00000', 'admin', '20151019090000');

delete gab_dxzp_bwpz where jylxbm in('100301','100303','100307','100309','100201','100203','100205','100101','100103','100105','100402');
insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100301', '������ϸ��ѯ', '945106', '������ϸ��ѯ', '1', '0', '0', '100302', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100303', '�����ѯ', '945107', '�����ѯ', '1', '0', '0', '100304', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100307', '��̬�����ѯ', '945109', '��̬�����ѯ', '1', '0', '0', '100308', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100309', '�ͻ�ȫ�˺Ų�ѯ', '945110', '�ͻ�ȫ�˺Ų�ѯ', '1', '0', '0', '100310', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100201', '����', '945103', '����', '1', '0', '0', '100202', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100203', '������', '945104', '������', '1', '0', '0', '100204', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100205', '��������', '945105', '��������', '1', '0', '0', '100206', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100101', 'ֹ��', '945100', 'ֹ��', '1', '0', '0', '100102', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100103', 'ֹ�����', '945101', 'ֹ�����', '1', '0', '0', '100104', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100105', 'ֹ������', '945102', 'ֹ������', '1', '0', '0', '100106', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100402', '�����ٱ�����', '945127', '�����ٱ�����', '1', '0', '0', '100402', '', '');

commit;