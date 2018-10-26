
--创建索引--
create  index xdxx_gaywbm_fsjg on gab_dxzp_xdxx(gaywsqbh,fsjgbm);

-- 应用信息 -
delete from app_yyxx where YYBS='040';
insert into app_yyxx (YYBS, YYMC, YYSM, YYKFKSRQ, YYKFJSRQ, YYFBRQ, YYBBH, YHH, SQH, YYKFJL, YYZBJL, YYZT, EXTFLD) 
values ('040', 'sfxt', '司法查控', '', '', '20160225', '2.1.0.1', '', '', 'Tuql', 'Tuql', '0', '');
commit;

-- 单位信息 --
delete from app_dwxx where dwbh = 'dxzp';
insert into APP_DWXX (dwbh, dwmc, dwzjlx, dwzjhm, dwlxr, dwlxrdh, dwdz, dwemail, whjg, whgy, whsj, extfld1, extfld2, zt)
values ('dxzp', '公安部电信诈骗', null, null, null, null, null, null, '00000', 'admin', '20160225012643', null, null, '0');
commit;

-- 通讯参数维护 --
delete from APP_TXAQXX where ljbs='sfxtdxzp';
insert into APP_TXAQXX (ljbs, ljmc, ljlx, dwbh, qdkz, txms, txdz, txdk, fscs, jscs, ljjgh, ljgyh, ljzdh, key1, key2, key3, ftpdz, ftpyh, ftpmm, ftpgzfs, ftpcsfs, ftpzdms, ftpdflj, ftpbdlj, whjg, whgy, whsj, extfld1, extfld2, txzt, qdzt)
values ('sfxtdxzp', '电信诈骗中心', '3', 'dxzp', null, '1', '127.0.0.1', '40001', 60, 60, null, null, null, null, null, null, null, null, null, null, '1', null, '/home/gapslx/file/dxzp', '/home/gapslx/file/dxzp/', '00000', 'admin', '20160225015812', 'NODEIN_GAPS2QZXT', null, '0', '2');
commit;

