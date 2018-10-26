
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
comment on table agent_fsxq is '��˰�����';
comment on column agent_fsxq.PCH is '���κ�';    
comment on column agent_fsxq.XH is '���';  
comment on column agent_fsxq.ZXRTDBH is 'ִ�����Ŷӱ��'; 
comment on column agent_fsxq.ZXJGMC is 'ִ�л�������'; 
comment on column agent_fsxq.TZSHM is '֪ͨ�����'; 
comment on column agent_fsxq.KHMC is '�ͻ�����'; 
comment on column agent_fsxq.YSJE is 'Ӧ�ս��'; 
comment on column agent_fsxq.ZZNJ is '�����ɽ�'; 
comment on column agent_fsxq.FYNFS is '���������'; 
comment on column agent_fsxq.ZH is '�˺�'; 
comment on column agent_fsxq.SKRMC is '�տ�������'; 
comment on column agent_fsxq.BZ is '��ע'; 
comment on column agent_fsxq.FYNF is '�������'; 
comment on column agent_fsxq.FY is '����'; 
comment on column agent_fsxq.BJ is '����'; 
comment on column agent_fsxq.ZNJ is '���ɽ�'; 
comment on column agent_fsxq.ZNJTS is '���ɽ�����'; 
comment on column agent_fsxq.SJH is '�ֻ���'; 
comment on column agent_fsxq.JFRQ is '�ɷ�����'; 
comment on column agent_fsxq.remark1 is '�����ֶ�1'; 
comment on column agent_fsxq.remark2 is '�����ֶ�2'; 
comment on column agent_fsxq.remark3 is '�����ֶ�3';
comment on column agent_fsxq.remark4 is '�����ֶ�4';
comment on column agent_fsxq.remark5 is '�����ֶ�5';
                                                               
