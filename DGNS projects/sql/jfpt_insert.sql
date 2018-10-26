/**
说明
kztj1：DEFAULT1-缴费人默认手续费
       DEFAULT2-商户默认手续费
kztj1：1-本行卡
       2-他行卡
**/
insert into app_xlkz(pkey,curr_value,pinc,min_value,max_value,remark,whjg,whgy,whsj)/**不确定是否已配置，若已配置则无需插入**/
values('K_DWBH','100001','1','100001','999999','单位编号','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'));

insert into app_yyxx(yybs,yymc,yysm,yyfbrq,yybbh,yykfjl,yyzbjl,yyzt)
values('400','jfpt','缴费平台',to_char(current date,'yyyymmdd'),'0.0.0.1','sunpengjun','sunpengjun','0');

insert into app_cpxx(cpdm,cpmc,yybs,zbjg,ywrqlx,qdkzbz,jgkzcs,sxfbz,sfqybz,qyms,xyxljz,kkfs,jzsx,dzms,lsblts,pdblts,jyfs,rzms,whjg,whgy,whsj,cpzt,sxftkbz)
values('4001000','代收学杂费','400','00000','1','1','0','0','0','2','K_DWBH','1','0','1',0,0,'1','1','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'),'0','0');

insert into app_sxffl(flbs,xh,fdbz,nwkbz,sxxkz,sxje,xxje,jslx,jscs,kjbz,kjcs,sm,whjg,whgy,whsj)
values('JFPT_MRFL_S','1','0','0','1',0.00,0.00,'1',0.000000,'0',0.000000,'客户默认收费费率','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'));
insert into app_sxffl(flbs,xh,fdbz,nwkbz,sxxkz,sxje,xxje,jslx,jscs,kjbz,kjcs,sm,whjg,whgy,whsj)
values('JFPT_MRFL_G','1','0','0','1',0.00,0.00,'1',0.000000,'0',0.000000,'商户默认收费费率','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'));


insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','TRADER_CODE','010020160119170814','中间业务在支付网关的商户号');
insert into agent_csys(lb,srcs,sccs,ms)values('ZHXX','DSZH','120010190010017087','一二三');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','940062','00','00-农商行借记卡');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','622328','00','00-农商行借记卡');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','623038','00','00-农商行借记卡');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','625288','01','01-农商行贷记卡');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','625888','01','01-农商行贷记卡');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','623198','02','02-本机构村镇行借记卡');
insert into agent_csys(lb,srcs,sccs,ms)values('ISREMOTE','4001000','0','是否上第三方 0:否 1:是');
insert into agent_csys(lb,srcs,sccs,ms)values('THIRD_REFUND','4001000','0','是否上第三方退款 0:否 1:是');
insert into agent_csys(lb,srcs,sccs,ms)values('THIRD_CHECK','4001000','0','是否上第三方对账 0:否 1:是');
insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','CLINET_NO','2000936391','中间业务在支付网关的客户号');
insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','FTP_IP','10.8.6.30','支付网关对账文件服务器地址');
insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','FTP_USER','epayusr','支付网关对账文件服务器用户名');
insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','FTP_PWD','123456','支付网关对账文件服务器密码');
insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','FTP_PATH','/home/epayusr/file','支付网关对账文件路径');

insert into APP_JYXX values('920004','缴费平台与核心对明细','400','0','1','1','1','0','00000','admin','','','','0');
insert into APP_JYXX values('920009','缴费平台与支付网关对明细','400','0','1','1','1','0','00000','admin','','','','0');
insert into APP_JYXX values('920305','缴费平台(直接缴费)','400','0','0','0','0','0','00000','admin','','','','0');

insert into app_qdxx values('211','现金管理','现金管理','1','','','0','0','00000','admin','20160520025257','','','0');
insert into app_qdxx values('212','东莞农商行网站','东莞农商行网站','1','','','0','0','00000','admin','','','','0');

insert into app_txaqxx values(
'jfpt','缴费平台','1','400100010000000','1','1','','',60,60,'','','','','','','','','','','','','','','00000','admin',to_char(sysdate,'yyyymmddhh24miss'),'','','0','');
