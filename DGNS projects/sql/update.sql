update t_dict set DICT_INFO='��ʱδ֧��' where DICT_KIND='yxt_state' and DICT_KEY='18';

delete ywty_tokeninfo where LJBS in('hyzftel','hyzfcard');
insert into ywty_tokeninfo(LJBS,TOKENID,DIGEST,LJBSNAME,REMARK1) values('hyzftel','test01','22149','����֧�����ѳ�ֵ','21950');
insert into ywty_tokeninfo(LJBS,TOKENID,DIGEST,LJBSNAME,REMARK1) values('hyzfcard','test01','22144','����֧�����ܳ�ֵ','21952');
