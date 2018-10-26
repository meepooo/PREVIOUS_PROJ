delete APP_CSKZ where csjz='K_DXZP_AUTOPROC';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_DXZP_AUTOPROC','0','040','/gabdxzp/xxcs/autoprocs','10','自动任务处理笔数','0','00000','admin','20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_HOST_PUB', '0', '040', '/gabdxzp/YorNhostpubcl', '0', '是否核心公共处理', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_Attach_PATH', '0', '040', '/gabdxzp/AttachmentPATH', '/file/gabdxzp/attachment', '文书路径', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_Hhmd_MoveMins', '0', '040', '/gabdxzp/hhmd/movemins', '0', '黑灰名单下载偏移分钟数', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_Dtcx_MoveDate', '0', '040', '/gabdxzp/dtcx/movedate', '183', '动查截止日期空,偏移6个月', '0', '00000', 'admin', '20151019090000');