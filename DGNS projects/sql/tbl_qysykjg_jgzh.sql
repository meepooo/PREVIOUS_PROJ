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
	comment on table tbl_qysykjg_jgzh is '预售资金监管_监管账户表';
	comment on column tbl_qysykjg_jgzh.bookdate is '登记日期';
	comment on column tbl_qysykjg_jgzh.Booktime is '登记时间';
	comment on column tbl_qysykjg_jgzh.CorpID is '开发企业ID';
	comment on column tbl_qysykjg_jgzh.CorpName is '开发企业名称';
	comment on column tbl_qysykjg_jgzh.ItemID is '预售项目ID';
	comment on column tbl_qysykjg_jgzh.ItemName is '预售项目名称';
	comment on column tbl_qysykjg_jgzh.AccountType is '账户类型';
	comment on column tbl_qysykjg_jgzh.BankName is '监管银行名称';
	comment on column tbl_qysykjg_jgzh.AccountName is '监管账户名称';
	comment on column tbl_qysykjg_jgzh.Account is '监管账号';
	comment on column tbl_qysykjg_jgzh.Status is '监管状态';
	comment on column tbl_qysykjg_jgzh.Orgid is '账务所属机构';
	comment on column tbl_qysykjg_jgzh.Updatedate is '更新日期';
	comment on column tbl_qysykjg_jgzh.Updatetime is '更新时间';
	comment on column tbl_qysykjg_jgzh.reportid is '报文流水id';
	comment on column tbl_qysykjg_jgzh.remark1 is '备用1';
	comment on column tbl_qysykjg_jgzh.remark2 is '备用2';
	comment on column tbl_qysykjg_jgzh.remark3 is '备用3';