-- 交易信息 --
delete from APP_JYXX where yybs='040';
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945111', '案件举报', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945112', '异常开卡', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945113', '涉案账户', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945114', '异常事件', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945115', '账户涉案', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945116', '身份涉案', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945117', '业务处理', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945118', '定时轮询业务处理', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945119', '通用查询', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945120', '定时获取前置消息', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945121', '手工拒绝处理', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('945122', '批量信息上报', '040', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');
insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('945123', '动态查询上报', '040', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');
insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('945124', '动态查询实时推送', '040', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');
insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('945125', '超时查证', '040', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');
insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('LoadHhmd', '黑灰名单下载', '040', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('945126', '上报信息批量导入', '040', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');
insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('945127', '案件举报反馈', '040', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');
insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('945128', '获取托管机构消息', '040', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');


commit;

-- 产品信息 --
delete from APP_CPXX where cpdm='sfxt_dxzp';
insert into APP_CPXX (cpdm, cpmc, yybs, zbjg, zbgy, khjl, ywrqlx, qdkzbz, jgkzcs, sxfbz, sfqybz, qyms, xyxljz, kkfs, jzsx, dzms, zjyyh, zjzyyh, lsblts, pdblts, jyfs, rzms, whjg, whgy, whsj, extfld1, extfld2, cpzt, pzbd, ywb)
values ('sfxt_dxzp', '司法系统电信诈骗', '040', '00000', 'admin', null, '2', '1', '0', '1', '0', null, null, '1', '0', '2', null, null, 0, 0, '1', '1', '00000', 'tuql', '20160225133840', null, null, '0', '06', null);
commit;

-- 单位产品协议 --
delete from APP_DWCPXY where dwbh='dxzp';
insert into APP_DWCPXY (dwbh, cpdm, ywbh, ywmc, xybh, yhdm, ljbs, zhlx, sfbz, dszh, dszhmc, dfzh, dfzhmc, khjl, lxr, email, lxdh, hyksrq, hyjsrq, bljg, blgy, blrq, zhzded, whjg, whgy, whsj, extfld1, extfld2, qyzt)
values ('dxzp', 'sfxt_dxzp', 'dxzp', '电信诈骗业务', null, null, null, null, '3', '9000123456', '自扣还款代收账户', null, null, null, null, null, null, null, null, null, null, null, 0, '00000', 'tuql', '20160225135320', null, null, '0');
commit;

-- 前置参数信息 --
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_DXZP_SYNFLAG','0','040','/gabdxzp/hxsynflg','0','同步标志0-同步 1-异步','0','00000','admin','20151019090000');
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_DXZP_QSJGID','0','040','/gabdxzp/qsjgid','111111000000','缺省机构ID','0','00000','admin','20151019090000');
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_DXZP_DDMIN','0','040','/gabdxzp/xxcs/ddmin','15','提前兜底N分钟','0','00000','admin','20151019090000');
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_DXZP_AUTOPROC','0','040','/gabdxzp/xxcs/autoproc','10','自动任务处理笔数','0','00000','admin','20151019090000');
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_DXZP_YHJGID','0','040','/gabdxzp/xxcs/yhjgid','10000','银行机构代码','0','00000','admin','20151019090000');

--DEL BY TUQL  20160407 此参数需从GAB_DXZP_945112组件传入
--insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
--values ('K_DXZP_YorNbatch', '0', '040', '/gabdxzp/YorNbatch', '1', '上报是否批量', '0', '00000', 'admin', '20151019090000');
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_AID_SERIAL_XL', '0', '040', '/sfxt/xl', 'FYCK', '司法查控序列', '0', '00000', 'admin', '20151019090000');


insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_HOST_FILE', '0', '040', '/gabdxzp/YorNhostfile', '1', '核心返回是否文件', '0', '00000', 'admin', '20151019090000');

Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_SFXT_HXFCBZ','0','040','/sfxt/hxfcbz','0','核心防重标志0-不防,1-防重','0','00000','admin','20151019090000');

Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_GABDXZP_MDYZZL','0','040','/gabdxzp/mdyzzl','1','名单验证直连 0-否 1-是','0','00000','admin','20151019090000');

update  APP_CSKZ set cstj='040', jdm='/sfxt/xl',jzlx='0' where csjz='K_AID_SERIAL_XL';
--select nextval for FYCK as ID from SYSIBM.SYSDUMMY1

-- FTP信息 --
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_FTP_MODE', '0', '040', '/gabdxzp/mode', '00', 'FTP模式00--被动，01--主动', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_FTP_IP', '0', '040', '/gabdxzp/ftpip', '127.0.0.1', 'FTP的ip地址', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_FTP_PORT', '0', '040', '/gabdxzp/port', 'port', 'FTP的端口', '0', '00000', 'admin', '20151019090000');


insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_FTP_USERNAME', '0', '040', '/gabdxzp/username', 'username', 'FTP的用户名', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_FTP_PASSWORD', '0', '040', '/gabdxzp/password', 'password', 'FTP的密码', '0', '00000', 'admin', '20151019090000');


insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_FTP_CALLSHELL', '0', '040', '/gabdxzp/ftpjb', 'CommFtpPub.sh', 'FTP的调用脚本', '0', '00000', 'admin', '20151019090000');


insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_SFXT_XNJG', '0', '040', '/sfxt/xnjg', '81201', '虚拟机构', '0', '00000', 'admin', '20151019090000');
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_SFXT_XNGY', '0', '040', '/sfxt/xngy', 'BR1111', '虚拟柜员', '0', '00000', 'admin', '20151019090000');
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_MAX_TJHXCS', '0', '040', '/gabdxzp/maxtjhxcs', '2', '提交核心最大次数', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_MAX_FKQZCS', '0', '040', '/gabdxzp/maxfkqzcs', '2', '反馈前置最大次数', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_CZGYM', '0', '040', '/gabdxzp/czgym', '小明', '银行经办姓名', '0', '00000', 'admin', '20151019090000');
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_CZGYDH', '0', '040', '/gabdxzp/czgydh', '13323233232', '银行经办电话', '0', '00000', 'admin', '20151019090000');
--add by tuql 20160411
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_FRBANK', '0', '040', '/gabdxzp/brbank', '102100099996', '法人行号中国工商银行', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_SBL_LZMODE', '0', '040', '/gabdxzp/SBL_LZMODE', '01', '标准模式（只针对于上报类）', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_FEEDBACKLIMIT', '0', '040', '/Response/Body/FeedbackLimit', '24', '反馈限定时间（可以根据自己的情况设定）', '0', '00000', 'admin', '20151019090000');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_DXZP_SUB_JYDM', '0', '040', '/gabdxzp/subjydm', '945126', '批量文件导入子流程', '0', '00000', 'admin', '20151019090000');


commit;



insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100301', '交易明细查询', '945106', '交易明细查询', '1', '0', '0', '100302', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100303', '主体查询', '945107', '主体查询', '1', '0', '0', '100304', '', '');

insert into gab_dxzp_bwpz (JYLXBM, JYLXMC, JYDM, JYMC, XXLZMS, LDHZDBZ, FKQZDBZ, BY1, BY2, BY3)
values ('100305', '动态查询', '945108', '动态查询', '1', '0', '1', '100306', '', '');

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

create sequence FYCK
minvalue 1
maxvalue 9999999
start with 1
increment by 1
nocache
order;

