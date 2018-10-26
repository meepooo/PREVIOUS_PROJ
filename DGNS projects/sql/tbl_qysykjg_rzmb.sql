drop table tbl_qysykjg_rzmb;
create table tbl_qysykjg_rzmb (
		 rzm varchar(50),
		  Buildtime varchar(50),
		   remark1 varchar(50),
		    remark2 varchar(50),
			 remark3 varchar(50),
			  remark4 varchar(50),
			   remark5 varchar(50)
		);
	comment on table tbl_qysykjg_rzmb is '预售资金监管_认证码表';
	comment on column tbl_qysykjg_rzmb.rzm is '认证码';
	comment on column tbl_qysykjg_rzmb.Buildtime is '生成时间';
	comment on column tbl_qysykjg_rzmb.remark1 is '备用1';
	comment on column tbl_qysykjg_rzmb.remark2 is '备用2';
	comment on column tbl_qysykjg_rzmb.remark3 is '备用3';
	comment on column tbl_qysykjg_rzmb.remark4 is '备用4';
	comment on column tbl_qysykjg_rzmb.remark5 is '备用5';
