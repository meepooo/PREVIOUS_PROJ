drop table yw_task_ctrl;
--==============================================================
-- Table:  yw_task_ctrl 
--==============================================================
create table  yw_task_ctrl 
(
    rwrq           CHAR(8)               not null,
    rwsj           CHAR(6)               not null,
    cpdm           VARCHAR(32)           not null,
    rwdm           VARCHAR(32)           not null,
    qtzd           VARCHAR(32)           not null,
    qzlsh          VARCHAR(8)            not null,
    rwzt           CHAR(1)               not null,
    ptxym          VARCHAR(16),
    ptxyxx         VARCHAR(32),
    by1            VARCHAR(16),
   constraint  pk_yw_task_ctrl  primary key ( rwrq,rwsj,cpdm,rwdm,qtzd )
);

comment on table yw_task_ctrl is
'������Ʊ�';

comment on column yw_task_ctrl.rwrq is
'��������';

comment on column yw_task_ctrl.rwsj is
'����ʱ��';

comment on column yw_task_ctrl.cpdm is
'��Ʒ����';

comment on column yw_task_ctrl.rwdm is
'�������';

comment on column yw_task_ctrl.qtzd is
'�����ֶ�,������ͬһ���̲���ʱ���������ֲ�ͬҵ��������ֶ�';

comment on column yw_task_ctrl.qzlsh is
'ǰ����ˮ��';

comment on column yw_task_ctrl.rwzt is
'����״̬��0-�ɹ���1-ʧ�ܣ�9-������';

comment on column yw_task_ctrl.ptxym is
'ƽ̨��Ӧ��';

comment on column yw_task_ctrl.ptxyxx is
'ƽ̨��Ӧ��Ϣ';

comment on column yw_task_ctrl.by1 is
'����1';
