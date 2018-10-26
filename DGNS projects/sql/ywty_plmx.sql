drop table ywty_plmx;
create table ywty_plmx
(
	pcbh varchar(32) not null,
	pcnbxh int not null,
	ywls varchar(32),
	ptls varchar(32),
	jyls varchar(32),
	yxj varchar(1),
	ywlx varchar(8),
	ywzl varchar(6),
	yhbj varchar(1),
	hkyl varchar(1),
	tcydbj varchar(1),
	jjbj varchar(1),
	htbh varchar(32),
	qxrq varchar(8),
	khyhzh varchar(32),
	khyhzhmc varchar(70),
	zhkhh varchar(14),
	zhkhhmc varchar(100),
	yjjyje decimal(15,2),
	sxfbj varchar(1),
	sxfzh varchar(32),
	sxfje decimal(15,2),
	sjjyje decimal(15,2),
	sjsxfje decimal(15,2),
	zym varchar(5),
	lrgy varchar(10),
	lrrq varchar(8),
	ptrq varchar(8),
	ptsj varchar(6),
	whrq varchar(8),
	whgy varchar(10),
	fy varchar(62),
	bz varchar(62),
	zjlx varchar(2),
	zjhm varchar(20),
	zjyxrq varchar(10),
	sex varchar(1),
	csrq varchar(10),
	address varchar(70),
	fzjg varchar(22),
	yzbm varchar(7),
	phoneno varchar(15),
	yybj varchar(1),
	yyrq varchar(8),
	yysj varchar(6),
	dsfrq varchar(8),
	dsfls varchar(11),
	dsfjylx varchar(20),
	dsfjym varchar(20),
	dsfxym varchar(12),
	dsfxyxx varchar(150),
	dsfjyzt varchar(1),
	dsfdzbj varchar(1),
	zjjzgy varchar(10),
	zjjzrq varchar(8),
	zjjzls varchar(32),
	zjgyls varchar(32),
	khzfls varchar(32),
	zjxym varchar(12),
	zjxyxx varchar(150),
	zjjyzt varchar(1),
	zjdzbj varchar(1),
	czgy varchar(10),
	czrq varchar(8),
	czls varchar(11),
	fscs int,
	jyxym varchar(12),
	jyxyxx varchar(150),
	jyzt varchar(1),
	by1 varchar(40),
	by2 varchar(40),
	by3 varchar(40),
	by4 varchar(40),
	by5 varchar(255),
	by6 varchar(255),
	constraint P_K_YWTY_PLMX_1 primary key (PCBH, PCNBXH)
);

