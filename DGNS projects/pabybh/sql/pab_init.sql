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



insert into app_yyxx values('041','pabybh','ƽ�����ٺ�','20160601','20161101','20161231','3.0.0.0','','','LIYJ','LIYJ','0','');
insert into app_qdxx values('403','pabybh','ƽ�����ٺ�','1','','','0','0','00000','admin','','','','0');

INSERT INTO APP_XLKZ (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY, WHSJ) 
VALUES ('K_PABYBH_XYBH', 1, 1, 1, 99999999, 'ƽ������Э����', '00000', 'admin', '20150820090000');


insert into app_jyxx values('944301','ǩ��/ǩ��','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944302','�ʽ�ת','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944303','�ʽ����','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944304','����֪ͨ','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944305','����״̬��ѯ','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944306','���Ԥָ��ȷ��','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944307','ǩԼ�˻����','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944308','���Ԥָ��ȷ�ϳ���','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944309','�ͻ�ǩԼ�˻�����ѯ','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944310','��ѯ�ͻ�֤ȯ�ʽ����','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944311','��ѯ�ͻ��������Ĵ��ǩԼ��Ϣ','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944312','һ��ʽǩԼ','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944313','��ѯ������ϸ','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944314','����֪ͨ��ȯ����Ϣͬ����','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944315','����ȯ����Ϣͬ��','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944316','��ϸ���ˣ���ȫ��������','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944317','��ƽ��ϸ����','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944318','�ʽ����㻮ת','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944319','���ؽ�����ϸ��ѯ','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944320','����ǩԼ��Ϣ��ѯ','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944321','����״̬��ѯ','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944322','���Ķ�����ϸ��ѯ','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944323','����������ϸ��ѯ','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944324','��ƽ��ϸ��ѯ','041','0','1','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('944325','�����˹������ʽ�㻮','041','0','0','1','1','1','00000','admin','','','','0');
insert into app_jyxx values('701509','���Ľ���״̬��ѯ','041','0','0','1','1','1','00000','admin','','','','0');


INSERT INTO APP_TXAQXX (LJBS, LJMC, LJLX, DWBH, QDKZ, TXMS, TXDZ, TXDK, FSCS, JSCS, LJJGH, LJGYH, LJZDH, KEY1, KEY2, KEY3, FTPDZ, FTPYH, FTPMM, FTPGZFS, FTPCSFS, FTPZDMS, FTPDFLJ, FTPBDLJ, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, TXZT, QDZT) 
VALUES ('pabybh', 'ƽ�����ٺ�', '3', '', '', '1', '10.8.208.173', '50023', 60, 60, '88888', '81108', 'TTYGAPS', 'NODEIN_GAPS2PABYBH', '', '', '', '', '', null, '', null, '', null, '00000', 'admin', '20160225015812', '', '', '0', '');

INSERT INTO PABYBH_SVRINFO 
VALUES ('7558', '0802', 'ƽ�����������', '000000|235959', '0', '', '', '');
INSERT INTO PABYBH_SVRINFO 
VALUES ('7558', '0001', 'ƽ����������', '000000|235959', '0', '', '', '');

INSERT INTO PABYBH_SECKEY (COBANKNO, ENCRYPTIP, ENCRYPTPORT, ENCRYPTSYSID, ENCRYPTEXTID, ZMK, ZAK, IEPZPK, COUNTERZPK, HOSTZPK, EXTFLD1, EXTFLD2, EXTFLD3, EXTFLD4) 
VALUES ('7558', '', '', '', '', '', '100021.PAB001000.zak', '100021.PAB001000.zpk', '', '', null, null, null, null);


INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900015', 'ǩ��/ǩ��', '0001', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900007', '�ʽ�ת', '0001', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900023', '�ʽ����', '0001', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900017', '����֪ͨ', '0001', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900029', '����״̬��ѯ', '0001', '0', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908001', 'Ԥָ��ȷ��', '0802', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908003', 'ǩԼ�˻����', '0802', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908004', '��ת֤', '0802', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908005', '֤ת��', '0802', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908006', '��ѯ�ͻ�֤ȯ�ʽ����', '0802', '0', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900026', '�����ύ֪ͨ', '0001', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908020', '��ѯ���ǩԼ��Ϣ', '0802', '0', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908022', '���Ԥָ��ȷ�ϳ���', '0802', '0', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('900013', '��ѯ�ͻ������˻����', '0001', '0', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908026', 'һ��ʽǩԼ', '0802', '1', null, null, null);
INSERT INTO PABYBH_PABTRANSCTL (TRANSCODE, TRANSNAME, SVRCODE, MACFLAG, EXTFLD1, EXTFLD2, EXTFLD3) VALUES ('908008', '��ѯ������ϸ', '0802', '0', null, null, null);

