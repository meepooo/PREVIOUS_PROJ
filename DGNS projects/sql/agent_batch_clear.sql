drop table agent_batch_clear;
--==============================================================
-- Table: AGENT_BATCH_CLEAR
--==============================================================
create table AGENT_BATCH_CLEAR
(
   qsrq                 CHAR(8)             not null,
   qssj                 CHAR(6),
   qsls                 VARCHAR(16)         not null,
   qsbs                 INTEGER,
   qsje                 DECIMAL(16,2),
   qslx                 CHAR(1)             not null,
   qsfx                 CHAR(1)             not null,
   qszt                 CHAR(1),
   sbyy                 VARCHAR(200),
   cpdm                 VARCHAR(16),
   cpmc                 VARCHAR(100),
   dwbh                 VARCHAR(16),
   dwmc                 VARCHAR(100),
   pkrq                 CHAR(8)             not null,
   ptpch                CHAR(8)             not null,
   batch_no             VARCHAR(32)         not null,
   file_name            VARCHAR(128),
   tot_succ_cnt         INTEGER,
   tot_succ_amt         DECIMAL(16,2),
   fkhhh                VARCHAR(32),
   fkrmc                VARCHAR(200),
   fkrzh                VARCHAR(32),
   skhhh                VARCHAR(32),
   skrmc                VARCHAR(200),
   skrzh                VARCHAR(32),
   ywbh                 VARCHAR(16)         not null,
   dzrq                 CHAR(8)             not null,
   kzzd1                VARCHAR(80),
   kzzd2                VARCHAR(80),
   kzzd3                VARCHAR(80),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_BATCH_CLEAR primary key (qsrq, qsls)
);

CREATE INDEX AGENT_BATCH_CLEAR_IDX1 ON AGENT_BATCH_CLEAR(ywbh,dzrq,batch_no);
CREATE INDEX AGENT_BATCH_CLEAR_IDX2 ON AGENT_BATCH_CLEAR(dzrq,qslx,qsfx);

comment on table AGENT_BATCH_CLEAR is
'�������մ���������ˮ��';

comment on column agent_batch_clear.qsrq is
'�������� YYYYMMDD';    
   
comment on column agent_batch_clear.qssj is
'����ʱ�� HHMMSS';      
   
comment on column agent_batch_clear.qsls is
'������ˮ';             
   
comment on column agent_batch_clear.qsbs is
'�������';             
   
comment on column agent_batch_clear.qsje is
'������';

comment on column agent_batch_clear.qslx is
'�������� 1-�ʽ����� 2-���������� 3-���������˻�';

comment on column agent_batch_clear.qsfx is
'���㷽�� 1-ҵ���� 2-����1 3-����2 4-����3 5-����4 6-����5';

comment on column agent_batch_clear.qszt is
'����״̬ 9-��ʼ 1-�ɹ� 2-ʧ�� 3-��ʱ';

comment on column agent_batch_clear.sbyy is
'ʧ��ԭ��';

comment on column agent_batch_clear.cpdm is
'��Ʒ����';

comment on column agent_batch_clear.cpmc is
'��Ʒ����';

comment on column agent_batch_clear.dwbh is
'��λ���';

comment on column agent_batch_clear.dwmc is
'��λ����';

comment on column agent_batch_clear.pkrq is
'��������';

comment on column agent_batch_clear.ptpch is
'ƽ̨���κ�';

comment on column agent_batch_clear.batch_no is
'�̻����κ�';

comment on column agent_batch_clear.file_name is
'�����ļ���';

comment on column agent_batch_clear.tot_succ_cnt is
'�ɹ��ܱ���';

comment on column agent_batch_clear.tot_succ_amt is
'�ɹ��ܽ��';

comment on column agent_batch_clear.fkhhh is
'�������к�';

comment on column agent_batch_clear.fkrmc is
'����������';

comment on column agent_batch_clear.fkrzh is
'�������˺�';

comment on column agent_batch_clear.skhhh is
'�տ����к�';

comment on column agent_batch_clear.skrmc is
'�տ�������';

comment on column agent_batch_clear.skrzh is
'�տ����˺�';

comment on column agent_batch_clear.ywbh is
'ҵ����';

comment on column agent_batch_clear.dzrq is
'�������� YYYYMMDD';

comment on column agent_batch_clear.kzzd1 is
'��չ�ֶ�1';

comment on column agent_batch_clear.kzzd2 is
'��չ�ֶ�2';

comment on column agent_batch_clear.kzzd3 is
'��չ�ֶ�3';

comment on column agent_batch_clear.kzzd4 is
'��չ�ֶ�4';

comment on column agent_batch_clear.kzzd5 is
'��չ�ֶ�5';
