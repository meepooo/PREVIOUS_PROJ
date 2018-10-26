--索引--
create  index zjbgjj_sendserl_jydm on yw_gjj_sendserial(transcode);
create  index zjbgjj_drbatch_no on yw_gjj_drbatch(batchno);
--文件名防重--
create unique index zipfilename_drbatch on yw_gjj_drbatch (zipfilename);
create unique index zipfilename_crcapint on yw_gjj_crcapint (zipfilename);

-- 应用信息 -
delete from app_yyxx where YYBS='082';
insert into app_yyxx (YYBS, YYMC, YYSM, YYKFKSRQ, YYKFJSRQ, YYFBRQ, YYBBH, YHH, SQH, YYKFJL, YYZBJL, YYZT, EXTFLD) 
values ('082', 'zjb', '住建部', '', '', '20160225', '2.1.0.1', '', '', 'Lkq', 'Lkq', '0', '');
commit;

-- 单位信息 --
delete from app_dwxx where dwbh = 'gjj';
insert into APP_DWXX (dwbh, dwmc, dwzjlx, dwzjhm, dwlxr, dwlxrdh, dwdz, dwemail, whjg, whgy, whsj, extfld1, extfld2, zt)
values ('gjj', '公积金', null, null, null, null, null, null, '00000', 'admin', '20160225012643', null, null, '0');
commit;

-- 通讯参数维护 --
delete from APP_TXAQXX where ljbs='zjbgjj';
insert into APP_TXAQXX (ljbs, ljmc, ljlx, dwbh, qdkz, txms, txdz, txdk, fscs, jscs, ljjgh, ljgyh, ljzdh, key1, key2, key3, ftpdz, ftpyh, ftpmm, ftpgzfs, ftpcsfs, ftpzdms, ftpdflj, ftpbdlj, whjg, whgy, whsj, extfld1, extfld2, txzt, qdzt)
values ('zjbgjj', '住建部公积金', '3', 'gjj', null, '1', '127.0.0.1', '40001', 60, 60, null, null, null, null, null, null, null, null, null, null, '1', null, '/home/gapslx/file/gjj', '/home/gapslx/file/gjj/', '00000', 'admin', '20160225015812', 'NODEIN_ZJBGJJ', null, '0', '2');
commit;

-- 交易信息 --
delete from APP_JYXX where yybs='082';
insert into APP_JYXX (jydm, jymc, yybs, jylx, lsjlbz, rzbz, bbbz, cpxg, whjg, whgy, whsj, extfld1, extfld2, qtbz)
values ('976025', '账户变动通知', '082', '0', '1', '1', '1', '0', '00000', 'admin', null, null, null, '0');

commit;

-- 产品信息 --
delete from APP_CPXX where cpdm='zjb_gjj';
insert into APP_CPXX (cpdm, cpmc, yybs, zbjg, zbgy, khjl, ywrqlx, qdkzbz, jgkzcs, sxfbz, sfqybz, qyms, xyxljz, kkfs, jzsx, dzms, zjyyh, zjzyyh, lsblts, pdblts, jyfs, rzms, whjg, whgy, whsj, extfld1, extfld2, cpzt, pzbd, ywb)
values ('zjb_gjj', '住建部公积金', '082', '00000', 'admin', null, '2', '1', '0', '1', '0', null, null, '1', '0', '2', null, null, 0, 0, '1', '1', '00000', 'liukq', '20160225133840', null, null, '0', '06', null);
commit;

-- 单位产品协议 --
delete from APP_DWCPXY where dwbh='gjj';
insert into APP_DWCPXY (dwbh, cpdm, ywbh, ywmc, xybh, yhdm, ljbs, zhlx, sfbz, dszh, dszhmc, dfzh, dfzhmc, khjl, lxr, email, lxdh, hyksrq, hyjsrq, bljg, blgy, blrq, zhzded, whjg, whgy, whsj, extfld1, extfld2, qyzt)
values ('gjj', 'zjb_gjj', 'gjj', '公积金', null, null, null, null, '3', '9000123456', '自扣还款代收账户', null, null, null, null, null, null, null, null, null, null, null, 0, '00000', 'liukq', '20160225135320', null, null, '0');
commit;

-- 前置参数信息 --
insert into yw_gjj_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_ZJBGJJ_SERIAL_XL', '0', '082', '/zjbgjj/xl', 'zjbgjj', '住建部公积金序列', '0', '00000', 'admin', '20151019090000');

insert into yw_gjj_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_ZJBGJJ_XNJG', '0', '082', '/zjbgjj/xnjg', '000001', '虚拟机构', '0', '00000', 'admin', '20151019090000');
insert into yw_gjj_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_ZJBGJJ_XNGY', '0', '082', '/zjbgjj/xngy', 'A00001', '虚拟柜员', '0', '00000', 'admin', '20151019090000');

Insert into yw_gjj_cskz (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_ZJBGJJ_SYNFLAG','0','082','/zjbgjj/hxsynflg','0','同步标志0-同步 1-异步','0','00000','admin','20151019090000');
insert into yw_gjj_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_ZJBGJJ_MAX_TJHXCS', '0', '082','/zjbgjj/maxtjhxcs', '2', '提交核心最大次数', '0', '00000', 'admin', '20151019090000');

insert into yw_gjj_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ)
values ('K_ZJBGJJ_YHDM', '0', '082', '/zjbgjj/yhdm', '313068', '银行代码', '0', '00000', 'admin', '20151019090000');

insert into yw_gjj_cskz (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_ZJBGJJ_AUTOPROC','0','082','/zjbgjj/autoprocs','10','自动任务处理笔数','0','00000','admin','20151019090000');


insert into yw_gjj_cskz (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_ZJBGJJ_ISLSGXH','0','082','/zjbgjj/islsgxh','1','是否乐山个性化（1-是,0-否）','0','00000','admin','20151019090000');

insert into yw_gjj_cskz (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) 
values ('K_ZJBGJJ_SLEEPMS','0','082','/zjbgjj/sleepms','100','批量转单笔上核心休眠毫秒数','0','00000','admin','20151019090000');


commit;

--初始化业务表--
insert into yw_gjj_sign (SENDNODE, RECEIVENODE, ZWRQ, RECEIVEDATE, BDCDATE, DOTIME, KEYFILENAME, HANDKEY, BANKNO, STATUS, REMARK, REMARK1, REMARK2, REMARK3, REMARK4)
values ('313068', 'C51130', '20170508', '20170508', '20170508', '164003  ', '/home/nfsdata/nipp_only/zjbgjj/key/key', '', '', '1', '', '', '', '', '');

commit;





/*住建部公积金序列*/
create sequence zjbgjj
minvalue 1
maxvalue 999999
start with 1
increment by 1
nocache
cycle 
order;
