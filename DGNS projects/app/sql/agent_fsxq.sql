drop table agent_fsxq;

create table agent_fsxq
(
PCH        varchar2(32),
XH         INT,
ZXRTDBH    STRING(50),
ZXJGMC     STRING(300),
TZSHM      STRING(50),
KHMC       STRING(150),
YSJE       DOUBLE(20,2),
ZZNJ       DOUBLE(20,2),
FYNFS      INT,
ZH         STRING(50),
SKRMC      STRING(150),
BZ         STRING(300),
FYNF       STRING(4),
FY         DOUBLE(20,2),
BJ         DOUBLE(20,2),
ZNJ        DOUBLE(20,2),
ZNJTS      INT,
SJH        varchar2(16),
JFRQ       varchar2(8),
REMARK1    Varchar(200),
REMARK2    Varchar(200),
REMARK3    Varchar(200),
REMARK4    Varchar(200),
REMARK5    Varchar(200)
);

comment on table  agent_faxq  is '��˰�����' ;
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
comment on column agent_fsxq.REMARK1 is '�����ֶ�1';
comment on column agent_fsxq.REMARK2 is '�����ֶ�2';
comment on column agent_fsxq.REMARK3 is '�����ֶ�3';
comment on column agent_fsxq.REMARK4 is '�����ֶ�4';
comment on column agent_fsxq.REMARK5 is '�����ֶ�5';