comment on table  ywty_plmx  is 'ywty_plmx' ;
comment on column ywty_plmx.PCBH is '���α��' ;
comment on column ywty_plmx.PCNBXH is '�����ڲ����' ;
comment on column ywty_plmx.YWLS is 'ҵ����ˮ��' ;
comment on column ywty_plmx.PTLS is 'ƽ̨��ˮ��' ;
comment on column ywty_plmx.JYLS is '������ˮ' ;
comment on column ywty_plmx.YXJ is '���ȼ�' ;
comment on column ywty_plmx.YWLX is 'ҵ������' ;
comment on column ywty_plmx.YWZL is 'ҵ������' ;
comment on column ywty_plmx.YHBJ is '���б��' ;
comment on column ywty_plmx.HKYL is '�����·' ;
comment on column ywty_plmx.TCYDBJ is 'ͬ����ر��' ;
comment on column ywty_plmx.JJBJ is '�Ӽ����' ;
comment on column ywty_plmx.HTBH is '��ͬ���' ;
comment on column ywty_plmx.QXRQ is '��������' ;
comment on column ywty_plmx.KHYHZH is '�ͻ������˺�' ;
comment on column ywty_plmx.KHYHZHMC is '�ͻ������˺Ż���' ;
comment on column ywty_plmx.ZHKHH is '�ͻ������˺ſ����к�' ;
comment on column ywty_plmx.ZHKHHMC is '�ͻ������˺ſ���������' ;
comment on column ywty_plmx.YJJYJE is 'Ӧ�ǽ��׽��' ;
comment on column ywty_plmx.SXFBJ is '�����ѱ��' ;
comment on column ywty_plmx.SXFZH is '�������˺�' ;
comment on column ywty_plmx.SXFJE is '�����ѽ��' ;
comment on column ywty_plmx.SJJYJE is 'ʵ�ǽ��׽��' ;
comment on column ywty_plmx.SJSXFJE is 'ʵ�������ѽ��' ;
comment on column ywty_plmx.ZYM is 'ժҪ����' ;
comment on column ywty_plmx.LRGY is '¼���Ա' ;
comment on column ywty_plmx.LRRQ is '¼������' ;
comment on column ywty_plmx.PTRQ is 'ƽ̨����' ;
comment on column ywty_plmx.PTSJ is 'ƽ̨ʱ��' ;
comment on column ywty_plmx.WHRQ is 'ά������' ;
comment on column ywty_plmx.WHGY is 'ά����Ա' ;
comment on column ywty_plmx.FY is '����' ;
comment on column ywty_plmx.BZ is '��ע' ;
comment on column ywty_plmx.ZJLX is '֤������' ;
comment on column ywty_plmx.ZJHM is '֤������' ;
comment on column ywty_plmx.ZJYXRQ is '��Ч����' ;
comment on column ywty_plmx.SEX is '�Ա�' ;
comment on column ywty_plmx.CSRQ is '��������' ;
comment on column ywty_plmx.ADDRESS is '��ַ' ;
comment on column ywty_plmx.FZJG is '��֤����' ;
comment on column ywty_plmx.YZBM is '��������' ;
comment on column ywty_plmx.PHONENO is '�绰����' ;
comment on column ywty_plmx.YYBJ is 'ԤԼ���' ;
comment on column ywty_plmx.YYRQ is 'ԤԼ����' ;
comment on column ywty_plmx.YYSJ is 'ԤԼʱ��' ;
comment on column ywty_plmx.DSFRQ is '����������' ;
comment on column ywty_plmx.DSFLS is '��������ˮ��' ;
comment on column ywty_plmx.DSFJYLX is '��������������' ;
comment on column ywty_plmx.DSFJYM is '���������״���' ;
comment on column ywty_plmx.DSFXYM is '��������Ӧ��' ;
comment on column ywty_plmx.DSFXYXX is '��������Ӧ��Ϣ' ;
comment on column ywty_plmx.DSFJYZT is '����������״̬' ;
comment on column ywty_plmx.DSFDZBJ is '���������˱�־' ;
comment on column ywty_plmx.ZJJZGY is '�������˹�Ա' ;
comment on column ywty_plmx.ZJJZRQ is '������������' ;
comment on column ywty_plmx.ZJJZLS is '����������ˮ' ;
comment on column ywty_plmx.ZJGYLS is '������Ա��ˮ' ;
comment on column ywty_plmx.KHZFLS is '����֧����ˮ' ;
comment on column ywty_plmx.ZJXYM is '������Ӧ��' ;
comment on column ywty_plmx.ZJXYXX is '������Ӧ��Ϣ' ;
comment on column ywty_plmx.ZJJYZT is '����������״̬' ;
comment on column ywty_plmx.ZJDZBJ is '�������˱�־' ;
comment on column ywty_plmx.CZGY is '������Ա' ;
comment on column ywty_plmx.CZRQ is '��������' ;
comment on column ywty_plmx.CZLS is '������ˮ' ;
comment on column ywty_plmx.FSCS is '���ʹ���' ;
comment on column ywty_plmx.JYXYM is '������Ӧ��' ;
comment on column ywty_plmx.JYXYXX is '������Ӧ��Ϣ' ;
comment on column ywty_plmx.JYZT is '����״̬' ;
comment on column ywty_plmx.BY1 is '����1' ;
comment on column ywty_plmx.BY2 is '����2' ;
comment on column ywty_plmx.BY3 is '����3' ;
comment on column ywty_plmx.BY4 is '����4' ;
comment on column ywty_plmx.BY5 is '����5' ;
comment on column ywty_plmx.BY6 is '����6' ;
