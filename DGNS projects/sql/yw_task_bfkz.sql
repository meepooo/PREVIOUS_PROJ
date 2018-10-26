drop table yw_task_bfkz;
--==============================================================
-- Table:  yw_task_bfkz 
--==============================================================
create table  yw_task_bfkz 
(
    cpdm           VARCHAR(32)           not null,
    rwdm           VARCHAR(32)           not null,
    qtzd           VARCHAR(32)           not null,
    bfbz           CHAR(1),
    bfjg           VARCHAR(5),
    by1            VARCHAR(16),
   constraint  pk_yw_task_bfkz  primary key ( cpdm,rwdm,qtzd )
);

comment on table yw_task_bfkz is
'���񲢷����Ʊ�';

comment on column yw_task_bfkz.cpdm is
'��Ʒ����';

comment on column yw_task_bfkz.rwdm is
'�������';

comment on column yw_task_bfkz.qtzd is
'�����ֶ�,������ͬһ���̲���ʱ���������ֲ�ͬҵ��������ֶ�';

comment on column yw_task_bfkz.bfbz is
'������־��0-����������1-������';

comment on column yw_task_bfkz.bfjg is
'����ʱ�����������ֶ�';

comment on column yw_task_bfkz.by1 is
'����1';
