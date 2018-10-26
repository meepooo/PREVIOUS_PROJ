drop table tbl_qysykjg_jgzh;
create table tbl_qysykjg_jgzh (
		 bookdate varchar(8) NOT  NULL ,
		  Booktime varchar(8),
		   CorpID varchar(32), 
		    CorpName varchar(100),
			 ItemID varchar(32),
			  ItemName varchar(100),
			   AccountType varchar(1),
			    BankName varchar(100),
				 AccountName varchar(100),
				  Account varchar(32),
				   Status varchar(1),
				    Orgid varchar(50),
					 Updatedate varchar(50),
					  Updatetime varchar(50),
					   reportid varchar(20),		
					    remark1 varchar(254),
						 remark2 varchar(254),
						  remark3 varchar(254),
						   constraint tbl_qysykjg_jgzh primary key (bookdate)
		);
	comment on table tbl_qysykjg_jgzh is 'Ԥ���ʽ���_����˻���';
	comment on column tbl_qysykjg_jgzh.bookdate is '�Ǽ�����';
	comment on column tbl_qysykjg_jgzh.Booktime is '�Ǽ�ʱ��';
	comment on column tbl_qysykjg_jgzh.CorpID is '������ҵID';
	comment on column tbl_qysykjg_jgzh.CorpName is '������ҵ����';
	comment on column tbl_qysykjg_jgzh.ItemID is 'Ԥ����ĿID';
	comment on column tbl_qysykjg_jgzh.ItemName is 'Ԥ����Ŀ����';
	comment on column tbl_qysykjg_jgzh.AccountType is '�˻�����';
	comment on column tbl_qysykjg_jgzh.BankName is '�����������';
	comment on column tbl_qysykjg_jgzh.AccountName is '����˻�����';
	comment on column tbl_qysykjg_jgzh.Account is '����˺�';
	comment on column tbl_qysykjg_jgzh.Status is '���״̬';
	comment on column tbl_qysykjg_jgzh.Orgid is '������������';
	comment on column tbl_qysykjg_jgzh.Updatedate is '��������';
	comment on column tbl_qysykjg_jgzh.Updatetime is '����ʱ��';
	comment on column tbl_qysykjg_jgzh.reportid is '������ˮid';
	comment on column tbl_qysykjg_jgzh.remark1 is '����1';
	comment on column tbl_qysykjg_jgzh.remark2 is '����2';
	comment on column tbl_qysykjg_jgzh.remark3 is '����3';
