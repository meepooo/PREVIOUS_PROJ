delete from app_cskz where CSTJ='041';


insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)	
values ('K_PABYBH_SETTLEFUND', '2', '041', '/pabybh/paractl/settleFund', '1', '联动清算资金 0不联动 1联动', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)	
values ('K_PABYBH_HOSTSIGN', '2', '041', '/pabybh/paractl/hostSign', '1', '核心签约登记 0不签约 1签约登记', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)
values ('K_PABYBH_HOSTCHE', '2', '041', '/pabybh/paractl/hostChe', '1', '联动主机对账 0不联动 1联动', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)
values ('K_PABYBH_GETHOSTFILE', '2', '041', '/pabybh/paractl/getHostFile', '1', '联动获取主机对账文件 0不联动 1联动', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)
values ('K_PABYBH_FILEPATH', '2', '041', '/pabybh/paractl/filePath', '/home/gapsv4/file/pabybh', '平安银百合文件目录', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)
values ('K_PABYBH_LOCGXPPA', '2', '041', '/pabybh/paractl/locGxpPa', '/home/wlgxp/file/pabybh', '平安GXP来盘文件目录', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)
values ('K_PABYBH_IEPFILEPA', '2', '041', '/pabybh/paractl/iepFilePa', '.', '平安远地文件目录', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)
values ('K_PABYBH_PABCOMM', '2', '041', '/pabybh/paractl/pabComm', '1', '中心通讯方式：1通过GXP 2直连中心', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)
values ('K_PABYBH_PABCHEFP', '2', '041', '/pabybh/paractl/pabCheFP', '/home/gapsv4/file/pabybh/iepchk', '中心对账文件路径', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)
values ('K_PABYBH_HOSTCHEFP', '2', '041', '/pabybh/paractl/hostCheFP', '/home/gapsv4/file/pabybh/hostchk', '核心对账文件路径', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)
values ('K_PABYBH_PABPARAFP', '2', '041', '/pabybh/paractl/pabParaFP', '/home/gapsv4/file/pabybh/ieppara', '中心参数文件路径', '0', '00000', 'admin', '20161017051304');

insert into app_cskz (CSJZ,  CSLX,  CSTJ,  JDM,  JDZ,  REMARK,  JZLX,  WHJG,  WHGY,  WHSJ)
values ('K_PABYBH_LOCPARAFP', '2', '041', '/pabybh/paractl/locParaFP', '/home/gapsv4/file/pabybh/locpara', '本地参数文件路径', '0', '00000', 'admin', '20161017051304');
