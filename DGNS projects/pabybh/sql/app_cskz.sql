delete from app_cskz where CSTJ='041';


insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_SETTLEFUND', '2', '041', '/pabybh/paractl/settlefund', '1', '联动清算资金 0不联动 1联动', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_HOSTSIGN', '2', '041', '/pabybh/paractl/hostsign', '1', '核心签约登记 0不签约 1签约登记', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_HOSTCHE', '2', '041', '/pabybh/paractl/hostche', '1', '联动核心对账0不联动 1联动', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_GETHOSTFILE', '2', '041', '/pabybh/paractl/gethostfile', '1', '联动获取主机对账文件 0不联动 1联动', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_FILEPATH', '2', '041', '/pabybh/paractl/filepath', '/home/gapsv4/file/pabybh', '平安银百合文件目录', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_LOCGXPPA', '2', '041', '/pabybh/paractl/locgxppa', '/home/wlgxp/file/pabybh', '平安GXP来盘文件目录', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_IEPFILEPA', '2', '041', '/pabybh/paractl/iepfilepa', '.', '平安远地文件目录', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_PABCOMM', '2', '041', '/pabybh/paractl/pabcomm', '1', '与中心连接方式1通过GXP 2直连中心', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_PABCHEFP', '2', '041', '/pabybh/paractl/pabchefp', '/home/gapsv4/file/pabybh/iepchk', '中心对账文件路径', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_HOSTCHEFP', '2', '041', '/pabybh/paractl/hostchefp', '/home/gapsv4/file/pabybh/hostchk', '核心对账文件路径', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_PABPARAFP', '2', '041', '/pabybh/paractl/pabparafp', '/home/gapsv4/file/pabybh/ieppara', '中心参数文件路径', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)values ('K_PABYBH_LOCPARAFP', '2', '041', '/pabybh/paractl/locparafp', '/home/gapsv4/file/pabybh/locpara', '本地参数文件路径', '0', '00000', 'admin', '20161017051304');

commit;