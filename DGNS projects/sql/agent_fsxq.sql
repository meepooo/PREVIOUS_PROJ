
drop table agent_fsxq;
create table agent_fsxq
(
	pch        VARCHAR(32),
	xh         INTEGER,     
	zxrtdbh    VARCHAR(50),  
	zxjgmc     VARCHAR(300), 
	tzshm      VARCHAR(50),  
	khmc       VARCHAR(150), 
	ysje       DECIMAL(20,2),
	zznj       DECIMAL(20,2),
	fynfs      INTEGER, 
	zh         VARCHAR(50),  
	skrmc      VARCHAR(150), 
	bz         VARCHAR(300), 
	fynf       VARCHAR(4),       
	fy         DECIMAL(20,2),    
	bj         DECIMAL(20,2),    
	znj        DECIMAL(20,2),    
	znjts      INTEGER,     
	sjh        VARCHAR(16),    
	jfrq       VARCHAR(8),     
	remark1    VARCHAR(200),    
	remark2    VARCHAR(200),   
	remark3    VARCHAR(200),    
	remark4    VARCHAR(200),   
	remark5    VARCHAR(200)    
);
comment on table agent_fsxq is '非税详情表';
comment on column agent_fsxq.PCH is '批次号';    
comment on column agent_fsxq.XH is '序号';  
comment on column agent_fsxq.ZXRTDBH is '执行人团队编号'; 
comment on column agent_fsxq.ZXJGMC is '执行机构名称'; 
comment on column agent_fsxq.TZSHM is '通知书号码'; 
comment on column agent_fsxq.KHMC is '客户名称'; 
comment on column agent_fsxq.YSJE is '应收金额'; 
comment on column agent_fsxq.ZZNJ is '总滞纳金'; 
comment on column agent_fsxq.FYNFS is '费用年份数'; 
comment on column agent_fsxq.ZH is '账号'; 
comment on column agent_fsxq.SKRMC is '收款人名称'; 
comment on column agent_fsxq.BZ is '备注'; 
comment on column agent_fsxq.FYNF is '费用年份'; 
comment on column agent_fsxq.FY is '费用'; 
comment on column agent_fsxq.BJ is '本金'; 
comment on column agent_fsxq.ZNJ is '滞纳金'; 
comment on column agent_fsxq.ZNJTS is '滞纳金天数'; 
comment on column agent_fsxq.SJH is '手机号'; 
comment on column agent_fsxq.JFRQ is '缴费日期'; 
comment on column agent_fsxq.remark1 is '备用字段1'; 
comment on column agent_fsxq.remark2 is '备用字段2'; 
comment on column agent_fsxq.remark3 is '备用字段3';
comment on column agent_fsxq.remark4 is '备用字段4';
comment on column agent_fsxq.remark5 is '备用字段5';
                                                               
