delete from app_yyxx where yybs='041';
delete from app_qdxx where qdbs='403';
delete from APP_XLKZ where pkey='K_PABYBH_XYBH';
delete from app_jyxx where yybs='041';
delete from APP_TXAQXX where ljbs='pabybh';
delete from PABYBH_SVRINFO;
delete from PABYBH_SECKEY;
delete from PABYBH_PABTRANSCTL ; 
delete from PABYBH_ORGCFG ; 
delete from APP_MSGNOTICEPEOPLE where BUSNO='003001510000';
delete from PABYBH_COURSE_INFO ;



insert into app_yyxx values('041','pabybh','平安银百合','20160601','20161101','20161231','3.0.0.0','','','LIYJ','LIYJ','0','');
insert into app_qdxx values('403','pabybh','平安银百合','1','','','0','0','00000','admin','','','','0');

INSERT INTO APP_XLKZ (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY, WHSJ) 
VALUES ('K_PABYBH_XYBH', 1, 1, 1, 99999999, '平安银银协议编号', '00000', 'admin', '20150820090000');


insert into app_jyxx values('944301','签到/签退','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944302','资金划转','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944303','资金冲正','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944304','对账通知','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944305','交易状态查询','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944306','存管预指定确定','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944307','签约账户变更','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944308','存管预指定确认撤销','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944309','客户签约账户余额查询','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944310','查询客户证券资金余额','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944311','查询客户银银中心存管签约信息','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944312','一步式签约','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944313','查询交易明细','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944314','批量通知（券商信息同步）','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944315','柜面券商信息同步','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944316','明细对账（完全、继续）','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944317','不平明细调账','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944318','资金清算划转','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944319','本地交易明细查询','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944320','本地签约信息查询','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944321','对账状态查询','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944322','核心对账明细查询','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944323','银银对账明细查询','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944324','不平明细查询','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944325','当日人工处理资金汇划','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('701509','核心交易状态查询','041','0','0','1','1','1','00000','admin','','','','0');


INSERT INTO APP_TXAQXX (LJBS, LJMC, LJLX, DWBH, QDKZ, TXMS, TXDZ, TXDK, FSCS, JSCS, LJJGH, LJGYH, LJZDH, KEY1, KEY2, KEY3, FTPDZ, FTPYH, FTPMM, FTPGZFS, FTPCSFS, FTPZDMS, FTPDFLJ, FTPBDLJ, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, TXZT, QDZT) 
VALUES ('pabybh', '平安银百合', '3', '', '', '1', '10.8.208.173', '50023', 60, 60, '88888', '81108', 'TTYGAPS', 'NODEIN_GAPS2PABYBH', '', '', '', '', '', null, '', null, '', null, '00000', 'admin', '20160225015812', '', '', '0', '');

INSERT INTO PABYBH_SVRINFO 
VALUES ('7558', '0802', '平安第三方存管', '000000|235959', '0', '', '', '');
INSERT INTO PABYBH_SVRINFO 
VALUES ('7558', '0001', '平安银银公共', '000000|235959', '0', '', '', '');

INSERT INTO PABYBH_SECKEY (COBANKNO, ENCRYPTIP, ENCRYPTPORT, ENCRYPTSYSID, ENCRYPTEXTID, ZMK, ZAK, IEPZPK, COUNTERZPK, HOSTZPK, EXTFLD1, EXTFLD2, EXTFLD3, EXTFLD4) 
VALUES ('7558', '', '', '', '', '', '100021.PAB001000.zak', '100021.PAB001000.zpk', '', '', null, null, null, null);


INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900015', '签到/签退', '0001', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900007', '资金划转', '0001', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900023', '资金冲正', '0001', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900017', '对账通知', '0001', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900029', '交易状态查询', '0001', '0', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908001', '预指定确认', '0802', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908003', '签约账户变更', '0802', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908004', '银转证', '0802', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908005', '证转银', '0802', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908006', '查询客户证券资金余额', '0802', '0', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900026', '批量提交通知', '0001', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908020', '查询存管签约信息', '0802', '0', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908022', '存管预指定确认撤销', '0802', '0', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900013', '查询客户结算账户余额', '0001', '0', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908026', '一步式签约', '0802', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908008', '查询交易明细', '0802', '0', null, null, null);

INSERT INTO PABYBH_ORGCFG (COBANKNO, COBANKNAME, CUSTMANAGERNO, ACCT, ACCTNAME, ACCT1, ACCT1NAME, ACCT2, ACCT2NAME, ACCT3, ACCT3NAME, ACCT4, ACCT4NAME, SIGNSTATUS, AREACODE, COORGNO, WORKDATE, WORKSERIALNO, MAINTAINDATE, MAINTAINTIME, EXTFLD1, EXTFLD2, EXTFLD3, EXTFLD4, EXTFLD5, EXTFLD6) 
VALUES ('7558', null, null, null, null, '000010126220011057', '创富理财代销资金专户', '000010113920010006', '明天会更好有限责任公司', null, null, null, null, '1', null, null, '20170828', null, null, null, null, null, null, null, null, null);

--添加手机号
INSERT INTO APP_MSGNOTICEPEOPLE (PROCODE, BUSNO, PHONE, PEOPLENAME, MSGNOTICETYPE, OPENFLAG, OPERATETIME, OPERATEBRC, OPERATETEL, BUSTYPE, REMARK1, REMARK2, REMARK3, REMARK4, REMARK5) 
VALUES ('0030015', '003001510000', '1331666112', 'xx', '01', '0', '20170503171333', '00000       ', 'admin       ', '00', '          ', '                    ', '                                                  ', '                                                                                                    ', '                                                                                                                                                                                                        ');


--初始化分录科目信息
INSERT INTO PABYBH_COURSE_INFO (ID, COURSE_CODE, COURSE_NAME, COURSE_ACCOUNT, COURSE_DESC) VALUES ('3', '1124_TRANSIT', '法定存款准备金', '000010111241112223', '银银转账清算户');
INSERT INTO PABYBH_COURSE_INFO (ID, COURSE_CODE, COURSE_NAME, COURSE_ACCOUNT, COURSE_DESC) VALUES ('4', '2323_TRANSIT', '上存联社省辖保证金', '999990123231111129', '银银转账结算户');
INSERT INTO PABYBH_COURSE_INFO (ID, COURSE_CODE, COURSE_NAME, COURSE_ACCOUNT, COURSE_DESC) VALUES ('5', '1123_CLEAR', '光大银行广州分行', '999990111230011182', 'AA');
INSERT INTO PABYBH_COURSE_INFO (ID, COURSE_CODE, COURSE_NAME, COURSE_ACCOUNT, COURSE_DESC) VALUES ('1', '2622_TRANSIT', '委托及代理负债业务-银银转帐', '000010126220011057', '创富理财代销资金专户');
INSERT INTO PABYBH_COURSE_INFO (ID, COURSE_CODE, COURSE_NAME, COURSE_ACCOUNT, COURSE_DESC) VALUES ('2', '1392_TRANSIT', '委托及代理资产业务——', '000010113920010006', '明天会更好有限责任公司');


commit;