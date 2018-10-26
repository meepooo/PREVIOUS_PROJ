drop table ywty_plhz;
create table ywty_plhz
(
	stat varchar(1),
	pcbh varchar(32) not null,
	cpdm varchar(20),
	xybh varchar(20),
	sffg varchar(1),
	jyly varchar(4),
	jym varchar(6),
	jyrq varchar(8),
	jyxh varchar(32),
	jysj varchar(6),
	dwkhh varchar(20),
	dwmc varchar(100),
	lrjg varchar(12),
	lrgy varchar(10),
	lrrq varchar(8),
	fhgy varchar(10),
	fhrq varchar(9),
	qrgy varchar(10),
	qrrq varchar(8),
	scgy varchar(10),
	scrq varchar(8),
	dwzh varchar(35),
	dwnbzh varchar(35),
	hbdm varchar(3),
	zzbh varchar(38),
	yjzbs int,
	yjzje decimal(15,2),
	sxfbj varchar(1),
	yssxfje decimal(15,2),
	rzrq varchar(8),
	sjzbs int,
	sjzje decimal(15,2),
	sssxfje decimal(15,2),
	certno varchar(20),
	xmbm varchar(20),
	ywj varchar(60),
	jgwj varchar(60),
	zym varchar(5),
	zynr varchar(60),
	kkrq varchar(8),
	kkls varchar(32),
	tkrq varchar(8),
	tkls varchar(11),
	md5 varchar(32),
	by1 varchar(40),
	by2 varchar(40),
	by3 varchar(40),
	by4 varchar(40),
	by5 varchar(255),
	by6 varchar(255),
	constraint P_K_YWTY_PLHZ_1 primary key (PCBH)
);

comment on table  ywty_plhz  is 'ywty_plhz' ;
comment on column ywty_plhz.STAT is '״̬' ;
comment on column ywty_plhz.PCBH is '���α��' ;
comment on column ywty_plhz.CPDM is '��Ʒ����' ;
comment on column ywty_plhz.XYBH is 'Э����' ;
comment on column ywty_plhz.SFFG is '�ո����' ;
comment on column ywty_plhz.JYLY is '������Դ' ;
comment on column ywty_plhz.JYM is '������' ;
comment on column ywty_plhz.JYRQ is '��������' ;
comment on column ywty_plhz.JYXH is '�������' ;
comment on column ywty_plhz.JYSJ is '����ʱ��' ;
comment on column ywty_plhz.DWKHH is '��λ�ͻ���' ;
comment on column ywty_plhz.DWMC is '��λ����' ;
comment on column ywty_plhz.LRJG is '¼�����' ;
comment on column ywty_plhz.LRGY is '¼���Ա' ;
comment on column ywty_plhz.LRRQ is '¼������' ;
comment on column ywty_plhz.FHGY is '���˹�Ա' ;
comment on column ywty_plhz.FHRQ is '��������' ;
comment on column ywty_plhz.QRGY is 'ȷ�Ϲ�Ա' ;
comment on column ywty_plhz.QRRQ is 'ȷ������' ;
comment on column ywty_plhz.SCGY is 'ɾ����Ա' ;
comment on column ywty_plhz.SCRQ is 'ɾ������' ;
comment on column ywty_plhz.DWZH is '��λ�˺�' ;
comment on column ywty_plhz.DWNBZH is '��λ�ڲ��˺�' ;
comment on column ywty_plhz.HBDM is '���Ҵ���' ;
comment on column ywty_plhz.ZZBH is '���˲���' ;
comment on column ywty_plhz.YJZBS is 'Ӧ���ܱ���' ;
comment on column ywty_plhz.YJZJE is 'Ӧ���ܽ��' ;
comment on column ywty_plhz.SXFBJ is '�����ѱ��' ;
comment on column ywty_plhz.YSSXFJE is 'Ӧ���������ܽ��' ;
comment on column ywty_plhz.RZRQ is '��������' ;
comment on column ywty_plhz.SJZBS is 'ʵ���ܱ���' ;
comment on column ywty_plhz.SJZJE is 'ʵ���ܽ��' ;
comment on column ywty_plhz.SSSXFJE is 'ʵ���������ܽ��' ;
comment on column ywty_plhz.CERTNO is 'ƾ֤��' ;
comment on column ywty_plhz.XMBM is '��Ŀ���' ;
comment on column ywty_plhz.YWJ is 'Դ�ļ�' ;
comment on column ywty_plhz.JGWJ is '����ļ�' ;
comment on column ywty_plhz.ZYM is 'ժҪ����' ;
comment on column ywty_plhz.ZYNR is 'ժҪ' ;
comment on column ywty_plhz.KKRQ is '�ۿ�����' ;
comment on column ywty_plhz.KKLS is '�ۿ���ˮ' ;
comment on column ywty_plhz.TKRQ is '�˿�����' ;
comment on column ywty_plhz.TKLS is '�˿���ˮ' ;
comment on column ywty_plhz.MD5 is 'MD5У��' ;
comment on column ywty_plhz.BY1 is '�����ֶ�1' ;
comment on column ywty_plhz.BY2 is '�����ֶ�2' ;
comment on column ywty_plhz.BY3 is '�����ֶ�3' ;
comment on column ywty_plhz.BY4 is '�����ֶ�4' ;
comment on column ywty_plhz.BY5 is '�����ֶ�5' ;
comment on column ywty_plhz.BY6 is '�����ֶ�6' ;