INSERT INTO PABYBH_ORGCFG (COBANKNO, COBANKNAME, CUSTMANAGERNO, ACCT, ACCTNAME, ACCT1, ACCT1NAME, ACCT2, ACCT2NAME, ACCT3, ACCT3NAME, ACCT4, ACCT4NAME, SIGNSTATUS, AREACODE, COORGNO, WORKDATE, WORKSERIALNO, MAINTAINDATE, MAINTAINTIME, EXTFLD1, EXTFLD2, EXTFLD3, EXTFLD4, EXTFLD5, EXTFLD6) 
VALUES ('7558', null, null, null, null, '000010126220011057', '������ƴ����ʽ�ר��', '000010113920010006', '���������������ι�˾', null, null, null, null, '1', null, null, '20170828', null, null, null, null, null, null, null, null, null);

--����ֻ���
INSERT INTO APP_MSGNOTICEPEOPLE (PROCODE, BUSNO, PHONE, PEOPLENAME, MSGNOTICETYPE, OPENFLAG, OPERATETIME, OPERATEBRC, OPERATETEL, BUSTYPE, REMARK1, REMARK2, REMARK3, REMARK4, REMARK5) 
VALUES ('0030015', '003001510000', '1331666112', 'xx', '01', '0', '20170503171333', '00000       ', 'admin       ', '00', '          ', '                    ', '                                                  ', '                                                                                                    ', '                                                                                                                                                                                                        ');


--��ʼ����¼��Ŀ��Ϣ
INSERT INTO PABYBH_COURSE_INFO (ID, COURSE_CODE, COURSE_NAME, COURSE_ACCOUNT, COURSE_DESC) VALUES ('3', '1124_TRANSIT', '�������׼����', '000010111241112223', '����ת�����㻧');
INSERT INTO PABYBH_COURSE_INFO (ID, COURSE_CODE, COURSE_NAME, COURSE_ACCOUNT, COURSE_DESC) VALUES ('4', '2323_TRANSIT', '�ϴ�����ʡϽ��֤��', '999990123231111129', '����ת�˽��㻧');
INSERT INTO PABYBH_COURSE_INFO (ID, COURSE_CODE, COURSE_NAME, COURSE_ACCOUNT, COURSE_DESC) VALUES ('5', '1123_CLEAR', '������й��ݷ���', '999990111230011182', 'AA');
INSERT INTO PABYBH_COURSE_INFO (ID, COURSE_CODE, COURSE_NAME, COURSE_ACCOUNT, COURSE_DESC) VALUES ('1', '2622_TRANSIT', 'ί�м�����ծҵ��-����ת��', '000010126220011057', '������ƴ����ʽ�ר��');
INSERT INTO PABYBH_COURSE_INFO (ID, COURSE_CODE, COURSE_NAME, COURSE_ACCOUNT, COURSE_DESC) VALUES ('2', '1392_TRANSIT', 'ί�м������ʲ�ҵ�񡪡�', '000010113920010006', '���������������ι�˾');


commit;